#include <stdio.h>
#include <xmmintrin.h>
#include <stdlib.h>

int main() {

    __m128 v = _mm_set_ps( 0.0f, 0.0f, 0.0f, 0.0f );

    // v = _mm_mul_ps(v,v);

    // __m128 t = _mm_add_ps(v, _mm_movehl_ps(v, v));
    // __m128 sum = _mm_add_ss(t, _mm_shuffle_ps(t, t, 1));

    __m128 sum ;//= v;//_mm_sqrt_ps(v);

    sum = _mm_cmpeq_ps(v, _mm_setzero_ps());
const int mask = _mm_movemask_ps( sum );
printf( "%i\n", mask );

    // float * res = aligned_alloc(16, 4 * sizeof(float));

    // _mm_store_ps(res, sum);

    // for(int i = 0; i < 4; i++) {
    //     printf("%f ", res[i]);
    // }
    // printf("\n");

    return 0;
}