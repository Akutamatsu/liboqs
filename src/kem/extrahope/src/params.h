#ifndef PARAMS_H
#define PARAMS_H

#define RING_N 512
#define RING_NH 256
#define RING_Q 257

#define RING_N0 4         /* degree of bottom poly mod */
#define ROOT_OF_UNITY 3

#define RNDBYTES_LEN 32   /* size in bytes of hashes, and seeds */

#define KYBER_SYMBYTES RNDBYTES_LEN

/* log q * n / 8 (bytes) */
#define POLYBYTES_LEN       ((9*RING_N)/8)

#define MY_COMPRESS
#define POLYBYTES_CMPR_LEN  ((5*RING_N)/8)

#define CPAKEM_PUB_LEN  (POLYBYTES_LEN + RNDBYTES_LEN)
#define CPAKEM_PRIV_LEN (POLYBYTES_LEN)
#define CPAKEM_CIPH_LEN (POLYBYTES_LEN + POLYBYTES_CMPR_LEN)

#define KYBER_NAMESPACE(s) pqclean_extrahope_ref##s

#endif
