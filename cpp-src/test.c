#include <stdio.h>
#include <stdlib.h>
#include <xmmintrin.h>

int main() {

    __m128 v1 = _mm_set_ps( 2.0f, 2.0f, 2.0f, 2.0f );
    __m128 v2 = _mm_set_ps( 1.0f, 1.0f, 1.0f, 1.0f );

    // v = _mm_mul_ps(v,v);

    // __m128 t = _mm_add_ps(v, _mm_movehl_ps(v, v));
    // __m128 sum = _mm_add_ss(t, _mm_shuffle_ps(t, t, 1));

    __m128 sum = _mm_div_ps(v2, v1);

    float * res = aligned_alloc(16, 4 * sizeof(float));

    _mm_store_ps(res, sum);

    for(int i = 0; i < 4; i++) {
        printf("%f ", res[i]);
    }
    printf("\n");

    return 0;
}