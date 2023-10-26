#ifndef BASE64_H
#define BASE64_H

#include <stddef.h>
#include <stdint.h>

char *base64_encode(const uint8_t *data, size_t size);

#endif
