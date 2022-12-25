#ifndef __vector_3__h
#define __vector_3__h

#include <xmmintrin.h>

class Vector3 {

private:
    __m128 _v3;

public:

    void load_from(float * ptr);

    void add(__m128 v1, __m128 v2);

    void sub(__m128 v1, __m128 v2);

    __m128 cross(__m128 v1);
    
    __m128 cross_vectors(__m128 v1, __m128 v2);

    float length() noexcept;

    Vector3 multiply_scalar(const float scalar) noexcept;

    Vector3 divide_scalar(const float scalat) noexcept;

    Vector3 normalize() noexcept;
};

#endif