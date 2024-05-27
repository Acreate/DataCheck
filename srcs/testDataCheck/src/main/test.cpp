#include "test.h"
#include <iostream>
#include <nameSpace/cylDataCheck.h>
#include "../auto_generate_files/macro/cmake_to_c_cpp_header_env.h"
#include "data/dataCheck/DataCheck.h"
#include "data/serialization/Serialization.h"
#include "data/unserialize/Unserialize.h"
void testSerialization( ) {

	bool flag = true;
	uint64_t resuult;
	auto dataArray = cylDataCheck::Serialization< bool >::serialization( flag, resuult );
	if( dataArray ) {
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
		std::cout << std::endl;
	}
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
	if( dataArray ) {
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
		std::cout << std::endl;
	}
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
void testDataCheckBool( ) {
	uint64_t resuult;
	bool flag = true;
	cylDataCheck::Data_Array dataArray = cylDataCheck::Serialization< bool >::serialization( flag, resuult );
	if( dataArray ) {
		std::cout << u8"原型 : ";
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
		std::cout << std::endl;
	}

	std::cout << "bool ====================" << std::endl;

	cylDataCheck::DataCheck dataCheck = cylDataCheck::DataCheck( dataArray.get( ) );
	dataArray = dataCheck.bigEndianSerialization( );
	if( dataArray ) {
		std::cout << u8"大端 : ";
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
		std::cout << std::endl;
	}
	dataArray = dataCheck.littleEndianSerialization( );
	if( dataArray ) {
		std::cout << u8"小端 : ";
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
		std::cout << std::endl;
	}

	std::cout << "--------------------" << std::endl;
}

void testDataCheckInt( ) {
	uint64_t resuult;
	cylDataCheck::Data_Array dataArray = cylDataCheck::Serialization< int >::serialization( 22, resuult );
	if( dataArray ) {
		std::cout << u8"原型 : ";
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
		std::cout << std::endl;
	}
	std::cout << "int ====================" << std::endl;
	cylDataCheck::DataCheck dataCheck = cylDataCheck::DataCheck( dataArray.get( ) );
	dataArray = dataCheck.bigEndianSerialization( );
	if( dataArray ) {
		std::cout << u8"大端 : ";
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
		std::cout << std::endl;
	}
	dataArray = dataCheck.littleEndianSerialization( );
	if( dataArray ) {
		std::cout << u8"小端 : ";
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
		std::cout << std::endl;
	}

	std::cout << "--------------------" << std::endl;

}
void testDataCheckIntArray( ) {
	uint64_t resuult;
	int intArray[ ] = { 24
		, 56
		, 89
		, 00 };

	cylDataCheck::Data_Array dataArray = cylDataCheck::Serialization< int [ ] >::serialization( intArray, 4, resuult );
	if( dataArray ) {
		std::cout << u8"原型 : ";
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
		std::cout << std::endl;
	}
	std::cout << "int [ ] ====================" << std::endl;
	cylDataCheck::DataCheck dataCheck = cylDataCheck::DataCheck( dataArray.get( ) );
	dataArray = dataCheck.bigEndianSerialization( );
	if( dataArray ) {
		std::cout << u8"大端 : ";
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
		std::cout << std::endl;
	}
	dataArray = dataCheck.littleEndianSerialization( );
	if( dataArray ) {
		std::cout << u8"小端 : ";
		for( int index = 0; index < resuult; ++index )
			std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
		std::cout << std::endl;
	}

	std::cout << "--------------------" << std::endl;

}
/// <summary>
/// 大端与小端相互转换
/// </summary>
void testDataCheckBitToLit( ) {

	if( cylDataCheck::DataCheck::nativeIsBegEndian( ) ) { // 本地为大端
		std::cout << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTT" << std::endl;
		std::cout << u8"本地为大端，需要进行获取小端端，并且初始化一个校验串，最后获取大端校验 " << std::endl;
		uint64_t resuult;
		cylDataCheck::Data_Array dataArray = cylDataCheck::Serialization< int >::serialization( 22, resuult ); // 获取大端数据
		if( dataArray ) {
			std::cout << u8"原型 : " << std::endl << '\t';;
			for( int index = 0; index < resuult; ++index )
				std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
			std::cout << std::endl;
		}
		std::cout << "int ====================" << std::endl;
		std::cout << "使用本地(大端)初始化一个校验串" << std::endl;
		cylDataCheck::DataCheck dataCheck = cylDataCheck::DataCheck( dataArray.get( ) );
		std::cout << u8"使用校验串获取小端数据" << std::endl;
		dataArray = dataCheck.littleEndianSerialization( );// 转换为小端
		std::cout << u8"使用小端数据数据初始化校验串" << std::endl;
		dataCheck = cylDataCheck::DataCheck( dataArray.get( ) ); // 小端数据重新初始化一个校验串
		std::cout << u8"使用被小端数据初始化的校验串获取本地(大端)数据" << std::endl;
		dataArray = dataCheck.bigEndianSerialization( ); // 获取大端数据。并且输出
		if( dataArray ) {
			std::cout << u8"获取到的大端 : " << std::endl << '\t';
			for( int index = 0; index < resuult; ++index )
				std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
			std::cout << std::endl;
		}
		std::cout << u8"转换结束" << std::endl;
		std::cout << "--------------------" << std::endl;

		int intArray[ ] = { 24
			, 56
			, 89
			, 00 };

		dataArray = cylDataCheck::Serialization< int [ ] >::serialization( intArray, 4, resuult );
		if( dataArray ) {
			std::cout << u8"原型 : " << std::endl << '\t';;
			for( int index = 0; index < resuult; ++index )
				std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
			std::cout << std::endl;
		}
		std::cout << "int [ ] ====================" << std::endl;
		std::cout << "使用本地(大端)初始化一个校验串" << std::endl;
		dataCheck = cylDataCheck::DataCheck( dataArray.get( ) );
		std::cout << u8"使用校验串获取小端数据" << std::endl;
		dataArray = dataCheck.littleEndianSerialization( );// 转换为小端
		std::cout << u8"使用小端数据数据初始化校验串" << std::endl;
		dataCheck = cylDataCheck::DataCheck( dataArray.get( ) ); // 小端数据重新初始化一个校验串
		std::cout << u8"使用被小端数据初始化的校验串获取本地(大端)数据" << std::endl;
		dataArray = dataCheck.bigEndianSerialization( ); // 获取大端数据。并且输出
		if( dataArray ) {
			std::cout << u8"获取到的大端 : " << std::endl << '\t';;
			for( int index = 0; index < resuult; ++index )
				std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
			std::cout << std::endl;
		}
		std::cout << u8"转换结束" << std::endl;
		std::cout << "--------------------" << std::endl;
	} else { // 本地为小端
		std::cout << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTT" << std::endl;
		std::cout << u8"本地为小端，需要进行 获取大端，并且初始化一个校验串，最后获取小端校验 " << std::endl;
		uint64_t resuult;
		cylDataCheck::Data_Array dataArray = cylDataCheck::Serialization< int >::serialization( 22, resuult ); // 获取小端数据
		if( dataArray ) {
			std::cout << u8"原型 : " << std::endl << '\t';;
			for( int index = 0; index < resuult; ++index )
				std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
			std::cout << std::endl;
		}
		std::cout << "int ====================" << std::endl;
		std::cout << "使用本地(小端)初始化一个校验串" << std::endl;
		cylDataCheck::DataCheck dataCheck = cylDataCheck::DataCheck( dataArray.get( ) );
		std::cout << u8"使用校验串获取大端数据" << std::endl;
		dataArray = dataCheck.bigEndianSerialization( );// 转换为大端
		std::cout << u8"使用大端数据数据初始化校验串" << std::endl;
		dataCheck = cylDataCheck::DataCheck( dataArray.get( ) ); // 大端数据重新初始化一个校验串
		std::cout << u8"使用被大端数据初始化的校验串获取本地(小端)数据" << std::endl;
		dataArray = dataCheck.littleEndianSerialization( ); // 获取小端数据。并且输出
		if( dataArray ) {
			std::cout << u8"获取到的小端 : " << std::endl << '\t';
			for( int index = 0; index < resuult; ++index )
				std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
			std::cout << std::endl;
		}
		std::cout << u8"转换结束" << std::endl;
		std::cout << "--------------------" << std::endl;

		int intArray[ ] = { 24
			, 56
			, 89
			, 00 };

		dataArray = cylDataCheck::Serialization< int [ ] >::serialization( intArray, 4, resuult );
		if( dataArray ) {
			std::cout << u8"原型 : " << std::endl << '\t';;
			for( int index = 0; index < resuult; ++index )
				std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
			std::cout << std::endl;
		}
		std::cout << "int [ ] ====================" << std::endl;
		std::cout << "使用本地(小端)初始化一个校验串" << std::endl;
		dataCheck = cylDataCheck::DataCheck( dataArray.get( ) );
		std::cout << u8"使用校验串获取大端数据" << std::endl;
		dataArray = dataCheck.bigEndianSerialization( );// 转换为大端
		std::cout << u8"使用大端数据数据初始化校验串" << std::endl;
		dataCheck = cylDataCheck::DataCheck( dataArray.get( ) ); // 大端数据重新初始化一个校验串
		std::cout << u8"使用被大端数据初始化的校验串获取本地(小端)数据" << std::endl;
		dataArray = dataCheck.littleEndianSerialization( ); // 获取小端数据。并且输出
		if( dataArray ) {
			std::cout << u8"获取到的小端 : " << std::endl << '\t';;
			for( int index = 0; index < resuult; ++index )
				std::cout << static_cast< int >( dataArray[ index ] ) << ", ";
			std::cout << std::endl;
		}
		std::cout << u8"转换结束" << std::endl;
		std::cout << "--------------------" << std::endl;
	}

}
void testDataCheck( ) {
	std::cout << "\n\n-------------------- testDataCheck" << std::endl;
	uint64_t resuult;
	cylDataCheck::Data_Array dataArray = cylDataCheck::Serialization< int >::serialization( 22, resuult ); // 获取小端数据
	std::cout << u8"转换对象 : " << 22 << std::endl;
	auto dataCheck = cylDataCheck::DataCheck( dataArray );
	auto dataArrayPtr = dataCheck.getDataArrayPtr( );
	if( dataArrayPtr ) {
		std::cout << u8"输出 DataCheck : " << std::endl << '\t';
		uint64_t dataArrayLen = dataCheck.getDataArrayLen( );
		for( int index = 0; index < dataArrayLen; ++index )
			std::cout << static_cast< int >( dataArrayPtr[ index ] ) << ", ";
		std::cout << std::endl;
	}
	std::cout << "testDataCheck --------------------\n\n" << std::endl;
	testDataCheckBool( );
	testDataCheckInt( );
	testDataCheckIntArray( );
	testDataCheckBitToLit( );
}
