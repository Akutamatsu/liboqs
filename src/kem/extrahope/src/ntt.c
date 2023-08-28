#include <stdint.h>
#include "params.h"
#include "ntt.h"
#include "reduce.h"

/* Code to generate zetas and zetas_inv used in the number-theoretic transform:

#define ROOT_OF_UNITY 3

static const uint16_t tree[128] = {
  0, 64, 32, 96, 16, 80, 48, 112, 8, 72, 40, 104, 24, 88, 56, 120,
  4, 68, 36, 100, 20, 84, 52, 116, 12, 76, 44, 108, 28, 92, 60, 124,
  2, 66, 34, 98, 18, 82, 50, 114, 10, 74, 42, 106, 26, 90, 58, 122,
  6, 70, 38, 102, 22, 86, 54, 118, 14, 78, 46, 110, 30, 94, 62, 126,
  1, 65, 33, 97, 17, 81, 49, 113, 9, 73, 41, 105, 25, 89, 57, 121,
  5, 69, 37, 101, 21, 85, 53, 117, 13, 77, 45, 109, 29, 93, 61, 125,
  3, 67, 35, 99, 19, 83, 51, 115, 11, 75, 43, 107, 27, 91, 59, 123,
  7, 71, 39, 103, 23, 87, 55, 119, 15, 79, 47, 111, 31, 95, 63, 127
};

void init_ntt() {
  unsigned int i, j, k;
  int16_t tmp[128];

  tmp[0] = MONT;
  for(i = 1; i < 128; ++i)
    tmp[i] = fqmul(tmp[i-1], ROOT_OF_UNITY % KYBER_Q);

  for(i = 0; i < 128; ++i)
    zetas[i] = tmp[tree[i]];

  k = 0;
  for(i = 64; i >= 1; i >>= 1)
    for(j = i; j < 2*i; ++j)
      zetas_inv[k++] = -tmp[128 - tree[j]];

  zetas_inv[127] = ((KYBER_Q - 1) * ((KYBER_Q - 1)/128) % KYBER_Q) % KYBER_Q;
}

*/

const int16_t zetas[128] = {
	1, 241, 64, 4, 249, 128, 2, 225, 136, 137, 223, 30, 197, 189, 15, 17,
	81, 246, 44, 67, 123, 88, 162, 235, 222, 46, 73, 117, 23, 146, 187, 92,
	9, 113, 62, 36, 185, 124, 18, 226, 196, 205, 208, 13, 231, 159, 135, 153,
	215, 158, 139, 89, 79, 21, 173, 59, 199, 157, 143, 25, 207, 29, 141, 57,
	3, 209, 192, 12, 233, 127, 6, 161, 151, 154, 155, 90, 77, 53, 45, 51,
	243, 224, 132, 201, 112, 7, 229, 191, 152, 138, 219, 94, 69, 181, 47, 19,
	27, 82, 186, 108, 41, 115, 54, 164, 74, 101, 110, 39, 179, 220, 148, 202,
	131, 217, 160, 10, 237, 63, 5, 177, 83, 214, 172, 75, 107, 87, 166, 171,
};
const int16_t zetas_inv[128] = {
	86, 91, 170, 150, 182, 85, 43, 174, 80, 252, 194, 20, 247, 97, 40, 126,
	55, 109, 37, 78, 218, 147, 156, 183, 93, 203, 142, 216, 149, 71, 175, 230,
	238, 210, 76, 188, 163, 38, 119, 105, 66, 28, 250, 145, 56, 125, 33, 14,
	206, 212, 204, 180, 167, 102, 103, 106, 96, 251, 130, 24, 245, 65, 48, 254,
	200, 116, 228, 50, 232, 114, 100, 58, 198, 84, 236, 178, 168, 118, 99, 42,
	104, 122, 98, 26, 244, 49, 52, 61, 31, 239, 133, 72, 221, 195, 144, 248,
	165, 70, 111, 234, 140, 184, 211, 35, 22, 95, 169, 134, 190, 213, 11, 176,
	240, 242, 68, 60, 227, 34, 120, 121, 32, 255, 129, 8, 253, 193, 16, 255,
};

/*************************************************
* Name:        fqmul
*
* Description: Multiplication followed by Montgomery reduction
*
* Arguments:   - int16_t a: first factor
*              - int16_t b: second factor
*
* Returns 16-bit integer congruent to a*b*R^{-1} mod q
**************************************************/
static int16_t fqmul(int16_t a, int16_t b) {
    return my_reduce((int32_t)a*b);
}

/*************************************************
* Name:        ntt
*
* Description: Inplace number-theoretic transform (NTT) in Rq
*              input is in standard order, output is in bitreversed order
*
* Arguments:   - int16_t r[256]: pointer to input/output vector of elements
*                                of Zq
**************************************************/
void ntt(int16_t r[RING_N]) {
  unsigned int len, start, j, k;
  int16_t t, zeta;

  k = 1;
  for(len = RING_NH; len >= RING_N0; len >>= 1) {
    for(start = 0; start < RING_N; start = j + len) {
      zeta = zetas[k++];
      for(j = start; j < start + len; ++j) {
        t = fqmul(zeta, r[j + len]);
        r[j + len] = r[j] - t;
        r[j] = r[j] + t;
      }
    }
  }
}

