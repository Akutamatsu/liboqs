add_subdirectory(common)
add_subdirectory(crypto)

if(ENABLE_KEM_BIKE)
    add_subdirectory(kem/bike)
    set(KEM_OBJS ${BIKE_OBJS})
endif()

# MY CUSTOM ALG
if(ENABLE_KEM_EXTRAHOPE)
    add_subdirectory(kem/extrahope)
    set(KEM_OBJS ${KEM_OBJS} $<TARGET_OBJECTS:extrahope>)
endif()

if(ENABLE_KEM_FRODOKEM)
    add_subdirectory(kem/frodokem)
    set(KEM_OBJS ${KEM_OBJS} $<TARGET_OBJECTS:frodokem>)
endif()
if(ENABLE_KEM_KYBER)
    add_subdirectory(kem/kyber)
    set(KEM_OBJS ${KEM_OBJS} $<TARGET_OBJECTS:kyber>)
endif()
if(ENABLE_KEM_NEWHOPE)
    add_subdirectory(kem/newhope)
    set(KEM_OBJS ${KEM_OBJS} $<TARGET_OBJECTS:newhope>)
endif()
if(ENABLE_KEM_NTRU)
    add_subdirectory(kem/ntru)
    set(KEM_OBJS ${KEM_OBJS} $<TARGET_OBJECTS:ntru>)
endif()
if(ENABLE_KEM_SABER)
    add_subdirectory(kem/saber)
    set(KEM_OBJS ${KEM_OBJS} $<TARGET_OBJECTS:saber>)
endif()
if(ENABLE_KEM_SIKE OR ENABLE_KEM_SIDH)
    add_subdirectory(kem/sike)
    set(KEM_OBJS ${KEM_OBJS} $<TARGET_OBJECTS:sike>)
endif()

if(ENABLE_SIG_DILITHIUM)
    add_subdirectory(sig/dilithium)
    set(SIG_OBJS $<TARGET_OBJECTS:dilithium>)
endif()
if(ENABLE_SIG_MQDSS)
    add_subdirectory(sig/mqdss)
    set(SIG_OBJS ${SIG_OBJS} $<TARGET_OBJECTS:mqdss>)
endif()
if(ENABLE_SIG_PICNIC)
    add_subdirectory(sig/picnic)
    set(SIG_OBJS ${SIG_OBJS} $<TARGET_OBJECTS:picnic>)
endif()
if(ENABLE_SIG_QTESLA)
    add_subdirectory(sig/qtesla)
    set(SIG_OBJS ${SIG_OBJS} $<TARGET_OBJECTS:qtesla>)
endif()
if(ENABLE_SIG_SPHINCS)
    add_subdirectory(sig/sphincs)
    set(SIG_OBJS ${SIG_OBJS} $<TARGET_OBJECTS:sphincs>)
endif()

message(STATUS "KEM_OBJS: ${KEM_OBJS}")

add_library(oqs kem/kem.c
                ${KEM_OBJS}
                sig/sig.c
                ${SIG_OBJS}
                $<TARGET_OBJECTS:crypto>
                $<TARGET_OBJECTS:common>)

set_target_properties(oqs
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

install(TARGETS oqs
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib)

install(FILES ${PUBLIC_HEADERS}
        DESTINATION include/oqs)
