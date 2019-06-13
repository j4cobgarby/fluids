#include "vec.hpp"

vec2f::vec2f() : x(0), y(0) {}
vec2f::vec2f(float x, float y) : x(x), y(y) {}

bool vec2f::operator==(const vec2f rhs) {return x == rhs.x && y == rhs.y;}

vec2f vec2f::operator+(const vec2f rhs) {return vec2f(x+rhs.x, y+rhs.y);}
vec2f vec2f::operator+=(const vec2f rhs) {x += rhs.x; y += rhs.y; return *this;}

vec2f vec2f::operator-(const vec2f rhs) {return vec2f(x-rhs.x, y-rhs.y);}
vec2f vec2f::operator-=(const vec2f rhs) {x -= rhs.x; y -= rhs.y; return *this;}

vec2f vec2f::operator*(const float s) {return vec2f(x*s, y*s);}
vec2f vec2f::operator*=(const float s) {x *= s; y *= s; return  *this;}

vec2f vec2f::operator/(const float s) {return vec2f(x/s, y/s);}
vec2f vec2f::operator/=(const float s) {x /= s; y /= s; return  *this;}

float vec2f::magnitude() {return sqrt(x*x + y*y);}
float vec2f::mag_squared() {return x*x + y*y;}
