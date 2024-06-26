﻿#include <iostream>

#include "data/dataCheck/DataCheck.h"
#include "test.h"

int main( int argc, char *argv[ ] ) {
	std::locale locale( "zh_CN.UTF8" );
	std::locale::global( locale );
	std::cout.imbue( locale );
	std::wcout.imbue( locale );
	testSerialization( );
	std::cout << cylDataCheck::DataCheck::nativeIsBegEndian( ) << std::endl;
	std::cout << "VVVVVVVVVVVVVVVVVVVVVVVVVVV" << std::endl << std::endl;
	testDataCheck( );
	std::cout << std::endl << "↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑↑" << std::endl;
	return 0;
}
