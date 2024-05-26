#include "Serialization.h"
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

/// <summary>
/// 使用 serialization_size 内存大小存储 size 数据
/// </summary>
/// <param name="size">存储对象</param>
/// <param name="serialization_size">使用空间</param>
/// <param name="type">类型</param>
/// <returns>存储后的列表</returns>
inline Data_Array serializationSize( const uint64_t &size, const uint64_t &serialization_size, const uint64_t &type ) {
	uint8_t *px = new uint8_t[ serialization_size ];
	const uint8_t *ptr = reinterpret_cast< const uint8_t * >( &size );
	uint64_t index = 0, max = serialization_size / 2;
	for( ; index < max; ++index )
		px[ index ] = ptr[ index ];
	ptr = reinterpret_cast< const uint8_t * >( &type );
	for( ; index < serialization_size; ++index )
		px[ index ] = ptr[ index - max ];
	return std::shared_ptr< uint8_t[ ] >( px, []( uint8_t *p ) {
		delete[] p;
	} );
}

template< typename T_Serialization_Data_Unity >
Data_Array Serialization< T_Serialization_Data_Unity >::serialization( const T_Serialization_Data_Unity &serialization_data, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = firstUnitySize + sizeof( T_Serialization_Data_Unity ) + sizeof( DataCheck::begEndian );
	Data_Array dataArray = serializationSize( data_serialization_result_len, firstUnitySize, type );
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	*px = DataCheck::begEndian; // 大小端
	const uint8_t *ptr = reinterpret_cast< const uint8_t * >( &serialization_data );
	uint64_t index = 0;
	for( ; index < firstUnitySize; ++index )
		px[ index + 1 ] = dataArray[ index ];
	++index;
	for( ; index < data_serialization_result_len; ++index )
		px[ index ] = ptr[ index - firstUnitySize - 1 ];
	return std::shared_ptr< uint8_t[ ] >( px, []( uint8_t *p ) {
		delete[] p;
	} );
}
template< typename T_Serialization_Data_Unity >
DataCheck_Shared Serialization< T_Serialization_Data_Unity >::DataCheck( const T_Serialization_Data_Unity &serialization_data, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = sizeof( serialization_data );
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	const uint8_t *ptr = reinterpret_cast< const uint8_t * >( &serialization_data );
	for( auto index = 0; index < data_serialization_result_len; ++index )
		px[ index ] = ptr[ index ];
	auto allSize = sizeof( data_serialization_result_len ) + data_serialization_result_len + sizeof( cylDataCheck::DataCheck::begEndian ) + sizeof( type );
	auto sharedPtr = std::shared_ptr< uint8_t[ ] >( px, []( uint8_t *p ) {
		delete[] p;
	} );
	auto dataChackSPtr = std::make_shared< cylDataCheck::DataCheck >( cylDataCheck::DataCheck::begEndian, allSize, type, sharedPtr, data_serialization_result_len );
	return dataChackSPtr;
}

template< typename T_Serialization_Data_Array_Ptr >
Data_Array Serialization< T_Serialization_Data_Array_Ptr [ ] >::serialization( const T_Serialization_Data_Array_Ptr *serialization_data, const uint64_t &array_count, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = firstUnitySize + sizeof( *serialization_data ) * array_count + sizeof( DataCheck::begEndian );
	Data_Array dataArray = serializationSize( data_serialization_result_len, firstUnitySize, type );
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	*px = DataCheck::begEndian;
	const uint8_t *ptr = reinterpret_cast< const uint8_t * >( serialization_data );
	uint64_t index = 0;
	for( ; index < firstUnitySize; ++index )
		px[ index + 1 ] = dataArray[ index ];
	++index;
	for( ; index < data_serialization_result_len; ++index )
		px[ index ] = ptr[ index - firstUnitySize - 1 ];
	return std::shared_ptr< uint8_t[ ] >( px, []( uint8_t *p ) {
		delete[] p;
	} );
}
template< typename T_Serialization_Data_Array_Ptr >
DataCheck_Shared Serialization< T_Serialization_Data_Array_Ptr[ ] >::DataCheck( const T_Serialization_Data_Array_Ptr *serialization_data, const uint64_t &array_count, uint64_t &data_serialization_result_len ) {
	data_serialization_result_len = sizeof( *serialization_data ) * array_count;
	uint8_t *px = new uint8_t[ data_serialization_result_len ];
	const uint8_t *ptr = reinterpret_cast< const uint8_t * >( serialization_data );
	for( auto index = 0; index < data_serialization_result_len; ++index )
		px[ index ] = ptr[ index ];
	auto allSize = sizeof( data_serialization_result_len ) + data_serialization_result_len + sizeof( cylDataCheck::DataCheck::begEndian ) + sizeof( type );
	auto sharedPtr = std::shared_ptr< uint8_t[ ] >( px, []( uint8_t *p ) {
		delete[] p;
	} );
	auto dataChackSPtr = std::make_shared< cylDataCheck::DataCheck >( cylDataCheck::DataCheck::begEndian, allSize, type, sharedPtr, data_serialization_result_len );
	return dataChackSPtr;
}
