/**
 * @file
 *
 * @author jeff.daily@pnnl.gov
 *
 * Copyright (c) 2014 Battelle Memorial Institute.
 *
 * All rights reserved. No warranty, explicit or implicit, provided.
 *
 * This file was converted to C code from the raw file found at
 * ftp://ftp.cbi.pku.edu.cn/pub/software/blast/matrices/PAM410, the
 * Center for Bioinformatics, Peking University, China.
 */
#ifndef _PARASAIL_PAM410_H_
#define _PARASAIL_PAM410_H_

#include "parasail.h"
#include "pam_map.h"

/* # */
/* # This matrix was produced by "pam" Version 1.0.6 [28-Jul-93] */
/* # */
/* # PAM 410 substitution matrix, scale = ln(2)/6 = 0.115525 */
/* # */
/* # Expected score = -0.617, Entropy = 0.131 bits */
/* # */
/* # Lowest score = -10, Highest score = 31 */
/* # */

static const int parasail_pam410_[] = {
/*        A   R   N   D   C   Q   E   G   H   I   L   K   M   F   P   S   T   W   Y   V   B   Z   X   * */
/* A */   1, -1,  0,  1, -2,  0,  1,  2, -1,  0, -2, -1, -1, -4,  1,  1,  1, -7, -4,  0,  1,  0,  0,-10,
/* R */  -1,  6,  1,  0, -4,  2,  0, -2,  2, -2, -3,  4,  0, -5,  0,  0,  0,  4, -5, -2,  0,  1,  0,-10,
/* N */   0,  1,  1,  2, -4,  1,  2,  1,  1, -2, -3,  1, -2, -4,  0,  1,  1, -5, -3, -1,  2,  2,  0,-10,
/* D */   1,  0,  2,  3, -6,  2,  3,  1,  1, -2, -4,  1, -2, -6,  0,  1,  0, -8, -5, -2,  3,  3,  0,-10,
/* C */  -2, -4, -4, -6, 20, -6, -6, -4, -4, -3, -7, -6, -6, -4, -3,  0, -2,-10,  1, -2, -5, -6, -3,-10,
/* Q */   0,  2,  1,  2, -6,  3,  2,  0,  3, -2, -2,  1, -1, -5,  1,  0,  0, -5, -4, -2,  2,  3,  0,-10,
/* E */   1,  0,  2,  3, -6,  2,  3,  1,  1, -2, -3,  1, -2, -6,  0,  1,  0, -8, -5, -2,  3,  3,  0,-10,
/* G */   2, -2,  1,  1, -4,  0,  1,  5, -1, -2, -4, -1, -3, -6,  0,  1,  1, -8, -6, -1,  1,  0,  0,-10,
/* H */  -1,  2,  1,  1, -4,  3,  1, -1,  6, -2, -2,  1, -2, -2,  0,  0, -1, -3,  0, -2,  1,  2,  0,-10,
/* I */   0, -2, -2, -2, -3, -2, -2, -2, -2,  4,  4, -2,  3,  2, -2, -1,  0, -6,  0,  4, -2, -2,  0,-10,
/* L */  -2, -3, -3, -4, -7, -2, -3, -4, -2,  4,  8, -3,  5,  4, -3, -3, -1, -2,  1,  3, -3, -3, -1,-10,
/* K */  -1,  4,  1,  1, -6,  1,  1, -1,  1, -2, -3,  5,  0, -6,  0,  0,  0, -3, -5, -2,  1,  1,  0,-10,
/* M */  -1,  0, -2, -2, -6, -1, -2, -3, -2,  3,  5,  0,  5,  1, -2, -1,  0, -4, -2,  2, -2, -2,  0,-10,
/* F */  -4, -5, -4, -6, -4, -5, -6, -6, -2,  2,  4, -6,  1, 14, -5, -4, -3,  2, 12,  0, -5, -5, -2,-10,
/* P */   1,  0,  0,  0, -3,  1,  0,  0,  0, -2, -3,  0, -2, -5,  6,  1,  1, -7, -5, -1,  0,  0,  0,-10,
/* S */   1,  0,  1,  1,  0,  0,  1,  1,  0, -1, -3,  0, -1, -4,  1,  1,  1, -3, -3, -1,  1,  0,  0,-10,
/* T */   1,  0,  1,  0, -2,  0,  0,  1, -1,  0, -1,  0,  0, -3,  1,  1,  2, -6, -3,  0,  0,  0,  0,-10,
/* W */  -7,  4, -5, -8,-10, -5, -8, -8, -3, -6, -2, -3, -4,  2, -7, -3, -6, 31,  2, -7, -6, -7, -4,-10,
/* Y */  -4, -5, -3, -5,  1, -4, -5, -6,  0,  0,  1, -5, -2, 12, -5, -3, -3,  2, 15, -2, -4, -5, -2,-10,
/* V */   0, -2, -1, -2, -2, -2, -2, -1, -2,  4,  3, -2,  2,  0, -1, -1,  0, -7, -2,  4, -2, -2,  0,-10,
/* B */   1,  0,  2,  3, -5,  2,  3,  1,  1, -2, -3,  1, -2, -5,  0,  1,  0, -6, -4, -2,  2,  2,  0,-10,
/* Z */   0,  1,  2,  3, -6,  3,  3,  0,  2, -2, -3,  1, -2, -5,  0,  0,  0, -7, -5, -2,  2,  3,  0,-10,
/* X */   0,  0,  0,  0, -3,  0,  0,  0,  0,  0, -1,  0,  0, -2,  0,  0,  0, -4, -2,  0,  0,  0, -1,-10,
/* * */ -10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,-10,  1
};

static const parasail_matrix_t parasail_pam410 = {
    "pam410",
    parasail_pam410_,
    parasail_pam_map,
    24,
    0
};

#endif /* _PARASAIL_PAM410_H_ */
