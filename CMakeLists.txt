cmake_minimum_required (VERSION 3.6)

project(liboqs C ASM)
set(OQS_VERSION_TEXT "0.2.1-dev")
set(OQS_COMPILE_BUILD_TARGET "${CMAKE_SYSTEM_PROCESSOR}-${CMAKE_HOST_SYSTEM}")

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
if(CMAKE_C_COMPILER_ID STREQUAL "GNU" OR
   CMAKE_C_COMPILER_ID STREQUAL "Clang" OR
   CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fvisibility=hidden -Wall -Wextra -O3")
endif()
if(CMAKE_C_COMPILER_ID STREQUAL "Clang" OR
   CMAKE_C_COMPILER_ID STREQUAL "AppleClang")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fcolor-diagnostics -Wno-missing-braces")
endif()
if(BUILD_SHARED_LIBS)
  set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)
endif()

include(config/cpu-extensions.cmake)
include(config/alg-support.cmake)

if(USE_OPENSSL)
    if(NOT DEFINED OPENSSL_ROOT_DIR)
        if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Darwin")
            set(OPENSSL_ROOT_DIR "/usr/local/opt/openssl@1.1")
        elseif(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
            set(OPENSSL_ROOT_DIR "/usr")
        endif()
    endif()
    find_package(OpenSSL REQUIRED)
endif()

set(PUBLIC_HEADERS ${PROJECT_SOURCE_DIR}/src/oqs.h
            ${PROJECT_SOURCE_DIR}/src/common/common.h
            ${PROJECT_SOURCE_DIR}/src/common/rand.h
            ${PROJECT_SOURCE_DIR}/src/crypto/aes/aes.h
            ${PROJECT_SOURCE_DIR}/src/crypto/sha2/sha2.h
            ${PROJECT_SOURCE_DIR}/src/crypto/sha3/sha3.h
            ${PROJECT_SOURCE_DIR}/src/kem/kem.h
            ${PROJECT_SOURCE_DIR}/src/sig/sig.h)

if(ENABLE_KEM_BIKE)
    set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_SOURCE_DIR}/src/kem/bike/kem_bike.h)
endif()

if(ENABLE_KEM_EXTRAHOPE)
    set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_SOURCE_DIR}/src/kem/extrahope/kem_extrahope.h)
endif()
if(ENABLE_KEM_FRODOKEM)
    set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_SOURCE_DIR}/src/kem/frodokem/kem_frodokem.h)
endif()
if(ENABLE_KEM_KYBER)
    set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_SOURCE_DIR}/src/kem/kyber/kem_kyber.h)
endif()
if(ENABLE_KEM_NEWHOPE)
    set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_SOURCE_DIR}/src/kem/newhope/kem_newhope.h)
endif()
if(ENABLE_KEM_NTRU)
    set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_SOURCE_DIR}/src/kem/ntru/kem_ntru.h)
endif()
if(ENABLE_KEM_SABER)
    set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_SOURCE_DIR}/src/kem/saber/kem_saber.h)
endif()
if(ENABLE_KEM_SIKE OR ENABLE_KEM_SIDH)
    set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_SOURCE_DIR}/src/kem/sike/kem_sike.h)
endif()

if(ENABLE_SIG_DILITHIUM)
    set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_SOURCE_DIR}/src/sig/dilithium/sig_dilithium.h)
endif()
if(ENABLE_SIG_MQDSS)
    set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_SOURCE_DIR}/src/sig/mqdss/sig_mqdss.h)
endif()
if(ENABLE_SIG_PICNIC)
    set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_SOURCE_DIR}/src/sig/picnic/sig_picnic.h)
endif()
if(ENABLE_SIG_QTESLA)
    set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_SOURCE_DIR}/src/sig/qtesla/sig_qtesla.h)
endif()
if(ENABLE_SIG_SPHINCS)
    set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_SOURCE_DIR}/src/sig/sphincs/sig_sphincs.h)
endif()
execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_BINARY_DIR}/include/oqs)
execute_process(COMMAND ${CMAKE_COMMAND} -E copy ${PUBLIC_HEADERS} ${PROJECT_BINARY_DIR}/include/oqs)
configure_file(oqsconfig.h.cmake ${PROJECT_BINARY_DIR}/include/oqs/oqsconfig.h)
set(PUBLIC_HEADERS ${PUBLIC_HEADERS} ${PROJECT_BINARY_DIR}/include/oqs/oqsconfig.h)

include_directories(${PROJECT_BINARY_DIR}/include)
add_subdirectory(src)

add_subdirectory(tests)

find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOXYFILE ${PROJECT_SOURCE_DIR}/docs/.Doxyfile)
    add_custom_target(
        gen_docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        COMMENT "Generate API documentation with Doxygen."
        USES_TERMINAL)
endif()
