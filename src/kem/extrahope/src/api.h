#ifndef API_H
#define API_H

#include "params.h"

#define CRYPTO_SECRETKEYBYTES  CPAKEM_PRIV_LEN
#define CRYPTO_PUBLICKEYBYTES  CPAKEM_PUB_LEN
#define CRYPTO_CIPHERTEXTBYTES CPAKEM_CIPH_LEN
#define CRYPTO_BYTES           RNDBYTES_LEN

#define CRYPTO_ALGNAME "testHope512-CPAKEM"

int PQCLEAN_EXTRAHOPE512_CLEAN_crypto_kem_keypair(unsigned char *pk, unsigned char *sk);

int PQCLEAN_EXTRAHOPE512_CLEAN_crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);

int PQCLEAN_EXTRAHOPE512_CLEAN_crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);

#endif
