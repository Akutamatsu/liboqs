#ifndef _OQS_KEM_EXTRAHOPE_H
#define _OQS_KEM_EXTRAHOPE_H

#include <oqs/oqs.h>

#if 0
#define EXHOPE_POLYBYTES            576 //((9*512)/8)
#define EXHOPE_POLYCOMPRESSEDBYTES  320 //(( 5*EXHOPE_N)/8)

#define EXHOPE_CPAPKE_PUBLICKEYBYTES  608 //(EXHOPE_POLYBYTES + 32)
#define EXHOPE_CPAPKE_SECRETKEYBYTES  576 //(EXHOPE_POLYBYTES)
#define EXHOPE_CPAPKE_CIPHERTEXTBYTES 896 //(EXHOPE_POLYBYTES + EXHOPE_POLYCOMPRESSEDBYTES)

#define EXHOPE_CCAKEM_PUBLICKEYBYTES EXHOPE_CPAPKE_PUBLICKEYBYTES
#define EXHOPE_CCAKEM_SECRETKEYBYTES (EXHOPE_CPAPKE_SECRETKEYBYTES + EXHOPE_CPAPKE_PUBLICKEYBYTES)
#define EXHOPE_CCAKEM_CIPHERTEXTBYTES EXHOPE_CPAPKE_CIPHERTEXTBYTES
#endif

#ifdef OQS_ENABLE_KEM_extrahope_512
#define OQS_KEM_extrahope_512_length_public_key 608
#define OQS_KEM_extrahope_512_length_secret_key 1184
#define OQS_KEM_extrahope_512_length_ciphertext 896
#define OQS_KEM_extrahope_512_length_shared_secret 32
OQS_KEM *OQS_KEM_extrahope_512_new(void);
OQS_API OQS_STATUS OQS_KEM_extrahope_512_keypair(uint8_t *public_key, uint8_t *secret_key);
OQS_API OQS_STATUS OQS_KEM_extrahope_512_encaps(uint8_t *ciphertext, uint8_t *shared_secret, const uint8_t *public_key);
OQS_API OQS_STATUS OQS_KEM_extrahope_512_decaps(uint8_t *shared_secret, const unsigned char *ciphertext, const uint8_t *secret_key);
#endif

#endif
