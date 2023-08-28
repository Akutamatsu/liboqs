#ifndef INDCPA_H
#define INDCPA_H

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
