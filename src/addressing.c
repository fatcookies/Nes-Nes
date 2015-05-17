#include "addressing.h"
#include "cpu.h"

inline uint16_t immediate() {
	return next();
}

inline uint16_t zeropage() {
	return next();
}

inline uint16_t zeropage_x() {
	return (uint16_t) (next() + registers->x);
}

inline uint16_t zeropage_y() {
	return (uint16_t) (next() + registers->y);
}

inline uint16_t absolute() {
	return next16();
}

inline uint16_t absolute_x() {
	return next16() + registers->x;
}

inline uint16_t absolute_y() {
	return next16() + registers->y;
}

inline uint16_t indirect_x() {
	return fetch16(next() + registers->x);
}

inline uint16_t indirect_y() {
	return fetch16(next()) + registers->y;
}