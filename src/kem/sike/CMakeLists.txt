set(SRCS kem_sike.c
         P434/P434.c
         P434/P434_compressed.c
         P503/P503.c P503/P503_compressed.c
         P610/P610.c
         P610/P610_compressed.c
         P751/P751.c
         P751/P751_compressed.c)

if(${ARCH} STREQUAL "x86")
    add_compile_definitions(_GENERIC_ _X86_)
elseif(${ARCH} STREQUAL "x86_64")
    add_compile_definitions(_AMD64_)
    if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
        set(SRCS ${SRCS} P503/AMD64/fp_x64_asm.S
                         P751/AMD64/fp_x64_asm.S)
        if(USE_BMI2_INSTRUCTIONS)
            add_compile_definitions(_MULX_ _ADX_)
            set(SRCS ${SRCS} P434/AMD64/fp_x64_asm.S
                             P610/AMD64/fp_x64_asm.S)
    endif()
endif()
elseif(${ARCH} STREQUAL "arm")
    add_compile_definitions(_GENERIC_ _ARM_)
elseif(${ARCH} STREQUAL "arm64")
    add_compile_definitions(_ARM64_)
    if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
        set(SRCS ${SRCS} P503/AMD64/fp_x64_asm.S
                         P751/AMD64/fp_x64_asm.S)
    endif()
endif()


add_library(sike OBJECT ${SRCS})
