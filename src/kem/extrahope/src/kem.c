#include <string.h>
#include "api.h"
#include "cpapke.h"
#include "params.h"
#include "randombytes.h"
#include "fips202.h"

/*************************************************
* Name:        crypto_kem_keypair
*
* Description: Generates public and private key
*              for CCA secure NewHope key encapsulation
*              mechanism
*
* Arguments:   - unsigned char *pk: pointer to output public key (an already allocated array of CRYPTO_PUBLICKEYBYTES bytes)
*              - unsigned char *sk: pointer to output private key (an already allocated array of CRYPTO_SECRETKEYBYTES bytes)
*
* Returns 0 (success)
**************************************************/
int PQCLEAN_EXTRAHOPE512_CLEAN_crypto_kem_keypair(unsigned char *pk, unsigned char *sk)
{
    size_t i;
    PQCLEAN_EXTRAHOPE512_CLEAN_cpapke_keypair(pk, sk);/* First put the actual secret key into sk */
    for (i = 0; i < EXHOPE_CPAPKE_PUBLICKEYBYTES; i++) {
        sk[i + EXHOPE_CPAPKE_SECRETKEYBYTES] = pk[i];
    }
    /* No need for the re-encryption */
    /* No need for the value s for rejection */
    
    return 0;
}

/*************************************************
* Name:        crypto_kem_enc
*
* Description: Generates cipher text and shared
*              secret for given public key
*
* Arguments:   - unsigned char *ct:       pointer to output cipher text (an already allocated array of CRYPTO_CIPHERTEXTBYTES bytes)
*              - unsigned char *ss:       pointer to output shared secret (an already allocated array of CRYPTO_BYTES bytes)
*              - const unsigned char *pk: pointer to input public key (an already allocated array of CRYPTO_PUBLICKEYBYTES bytes)
*
* Returns 0 (success)
**************************************************/
int PQCLEAN_EXTRAHOPE512_CLEAN_crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk)
{
  unsigned char buf[2*RNDBYTES_LEN];
  shake256incctx state;
  
  randombytes(buf,RNDBYTES_LEN);
  shake256(buf,2*RNDBYTES_LEN,buf,RNDBYTES_LEN);  /* Don't release system RNG output */

  PQCLEAN_EXTRAHOPE512_CLEAN_cpapke_enc(ct, buf, pk, buf+RNDBYTES_LEN); /* coins are in buf+NEWHOPE_SYMBYTES */
  
  shake256_inc_init(&state);
  shake256_inc_absorb(&state, buf, RNDBYTES_LEN);
  shake256_inc_absorb(&state, ct, EXHOPE_CPAPKE_CIPHERTEXTBYTES);
  shake256_inc_finalize(&state);
  
  shake256_inc_squeeze(ss, CRYPTO_BYTES, &state);  /* hash concatenation of plaintext and ciph to ss */
  return 0;
}

// void shake256_inc_init(shake256incctx *state);
// void shake256_inc_absorb(shake256incctx *state, const uint8_t *input, size_t inlen);
// void shake256_inc_finalize(shake256incctx *state);
// void shake256_inc_squeeze(uint8_t *output, size_t outlen, shake256incctx *state);

/*************************************************
* Name:        crypto_kem_dec
*
* Description: Generates shared secret for given
*              cipher text and private key
*
* Arguments:   - unsigned char *ss:       pointer to output shared secret (an already allocated array of CRYPTO_BYTES bytes)
*              - const unsigned char *ct: pointer to input cipher text (an already allocated array of CRYPTO_CIPHERTEXTBYTES bytes)
*              - const unsigned char *sk: pointer to input private key (an already allocated array of CRYPTO_SECRETKEYBYTES bytes)
*
* Returns 0 (success)
**************************************************/
int PQCLEAN_EXTRAHOPE512_CLEAN_crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk)
{
  shake256incctx state;
  PQCLEAN_EXTRAHOPE512_CLEAN_cpapke_dec(ss, ct, sk);

  shake256_inc_init(&state);
  shake256_inc_absorb(&state, ss, RNDBYTES_LEN);
  shake256_inc_absorb(&state, ct, EXHOPE_CPAPKE_CIPHERTEXTBYTES);
  shake256_inc_finalize(&state);
  
  shake256_inc_squeeze(ss, CRYPTO_BYTES, &state);  /* hash concatenation of plaintext and ciph to ss */

  return 0;
}
