if(OQS_ENABLE_KEM_saber_lightsaber)
    set(SRCS kem_saber_lightsaber.c
             pqclean_lightsaber_clean/cbd.c
             pqclean_lightsaber_clean/kem.c
             pqclean_lightsaber_clean/pack_unpack.c
             pqclean_lightsaber_clean/poly.c
             pqclean_lightsaber_clean/poly_mul.c
             pqclean_lightsaber_clean/SABER_indcpa.c
             pqclean_lightsaber_clean/verify.c)
endif()
if(OQS_ENABLE_KEM_saber_saber)
    set(SRCS ${SRCS} kem_saber_saber.c
                     pqclean_saber_clean/cbd.c
                     pqclean_saber_clean/kem.c
                     pqclean_saber_clean/pack_unpack.c
                     pqclean_saber_clean/poly.c
                     pqclean_saber_clean/poly_mul.c
                     pqclean_saber_clean/SABER_indcpa.c
                     pqclean_saber_clean/verify.c)
endif()

if(OQS_ENABLE_KEM_saber_firesaber)
    set(SRCS ${SRCS} kem_saber_firesaber.c
                     pqclean_firesaber_clean/cbd.c
                     pqclean_firesaber_clean/kem.c
                     pqclean_firesaber_clean/pack_unpack.c
                     pqclean_firesaber_clean/poly.c
                     pqclean_firesaber_clean/poly_mul.c
                     pqclean_firesaber_clean/SABER_indcpa.c
                     pqclean_firesaber_clean/verify.c)
endif()

add_library(saber OBJECT ${SRCS})
target_include_directories(saber PRIVATE ${PROJECT_SOURCE_DIR}/src/common/pqclean_shims)
