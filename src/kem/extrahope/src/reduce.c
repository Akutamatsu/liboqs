#include <stdint.h>
#include "params.h"
#include "reduce.h"

/*************************************************
* Name:        my_reduce
*
* Description: Montgomery reduction; given a product 'a' of two 16-bit integer,
*              computes 16-bit integer congruent to a mod q,
*              where q=257
*
* Arguments:   - int32_t a: input integer to be reduced;
*                           has to be in {-32768, ..., 32767}
*
* Returns:     integer in {-128, ..., 128} congruent to a mod q.
**************************************************/
int16_t my_reduce(int32_t a)
{
    uint16_t tmp;
    int16_t r;

    r = a & 0xff; // bitlen(r) = 8 
    tmp = (a >> 8); // tmp can be positive or negative
    r = r - tmp;

    return r;
}

/*************************************************
* Name:        barrett_reduce
*
* Description: Barrett reduction; given a 16-bit integer a, computes
*              16-bit integer congruent to a mod q in {0,...,q}
*
* Arguments:   - int16_t a: input integer to be reduced
*
* Returns:     integer in {0,...,q} congruent to a modulo q.
**************************************************/
int16_t barrett_reduce(int16_t a) {
  int16_t t;
  const int16_t v = ((1U << 18) + RING_Q/2)/RING_Q;

  t  = (int32_t)v*a >> 18;
  t *= RING_Q;
  return a - t;
}

/*************************************************
* Name:        csubq
*
* Description: Conditionallly subtract q
*
* Arguments:   - int16_t x: input integer
*
* Returns:     a - q if a >= q, else a
**************************************************/
int16_t csubq(int16_t a) {
  a -= RING_Q;
  a += (a >> 15) & RING_Q;
  return a;
}
