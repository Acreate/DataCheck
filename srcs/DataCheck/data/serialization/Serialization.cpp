﻿#include "Serialization.h"
#include "../dataCheck/DataCheck.h"
using namespace cylDataCheck;


template class Serialization< bool >;

template class Serialization< int8_t >;
template class Serialization< int16_t >;
template class Serialization< int32_t >;
template class Serialization< int64_t >;

template class Serialization< uint8_t >;
template class Serialization< uint16_t >;
template class Serialization< uint32_t >;
template class Serialization< uint64_t >;

template class Serialization< float >;
template class Serialization< double >;

template class Serialization< bool [ ] >;

template class Serialization< int8_t [ ] >;
template class Serialization< int16_t [ ] >;
template class Serialization< int32_t [ ] >;
template class Serialization< int64_t [ ] >;

template class Serialization< uint8_t [ ] >;
template class Serialization< uint16_t [ ] >;
template class Serialization< uint32_t [ ] >;
template class Serialization< uint64_t [ ] >;

template class Serialization< float [ ] >;
template class Serialization< double [ ] >;


template< typename T_Serialization_Data_Unity >
uint64_t Serialization< T_Serialization_Data_Unity >::firstUnitySize = sizeof( uint64_t ) * 2;
template< typename T_Serialization_Data_Unity >
uint64_t Serialization< T_Serialization_Data_Unity >::type = 1;

template< typename T_Serialization_Data_Array_Ptr >
uint64_t Serialization< T_Serialization_Data_Array_Ptr [ ] >::firstUnitySize = sizeof( uint64_t ) * 2;
template< typename T_Serialization_Data_Array_Ptr >
uint64_t Serialization< T_Serialization_Data_Array_Ptr [ ] >::type = 2;

template< typename T_Serialization_Data_Unity >
Data_Array Serialization< T_Serialization_Data_Unity >::serialization( const T_Serialization_Data_Unity &serialization_data, uint64_t &data_serialization_result_len ) {
	uint64_t array_count = 1;
	uint64_t arrayCounSize = sizeof( array_count );
	uint64_t endianFlagSize = sizeof( DataCheck::begEndian );
	uint64_t maxBuffLenSize = sizeof( data_serialization_result_len );
	uint64_t typeSize = sizeof( type );
	uint64_t serializationDataSize = sizeof( serialization_data );

	data_serialization_result_len = maxBuffLenSize + typeSize + serializationDataSize + arrayCounSize + endianFlagSize;

	uint8_t *orgPtr = new uint8_t[ data_serialization_result_len ]; // 原始指针
	uint8_t *offsetPtr = orgPtr; // 操作指针

	*offsetPtr = DataCheck::begEndian; // 大小端
	offsetPtr += endianFlagSize; // 偏移一个大小端单位

	uint64_t index = 0;
	const uint8_t *ptr = reinterpret_cast< const uint8_t * >( &data_serialization_result_len ); // 获取总大小长度
	for( ; index < maxBuffLenSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	offsetPtr += maxBuffLenSize;

	ptr = reinterpret_cast< const uint8_t * >( &type );
	for( index = 0; index < typeSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	offsetPtr += typeSize;

	ptr = reinterpret_cast< const uint8_t * >( &array_count );
	for( index = 0; index < arrayCounSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	offsetPtr += arrayCounSize;

	ptr = reinterpret_cast< const uint8_t * >( &serialization_data );
	for( index = 0; index < serializationDataSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	return std::shared_ptr< uint8_t[ ] >( orgPtr, []( uint8_t *p ) {
		delete[] p;
	} );
}

template< typename T_Serialization_Data_Array_Ptr >
Data_Array Serialization< T_Serialization_Data_Array_Ptr [ ] >::serialization( const T_Serialization_Data_Array_Ptr *serialization_data, const uint64_t &array_count, uint64_t &data_serialization_result_len ) {

	uint64_t endianFlagSize = sizeof( DataCheck::begEndian );
	uint64_t maxBuffLenSize = sizeof( data_serialization_result_len );
	uint64_t typeSize = sizeof( type );
	uint64_t arrayCounSize = sizeof( array_count );
	uint64_t serializationDataSize = sizeof( T_Serialization_Data_Array_Ptr ) * array_count;

	data_serialization_result_len = endianFlagSize + maxBuffLenSize + typeSize + arrayCounSize + serializationDataSize;

	uint8_t *orgPtr = new uint8_t[ data_serialization_result_len ]; // 原始指针
	// 返回对象
	auto resultShared = std::shared_ptr< uint8_t[ ] >( orgPtr, []( uint8_t *p ) {
		delete[] p;
	} );
	uint8_t *offsetPtr = orgPtr; // 操作指针

	*offsetPtr = DataCheck::begEndian; // 大小端
	offsetPtr += endianFlagSize; // 偏移一个大小端单位

	uint64_t index = 0;
	const uint8_t *ptr = reinterpret_cast< const uint8_t * >( &data_serialization_result_len ); // 获取总大小长度
	for( ; index < maxBuffLenSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	offsetPtr += maxBuffLenSize;

	ptr = reinterpret_cast< const uint8_t * >( &type );
	for( index = 0; index < typeSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	offsetPtr += typeSize;

	ptr = reinterpret_cast< const uint8_t * >( &array_count );
	for( index = 0; index < arrayCounSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	offsetPtr += arrayCounSize;

	ptr = reinterpret_cast< const uint8_t * >( serialization_data );
	for( index = 0; index < serializationDataSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	return resultShared;
}
