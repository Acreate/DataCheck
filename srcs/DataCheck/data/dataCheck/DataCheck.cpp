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
	if( size == 0 )
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


bool DataCheck::begEndian = DataCheck::isBegEndian( );