/*************************************************
* Name:        invntt_tomont
*
* Description: Inplace inverse number-theoretic transform in Rq and
*              multiplication by Montgomery factor 2^16.
*              Input is in bitreversed order, output is in standard order
*
* Arguments:   - int16_t r[256]: pointer to input/output vector of elements
*                                of Zq
**************************************************/
void invntt(int16_t r[RING_N]) {
  unsigned int start, len, j, k;
  int16_t t, zeta;

  k = 0;
  for(len = RING_N0; len <= RING_NH; len <<= 1) {
    for(start = 0; start < RING_N; start = j + len) {
      zeta = zetas_inv[k++];
      for(j = start; j < start + len; ++j) {
        t = r[j];
        r[j] = barrett_reduce(t + r[j + len]);
        r[j + len] = t - r[j + len];
        r[j + len] = fqmul(zeta, r[j + len]);
      }
    }
  }

  for(j = 0; j < RING_N; ++j)
    r[j] = fqmul(r[j], zetas_inv[127]);
}

/*************************************************
* Name:        basemul
*
* Description: Multiplication of polynomials in Zq[X]/(X^2-zeta)
*              used for multiplication of elements in Rq in NTT domain
*
* Arguments:   - int16_t r[2]:       pointer to the output polynomial
*              - const int16_t a[2]: pointer to the first factor
*              - const int16_t b[2]: pointer to the second factor
*              - int16_t zeta:       integer defining the reduction polynomial
**************************************************/
#if 1
static void mult_poly4(int16_t *r,
    const int16_t *a,
    const int16_t *b,
    int16_t zeta)
{
    int16_t prod[7] = { 0 };
    int16_t asum[2], bsum[2];
    int i;

    for (i = 0; i < 2; i++) {
        asum[i] = a[2 * i] + a[2 * i + 1];
        bsum[i] = b[2 * i] + b[2 * i + 1];
    }
    prod[2] = fqmul(a[1], b[1]);
    prod[0] = fqmul(a[0], b[0]);
    prod[1] = fqmul(asum[0], bsum[0]);
    prod[1] = prod[1] - prod[0] - prod[2];

    prod[6] = fqmul(a[3], b[3]);
    prod[4] = fqmul(a[2], b[2]);
    prod[5] = fqmul(asum[1], bsum[1]);
    prod[5] = prod[5] - prod[6] - prod[4];

    for (i = 0; i < 2; i++) {
        asum[i] = a[i] + a[i + 2];
        bsum[i] = b[i] + b[i + 2];
    }

    r[2] = fqmul(asum[1], bsum[1]);
    r[0] = fqmul(asum[0], bsum[0]);
    asum[0] += asum[1];
    bsum[0] += bsum[1];
    r[1] = fqmul(asum[0], bsum[0]);
    r[1] = r[1] - r[0] - r[2];

    r[0] = r[0] - prod[0] - prod[4]; // reduce ?
    r[1] = r[1] - prod[1] - prod[5];
    r[2] = r[2] - prod[2] - prod[6];

    prod[2] += r[0];
    prod[4] += r[2];
    r[3] = r[1];

    r[0] = prod[0] + fqmul(prod[4], zeta);
    r[1] = prod[1] + fqmul(prod[5], zeta);
    r[2] = prod[2] + fqmul(prod[6], zeta);

    return;
}
#else 
static void mult_poly4(int16_t *r,
	const int16_t *a,
	const int16_t *b,
	int16_t zeta)
{
	int16_t buf[(KYBER_N0 << 1)-1] = { 0 }; // 7
	buf[0] = fqmul(a[0], b[0]);
	buf[1] = fqmul(a[1], b[0]);
	buf[1] += fqmul(a[0], b[1]);

	buf[2] = fqmul(a[2], b[0]);
	buf[2] += fqmul(a[1], b[1]);
	buf[2] += fqmul(a[0], b[2]);

	buf[3] = fqmul(a[3], b[0]);
	buf[3] += fqmul(a[2], b[1]);
	buf[3] += fqmul(a[1], b[2]);
	buf[3] += fqmul(a[0], b[3]);

	buf[4] = fqmul(a[3], b[1]);
	buf[4] += fqmul(a[2], b[2]);
	buf[4] += fqmul(a[1], b[3]);

	buf[5] = fqmul(a[3], b[2]);
	buf[5] += fqmul(a[2], b[3]);

	buf[6] = fqmul(a[3], b[3]);

	r[0] = buf[4];
	r[0] = fqmul(r[0], zeta);
	r[0] += buf[0];

	r[1] = buf[5];
	r[1] = fqmul(r[1], zeta);
	r[1] += buf[1];

	r[2] = buf[6];
	r[2] = fqmul(r[2], zeta);
	r[2] += buf[2];

	r[3] = buf[3];

	return;
}

#endif
void basemul(int16_t r[RING_N0],
             const int16_t a[RING_N0],
             const int16_t b[RING_N0],
             int16_t zeta)
{
	/* (KYBER_N0 == 4) */
	mult_poly4(r, a, b, zeta);
}
