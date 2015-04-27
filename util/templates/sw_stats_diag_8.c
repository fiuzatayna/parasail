/**
 * @file
 *
 * @author jeff.daily@pnnl.gov
 *
 * Copyright (c) 2014 Battelle Memorial Institute.
 *
 * All rights reserved. No warranty, explicit or implicit, provided.
 */
#include "config.h"

#include <stdlib.h>

%(HEADER)s

#include "parasail.h"
#include "parasail/memory.h"
#include "parasail/internal_%(ISA)s.h"
#include "parasail/matrices/blosum_map.h"

#define NEG_INF %(NEG_INF)s
%(FIXES)s

/* shift given vector v, insert val, return shifted val */
static inline %(VTYPE)s vshift(const %(VTYPE)s v, const int val)
{
    %(VTYPE)s ret = %(VRSHIFT)s(v, %(BYTES)s);
    ret = %(VINSERT)s(ret, val, %(LAST_POS)s);
    return ret;
}

#ifdef PARASAIL_TABLE
static inline void arr_store_si%(BITS)s(
        int *array,
        %(VTYPE)s vWscore,
        %(INDEX)s i,
        %(INDEX)s s1Len,
        %(INDEX)s j,
        %(INDEX)s s2Len)
{
%(PRINTER)s
}
#endif


#ifdef PARASAIL_TABLE
#define FNAME %(NAME_TABLE)s
#else
#define FNAME %(NAME)s
#endif

