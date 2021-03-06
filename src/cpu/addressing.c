#include "addressing.h"
#include "cpu.h"

 uint16_t immediate() {
	return next();
}

 uint16_t zeropage() {
	return next();
}

 uint16_t zeropage_x() {
	return (uint16_t) (next() + registers->x);
}

 uint16_t zeropage_y() {
	return (uint16_t) (next() + registers->y);
}

 uint16_t absolute() {
	return next16();
}

 uint16_t absolute_x() {
	return next16() + registers->x;
}

 uint16_t absolute_y() {
	return next16() + registers->y;
}

 uint16_t indirect() {
	return fetch16(next16());
}

 uint16_t indirect_x() {
	return fetch16(next() + registers->x);
}

 uint16_t indirect_y() {
	return fetch16(next()) + registers->y;
}


//special addressing modes where page boundaries may be crossed
 uint16_t absolute_x_pages() {
	uint16_t temp = next16();
	uint16_t res = temp + registers->x;
	if((temp & res) >> 8) {
		cycles++;
	}
	return res;
}

 uint16_t absolute_y_pages() {
	uint16_t temp = next16();
	uint16_t res = temp + registers->y;
	if((temp & res) >> 8) {
		cycles++;
	}
	return res;
}

 uint16_t indirect_y_pages() {
	uint16_t temp = fetch16(next());
	uint16_t res = temp + registers->y;
	if((temp & res) >> 8) {
		cycles++;
	}
	return res;
}