// Copyright [2017] <Mengxuan Zhu>

#include "./noise.h"

double noise::cubic_func(double x,
        const double param0, const double param1, const double param2,
        const double param3) {
  return param0+param1*x+param2*x*x+param3*x*x*x;
}

std::vector<double> noise::discrete_random_series(int size) {
  // set random number generator
  static std::random_device rd;
  static std::minstd_rand gen(rd());
  static std::uniform_real_distribution<double> randu(0, 1);

  // generate a series of discreted random numbers
  std::vector<double> rdlist(size+1);
  std::generate(rdlist.begin(), rdlist.end(), []{ return randu(gen); });

  return rdlist;
}

/*
   use cubic spline w/ natural BC
   the problem is to solve the equation:

   [[ 1      0                                   ] *[ m_0   = ypp
    [ step 4*step   step                         ]    m_1
    [        step 4*step   step                  ]    m_2
    [               step 4*step step             ]    m_3
    [                      ...   ...   ...       ]    ...
    [                           step 4*step step ]    m_n-1
    [                                  0    1    ]]   m_n  ]

    where
    ypp = 6*[0, ..., y_(i+1) - 2*y_i + y_(i-1), ... , 0]/step
    m is associated with the spline parameters

    use TDMA to solve this euqation
*/

std::vector<std::function<double(double)>> noise::cubic_spline_functions
    (const std::vector<double>& rdlist, const double step) {
  const int size = rdlist.size() - 1;
  // init diag elements
  std::vector<double> diag_main(size+1, 4*step);
  *diag_main.begin() = 1;
  *diag_main.rbegin() = 1;
  std::vector<double> diag_up(size, step);
  *diag_up.begin() = 0;
  std::vector<double> diag_down(size, step);
  *diag_down.rbegin() = 0;

  // init ypp vector
  std::vector<double> ypp(size+1);
  *ypp.begin() = 0;
  int index = {1};
  std::generate(ypp.begin()+1, ypp.end()-1, [&index, &rdlist, &step]{
    std::vector<double>::iterator x;
    double y2d = 6*(rdlist[index+1]-2*rdlist[index]+rdlist[index-1])/step;
    ++index;
    return y2d;
  });
  *ypp.rbegin() = 0;

  // apply TDMA
  std::vector<double> mval(size+1);
  std::vector<double> up_prime(diag_up);
  std::vector<double> y_prime(ypp);
  up_prime[0] = diag_up[0] / diag_main[0];
  y_prime[0] = ypp[0] / diag_main[0];
  for (int i = 1; i < size; ++i) {
    up_prime[i] = diag_up[i] / (diag_main[i]-diag_down[i]*up_prime[i-1]);
    y_prime[i] = (ypp[i]-diag_down[i]*y_prime[i-1])
        / (diag_main[i]-diag_down[i]*up_prime[i-1]);
  }
  y_prime[size] = (ypp[size]-diag_down[size]*y_prime[size-1])
      / (diag_main[size]-diag_down[size]*up_prime[size-1]);

  mval[size] = y_prime[size];
  for (int i = size-1; i >= 0; --i) {
    mval[i] = y_prime[i]-up_prime[i]*y_prime[i+1];
  }

  // calc params of cubic interpolational function
  std::vector<std::function<double(double)>> splines(size);
  index = {0};
  using namespace std::placeholders;
  std::generate(splines.begin(), splines.end(),
          [&step, &index, &mval, &rdlist]{
    double param[4] = {
      rdlist[index],
      (rdlist[index+1]-rdlist[index])/step
        - step*mval[index]/2
        - step*(mval[index+1]-mval[index])/6,
      mval[index]/2,
      (mval[index+1]-mval[index])/(6*step)
    };
    auto cubic = std::bind(noise::cubic_func, _1,
            param[0], param[1], param[2], param[3]);
    ++index;
    return cubic;
  });
  return splines;
}

  // calc values of interpolational points
std::vector<double> noise::coherent_series(
        std::vector<std::function<double(double)>> splines_function,
        int samples, const double step) {
  const int size = splines_function.size();
  std::vector<double> result(size * samples);
  for (int i = 0; i < size*samples; ++i) {
    result[i] = splines_function[static_cast<int>(i/samples)]
        ((i%samples)*step/samples);
  }
  result.push_back(splines_function[size-1](step));

  return result;
}

std::vector<double> noise::coherent_series(int size, int samples) {
  auto rdlist = (noise::discrete_random_series(size));
  return noise::coherent_series(noise::cubic_spline_functions(rdlist), samples);
}

std::vector<std::vector<double>> noise::coherent_map(const int size1,
        const int size2, const int sample1, const int sample2) {
  std::vector<std::vector<double>> semi_coherent_noise_2d(size2+1,
          std::vector<double>(size1*sample1+1));
  // coherent along axis 2, discrete along axis 1
  std::generate(semi_coherent_noise_2d.begin(),
                semi_coherent_noise_2d.end(), [&size1, &sample1]{
    auto randomlist = noise::discrete_random_series(size1);
    auto spline = noise::cubic_spline_functions(randomlist);
    return noise::coherent_series(spline, sample1);
  });

  // transpose the map
  std::vector<std::vector<double>> semi_coherent_noise_2dT(
          size1*sample1+1, std::vector<double>(size2+1));
  for (int i = 0; i < size1*sample1+1; ++i)
    for (int j = 0; j < size2+1; ++j)
        semi_coherent_noise_2dT[i][j] = semi_coherent_noise_2d[j][i];

  // calc spline functions along axis 2
  std::vector<std::vector<double>> coherent_noise_2d;
  for (int i = 0; i < size1*sample1+1; ++i) {
    auto dummy_coherent_noise = noise::coherent_series
        (noise::cubic_spline_functions
         (semi_coherent_noise_2dT[i]), sample2);
    coherent_noise_2d.push_back(dummy_coherent_noise);
  }

  return coherent_noise_2d;
}
