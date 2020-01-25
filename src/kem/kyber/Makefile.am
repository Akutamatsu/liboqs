AUTOMAKE_OPTIONS = foreign
noinst_LTLIBRARIES  = libkemkyber.la
noinst_LTLIBRARIES += libkemkyber_512_90s.la libkemkyber_768_90s.la libkemkyber_1024_90s.la 

libkemkyber_la_LIBADD  = libkemkyber_512_90s.la libkemkyber_768_90s.la libkemkyber_1024_90s.la 
libkemkyber_la_SOURCES = 

libkemkyber_512_90s_la_SOURCES = kem_kyber_512_90s.c pqclean_kyber512-90s_clean/aes256ctr.c pqclean_kyber512-90s_clean/cbd.c pqclean_kyber512-90s_clean/indcpa.c pqclean_kyber512-90s_clean/kem.c pqclean_kyber512-90s_clean/ntt.c pqclean_kyber512-90s_clean/poly.c pqclean_kyber512-90s_clean/polyvec.c pqclean_kyber512-90s_clean/reduce.c pqclean_kyber512-90s_clean/verify.c 
libkemkyber_512_90s_la_CFLAGS  = $(AM_CFLAGS) -I../../common/pqclean_shims

libkemkyber_768_90s_la_SOURCES = kem_kyber_768_90s.c pqclean_kyber768-90s_clean/aes256ctr.c pqclean_kyber768-90s_clean/cbd.c pqclean_kyber768-90s_clean/indcpa.c pqclean_kyber768-90s_clean/kem.c pqclean_kyber768-90s_clean/ntt.c pqclean_kyber768-90s_clean/poly.c pqclean_kyber768-90s_clean/polyvec.c pqclean_kyber768-90s_clean/reduce.c pqclean_kyber768-90s_clean/verify.c 
libkemkyber_768_90s_la_CFLAGS  = $(AM_CFLAGS) -I../../common/pqclean_shims

libkemkyber_1024_90s_la_SOURCES = kem_kyber_1024_90s.c pqclean_kyber1024-90s_clean/aes256ctr.c pqclean_kyber1024-90s_clean/cbd.c pqclean_kyber1024-90s_clean/indcpa.c pqclean_kyber1024-90s_clean/kem.c pqclean_kyber1024-90s_clean/ntt.c pqclean_kyber1024-90s_clean/poly.c pqclean_kyber1024-90s_clean/polyvec.c pqclean_kyber1024-90s_clean/reduce.c pqclean_kyber1024-90s_clean/verify.c 
libkemkyber_1024_90s_la_CFLAGS  = $(AM_CFLAGS) -I../../common/pqclean_shims

