#include "poly.h"
#include "ntt.h"
#include "reduce.h"
#include "fips202.h"

/*************************************************
* Name:        coeff_freeze
* 
* Description: Fully reduces an integer modulo q in constant time
*
* Arguments:   uint16_t x: input integer to be reduced
*              
* Returns integer in {0,...,q-1} congruent to x modulo q
**************************************************/
static uint16_t coeff_freeze(uint16_t x)
{
#if 1
  uint16_t m,r;
  int16_t c;
  r = x % RING_Q;

  m = r - RING_Q;
  c = m;
  c >>= 15;
  r = m ^ ((r^m)&c);

  return r;
#else
	return barrett_reduce(x);
#endif
}

/*************************************************
* Name:        flipabs
* 
* Description: Computes |(x mod q) - Q/2|
*
* Arguments:   uint16_t x: input coefficient
*              
* Returns |(x mod q) - Q/2|
**************************************************/
static uint16_t flipabs(uint16_t x)
{
  int16_t r,m;
  r = coeff_freeze(x);

  r = r - RING_Q/2;
  m = r >> 15;
  return (r + m) ^ m;
}


/*************************************************
* Name:        poly_frombytes
*
* Description: De-serialization of a polynomial
*
* Arguments:   - poly *r:                pointer to output polynomial
*              - const unsigned char *a: pointer to input byte array
**************************************************/
void poly_frombytes(poly *r, const unsigned char *a)
{
    int i, j;
    uint16_t tmp;
    for (i = 0; i < RING_N / 8; i++)
    {
        tmp = a[9 * i];
        for (j = 0; j < 8; j++) {
            r->coeffs[8 * i + j] = ((tmp & 1) << 8) | a[9 * i + j + 1];
            tmp >>= 1;
        }
    }
}

/*************************************************
* Name:        poly_tobytes
*
* Description: Serialization of a polynomial
*
* Arguments:   - unsigned char *r: pointer to output byte array
*              - const poly *p:    pointer to input polynomial
**************************************************/
void poly_tobytes(unsigned char *r, const poly *p)
{ // 8 coeff --> 9 byte
    int i, j, k;
    uint16_t t[8];
    uint8_t tmp;
    for (i = 0; i < RING_N / 8; i++)
    {
        tmp = 0;
        for (j = 0; j < 8; j++) {
            t[j] = coeff_freeze(p->coeffs[8 * i + j]);
            tmp |= ((t[j] & 0x100) >> ( 8 - j ));
        }
        r[9 * i] = tmp;
        for (k = 1; k < 9; k++) {
            r[9 * i + k] = (uint8_t) t[k-1];
        }
    }
}

#ifdef MY_COMPRESS
/*************************************************
* Name:        poly_compress
*
* Description: Compression and subsequent serialization of a polynomial
*
* Arguments:   - unsigned char *r: pointer to output byte array
*              - const poly *p:    pointer to input polynomial
**************************************************/
void poly_compress(unsigned char *r, const poly *p)
{ // preserve higher 5 bits from total 9 bits
    unsigned int i, j, k = 0;

    uint32_t t[8];

    for (i = 0; i < RING_N; i += 8)
    {
        for (j = 0; j < 8; j++)
        {
            t[j] = coeff_freeze(p->coeffs[i + j]);
            t[j] = (((t[j] << 5) + RING_Q / 2) / RING_Q) & 0x1f;
        }
        r[k] = t[0] | (t[1] << 5); // 5 +(3
        r[k + 1] = (t[1] >> 3) | (t[2] << 2) | (t[3] << 7); // 2)+ 5 +(1
        r[k + 2] = (t[3] >> 1) | (t[4] << 4);               // 4)+(4
        r[k + 3] = (t[4] >> 4) | (t[5] << 1) | (t[6] << 6); // 1)+ 5 +(2
        r[k + 4] = (t[6] >> 2) | (t[7] << 3);               // 3)+ 5
        k += 5;
    }
}

