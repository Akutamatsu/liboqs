if(OQS_ENABLE_KEM_kyber_512)
    set(SRCS kem_kyber_512.c
             pqclean_kyber512_clean/cbd.c
             pqclean_kyber512_clean/indcpa.c
             pqclean_kyber512_clean/kem.c
             pqclean_kyber512_clean/ntt.c
             pqclean_kyber512_clean/poly.c
             pqclean_kyber512_clean/polyvec.c
             pqclean_kyber512_clean/reduce.c
             pqclean_kyber512_clean/verify.c
             pqclean_kyber512_clean/symmetric-fips202.c)
endif()
if(OQS_ENABLE_KEM_kyber_512_90s)
    set(SRCS ${SRCS} kem_kyber_512_90s.c
             pqclean_kyber512-90s_avx2/aes256ctr.c
             pqclean_kyber512-90s_avx2/cbd.c
             pqclean_kyber512-90s_avx2/consts.c
             pqclean_kyber512-90s_avx2/indcpa.c
             pqclean_kyber512-90s_avx2/kem.c
             pqclean_kyber512-90s_avx2/poly.c
             pqclean_kyber512-90s_avx2/polyvec.c
             pqclean_kyber512-90s_avx2/rejsample.c
             pqclean_kyber512-90s_avx2/verify.c
             pqclean_kyber512-90s_avx2/basemul.S
             pqclean_kyber512-90s_avx2/fq.s
             pqclean_kyber512-90s_avx2/invntt.s
             pqclean_kyber512-90s_avx2/ntt.s
             pqclean_kyber512-90s_avx2/shuffle.s)
endif()
if(OQS_ENABLE_KEM_kyber_768)
    set(SRCS ${SRCS} kem_kyber_768.c
                     pqclean_kyber768_clean/cbd.c
                     pqclean_kyber768_clean/indcpa.c
                     pqclean_kyber768_clean/kem.c
                     pqclean_kyber768_clean/ntt.c
                     pqclean_kyber768_clean/poly.c
                     pqclean_kyber768_clean/polyvec.c
                     pqclean_kyber768_clean/reduce.c
                     pqclean_kyber768_clean/verify.c
                     pqclean_kyber768_clean/symmetric-fips202.c)
endif()
if(OQS_ENABLE_KEM_kyber_768_90s)
    set(SRCS ${SRCS} kem_kyber_768_90s.c
                     pqclean_kyber768-90s_avx2/aes256ctr.c
                     pqclean_kyber768-90s_avx2/cbd.c
                     pqclean_kyber768-90s_avx2/consts.c
                     pqclean_kyber768-90s_avx2/indcpa.c
                     pqclean_kyber768-90s_avx2/kem.c
                     pqclean_kyber768-90s_avx2/poly.c
                     pqclean_kyber768-90s_avx2/polyvec.c
                     pqclean_kyber768-90s_avx2/rejsample.c
                     pqclean_kyber768-90s_avx2/verify.c
                     pqclean_kyber768-90s_avx2/basemul.S
                     pqclean_kyber768-90s_avx2/fq.s
                     pqclean_kyber768-90s_avx2/invntt.s
                     pqclean_kyber768-90s_avx2/ntt.s
                     pqclean_kyber768-90s_avx2/shuffle.s)
endif()
if(OQS_ENABLE_KEM_kyber_1024)
    set(SRCS ${SRCS} kem_kyber_1024.c
                     pqclean_kyber1024_clean/cbd.c
                     pqclean_kyber1024_clean/indcpa.c
                     pqclean_kyber1024_clean/kem.c
                     pqclean_kyber1024_clean/ntt.c
                     pqclean_kyber1024_clean/poly.c
                     pqclean_kyber1024_clean/polyvec.c
                     pqclean_kyber1024_clean/reduce.c
                     pqclean_kyber1024_clean/verify.c
                     pqclean_kyber1024_clean/symmetric-fips202.c)
endif()
if(OQS_ENABLE_KEM_kyber_1024_90s)
    set(SRCS ${SRCS} kem_kyber_1024_90s.c
                     pqclean_kyber1024-90s_avx2/aes256ctr.c
                     pqclean_kyber1024-90s_avx2/cbd.c
                     pqclean_kyber1024-90s_avx2/consts.c
                     pqclean_kyber1024-90s_avx2/indcpa.c
                     pqclean_kyber1024-90s_avx2/kem.c
                     pqclean_kyber1024-90s_avx2/poly.c
                     pqclean_kyber1024-90s_avx2/polyvec.c
                     pqclean_kyber1024-90s_avx2/rejsample.c
                     pqclean_kyber1024-90s_avx2/verify.c
                     pqclean_kyber1024-90s_avx2/basemul.S
                     pqclean_kyber1024-90s_avx2/fq.s
                     pqclean_kyber1024-90s_avx2/invntt.s
                     pqclean_kyber1024-90s_avx2/ntt.s
                     pqclean_kyber1024-90s_avx2/shuffle.s)
endif()

add_library(kyber OBJECT ${SRCS})
target_include_directories(kyber PRIVATE ${PROJECT_SOURCE_DIR}/src/common/pqclean_shims)

# For assembly include files
target_include_directories(kyber PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/pqclean_kyber512-90s_avx2)
target_include_directories(kyber PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/pqclean_kyber768-90s_avx2)
target_include_directories(kyber PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/pqclean_kyber1024-90s_avx2)
