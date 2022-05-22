/*
 * Copyright (c), Recep Aslantas.
 *
 * MIT License (MIT), htt../opensource.org/licenses/MIT
 * Full license can be found in the LICENSE file
 */

/*
 Functions:
   AE_INLINE mat4s aes_ortho_lh_no(float left,    float right,
                                      float bottom,  float top,
                                      float nearZ,   float farZ)
   AE_INLINE mat4s aes_ortho_aabb_lh_no(vec3s box[2]);
   AE_INLINE mat4s aes_ortho_aabb_p_lh_no(vec3s box[2],  float padding);
   AE_INLINE mat4s aes_ortho_aabb_pz_lh_no(vec3s box[2], float padding);
   AE_INLINE mat4s aes_ortho_default_lh_no(float aspect)
   AE_INLINE mat4s aes_ortho_default_s_lh_no(float aspect, float size)
 */

#ifndef aes_ortho_lh_no_h
#define aes_ortho_lh_no_h

#include "../../common.h"
#include "../../types-struct.h"
#include "../../plane.h"
#include "../../cam.h"

/*!
 * @brief set up orthographic projection matrix
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * @param[in]  left    viewport.left
 * @param[in]  right   viewport.right
 * @param[in]  bottom  viewport.bottom
 * @param[in]  top     viewport.top
 * @param[in]  nearZ   near clipping plane
 * @param[in]  farZ    far clipping plane
 * @returns    result matrix
 */
AE_INLINE
mat4s
aes_ortho_lh_no(float left,   float right,
                 float bottom, float top,
                 float nearZ,  float farZ) {
  mat4s dest;
  ae_ortho_lh_no(left, right, bottom, top, nearZ, farZ, dest.raw);
  return dest;
}

/*!
 * @brief set up orthographic projection matrix using bounding box
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * bounding box (AABB) must be in view space
 *
 * @param[in]  box   AABB
 * @returns    result matrix
 */
AE_INLINE
mat4s
aes_ortho_aabb_lh_no(vec3s box[2]) {
  mat4s dest;
  vec3  rawBox[2];

  aes_vec3_unpack(rawBox, box, 2);
  ae_ortho_aabb_lh_no(rawBox, dest.raw);

  return dest;
}

/*!
 * @brief set up orthographic projection matrix using bounding box
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * bounding box (AABB) must be in view space
 *
 * @param[in]  box     AABB
 * @param[in]  padding padding
 * @returns    result matrix
 */
AE_INLINE
mat4s
aes_ortho_aabb_p_lh_no(vec3s box[2], float padding) {
  mat4s dest;
  vec3  rawBox[2];

  aes_vec3_unpack(rawBox, box, 2);
  ae_ortho_aabb_p_lh_no(rawBox, padding, dest.raw);

  return dest;
}

/*!
 * @brief set up orthographic projection matrix using bounding box
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * bounding box (AABB) must be in view space
 *
 * @param[in]  box     AABB
 * @param[in]  padding padding for near and far
 * @returns    result matrix
 */
AE_INLINE
mat4s
aes_ortho_aabb_pz_lh_no(vec3s box[2], float padding) {
  mat4s dest;
  vec3  rawBox[2];

  aes_vec3_unpack(rawBox, box, 2);
  ae_ortho_aabb_pz_lh_no(rawBox, padding, dest.raw);

  return dest;
}

/*!
 * @brief set up unit orthographic projection matrix
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * @param[in]  aspect aspect ration ( width / height )
 * @returns    result matrix
 */
AE_INLINE
mat4s
aes_ortho_default_lh_no(float aspect) {
  mat4s dest;
  ae_ortho_default_lh_no(aspect, dest.raw);
  return dest;
}

/*!
 * @brief set up orthographic projection matrix with given CUBE size
 *        with a left-hand coordinate system and a
 *        clip-space of [-1, 1].
 *
 * @param[in]  aspect aspect ratio ( width / height )
 * @param[in]  size   cube size
 * @returns    result matrix
 */
AE_INLINE
mat4s
aes_ortho_default_s_lh_no(float aspect, float size) {
  mat4s dest;
  ae_ortho_default_s_lh_no(aspect, size, dest.raw);
  return dest;
}

#endif /* aes_ortho_lh_no_h */