/*************************************************
* Name:        poly_decompress
*
* Description: De-serialization and subsequent decompression of a polynomial;
*              approximate inverse of poly_compress
*
* Arguments:   - poly *r:                pointer to output polynomial
*              - const unsigned char *a: pointer to input byte array
**************************************************/
void poly_decompress(poly *r, const unsigned char *a)
{
    unsigned int i, j;
    for (i = 0; i < RING_N; i += 8)
    {
        r->coeffs[i + 0] = a[0] & 0x1f; // 5
        r->coeffs[i + 1] = (a[0] >> 5) | ((a[1] & 0x3) << 3); // 3)+(2
        r->coeffs[i + 2] = (a[1] >> 2) & 0x1f; // 5
        r->coeffs[i + 3] = (a[1] >> 7) | ((a[2] & 0xf) << 1); // 1)+(4
        r->coeffs[i + 4] = (a[2] >> 4) | ((a[3] & 0x1) << 4); // 4)+(1
        r->coeffs[i + 5] = (a[3] >> 1) & 0x1f; // 5
        r->coeffs[i + 6] = (a[3] >> 6) | ((a[4] & 0x7) << 2); // 2)+(3
        r->coeffs[i + 7] = (a[4] >> 3) & 0x1f; // 5
        a += 5;
        for (j = 0; j < 8; j++) {
            r->coeffs[i + j] = ((uint32_t)r->coeffs[i + j] * RING_Q + 16) >> 5; // 2^r/2 = 16, r = 5
        }
    }
}

#endif

/*************************************************
* Name:        poly_frommsg
* 
* Description: Convert 32-byte message to polynomial
*
* Arguments:   - poly *r:                  pointer to output polynomial
*              - const unsigned char *msg: pointer to input message
**************************************************/
void poly_frommsg(poly *r, const unsigned char *msg)
{
  unsigned int i,j,mask;
  for(i=0;i<32;i++) // XXX: MACRO for 32
  {
    for(j=0;j<8;j++)
    {
      mask = -((msg[i] >> j)&1);
      r->coeffs[8*i+j+  0] = mask & (RING_Q/2);
      r->coeffs[8*i+j+256] = mask & (RING_Q/2);
#if (RING_N == 1024)
      r->coeffs[8*i+j+512] = mask & (RING_Q/2);
      r->coeffs[8*i+j+768] = mask & (RING_Q/2);
#endif
    }
  }
}

/*************************************************
* Name:        poly_tomsg
* 
* Description: Convert polynomial to 32-byte message
*
* Arguments:   - unsigned char *msg: pointer to output message
*              - const poly *x:      pointer to input polynomial
**************************************************/
void poly_tomsg(unsigned char *msg, const poly *x)
{
  unsigned int i;
  uint16_t t;

  for(i=0;i<32;i++)
    msg[i] = 0;

  for(i=0;i<256;i++)
  {
    t  = flipabs(x->coeffs[i+  0]);
    t += flipabs(x->coeffs[i+256]);
    t = ((t - RING_Q/2));

    t >>= 15;
    msg[i>>3] |= t<<(i&7);
  }
}
 
/*************************************************
* Name:        poly_uniform
* 
* Description: Sample a polynomial deterministically from a seed,
*              with output polynomial looking uniformly random
*
* Arguments:   - poly *a:                   pointer to output polynomial
*              - const unsigned char *seed: pointer to input seed
**************************************************/
void poly_uniform(poly *a, const unsigned char *seed)
{
  unsigned int ctr, pos;
  uint16_t val0, val1;
  shake128ctx state;
  uint8_t buf[SHAKE128_RATE];
  uint8_t extseed[RNDBYTES_LEN+1];
  int i;

  for(i=0;i<RNDBYTES_LEN;i++)
    extseed[i] = seed[i];

  for(i=0;i<RING_N/64;i++) /* generate a in blocks of 64 coefficients */
  {
    ctr = 0;
    extseed[RNDBYTES_LEN] = i; /* domain-separate the 16 independent calls */
    shake128_absorb(&state, extseed, RNDBYTES_LEN+1);
    while(ctr < 64) /* Very unlikely to run more than once */
    {
      shake128_squeezeblocks(buf,1,&state);
      pos = 0;
      while(ctr < 64 && pos < SHAKE128_RATE)
      {
          val0 = (buf[pos] | ((uint16_t)buf[pos + 1] << 8)) & 0x3FF; // 10 bits = 8 + 2
          val1 = (buf[pos + 1] >> 2 | ((uint16_t)buf[pos + 2] << 6)) & 0x3FF; // 6 + 4
          pos += 3;

        if(val0 < 3 * RING_Q)
        {
          a->coeffs[i * 64 + ctr] = val0;
          ctr++;
        }
        if (ctr < 64 && val1 < 3 * RING_Q)
        {
            a->coeffs[i * 64 + ctr] = val1;
            ctr++;
        }
      }
    }
  }
}

/* ====================  FROM Kyber - poly.c ========================================= */

