#include "DataCheck.h"

#include <string>

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
	auto endianSize = sizeof( currentEndian );
	serialization_data += endianSize; // 跳过端信息
	auto index = 0;
	if( DataCheck::begEndian != currentEndian ) { // 端不同，需要逆转数据，转为本地端
		currentEndian = DataCheck::begEndian;
		auto dataSizeSize = sizeof( dataSize ); // 获取总长数据段大小
		auto ptr = reinterpret_cast< uint8_t * >( &dataSize ); // 指向总长数据段
		for( index = 0; index < dataSizeSize; ++index )
			ptr[ index ] = serialization_data[ index ];
		converEndian( ptr, dataSizeSize );
		serialization_data = serialization_data + dataSizeSize;// 跳过总长数据段

		auto dataTypeSize = sizeof( dataType ); // 获取数据类型段大小
		ptr = reinterpret_cast< uint8_t * >( &dataType ); // 指向数据类型段
		for( index = 0; index < dataTypeSize; ++index )
			ptr[ index ] = serialization_data[ index ];
		converEndian( ptr, dataTypeSize );
		serialization_data = serialization_data + dataTypeSize;// 跳过数据类型段

		auto dataArrayCountSize = sizeof( dataArrayCount ); // 获取数据元素个数段大小
		ptr = reinterpret_cast< uint8_t * >( &dataArrayCount ); // 指向数据元素个数段
		for( index = 0; index < dataArrayCountSize; ++index )
			ptr[ index ] = serialization_data[ index ];
		converEndian( ptr, dataArrayCountSize );
		serialization_data = serialization_data + dataArrayCountSize;// 跳过数据元素个数段
		// 还原数据长度
		auto residueSize = dataSize - 1 - dataSizeSize - dataTypeSize - dataArrayCountSize;
		uint8_t *newPtr = new uint8_t[ residueSize ];
		dataArrayShared = std::shared_ptr< uint8_t[ ] >( newPtr, []( uint8_t *p ) {
			delete[] p;
		} );
		size_t subIndex = 0;
		residueSize = residueSize / dataArrayCount;
		for( index = 0; true; ) {
			for( ; subIndex < residueSize; ++subIndex )
				newPtr[ subIndex ] = serialization_data[ subIndex ];
			converEndian( newPtr, residueSize );
			newPtr += residueSize;
			serialization_data += residueSize;
			if( index == dataArrayCount )
				break;
			subIndex = 0;
			++index;
		}
		return;
	}
	/// 相同端

	auto dataSizeSize = sizeof( dataSize ); // 获取总长数据段大小
	auto ptr = reinterpret_cast< uint8_t * >( &dataSize ); // 指向总长数据段
	for( index = 0; index < dataSizeSize; ++index )
		ptr[ index ] = serialization_data[ index ];
	serialization_data = serialization_data + dataSizeSize;// 跳过总长数据段

	auto dataTypeSize = sizeof( dataType ); // 获取数据类型段大小
	ptr = reinterpret_cast< uint8_t * >( &dataType ); // 指向数据类型段
	for( index = 0; index < dataTypeSize; ++index )
		ptr[ index ] = serialization_data[ index ];
	serialization_data = serialization_data + dataTypeSize;// 跳过数据类型段

	auto dataArrayCountSize = sizeof( dataArrayCount ); // 获取数据元素个数段大小
	ptr = reinterpret_cast< uint8_t * >( &dataArrayCount ); // 指向数据元素个数段
	for( index = 0; index < dataArrayCountSize; ++index )
		ptr[ index ] = serialization_data[ index ];
	serialization_data = serialization_data + dataArrayCountSize;// 跳过数据元素个数段
	// 还原数据长度
	auto residueSize = dataSize - 1 - dataSizeSize - dataTypeSize - dataArrayCountSize;
	uint8_t *newPtr = new uint8_t[ residueSize ];
	dataArrayShared = std::shared_ptr< uint8_t[ ] >( newPtr, []( uint8_t *p ) {
		delete[] p;
	} );
	for( index = 0; index < residueSize; ++index )
		newPtr[ index ] = serialization_data[ index ];
}
Data_Array DataCheck::littleEndianSerialization( ) {
	uint8_t *buffPtr = new uint8_t[ dataSize ];
	auto resultSPtr = std::shared_ptr< uint8_t[ ] >( buffPtr, []( uint8_t *p ) {
		delete[] p;
	} );

	auto offsetPtr = buffPtr; // 操作指针

	*offsetPtr = 0; // 小端
	auto endianSize = sizeof( currentEndian ); // 内存数据本身占用字节
	offsetPtr += endianSize; // 偏移大端数据

	uint64_t index = 0;
	const uint8_t *ptr = reinterpret_cast< uint8_t * >( &dataSize ); // 指向数据量
	auto dataSizeSize = sizeof( dataSize ); // 内存数据本身占用字节
	for( ; index < dataSizeSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	offsetPtr += dataSizeSize; // 跳过总占用数据段

	ptr = reinterpret_cast< uint8_t * >( &dataType ); // 数据类型
	auto dataTypeSize = sizeof( dataType ); // 类型数据本身占用字节
	for( index = 0; index < dataTypeSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	offsetPtr += dataTypeSize; // 跳过数据类型

	ptr = reinterpret_cast< uint8_t * >( &dataArrayCount ); // 数据个数
	auto dataArrayCountSize = sizeof( dataArrayCount ); // 数据个数数据本身占用字节
	for( index = 0; index < dataArrayCountSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	offsetPtr += dataArrayCountSize; // 跳过数据个数

	auto residueSize = dataSize - endianSize - dataSizeSize - dataTypeSize - dataArrayCountSize;// 剩余数量
	if( residueSize == 0 )
		return nullptr;

	if( dataType == 1 ) { // 单元素
		ptr = dataArrayShared.get( );
		for( index = 0; index < residueSize; ++index )
			offsetPtr[ index ] = ptr[ index ];
	} else if( dataType == 2 ) { // 列表
		auto typeUnitySize = residueSize / dataArrayCount; // 元素大小
		ptr = dataArrayShared.get( );
		index = 0;
		for( uint64_t subIndex = 0; true; ++index ) {
			for( ; subIndex < typeUnitySize; ++subIndex )
				offsetPtr[ subIndex ] = ptr[ subIndex ];
			if( index == dataArrayCount )
				break;
			offsetPtr += typeUnitySize;
			ptr += typeUnitySize;
			subIndex = 0;
		}

	}
	return resultSPtr;
}
Data_Array DataCheck::bigEndianSerialization( ) {
	uint8_t *buffPtr = new uint8_t[ dataSize ];
	auto resultSPtr = std::shared_ptr< uint8_t[ ] >( buffPtr, []( uint8_t *p ) {
		delete[] p;
	} );

	auto offsetPtr = buffPtr; // 操作指针

	*offsetPtr = 1; // 大端
	auto endianSize = sizeof( currentEndian ); // 内存数据本身占用字节
	offsetPtr += endianSize; // 偏移大端数据

	uint64_t index = 0;
	const uint8_t *ptr = reinterpret_cast< uint8_t * >( &dataSize ); // 指向数据量
	auto dataSizeSize = sizeof( dataSize ); // 内存数据本身占用字节
	for( ; index < dataSizeSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	converEndian( offsetPtr, dataSizeSize ); // 逆转总占用数据段
	offsetPtr += dataSizeSize; // 跳过总占用数据段

	ptr = reinterpret_cast< uint8_t * >( &dataType ); // 数据类型
	auto dataTypeSize = sizeof( dataType ); // 类型数据本身占用字节
	for( index = 0; index < dataTypeSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	converEndian( offsetPtr, dataTypeSize ); // 逆转数据类型
	offsetPtr += dataTypeSize; // 跳过数据类型

	ptr = reinterpret_cast< uint8_t * >( &dataArrayCount ); // 数据个数
	auto dataArrayCountSize = sizeof( dataArrayCount ); // 数据个数数据本身占用字节
	for( index = 0; index < dataArrayCountSize; ++index )
		offsetPtr[ index ] = ptr[ index ];
	converEndian( offsetPtr, dataArrayCountSize ); // 逆转数据个数
	offsetPtr += dataArrayCountSize; // 跳过数据个数

	auto residueSize = dataSize - endianSize - dataSizeSize - dataTypeSize - dataArrayCountSize;// 剩余数量
	if( residueSize == 0 )
		return nullptr;

	if( dataType == 1 ) { // 单元素
		ptr = dataArrayShared.get( );
		for( index = 0; index < residueSize; ++index )
			offsetPtr[ index ] = ptr[ index ];
		auto typeUnitySize = residueSize / dataArrayCount;
		converEndian( offsetPtr, typeUnitySize ); // 逆转上一个元素
	} else if( dataType == 2 ) { // 列表
		auto typeUnitySize = residueSize / dataArrayCount; // 元素大小
		ptr = dataArrayShared.get( );
		index = 0;
		for( uint64_t subIndex = 0; true; ++index ) {
			for( ; subIndex < typeUnitySize; ++subIndex )
				offsetPtr[ subIndex ] = ptr[ subIndex ];
			converEndian( offsetPtr, typeUnitySize ); // 逆转上一个元素
			if( index == dataArrayCount )
				break;
			offsetPtr += typeUnitySize;
			ptr += typeUnitySize;
			subIndex = 0;
		}

	}
	return resultSPtr;
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
