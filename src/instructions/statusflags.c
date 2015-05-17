#include "statusflags.h"
#include "../cpu.h"

inline void ins_clc() {
	SET_CARRY(0);
}

inline void ins_cld() {
	SET_DEC(0);
}

inline void ins_cli() {
	SET_INTERRUPT(0);
}

inline void ins_clv() {
	SET_OVERFLOW(0);
}

inline void ins_sec() {
	SET_CARRY(1);
}

inline void ins_sed() {
	SET_DEC(1);
}

inline void ins_sei() {
	SET_INTERRUPT(1);
}