#fndef VECTOR_ARITHMETIC_H
#define VECTOR_ARITHMETIC_H

#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

template<typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T>& v);

template<typename T>
std::vector<T> operator+(std::vector<T> v1,std::vector<T> v2);

template<typename T>
std::vector<T> operator*(std::vector<T> v1,std::vector<T> v2);

template<typename T>
std::vector<T> operator-(std::vector<T> v1,std::vector<T> v2);

template<typename T>
std::vector<T> operator/(std::vector<T> v1,std::vector<T> v2);

template<typename T>
std::vector<T> operator+(std::vector<T> v, double x);

template<typename T>
std::vector<T> operator-(std::vector<T> v, double x);

template<typename T>
std::vector<T> operator*(double x, std::vector<T> v);

template<typename T>
std::vector<T> operator*(std::vector<T> v, double x);

template<typename T>
std::vector<T> operator/(std::vector<T> v, double x);

template<typename T>
std::vector<T> pow(std::vector<T> v, double k);


template<typename T>
std::ostream& operator<<(std::ostream& s, const std::vector<T>& v) {
  for (const auto& e : v) {
      s << e << ' ';
  }
  return s << '\n';
}

template<typename T>
std::vector<T> operator+(std::vector<T> v1,std::vector<T> v2){
  unsigned int dim = v1.size();
  std::vector<T> sum;
  for(unsigned int i = 0; i < dim; ++i){
    auto componet = v1[i]+v2[i];
    sum.push_back(componet);
  }
  return sum;
}

template<typename T>
std::vector<T> operator*(std::vector<T> v1,std::vector<T> v2){
  unsigned int dim = v1.size();
  std::vector<T> prod;
  for(unsigned int i = 0; i < dim; ++i){
    auto componet = v1[i]*v2[i];
    prod.push_back(componet);
  }
  return prod;
}

template<typename T>
std::vector<T> operator-(std::vector<T> v1,std::vector<T> v2){
  unsigned int dim = v1.size();
  std::vector<T> diff;
  for(unsigned int i = 0; i < dim; ++i){
    auto componet = v1[i]-v2[i];
    diff.push_back(componet);
  }
  return diff;
}

template<typename T>
std::vector<T> operator/(std::vector<T> v1,std::vector<T> v2){
  unsigned int dim = v1.size();
  std::vector<T> quot;
  for(unsigned int i = 0; i < dim; ++i)
    quot.push_back(v1[i]/v2[i]);
  return quot;
}

template<typename T>
std::vector<T> operator+(std::vector<T> v, double x){
  std::vector<T> sum;
  unsigned int dim = v.size();
  for(unsigned int i = 0; i < dim; ++i){
    auto componet = v[i]+x;
    sum.push_back(componet);
  }
  return sum;
}

template<typename T>
std::vector<T> operator-(std::vector<T> v, double x){
  std::vector<T> diff;
  unsigned int dim = v.size();
  for(unsigned int i = 0; i < dim; ++i){
    auto componet = v[i]-x;
    diff.push_back(componet);
  }
  return diff;
}

template<typename T>
std::vector<T> operator*(double x, std::vector<T> v){
  std::vector<T> prod;
  unsigned int dim = v.size();
  for(unsigned int i = 0; i < dim; ++i){
    auto componet = x*v[i];
    prod.push_back(componet);
  }
  return prod;
}

template<typename T>
std::vector<T> operator*(std::vector<T> v, double x){
    return x*v;
}

template<typename T>
std::vector<T> operator/(std::vector<T> v, double x){
    return (1/x)*v;
}

template<typename T>
std::vector<T> pow(std::vector<T> v, double k){
  std::vector<T> power;
  unsigned int dim = v.size();
  for(unsigned int i = 0; i < dim; ++i){
    auto componet = pow(v[i],k);
    power.push_back(componet);
  }
  return power;
}



#endif
