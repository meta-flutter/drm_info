#include <stdlib.h>

#include "base64.h"

#define BLOCK_ENC_SIZE 4
#define BLOCK_DEC_SIZE 3

static const char enc_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encode_block(char dst[static BLOCK_ENC_SIZE], const uint8_t src[static BLOCK_DEC_SIZE], size_t size)
{
	uint8_t a = src[0] >> 2;
	uint8_t b = ((src[1] & 0xF0) >> 4) | ((src[0] & 0x03) << 4);
	uint8_t c = ((src[2] & 0xC0) >> 6) | ((src[1] & 0x0F) << 2);
	uint8_t d = src[2] & 0x3F;

	dst[0] = enc_table[a];
	dst[1] = enc_table[b];
	dst[2] = size > 1 ? enc_table[c] : '=';
	dst[3] = size > 2 ? enc_table[d] : '=';
}

char *base64_encode(const uint8_t *data, size_t size)
{
	size_t num_blocks = size / BLOCK_DEC_SIZE;
	if (size % BLOCK_DEC_SIZE != 0) {
		num_blocks++;
	}

	char *out = malloc(BLOCK_ENC_SIZE * num_blocks + 1);
	if (!out)
		return NULL;

	size_t i = 0, j = 0;
	while (i < size) {
		uint8_t block[BLOCK_DEC_SIZE] = {0};
		size_t block_size = 0;
		while (i < size && block_size < BLOCK_DEC_SIZE) {
			block[block_size++] = data[i++];
		}

		encode_block(&out[j], block, block_size);
		j += BLOCK_ENC_SIZE;
	}

	out[j] = '\0';
	return out;
}
