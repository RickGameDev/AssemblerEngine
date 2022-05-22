/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), http://opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

#ifndef ae_mat_simd_avx_h
#define ae_mat_simd_avx_h
#ifdef __AVX__

#include "../../common.h"
#include "../intrin.h"

#include <immintrin.h>

AE_INLINE
void
ae_mat4_scale_avx(mat4 m, float s) {
  __m256 y0;
  y0 = _mm256_set1_ps(s);
  
  aem_store256(m[0], _mm256_mul_ps(y0, aem_load256(m[0])));
  aem_store256(m[2], _mm256_mul_ps(y0, aem_load256(m[2])));
}

AE_INLINE
void
ae_mat4_mul_avx(mat4 m1, mat4 m2, mat4 dest) {
  /* D = R * L (Column-Major) */

  __m256 y0, y1, y2, y3, y4, y5, y6, y7, y8, y9;

  y0 = aem_load256(m2[0]); /* h g f e d c b a */
  y1 = aem_load256(m2[2]); /* p o n m l k j i */

  y2 = aem_load256(m1[0]); /* h g f e d c b a */
  y3 = aem_load256(m1[2]); /* p o n m l k j i */

  /* 0x03: 0b00000011 */
  y4 = _mm256_permute2f128_ps(y2, y2, 0x03); /* d c b a h g f e */
  y5 = _mm256_permute2f128_ps(y3, y3, 0x03); /* l k j i p o n m */

  /* f f f f a a a a */
  /* h h h h c c c c */
  /* e e e e b b b b */
  /* g g g g d d d d */
  y6 = _mm256_permutevar_ps(y0, _mm256_set_epi32(1, 1, 1, 1, 0, 0, 0, 0));
  y7 = _mm256_permutevar_ps(y0, _mm256_set_epi32(3, 3, 3, 3, 2, 2, 2, 2));
  y8 = _mm256_permutevar_ps(y0, _mm256_set_epi32(0, 0, 0, 0, 1, 1, 1, 1));
  y9 = _mm256_permutevar_ps(y0, _mm256_set_epi32(2, 2, 2, 2, 3, 3, 3, 3));

  aem_store256(dest[0],
                _mm256_add_ps(_mm256_add_ps(_mm256_mul_ps(y2, y6),
                                            _mm256_mul_ps(y3, y7)),
                              _mm256_add_ps(_mm256_mul_ps(y4, y8),
                                            _mm256_mul_ps(y5, y9))));

  /* n n n n i i i i */
  /* p p p p k k k k */
  /* m m m m j j j j */
  /* o o o o l l l l */
  y6 = _mm256_permutevar_ps(y1, _mm256_set_epi32(1, 1, 1, 1, 0, 0, 0, 0));
  y7 = _mm256_permutevar_ps(y1, _mm256_set_epi32(3, 3, 3, 3, 2, 2, 2, 2));
  y8 = _mm256_permutevar_ps(y1, _mm256_set_epi32(0, 0, 0, 0, 1, 1, 1, 1));
  y9 = _mm256_permutevar_ps(y1, _mm256_set_epi32(2, 2, 2, 2, 3, 3, 3, 3));

  aem_store256(dest[2],
                _mm256_add_ps(_mm256_add_ps(_mm256_mul_ps(y2, y6),
                                            _mm256_mul_ps(y3, y7)),
                              _mm256_add_ps(_mm256_mul_ps(y4, y8),
                                            _mm256_mul_ps(y5, y9))));
}

#endif
#endif /* ae_mat_simd_avx_h */