#ifndef _OUR_TYPES_H_
#define _OUR_TYPES_H_

#include <inttypes.h>
#include <stdint.h>

typedef enum our_types_t {
	INT8,
	INT16,
	INT32,
	INT64,
	VOIDP
} our_types_t;

typedef union our_container_t {
	int8_t i8;
	int16_t i16;
	int32_t i32;
	int64_t l64;
	void *vp;
} our_container_t;

typedef struct out_types_container_t {
	our_types_t type;
	our_container_t container;
} out_types_container_t;

#endif

