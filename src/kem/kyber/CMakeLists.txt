if(OQS_ENABLE_KEM_kyber_512_90s)
    set(SRCS kem_kyber_512_90s.c
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
