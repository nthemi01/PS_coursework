#ifndef VECTOR_MAXMIN_H
#define VECTOR_MAXMIN_H

#include <vector>

template <typename T>
T max(std::vector<T> v);

template <typename T>
T max2d(std::vector<std::vector<T>> v);

template <typename T>
T min(std::vector<T> v);

template <typename T>
T min2d(std::vector<std::vector<T>> v);

template <typename T>
T max(std::vector<T> v){
  T tmpmax = v.front();
  for(auto& e:v)
    if(e>tmpmax)
      tmpmax = e;
  return tmpmax;
}

template <typename T>
T max2d(std::vector<std::vector<T>> v){
  T tmpmax = v.front().front();
  for(auto& e:v){
    T currmax = max(e);
    if(currmax>tmpmax)
      tmpmax = currmax;
  }
  return tmpmax;
}

template <typename T>
T min(std::vector<T> v){
  T tmpmax = v.front();
  for(auto& e:v)
    if(e<tmpmax)
      tmpmax = e;
  return tmpmax;
}

template <typename T>
T min2d(std::vector<std::vector<T>> v){
  T tmpmax = v.front().front();
  for(auto& e:v){
    T currmin = min(e);
    if(currmin<tmpmax)
      tmpmax = currmin;
  }
  return tmpmax;
}




#endif