parasail_result_t* FNAME(
        const char * const restrict _s1, const int s1Len,
        const char * const restrict _s2, const int s2Len,
        const int open, const int gap, const parasail_matrix_t *matrix)
{
    const %(INDEX)s N = %(LANES)s; /* number of values in vector */
    const %(INDEX)s PAD = N-1;
    const %(INDEX)s PAD2 = PAD*2;
    %(INT)s * const restrict s1      = parasail_memalign_%(INT)s(%(ALIGNMENT)s, s1Len+PAD);
    %(INT)s * const restrict s2B     = parasail_memalign_%(INT)s(%(ALIGNMENT)s, s2Len+PAD2);
    %(INT)s * const restrict _tbl_pr = parasail_memalign_%(INT)s(%(ALIGNMENT)s, s2Len+PAD2);
    %(INT)s * const restrict _del_pr = parasail_memalign_%(INT)s(%(ALIGNMENT)s, s2Len+PAD2);
    %(INT)s * const restrict _mch_pr = parasail_memalign_%(INT)s(%(ALIGNMENT)s, s2Len+PAD2);
    %(INT)s * const restrict _sim_pr = parasail_memalign_%(INT)s(%(ALIGNMENT)s, s2Len+PAD2);
    %(INT)s * const restrict _len_pr = parasail_memalign_%(INT)s(%(ALIGNMENT)s, s2Len+PAD2);
    %(INT)s * const restrict s2 = s2B+PAD; /* will allow later for negative indices */
    %(INT)s * const restrict tbl_pr = _tbl_pr+PAD;
    %(INT)s * const restrict del_pr = _del_pr+PAD;
    %(INT)s * const restrict mch_pr = _mch_pr+PAD;
    %(INT)s * const restrict sim_pr = _sim_pr+PAD;
    %(INT)s * const restrict len_pr = _len_pr+PAD;
#ifdef PARASAIL_TABLE
    parasail_result_t *result = parasail_result_new_table3(s1Len, s2Len);
#else
    parasail_result_t *result = parasail_result_new();
#endif
    %(INDEX)s i = 0;
    %(INDEX)s j = 0;
    %(INT)s score = NEG_INF;
    %(INT)s matches = NEG_INF;
    %(INT)s similar = NEG_INF;
    %(INT)s length = NEG_INF;
    %(STATS_SATURATION_CHECK_INIT)s
    %(VTYPE)s vNegInf = %(VSET1)s(NEG_INF);
    %(VTYPE)s vNegInf0 = %(VRSHIFT)s(vNegInf, %(BYTES)s); /* shift in a 0 */
    %(VTYPE)s vOpen = %(VSET1)s(open);
    %(VTYPE)s vGap  = %(VSET1)s(gap);
    %(VTYPE)s vZero = %(VSET1)s(0);
    %(VTYPE)s vOne = %(VSET1)s(1);
    %(VTYPE)s vOne16 = %(VSET1x16)s(1);
    %(VTYPE)s vN16 = %(VSET1x16)s(N);
    %(VTYPE)s vNegOne16 = %(VSET1x16)s(-1);
    %(VTYPE)s vILo16 = %(VSETx16)s(%(DIAG_ILO)s);
    %(VTYPE)s vIHi16 = %(VSETx16)s(%(DIAG_IHI)s);
    %(VTYPE)s vJresetLo16 = %(VSETx16)s(%(DIAG_JLO)s);
    %(VTYPE)s vJresetHi16 = %(VSETx16)s(%(DIAG_JHI)s);
    %(VTYPE)s vMaxScore = vNegInf;
    %(VTYPE)s vMaxMatch = vNegInf;
    %(VTYPE)s vMaxSimilar = vNegInf;
    %(VTYPE)s vMaxLength = vNegInf;
    %(VTYPE)s vILimit16 = %(VSET1x16)s(s1Len);
    %(VTYPE)s vJLimit16 = %(VSET1x16)s(s2Len);

    /* convert _s1 from char to int in range 0-23 */
    for (i=0; i<s1Len; ++i) {
        s1[i] = matrix->mapper[(unsigned char)_s1[i]];
    }
    /* pad back of s1 with dummy values */
    for (i=s1Len; i<s1Len+PAD; ++i) {
        s1[i] = 0; /* point to first matrix row because we don't care */
    }

    /* convert _s2 from char to int in range 0-23 */
    for (j=0; j<s2Len; ++j) {
        s2[j] = matrix->mapper[(unsigned char)_s2[j]];
    }
    /* pad front of s2 with dummy values */
    for (j=-PAD; j<0; ++j) {
        s2[j] = 0; /* point to first matrix row because we don't care */
    }
    /* pad back of s2 with dummy values */
    for (j=s2Len; j<s2Len+PAD; ++j) {
        s2[j] = 0; /* point to first matrix row because we don't care */
    }

    /* set initial values for stored row */
    for (j=0; j<s2Len; ++j) {
        tbl_pr[j] = 0;
        del_pr[j] = NEG_INF;
        mch_pr[j] = 0;
        sim_pr[j] = 0;
        len_pr[j] = 0;
    }
    /* pad front of stored row values */
    for (j=-PAD; j<0; ++j) {
        tbl_pr[j] = NEG_INF;
        del_pr[j] = NEG_INF;
        mch_pr[j] = 0;
        sim_pr[j] = 0;
        len_pr[j] = 0;
    }
    /* pad back of stored row values */
    for (j=s2Len; j<s2Len+PAD; ++j) {
        tbl_pr[j] = NEG_INF;
        del_pr[j] = NEG_INF;
        mch_pr[j] = 0;
        sim_pr[j] = 0;
        len_pr[j] = 0;
    }
    tbl_pr[-1] = 0; /* upper left corner */

    /* iterate over query sequence */
    for (i=0; i<s1Len; i+=N) {
        %(VTYPE)s vNscore = vNegInf0;
        %(VTYPE)s vNmatch = vZero;
        %(VTYPE)s vNsimilar = vZero;
        %(VTYPE)s vNlength = vZero;
        %(VTYPE)s vWscore = vNegInf0;
        %(VTYPE)s vWmatch = vZero;
        %(VTYPE)s vWsimilar = vZero;
        %(VTYPE)s vWlength = vZero;
        %(VTYPE)s vIns = vNegInf;
        %(VTYPE)s vDel = vNegInf;
        %(VTYPE)s vJLo16 = vJresetLo16;
        %(VTYPE)s vJHi16 = vJresetHi16;
        %(VTYPE)s vs1 = %(VSET)s(
                %(DIAG_VS1)s);
        %(VTYPE)s vs2 = vNegInf;
        %(DIAG_MATROW_DECL)s
        %(VTYPE)s vIltLimit = %(VPACKS)s(
                    %(VCMPLTx16)s(vILo16, vILimit16),
                    %(VCMPLTx16)s(vIHi16, vILimit16));
        /* iterate over database sequence */
        for (j=0; j<s2Len+PAD; ++j) {
            %(VTYPE)s vMat;
            %(VTYPE)s vNWscore = vNscore;
            %(VTYPE)s vNWmatch = vNmatch;
            %(VTYPE)s vNWsimilar = vNsimilar;
            %(VTYPE)s vNWlength = vNlength;
            vNscore = vshift(vWscore, tbl_pr[j]);
            vNmatch = vshift(vWmatch, mch_pr[j]);
            vNsimilar = vshift(vWsimilar, sim_pr[j]);
            vNlength = vshift(vWlength, len_pr[j]);
            vDel = vshift(vDel, del_pr[j]);
            vDel = %(VMAX)s(
                    %(VSUB)s(vNscore, vOpen),
                    %(VSUB)s(vDel, vGap));
            vIns = %(VMAX)s(
                    %(VSUB)s(vWscore, vOpen),
                    %(VSUB)s(vIns, vGap));
            vs2 = vshift(vs2, s2[j]);
            vMat = %(VSET)s(
                    %(DIAG_MATROW_USE)s
                    );
            vNWscore = %(VADD)s(vNWscore, vMat);
            vWscore = %(VMAX)s(vNWscore, vIns);
            vWscore = %(VMAX)s(vWscore, vDel);
            vWscore = %(VMAX)s(vWscore, vZero);
            /* conditional block */
            {
                %(VTYPE)s case1not;
                %(VTYPE)s case2not;
                %(VTYPE)s case2;
                %(VTYPE)s case3;
                %(VTYPE)s vCmatch;
                %(VTYPE)s vCsimilar;
                %(VTYPE)s vClength;
                case1not = %(VOR)s(
                        %(VCMPLT)s(vNWscore,vDel),
                        %(VCMPLT)s(vNWscore,vIns));
                case2not = %(VCMPLT)s(vDel,vIns);
                case2 = %(VANDNOT)s(case2not,case1not);
                case3 = %(VAND)s(case1not,case2not);
                vCmatch = %(VANDNOT)s(case1not,
                        %(VADD)s(vNWmatch, %(VAND)s(
                                %(VCMPEQ)s(vs1,vs2),vOne)));
                vCmatch = %(VOR)s(vCmatch, %(VAND)s(case2, vNmatch));
                vCmatch = %(VOR)s(vCmatch, %(VAND)s(case3, vWmatch));
                vCsimilar = %(VANDNOT)s(case1not,
                        %(VADD)s(vNWsimilar, %(VAND)s(
                                %(VCMPGT)s(vMat,vZero),vOne)));
                vCsimilar = %(VOR)s(vCsimilar, %(VAND)s(case2, vNsimilar));
                vCsimilar = %(VOR)s(vCsimilar, %(VAND)s(case3, vWsimilar));
                vClength= %(VANDNOT)s(case1not,
                        %(VADD)s(vNWlength, vOne));
                vClength= %(VOR)s(vClength,%(VAND)s(case2,
                            %(VADD)s(vNlength, vOne)));
                vClength= %(VOR)s(vClength,%(VAND)s(case3,
                            %(VADD)s(vWlength, vOne)));
                vWmatch = vCmatch;
                vWsimilar = vCsimilar;
                vWlength = vClength;
            }
            {
                %(VTYPE)s cond_zero = %(VCMPEQ)s(vWscore, vZero);
                vWmatch = %(VANDNOT)s(cond_zero, vWmatch);
                vWsimilar = %(VANDNOT)s(cond_zero, vWsimilar);
                vWlength = %(VANDNOT)s(cond_zero, vWlength);
            }

            /* as minor diagonal vector passes across the j=-1 boundary,
             * assign the appropriate boundary conditions */
            {
                %(VTYPE)s cond = %(VPACKS)s(
                        %(VCMPEQx16)s(vJLo16,vNegOne16),
                        %(VCMPEQx16)s(vJHi16,vNegOne16));
                vWscore = %(VANDNOT)s(cond, vWscore);
                vWmatch = %(VANDNOT)s(cond, vWmatch);
                vWsimilar = %(VANDNOT)s(cond, vWsimilar);
                vWlength = %(VANDNOT)s(cond, vWlength);
                vDel = %(VBLEND)s(vDel, vNegInf, cond);
                vIns = %(VBLEND)s(vIns, vNegInf, cond);
            }

            %(STATS_SATURATION_CHECK_MID)s
#ifdef PARASAIL_TABLE
            arr_store_si%(BITS)s(result->score_table, vWscore, i, s1Len, j, s2Len);
            arr_store_si%(BITS)s(result->matches_table, vWmatch, i, s1Len, j, s2Len);
            arr_store_si%(BITS)s(result->similar_table, vWsimilar, i, s1Len, j, s2Len);
            arr_store_si%(BITS)s(result->length_table, vWlength, i, s1Len, j, s2Len);
#endif
            tbl_pr[j-%(LAST_POS)s] = (%(INT)s)%(VEXTRACT)s(vWscore,0);
            mch_pr[j-%(LAST_POS)s] = (%(INT)s)%(VEXTRACT)s(vWmatch,0);
            sim_pr[j-%(LAST_POS)s] = (%(INT)s)%(VEXTRACT)s(vWsimilar,0);
            len_pr[j-%(LAST_POS)s] = (%(INT)s)%(VEXTRACT)s(vWlength,0);
            del_pr[j-%(LAST_POS)s] = (%(INT)s)%(VEXTRACT)s(vDel,0);
            /* as minor diagonal vector passes across table, extract
             * max values within the i,j bounds */
            {
                %(VTYPE)s cond_valid_J = %(VAND)s(
                        %(VPACKS)s(
                            %(VCMPGTx16)s(vJLo16, vNegOne16),
                            %(VCMPGTx16)s(vJHi16, vNegOne16)),
                        %(VPACKS)s(
                            %(VCMPLTx16)s(vJLo16, vJLimit16),
                            %(VCMPLTx16)s(vJHi16, vJLimit16)));
                %(VTYPE)s cond_max = %(VCMPGT)s(vWscore, vMaxScore);
                %(VTYPE)s cond_all = %(VAND)s(cond_max,
                        %(VAND)s(vIltLimit, cond_valid_J));
                vMaxScore = %(VBLEND)s(vMaxScore, vWscore, cond_all);
                vMaxMatch = %(VBLEND)s(vMaxMatch, vWmatch, cond_all);
                vMaxSimilar = %(VBLEND)s(vMaxSimilar, vWsimilar, cond_all);
                vMaxLength = %(VBLEND)s(vMaxLength, vWlength, cond_all);
            }
            vJLo16 = %(VADDx16)s(vJLo16, vOne16);
            vJHi16 = %(VADDx16)s(vJHi16, vOne16);
        }
        vILo16 = %(VADDx16)s(vILo16, vN16);
        vIHi16 = %(VADDx16)s(vIHi16, vN16);
    }

    /* max in vMaxScore */
    for (i=0; i<N; ++i) {
        %(INT)s value;
        value = (%(INT)s) %(VEXTRACT)s(vMaxScore, %(LAST_POS)s);
        if (value > score) {
            score = value;
            matches = (%(INT)s) %(VEXTRACT)s(vMaxMatch, %(LAST_POS)s);
            similar = (%(INT)s) %(VEXTRACT)s(vMaxSimilar, %(LAST_POS)s);
            length= (%(INT)s) %(VEXTRACT)s(vMaxLength, %(LAST_POS)s);
        }
        vMaxScore = %(VSHIFT)s(vMaxScore, %(BYTES)s);
        vMaxMatch = %(VSHIFT)s(vMaxMatch, %(BYTES)s);
        vMaxSimilar = %(VSHIFT)s(vMaxSimilar, %(BYTES)s);
        vMaxLength = %(VSHIFT)s(vMaxLength, %(BYTES)s);
    }

    %(STATS_SATURATION_CHECK_FINAL)s

    result->score = score;
    result->matches = matches;
    result->similar = similar;
    result->length = length;

    parasail_free(_len_pr);
    parasail_free(_sim_pr);
    parasail_free(_mch_pr);
    parasail_free(_del_pr);
    parasail_free(_tbl_pr);
    parasail_free(s2B);
    parasail_free(s1);

    return result;
}
