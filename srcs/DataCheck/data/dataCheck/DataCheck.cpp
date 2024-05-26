#include "DataCheck.h"

using namespace cylDataCheck;
bool DataCheck::isBegEndian( ) {
	union {
		uint32_t i;
		char c[ 4 ];
	} bint = { 0x01020304 };
	return bint.c[ 0 ] == 1;
}

bool DataCheck::begEndian = DataCheck::isBegEndian( );
