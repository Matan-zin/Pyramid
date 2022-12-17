#ifndef __vector_3__h
#define __vector_3__h


class Vector3 {

private:
    float * ptr;
    static inline int I0 = 0, I1 = 1, I2 = 2;

public:
    Vector3(float * p) : ptr(p) {};

    float * get_ptr() noexcept;

    void add(const Vector3& v, const float * res) noexcept;

    void sub(const Vector3& v, const float * res) noexcept;

    float length() noexcept;

    Vector3 multiply_scalar(const float scalar) noexcept;

    Vector3 divide_scalar(const float scalat) noexcept;

    Vector3 normalize() noexcept;

    Vector3 cross(const Vector3& v) noexcept;

    Vector3 cross_vectors(const Vector3& v1, const Vector3& v2) noexcept;
};

#endif