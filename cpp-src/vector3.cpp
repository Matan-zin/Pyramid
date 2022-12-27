#include <cmath>

#include "vector3.h"

constexpr int SIMD_NAN = 15;

inline __m128 _set_mm_to_one()
{
    return _mm_set_ps(1.0f,1.0f,1.0f,1.0f);
}

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
/** Calculate cross product of two vectors
 * x2 * y3 - x3 * y2
 * x3 * y1 - x1 * y3
 * x1 * y2 - x2 * y1
 */
{
    __m128 t0 = _mm_shuffle_ps(x,x,_MM_SHUFFLE(0,3,1,2));
    __m128 t1 = _mm_shuffle_ps(y,y,_MM_SHUFFLE(0,2,3,1));
    __m128 t2 = _mm_shuffle_ps(x,x,_MM_SHUFFLE(0,2,3,1));
    __m128 t3 = _mm_shuffle_ps(y,y,_MM_SHUFFLE(0,3,1,2));
    
    return _mm_sub_ps(_mm_mul_ps(t0,t1),_mm_mul_ps(t2,t3));
}

__m128 Vector3::length()
// Math.sqrt( this.x * this.x + this.y * this.y + this.z * this.z );
{
    __m128 t1 = _mm_mul_ps(_v3, _v3);
    __m128 t2 = _mm_add_ps(t1, _mm_movehl_ps(t1, t1));
    __m128 t3 = _mm_add_ss(t2, _mm_shuffle_ps(t2, t2, 1));
    
    t3 = _mm_shuffle_ps(t3,t3,_MM_SHUFFLE(3,3,3,3));
    
    return _mm_sqrt_ps(t3);
}

__m128 Vector3::multiply_scalar(__m128 v1)
{
    return _mm_mul_ps(
        _mm_mul_ps(_v3 , v1),
        _set_mm_to_one()
        );
}

__m128 Vector3::divide_scalar(__m128 v1)
{
    return multiply_scalar( 
        _mm_div_ps( _set_mm_to_one() , v1 )
    );
}

__m128 Vector3::normalize()
{
    __m128 len = this -> length();

    __m128 cmp = _mm_cmpeq_ps(len , _mm_setzero_ps());

    int mask = _mm_movemask_ps(cmp);

    if( mask == SIMD_NAN ) {
        return divide_scalar( _set_mm_to_one() );
    } else {
        return divide_scalar( len );
    }
}
