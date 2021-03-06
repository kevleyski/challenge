/* ============================================================================
Copyright (c) 2008-2014, Broadcom Corporation
All rights reserved.
Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
============================================================================ */

#ifndef VG_PATH_FILLER_4_H
#define VG_PATH_FILLER_4_H

#include "middleware/khronos/common/khrn_mem.h"

#define VG_PATH_FLAG_BOUNDS_VALID (1 << 4)
#define VG_PATH_FLAG_BOUNDS_LOOSE (1 << 5)
#define VG_PATH_FLAG_INTERP_TO    (1 << 6)
#define VG_PATH_FLAG_INTERP_FROM  (1 << 7)

typedef union {
   struct {
      MEM_HANDLE_T tess;

      union {
         struct {
            void *fill_rep, *stroke_rep;
            uint32_t fill_state_id[2], stroke_state_id[2]; /* the reason these aren't uint64_ts is to avoid alignment issues on platforms where alignof(uint64_t) > 4 */
         } glyph;
         struct {
            MEM_HANDLE_T head_a, head_b; /* don't hold references. paths should remove themselves from the lls in vg_path_extra_term (via discard_interp_to) */
         } interp_from;
      } u;
   } n;
   struct {
      MEM_HANDLE_T from_a, from_b, prev_a, prev_b, next_a, next_b; /* hold references to from_a and from_b */
      float t;
   } interp_to;
} VG_PATH_EXTRA_T;

#endif
