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
 * ftp://ftp.cbi.pku.edu.cn/pub/software/blast/matrices/PAM10, the
 * Center for Bioinformatics, Peking University, China.
 */
#ifndef _PARASAIL_PAM10_H_
#define _PARASAIL_PAM10_H_

#include "parasail.h"
#include "pam_map.h"

/* # */
/* # This matrix was produced by "pam" Version 1.0.6 [28-Jul-93] */
/* # */
/* # PAM 10 substitution matrix, scale = ln(2)/2 = 0.346574 */
/* # */
/* # Expected score = -8.27, Entropy = 3.43 bits */
/* # */
/* # Lowest score = -23, Highest score = 13 */
/* # */

static const int parasail_pam10_[] = {
/*        A   R   N   D   C   Q   E   G   H   I   L   K   M   F   P   S   T   W   Y   V   B   Z   X   * */
/* A */   7,-10, -7, -6,-10, -7, -5, -4,-11, -8, -9,-10, -8,-12, -4, -3, -3,-20,-11, -5, -6, -6, -6,-23,
/* R */ -10,  9, -9,-17,-11, -4,-15,-13, -4, -8,-12, -2, -7,-12, -7, -6,-10, -5,-14,-11,-11, -7, -9,-23,
/* N */  -7, -9,  9, -1,-17, -7, -5, -6, -2, -8,-10, -4,-15,-12, -9, -2, -5,-11, -7,-12,  7, -6, -6,-23,
/* D */  -6,-17, -1,  8,-21, -6,  0, -6, -7,-11,-19, -8,-17,-21,-12, -7, -8,-21,-17,-11,  7, -1, -9,-23,
/* C */ -10,-11,-17,-21, 10,-20,-20,-13,-10, -9,-21,-20,-20,-19,-11, -6,-11,-22, -7, -9,-18,-20,-13,-23,
/* Q */  -7, -4, -7, -6,-20,  9, -1,-10, -2,-11, -8, -6, -7,-19, -6, -8, -9,-19,-18,-10, -6,  7, -8,-23,
/* E */  -5,-15, -5,  0,-20, -1,  8, -7, -9, -8,-13, -7,-10,-20, -9, -7, -9,-23,-11,-10, -1,  7, -8,-23,
/* G */  -4,-13, -6, -6,-13,-10, -7,  7,-13,-17,-14,-10,-12,-12,-10, -4,-10,-21,-20, -9, -6, -8, -8,-23,
/* H */ -11, -4, -2, -7,-10, -2, -9,-13, 10,-13, -9,-10,-17, -9, -7, -9,-11,-10, -6, -9, -4, -4, -8,-23,
/* I */  -8, -8, -8,-11, -9,-11, -8,-17,-13,  9, -4, -9, -3, -5,-12,-10, -5,-20, -9, -1, -9, -9, -8,-23,
/* L */  -9,-12,-10,-19,-21, -8,-13,-14, -9, -4,  7,-11, -2, -5,-10,-12,-10, -9,-10, -5,-12,-10, -9,-23,
/* K */ -10, -2, -4, -8,-20, -6, -7,-10,-10, -9,-11,  7, -4,-20,-10, -7, -6,-18,-12,-13, -5, -6, -8,-23,
/* M */  -8, -7,-15,-17,-20, -7,-10,-12,-17, -3, -2, -4, 12, -7,-11, -8, -7,-19,-17, -4,-16, -8, -9,-23,
/* F */ -12,-12,-12,-21,-19,-19,-20,-12, -9, -5, -5,-20, -7,  9,-13, -9,-12, -7, -1,-12,-14,-20,-12,-23,
/* P */  -4, -7, -9,-12,-11, -6, -9,-10, -7,-12,-10,-10,-11,-13,  8, -4, -7,-20,-20, -9,-10, -7, -8,-23,
/* S */  -3, -6, -2, -7, -6, -8, -7, -4, -9,-10,-12, -7, -8, -9, -4,  7, -2, -8,-10,-10, -4, -8, -6,-23,
/* T */  -3,-10, -5, -8,-11, -9, -9,-10,-11, -5,-10, -6, -7,-12, -7, -2,  8,-19, -9, -6, -6, -9, -7,-23,
/* W */ -20, -5,-11,-21,-22,-19,-23,-21,-10,-20, -9,-18,-19, -7,-20, -8,-19, 13, -8,-22,-13,-21,-16,-23,
/* Y */ -11,-14, -7,-17, -7,-18,-11,-20, -6, -9,-10,-12,-17, -1,-20,-10, -9, -8, 10,-10, -9,-13,-11,-23,
/* V */  -5,-11,-12,-11, -9,-10,-10, -9, -9, -1, -5,-13, -4,-12, -9,-10, -6,-22,-10,  8,-11,-10, -8,-23,
/* B */  -6,-11,  7,  7,-18, -6, -1, -6, -4, -9,-12, -5,-16,-14,-10, -4, -6,-13, -9,-11,  7, -3, -8,-23,
/* Z */  -6, -7, -6, -1,-20,  7,  7, -8, -4, -9,-10, -6, -8,-20, -7, -8, -9,-21,-13,-10, -3,  7, -8,-23,
/* X */  -6, -9, -6, -9,-13, -8, -8, -8, -8, -8, -9, -8, -9,-12, -8, -6, -7,-16,-11, -8, -8, -8, -8,-23,
/* * */ -23,-23,-23,-23,-23,-23,-23,-23,-23,-23,-23,-23,-23,-23,-23,-23,-23,-23,-23,-23,-23,-23,-23,  1
};

static const parasail_matrix_t parasail_pam10 = {
    "pam10",
    parasail_pam10_,
    parasail_pam_map,
    24,
    0
};

#endif /* _PARASAIL_PAM10_H_ */
