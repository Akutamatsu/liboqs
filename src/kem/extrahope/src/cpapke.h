#ifndef INDCPA_H
#define INDCPA_H

#define EXHOPE_POLYBYTES            576 //((9*512)/8)
#define EXHOPE_POLYCOMPRESSEDBYTES  320 //(( 5*EXHOPE_N)/8)

#define EXHOPE_CPAPKE_PUBLICKEYBYTES  608 //(EXHOPE_POLYBYTES + 32)
#define EXHOPE_CPAPKE_SECRETKEYBYTES  576 //(EXHOPE_POLYBYTES)
#define EXHOPE_CPAPKE_CIPHERTEXTBYTES 890 //(EXHOPE_POLYBYTES + EXHOPE_POLYCOMPRESSEDBYTES)

int PQCLEAN_EXTRAHOPE512_CLEAN_cpapke_keypair(unsigned char *pk, 
                    unsigned char *sk);

int PQCLEAN_EXTRAHOPE512_CLEAN_cpapke_enc(unsigned char *c,
               const unsigned char *m,
               const unsigned char *pk,
               const unsigned char *coins);

int PQCLEAN_EXTRAHOPE512_CLEAN_cpapke_dec(unsigned char *m,
               const unsigned char *c,
               const unsigned char *sk);

#endif
