if(ENABLE_KEM_EXTRAHOPE)
    set(SRCS kem_extrahope512.c
             src/cpapke.c
             src/kem.c
             src/ntt.c
             src/poly.c
             src/reduce.c)
endif()

add_library(extrahope OBJECT ${SRCS})
target_include_directories(extrahope PRIVATE ${PROJECT_SOURCE_DIR}/src/common/pqclean_shims)
