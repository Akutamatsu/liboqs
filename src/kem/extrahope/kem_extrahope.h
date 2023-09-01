#ifndef _OQS_KEM_EXTRAHOPE_H
#define _OQS_KEM_EXTRAHOPE_H

#include <oqs/oqs.h>

#if 0
#define NEWHOPE_POLYBYTES            576 //((9*512)/8)
#define NEWHOPE_POLYCOMPRESSEDBYTES  320 //(( 5*NEWHOPE_N)/8)

#define NEWHOPE_CPAPKE_PUBLICKEYBYTES  608 //(NEWHOPE_POLYBYTES + 32)
#define NEWHOPE_CPAPKE_SECRETKEYBYTES  576 //(NEWHOPE_POLYBYTES)
#define NEWHOPE_CPAPKE_CIPHERTEXTBYTES 890 //(NEWHOPE_POLYBYTES + NEWHOPE_POLYCOMPRESSEDBYTES)

#define NEWHOPE_CCAKEM_PUBLICKEYBYTES 608
#define NEWHOPE_CCAKEM_SECRETKEYBYTES 1248
#define NEWHOPE_CCAKEM_CIPHERTEXTBYTES 922
/* for Targhi-Unruh */
#endif

#ifdef OQS_ENABLE_KEM_extrahope512
#define OQS_KEM_extrahope512_length_public_key 608
#define OQS_KEM_extrahope512_length_secret_key 1248
#define OQS_KEM_extrahope512_length_ciphertext 922
#define OQS_KEM_extrahope512_length_shared_secret 32
OQS_KEM *OQS_KEM_extrahope512_new(void);
OQS_API OQS_STATUS OQS_KEM_extrahope512_keypair(uint8_t *public_key, uint8_t *secret_key);
OQS_API OQS_STATUS OQS_KEM_extrahope512_encaps(uint8_t *ciphertext, uint8_t *shared_secret, const uint8_t *public_key);
OQS_API OQS_STATUS OQS_KEM_extrahope512_decaps(uint8_t *shared_secret, const unsigned char *ciphertext, const uint8_t *secret_key);
#endif

#endif
