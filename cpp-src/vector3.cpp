#include <cmath>

#include "vector3.h"

void Vector3::load_from(float * ptr) 
{
    _v3 = _mm_load_ps(ptr);
}

void Vector3::add(__m128 v1, __m128 v2)
{
    _v3 = _mm_add_ps(v1, v2);
}

void Vector3::sub(__m128 v1, __m128 v2)
{
    _v3 = _mm_sub_ps(v1, v2);
}

__m128 Vector3::cross(__m128 v3)
{
    _v3 = cross_vectors(_v3, v3);
}

__m128 Vector3::cross_vectors(__m128 x, __m128 y)
{
    __m128 t0 = _mm_shuffle_ps(x,x,_MM_SHUFFLE(0,3,1,2));
    __m128 t1 = _mm_shuffle_ps(y,y,_MM_SHUFFLE(0,2,3,1));
    __m128 t2 = _mm_shuffle_ps(x,x,_MM_SHUFFLE(0,2,3,1));
    __m128 t3 = _mm_shuffle_ps(y,y,_MM_SHUFFLE(0,3,1,2));
    
    return _mm_sub_ps(_mm_mul_ps(t0,t1),_mm_mul_ps(t2,t3));
}

float Vector3::length() noexcept {

}

Vector3 Vector3::multiply_scalar(const float scalar) noexcept {

}

Vector3 Vector3::divide_scalar(const float scalat) noexcept {

}

Vector3 Vector3::normalize() noexcept {

}
