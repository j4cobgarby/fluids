#ifndef VEC_HPP
#define VEC_HPP

#include <cmath>

class vec2f {
public:
  vec2f();
  vec2f(float x, float y);

  float x, y;

  bool operator==(const vec2f rhs);

  vec2f operator+(const vec2f rhs);
  vec2f operator+=(const vec2f rhs);

  vec2f operator-(const vec2f rhs);
  vec2f operator-=(const vec2f rhs); 

  vec2f operator*(const float s);
  vec2f operator*=(const float s);
  
  vec2f operator/(const float s);
  vec2f operator/=(const float s);

  float magnitude();
  float mag_squared();
};

#endif
