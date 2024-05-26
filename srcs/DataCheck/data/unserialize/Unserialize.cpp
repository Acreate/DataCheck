#include "Unserialize.h"
#include "../dataCheck/DataCheck.h"
using namespace cylDataCheck;

template class Unserialize< bool >;

template class Unserialize< int8_t >;
template class Unserialize< int16_t >;
template class Unserialize< int32_t >;
template class Unserialize< int64_t >;

template class Unserialize< uint8_t >;
template class Unserialize< uint16_t >;
template class Unserialize< uint32_t >;
template class Unserialize< uint64_t >;

template class Unserialize< float >;
template class Unserialize< double >;

template class Unserialize< bool [ ] >;

template class Unserialize< int8_t [ ] >;
template class Unserialize< int16_t [ ] >;
template class Unserialize< int32_t [ ] >;
template class Unserialize< int64_t [ ] >;

template class Unserialize< uint8_t [ ] >;
template class Unserialize< uint16_t [ ] >;
template class Unserialize< uint32_t [ ] >;
template class Unserialize< uint64_t [ ] >;

template class Unserialize< float [ ] >;
template class Unserialize< double [ ] >;

template< typename T_Serialization_Data_Unity >
uint64_t Unserialize< T_Serialization_Data_Unity >::firstUnitySize = sizeof( uint64_t ) * 2;
template< typename T_Serialization_Data_Unity >
uint64_t Unserialize< T_Serialization_Data_Unity >::type = 2;

template< typename T_Serialization_Data_Array_Ptr >
uint64_t Unserialize< T_Serialization_Data_Array_Ptr [ ] >::firstUnitySize = sizeof( uint64_t ) * 2;
template< typename T_Serialization_Data_Array_Ptr >
uint64_t Unserialize< T_Serialization_Data_Array_Ptr [ ] >::type = 2;

uint64_t analysisMemoryReadCount( const uint8_t *serialization_data, uint64_t read_max_count ) {
	uint64_t result;
	uint8_t *ptr = reinterpret_cast< uint8_t * >( &result );
	for( uint64_t index = 0; index < read_max_count; ++index )
		ptr[ index ] = serialization_data[ index ];
	return result;
}


template< typename T_Serialization_Data_Unity >
uint64_t Unserialize< T_Serialization_Data_Unity >::unserialize( const uint8_t *serialization_data, std::shared_ptr< T_Serialization_Data_Unity > &data_serialization_result ) {

	uint64_t readMaxCount = sizeof( firstUnitySize );
	uint8_t isbegEndian = *serialization_data;
	serialization_data = serialization_data + 1;
	uint64_t count = analysisMemoryReadCount( serialization_data, readMaxCount );
	serialization_data = serialization_data + readMaxCount;
	uint64_t type = analysisMemoryReadCount( serialization_data, readMaxCount );
	if( type != 1 ) // 类型不一致
		return 0;
	uint64_t typeSize = sizeof( T_Serialization_Data_Unity );
	uint64_t userCount = firstUnitySize + typeSize + sizeof( DataCheck::begEndian );
	if( count != userCount ) // 数量不一致
		return 0;
	T_Serialization_Data_Unity *resultPtr = new T_Serialization_Data_Unity;
	serialization_data = serialization_data + readMaxCount;
	uint8_t *ptr = reinterpret_cast< uint8_t * >( resultPtr );
	for( readMaxCount = 0; readMaxCount < typeSize; ++readMaxCount )
		ptr[ readMaxCount ] = serialization_data[ readMaxCount ];
	data_serialization_result = std::shared_ptr< T_Serialization_Data_Unity >( resultPtr );
	return userCount;
}


template< typename T_Serialization_Data_Array_Ptr >
uint64_t Unserialize< T_Serialization_Data_Array_Ptr [ ] >::unserialize( const uint8_t *serialization_data, std::shared_ptr< T_Serialization_Data_Array_Ptr[ ] > &data_serialization_result, uint64_t &data_serialization_result_count ) {

	uint64_t readMaxCount = sizeof( firstUnitySize );
	uint8_t isbegEndian = *serialization_data;
	serialization_data = serialization_data + 1;
	uint64_t userCount = analysisMemoryReadCount( serialization_data, readMaxCount );
	serialization_data = serialization_data + readMaxCount;
	uint64_t type = analysisMemoryReadCount( serialization_data, readMaxCount );
	if( type != 2 ) // 类型不一致
		return 0;
	uint64_t typeSize = sizeof( T_Serialization_Data_Array_Ptr );
	auto residueDataSize = userCount - firstUnitySize; // 剩余数据长度
	if( residueDataSize == 0 ) { // 没有剩余的空间，将会直接返回
		data_serialization_result_count = 0;
		return userCount;
	}

	data_serialization_result_count = residueDataSize / typeSize;
	T_Serialization_Data_Array_Ptr *resultPtr = new T_Serialization_Data_Array_Ptr[ data_serialization_result_count ];
	serialization_data = serialization_data + readMaxCount;
	uint8_t *ptr = reinterpret_cast< uint8_t * >( resultPtr );
	for( readMaxCount = 0; readMaxCount < residueDataSize; ++readMaxCount )
		ptr[ readMaxCount ] = serialization_data[ readMaxCount ];
	data_serialization_result = std::shared_ptr< T_Serialization_Data_Array_Ptr [ ] >( resultPtr, []( T_Serialization_Data_Array_Ptr *p ) {
		delete [] p;
	} );
	return userCount;
}