/*************************************************
* Name:        poly_basemul_montgomery
*
* Description: Multiplication of two polynomials in NTT domain
*
* Arguments:   - poly *r:       pointer to output polynomial
*              - const poly *a: pointer to first input polynomial
*              - const poly *b: pointer to second input polynomial
**************************************************/
void poly_mul_pointwise(poly *r, const poly *a, const poly *b)
{
    unsigned int i;
    for (i = 0; i < RING_N / 8; i++) {
        basemul(&r->coeffs[8 * i], &a->coeffs[8 * i], &b->coeffs[8 * i], zetas[64 + i]);
        basemul(&r->coeffs[8 * i + 4], &a->coeffs[8 * i + 4], &b->coeffs[8 * i + 4],
            -zetas[64 + i]);
    }
    poly_reduce(r);
}

static uint32_t load32_littleendian(const uint8_t x[4])
{
	uint32_t r;
	r = (uint32_t)x[0];
	r |= (uint32_t)x[1] << 8;
	r |= (uint32_t)x[2] << 16;
	r |= (uint32_t)x[3] << 24;
	return r;
}
static void cbd1(poly *r, const uint8_t buf[2*RING_N / 8]){ /* 2*RING_N / 8  */
	unsigned int i, j;
	uint32_t t;
	int16_t a, b;

	for (i = 0; i < RING_N / 16; i++) {
		t = load32_littleendian(buf + 4 * i);

        for (j = 0; j < 16; j++) {
            a = (t >> (2 * j + 0)) & 0x1;
            b = (t >> (2 * j + 1)) & 0x1;
            r->coeffs[16 * i + j] = a - b;
        }
	}
}

/*************************************************
* Name:        poly_getnoise_eta1
*
* Description: Sample a polynomial deterministically from a seed and a nonce,
*              with output polynomial close to centered binomial distribution
*              with parameter KYBER_ETA1
*
* Arguments:   - poly *r:             pointer to output polynomial
*              - const uint8_t *seed: pointer to input seed
*                                     (of length KYBER_SYMBYTES bytes)
*              - uint8_t nonce:       one-byte input nonce
**************************************************/
void poly_sample(poly *r, const uint8_t seed[RNDBYTES_LEN], uint8_t nonce)
{
	uint8_t buf[2 * RING_N / 8];
	uint8_t extseed[RNDBYTES_LEN + 2];
	for(int i = 0; i < RNDBYTES_LEN; i++) {
		extseed[i] = seed[i];
	}
	extseed[RNDBYTES_LEN] = nonce;
	extseed[RNDBYTES_LEN + 1] = 1;
	shake256(buf, sizeof(buf), extseed, RNDBYTES_LEN + 2);
	cbd1(r, buf);
}

/*************************************************
* Name:        poly_add
*
* Description: Add two polynomials
*
* Arguments: - poly *r:       pointer to output polynomial
*            - const poly *a: pointer to first input polynomial
*            - const poly *b: pointer to second input polynomial
**************************************************/
void poly_add(poly *r, const poly *a, const poly *b)
{
	unsigned int i;
	for (i = 0; i < RING_N; i++)
		r->coeffs[i] = a->coeffs[i] + b->coeffs[i];
}

/*************************************************
* Name:        poly_sub
*
* Description: Subtract two polynomials
*
* Arguments: - poly *r:       pointer to output polynomial
*            - const poly *a: pointer to first input polynomial
*            - const poly *b: pointer to second input polynomial
**************************************************/
void poly_sub(poly *r, const poly *a, const poly *b)
{
	unsigned int i;
	for (i = 0; i < RING_N; i++)
		r->coeffs[i] = a->coeffs[i] - b->coeffs[i];
}

/*************************************************
* Name:        poly_reduce
*
* Description: Applies Barrett reduction to all coefficients of a polynomial
*              for details of the Barrett reduction see comments in reduce.c
*
* Arguments:   - poly *r: pointer to input/output polynomial
**************************************************/
void poly_reduce(poly *r)
{
	unsigned int i;
	for (i = 0; i < RING_N; i++)
		r->coeffs[i] = barrett_reduce(r->coeffs[i]);
}

/*************************************************
* Name:        poly_ntt
*
* Description: Computes negacyclic number-theoretic transform (NTT) of
*              a polynomial in place;
*              inputs assumed to be in normal order, output in bitreversed order
*
* Arguments:   - uint16_t *r: pointer to in/output polynomial
**************************************************/
void poly_ntt(poly *r)
{
	ntt(r->coeffs);
	poly_reduce(r);
}

/*************************************************
* Name:        poly_invntt_tomont
*
* Description: Computes inverse of negacyclic number-theoretic transform (NTT)
*              of a polynomial in place;
*              inputs assumed to be in bitreversed order, output in normal order
*
* Arguments:   - uint16_t *a: pointer to in/output polynomial
**************************************************/
void poly_invntt(poly *r)
{
	invntt(r->coeffs);
}

