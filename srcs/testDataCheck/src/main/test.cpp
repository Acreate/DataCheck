#include "test.h"
#include <iostream>
#include <nameSpace/cylDataCheck.h>
#include "../auto_generate_files/macro/cmake_to_c_cpp_header_env.h"
#include "data/serialization/Serialization.h"
#include "data/unserialize/Unserialize.h"
void testSerialization( ) {

	bool flag = true;
	uint64_t resuult;
	auto dataArray = cylDataCheck::Serialization< bool >::serialization( flag, resuult );
	if( dataArray )
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
	std::cout << std::endl;
	std::cout << "bool ====================" << std::endl;
	std::shared_ptr< bool > resulBool = nullptr;
	uint64_t unserialize = cylDataCheck::Unserialize< bool >::unserialize( dataArray.get( ), resulBool );
	if( unserialize == 0 )
		std::cout << u8"bool 还原失败" << std::endl;
	else
		std::cout << u8"bool 还原:" << *resulBool << std::endl;
	std::cout << "--------------------" << std::endl;

	dataArray = cylDataCheck::Serialization< int >::serialization( 22, resuult );
	if( dataArray )
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
	std::cout << std::endl;
	std::cout << "int ====================" << std::endl;

	std::shared_ptr< int > resulInt = nullptr;
	unserialize = cylDataCheck::Unserialize< int >::unserialize( dataArray.get( ), resulInt );
	if( unserialize == 0 )
		std::cout << u8"int 还原失败" << std::endl;
	else
		std::cout << u8"int 还原:" << *resulInt << std::endl;
	std::cout << "--------------------" << std::endl;

	int intArray[ ] = { 24
		, 56
		, 89
		, 00 };
	dataArray = cylDataCheck::Serialization< int [ ] >::serialization( intArray, 4, resuult );
	if( dataArray )
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
	std::cout << std::endl;
	std::cout << "int [ ] ====================" << std::endl;

	std::shared_ptr< int[ ] > resulIntarray = nullptr;
	unserialize = cylDataCheck::Unserialize< int [ ] >::unserialize( dataArray.get( ), resulIntarray, resuult );
	if( unserialize == 0 )
		std::cout << u8"int [ ] 还原失败" << std::endl;
	else {
		std::cout << u8"int [ ] 还原:";
		for( int index = 0; index < resuult; ++index )
			std::cout << resulIntarray[ index ] << ", ";
		std::cout << std::endl;
	}
	std::cout << "--------------------" << std::endl;

}