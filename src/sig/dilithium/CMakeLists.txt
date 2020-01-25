if(OQS_ENABLE_SIG_dilithium_2)
    set(SRCS sig_dilithium_2.c
             pqclean_dilithium2_avx2/fips202x4.c
             pqclean_dilithium2_avx2/nttconsts.c
             pqclean_dilithium2_avx2/packing.c
             pqclean_dilithium2_avx2/poly.c
             pqclean_dilithium2_avx2/polyvec.c
             pqclean_dilithium2_avx2/rejsample.c
             pqclean_dilithium2_avx2/rounding.c
             pqclean_dilithium2_avx2/sign.c
             pqclean_dilithium2_avx2/stream.c
             pqclean_dilithium2_avx2/invntt.S
             pqclean_dilithium2_avx2/ntt.S
             pqclean_dilithium2_avx2/pointwise.S
             pqclean_dilithium2_avx2/reduce.S)
endif()
if(OQS_ENABLE_SIG_dilithium_3)
    set(SRCS ${SRCS} sig_dilithium_3.c
                     pqclean_dilithium3_avx2/fips202x4.c
                     pqclean_dilithium3_avx2/nttconsts.c
                     pqclean_dilithium3_avx2/packing.c
                     pqclean_dilithium3_avx2/poly.c
                     pqclean_dilithium3_avx2/polyvec.c
                     pqclean_dilithium3_avx2/rejsample.c
                     pqclean_dilithium3_avx2/rounding.c
                     pqclean_dilithium3_avx2/sign.c
                     pqclean_dilithium3_avx2/stream.c
                     pqclean_dilithium3_avx2/invntt.S
                     pqclean_dilithium3_avx2/ntt.S
                     pqclean_dilithium3_avx2/pointwise.S
                     pqclean_dilithium3_avx2/reduce.S)
endif()
if(OQS_ENABLE_SIG_dilithium_4)
    set(SRCS ${SRCS} sig_dilithium_4.c
                     pqclean_dilithium4_avx2/fips202x4.c
                     pqclean_dilithium4_avx2/nttconsts.c
                     pqclean_dilithium4_avx2/packing.c
                     pqclean_dilithium4_avx2/poly.c
                     pqclean_dilithium4_avx2/polyvec.c
                     pqclean_dilithium4_avx2/rejsample.c
                     pqclean_dilithium4_avx2/rounding.c
                     pqclean_dilithium4_avx2/sign.c
                     pqclean_dilithium4_avx2/stream.c
                     pqclean_dilithium4_avx2/invntt.S
                     pqclean_dilithium4_avx2/ntt.S
                     pqclean_dilithium4_avx2/pointwise.S
                     pqclean_dilithium4_avx2/reduce.S)
endif()

add_library(dilithium OBJECT ${SRCS})
target_include_directories(dilithium PRIVATE ${PROJECT_SOURCE_DIR}/src/common/pqclean_shims)
target_include_directories(dilithium PRIVATE ${CMAKE_CURRENT_LIST_DIR}/pqclean_dilithium2_avx2)
target_include_directories(dilithium PRIVATE ${CMAKE_CURRENT_LIST_DIR}/pqclean_dilithium3_avx2)
target_include_directories(dilithium PRIVATE ${CMAKE_CURRENT_LIST_DIR}/pqclean_dilithium4_avx2)
