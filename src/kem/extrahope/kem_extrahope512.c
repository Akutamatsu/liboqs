#include <stdlib.h>

#include <oqs/kem_extrahope.h>

#ifdef OQS_ENABLE_KEM_extrahope512

OQS_KEM *OQS_KEM_extrahope512_new() {

	OQS_KEM *kem = malloc(sizeof(OQS_KEM));
	if (kem == NULL) {
		return NULL;
	}
	kem->method_name = OQS_KEM_alg_extrahope512;

	kem->claimed_nist_level = 1;
	kem->ind_cca = true;

	kem->length_public_key = OQS_KEM_extrahope512_length_public_key;
	kem->length_secret_key = OQS_KEM_extrahope512_length_secret_key;
	kem->length_ciphertext = OQS_KEM_extrahope512_length_ciphertext;
	kem->length_shared_secret = OQS_KEM_nextrahope512_length_shared_secret;

	kem->keypair = OQS_KEM_extrahope512_keypair;
	kem->encaps = OQS_KEM_extrahope512_encaps;
	kem->decaps = OQS_KEM_extrahope512_decaps;

	return kem;
}

int PQCLEAN_EXTRAHOPE512_CLEAN_cpapke_keypair(unsigned char *pk, unsigned char *sk);
int PQCLEAN_EXTRAHOPE512_CLEAN_cpapke_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);
int PQCLEAN_EXTRAHOPE512_CLEAN_cpapke_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);

OQS_API OQS_STATUS OQS_KEM_extrahope512_keypair(uint8_t *public_key, uint8_t *secret_key) {
	return (OQS_STATUS) PQCLEAN_EXTRAHOPE512_CLEAN_cpapke_keypair(public_key, secret_key);
}
OQS_API OQS_STATUS OQS_KEM_extrahope512_encaps(uint8_t *ciphertext, uint8_t *shared_secret, const uint8_t *public_key) {
	return (OQS_STATUS) PQCLEAN_EXTRAHOPE512_CLEAN_cpapke_enc(ciphertext, shared_secret, public_key);
}
OQS_API OQS_STATUS OQS_KEM_extrahope512_decaps(uint8_t *shared_secret, const unsigned char *ciphertext, const uint8_t *secret_key) {
	return (OQS_STATUS) PQCLEAN_EXTRAHOPE512_CLEAN_cpapke_dec(shared_secret, ciphertext, secret_key);
}

#endif