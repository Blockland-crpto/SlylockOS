#ifndef __SECURE_CRYPTO_AES128_H
#define __SECURE_CRYPTO_AES128_H

#include <stdint.h>

void add_round_key(uint8_t *state, const uint8_t *round_key);
void key_expansion(const uint8_t *key, uint8_t *round_keys);
void aes_encrypt(const uint8_t* plaintext, const uint8_t* key, uint8_t* ciphertext);
void aes_decrypt(const uint8_t *ciphertext, const uint8_t *key, uint8_t *plaintext);


#endif