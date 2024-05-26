#include "DataCheck.h"

using namespace cylDataCheck;
bool DataCheck::isBegEndian( ) {
	union {
		uint32_t i;
		char c[ 4 ];
	} bint = { 0x01020304 };
	return bint.c[ 0 ] == 1;
}
void DataCheck::converEndian( uint8_t *ptr, uint64_t size ) {
	if( size == 0 || size == 1 )
		return;
	if( size == 2 ) {
		uint8_t temp = ptr[ 0 ];
		ptr[ 0 ] = ptr[ 1 ];
		ptr[ 1 ] = temp;
	} else if( size == 4 ) {
		uint8_t temp = ptr[ 0 ];
		ptr[ 0 ] = ptr[ 3 ];
		ptr[ 3 ] = temp;

		temp = ptr[ 1 ];
		ptr[ 1 ] = ptr[ 2 ];
		ptr[ 2 ] = temp;
	} else if( size == 6 ) {
		uint8_t temp = ptr[ 0 ];
		ptr[ 0 ] = ptr[ 5 ];
		ptr[ 5 ] = temp;

		temp = ptr[ 1 ];
		ptr[ 1 ] = ptr[ 4 ];
		ptr[ 4 ] = temp;

		temp = ptr[ 2 ];
		ptr[ 2 ] = ptr[ 3 ];
		ptr[ 3 ] = temp;
	} else if( size == 8 ) {
		uint8_t temp = ptr[ 0 ];
		ptr[ 0 ] = ptr[ 7 ];
		ptr[ 7 ] = temp;

		temp = ptr[ 1 ];
		ptr[ 1 ] = ptr[ 6 ];
		ptr[ 6 ] = temp;

		temp = ptr[ 2 ];
		ptr[ 2 ] = ptr[ 5 ];
		ptr[ 5 ] = temp;

		temp = ptr[ 3 ];
		ptr[ 3 ] = ptr[ 4 ];
		ptr[ 4 ] = temp;
	} else {
		uint8_t temp;
		--size;
		for( uint64_t index = 0; index < size; index++, --size ) {
			temp = ptr[ index ];
			ptr[ index ] = ptr[ size ];
			ptr[ size ] = temp;
		}
	}

}
DataCheck::~DataCheck( ) {
}
DataCheck::DataCheck( bool current_endian, uint64_t data_size, uint64_t data_type, const std::shared_ptr< uint8_t[ ] > &data_array_shared, const uint64_t data_array_count ): currentEndian( current_endian )
, dataSize( data_size )
, dataType( data_type )
, dataArrayShared( data_array_shared )
, dataArrayCount( data_array_count ) { }
DataCheck::DataCheck( uint8_t *serialization_data ) {
	currentEndian = *serialization_data; // 获取大小端
	serialization_data += 1;
	auto index = 0;
	if( DataCheck::begEndian != currentEndian ) { // 端不同，需要逆转数据，转为本地端
		auto ptr = reinterpret_cast< uint8_t * >( &dataSize );
		for( index = 0; index < 8; ++index )
			ptr[ index ] = serialization_data[ 7 - index ];

		serialization_data = serialization_data + 8;
		ptr = reinterpret_cast< uint8_t * >( &dataType );
		for( index = 0; index < 8; ++index )
			ptr[ index ] = serialization_data[ 7 - index ];
		serialization_data = serialization_data + 8;

		if( dataType == 1 ) { // 单元素
			auto residueSize = dataSize - 1 - sizeof( dataSize ) * 2;// 剩余数量
			uint8_t *newPtr = new uint8_t[ residueSize ];
			for( index = 0; index < residueSize; ++index )
				newPtr[ index ] = serialization_data[ index ];
			converEndian( newPtr, residueSize );
			dataArrayShared = std::shared_ptr< uint8_t[ ] >( newPtr, []( uint8_t *p ) {
				delete[] p;
			} );
		} else if( dataType == 2 ) { // 数组元素
			serialization_data = serialization_data + 8;
			ptr = reinterpret_cast< uint8_t * >( &dataArrayCount );
			for( index = 0; index < 8; ++index )
				ptr[ index ] = serialization_data[ 7 - index ];
			auto residueSize = dataSize - 1 - sizeof( dataSize ) * 3; // 剩余数量
			auto typeUnitySize = residueSize / dataArrayCount; // 元素大小
			uint8_t *buff = new uint8_t[ typeUnitySize ];
			uint8_t *newPtr = new uint8_t[ residueSize ];
			uint64_t subIndex = 0;
			uint64_t newPtrIndex = 0;
			for( index = 0; index < dataArrayCount; ++index ) {
				for( subIndex = 0; subIndex < typeUnitySize; ++subIndex )
					buff[ subIndex ] = serialization_data[ subIndex ];
				serialization_data += typeUnitySize; // 下一个元素
				converEndian( buff, typeUnitySize );
				for( subIndex = 0; subIndex < typeUnitySize; ++subIndex, ++newPtrIndex )
					newPtr[ newPtrIndex ] = buff[ subIndex ];
			}
			delete[] buff; // 删除元素
			dataArrayShared = std::shared_ptr< uint8_t[ ] >( newPtr, []( uint8_t *p ) {
				delete[] p;
			} );
		}

		return;
	}
	/// 相同端

	auto ptr = reinterpret_cast< uint8_t * >( &dataSize );
	for( index = 0; index < 8; ++index )
		ptr[ index ] = serialization_data[ index ];

	serialization_data = serialization_data + 8;
	ptr = reinterpret_cast< uint8_t * >( &dataType );
	for( index = 0; index < 8; ++index )
		ptr[ index ] = serialization_data[ index ];

	serialization_data = serialization_data + 8;

	if( dataType == 1 ) { // 单元素
		auto residueSize = dataSize - 1 - sizeof( dataSize ) * 2;// 剩余数量
		uint8_t *newPtr = new uint8_t[ residueSize ];
		for( index = 0; index < residueSize; ++index )
			newPtr[ index ] = serialization_data[ index ];
		dataArrayShared = std::shared_ptr< uint8_t[ ] >( newPtr, []( uint8_t *p ) {
			delete[] p;
		} );
	} else if( dataType == 2 ) { // 数组元素
		serialization_data = serialization_data + 8;
		ptr = reinterpret_cast< uint8_t * >( &dataArrayCount );
		for( index = 0; index < 8; ++index )
			ptr[ index ] = serialization_data[ 7 - index ];
		auto residueSize = dataSize - 1 - sizeof( dataSize ) * 3; // 剩余数量
		auto typeUnitySize = residueSize / dataArrayCount; // 元素大小
		uint8_t *buff = new uint8_t[ typeUnitySize ];
		uint8_t *newPtr = new uint8_t[ residueSize ];
		uint64_t subIndex = 0;
		uint64_t newPtrIndex = 0;
		for( index = 0; index < dataArrayCount; ++index ) {
			for( subIndex = 0; subIndex < typeUnitySize; ++subIndex )
				buff[ subIndex ] = serialization_data[ subIndex ];
			serialization_data += typeUnitySize; // 下一个元素
			for( subIndex = 0; subIndex < typeUnitySize; ++subIndex, ++newPtrIndex )
				newPtr[ newPtrIndex ] = buff[ subIndex ];
		}
		delete[] buff; // 删除元素
		dataArrayShared = std::shared_ptr< uint8_t[ ] >( newPtr, []( uint8_t *p ) {
			delete[] p;
		} );
	}

}

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


uint8_t DataCheck::begEndian = DataCheck::isBegEndian( );
