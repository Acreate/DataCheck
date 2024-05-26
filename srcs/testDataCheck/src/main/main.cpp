#include <iostream>
#include <nameSpace/cylDataCheck.h>
#include "../auto_generate_files/macro/cmake_to_c_cpp_header_env.h"
#include "data/serialization/Serialization.h"
int main( int argc, char *argv[ ] ) {

	bool flag = false;
	uint64_t resuult;
	auto dataArray = cylDataCheck::Serialization::getInstance( )->serialization( flag, resuult );
	if( dataArray )
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << std::endl;
	return 0;
}
