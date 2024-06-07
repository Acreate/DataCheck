#ifndef UNSERIALIZE_H_H_HEAD__FILE__
#define UNSERIALIZE_H_H_HEAD__FILE__
#pragma once
#include "../../nameSpace/cylDataCheck.h"
#include "../dataCheck/DataCheck.h"
namespace cylDataCheck {

	template< typename T_Serialization_Data_Unity >
	class DATACHECK_EXPORT Unserialize {

	private: // - 静态成员
		static uint64_t firstUnitySize;   // 首个单元大小（首个单元记录元素长度）
		static uint64_t type;   // 可以还原的类型
	public: // - 成员
		/// <summary>
		/// 从数据当中还原对象
		/// </summary>
		/// <param name="serialization_data">源数据</param>
		/// <param name="data_serialization_result_count">还原对象</param>
		/// <returns>使用数据长度，失败返回 0</returns>
		static uint64_t unserialize( const uint8_t *serialization_data, std::shared_ptr< T_Serialization_Data_Unity > &data_serialization_result_count );
	};


	template< typename T_Serialization_Data_Array_Ptr >
	class DATACHECK_EXPORT Unserialize< T_Serialization_Data_Array_Ptr [ ] > {
	private: // - 静态成员
		static uint64_t firstUnitySize;   // 首个单元大小（首个单元记录元素长度）
		static uint64_t type;   // 可以还原的类型
	public: // - 成员
		/// <summary>
		/// 从数据当中还原对象
		/// </summary>
		/// <param name="serialization_data">源数据</param>
		/// <param name="data_serialization_result">还原对象</param>
		/// <param name="data_serialization_result_count">还原对象元素个数</param>
		/// <returns>使用数据长度，失败返回 0</returns>
		static uint64_t unserialize( const uint8_t *serialization_data, std::shared_ptr< T_Serialization_Data_Array_Ptr[ ] > &data_serialization_result, uint64_t &data_serialization_result_count );
	};
	
	
	
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
	uint64_t Unserialize< T_Serialization_Data_Unity >::unserialize( const uint8_t *serialization_data, std::shared_ptr< T_Serialization_Data_Unity > &data_serialization_result_SPtr ) {
		uint8_t isbegEndian = *serialization_data;
		if( isbegEndian != DataCheck::begEndian ) // 大小端不匹配
			return 0;
		// 跳过大小端信息数据段
		uint64_t endianFlagSize = sizeof( DataCheck::begEndian );
		serialization_data = serialization_data + endianFlagSize;
		
		// 读取总长度
		uint64_t maxBuffLenSize = sizeof( uint64_t );
		uint64_t userCount = analysisMemoryReadCount( serialization_data, maxBuffLenSize );
		// 跳过数据总长度数据段
		serialization_data = serialization_data + maxBuffLenSize;
		// 读取类型
		uint64_t typeSize = sizeof( type );
		uint64_t type = analysisMemoryReadCount( serialization_data, typeSize );
		if( type != 1 ) // 类型不一致
			return 0;
		// 跳过类型配置数据段
		serialization_data = serialization_data + typeSize;
		// 读取元素个数
		uint64_t arrayCounSize = sizeof( uint64_t );
		uint64_t array_count = analysisMemoryReadCount( serialization_data, arrayCounSize );
		if( array_count == 0 )
			return 0;
		uint64_t serializationDataSize = sizeof( T_Serialization_Data_Unity );
		auto residueDataSize = userCount - typeSize - arrayCounSize - endianFlagSize - maxBuffLenSize; // 剩余数据长度
		if( residueDataSize < serializationDataSize * array_count )  // 没有剩余的空间，将会直接返回
			return userCount;
		
		serialization_data = serialization_data + arrayCounSize;
		T_Serialization_Data_Unity *resultPtr = new T_Serialization_Data_Unity;
		uint8_t *ptr = reinterpret_cast< uint8_t * >( resultPtr );
		for( auto index = 0; index < residueDataSize; ++index )
			ptr[ index ] = serialization_data[ index ];
		data_serialization_result_SPtr = std::shared_ptr< T_Serialization_Data_Unity >( resultPtr, []( T_Serialization_Data_Unity *p ) {
			delete p;
		} );
		return userCount;
		}
	
	
	template< typename T_Serialization_Data_Array_Ptr >
	uint64_t Unserialize< T_Serialization_Data_Array_Ptr [ ] >::unserialize( const uint8_t *serialization_data, std::shared_ptr< T_Serialization_Data_Array_Ptr[ ] > &data_serialization_result, uint64_t &data_serialization_result_count ) {
		
		uint8_t isbegEndian = *serialization_data;
		if( isbegEndian != DataCheck::begEndian ) // 大小端不匹配
			return 0;
		// 跳过大小端信息数据段
		uint64_t endianFlagSize = sizeof( DataCheck::begEndian );
		serialization_data = serialization_data + endianFlagSize;
		
		// 读取总长度
		uint64_t maxBuffLenSize = sizeof( uint64_t );
		uint64_t userCount = analysisMemoryReadCount( serialization_data, maxBuffLenSize );
		// 跳过数据总长度数据段
		serialization_data = serialization_data + maxBuffLenSize;
		// 读取类型
		uint64_t typeSize = sizeof( type );
		uint64_t type = analysisMemoryReadCount( serialization_data, typeSize );
		if( type != 2 ) // 类型不一致
			return 0;
		// 跳过类型配置数据段
		serialization_data = serialization_data + typeSize;
		// 读取元素个数
		uint64_t arrayCounSize = sizeof( uint64_t );
		data_serialization_result_count = analysisMemoryReadCount( serialization_data, arrayCounSize );
		if( data_serialization_result_count == 0 )
			return 0;
		uint64_t serializationDataSize = sizeof( T_Serialization_Data_Array_Ptr );
		auto residueDataSize = userCount - typeSize - arrayCounSize - endianFlagSize - maxBuffLenSize; // 剩余数据长度
		if( residueDataSize < serializationDataSize * data_serialization_result_count )  // 没有剩余的空间，将会直接返回
			return userCount;
		// 元素个数计数段
		serialization_data = serialization_data + arrayCounSize;
		
		T_Serialization_Data_Array_Ptr *resultPtr = new T_Serialization_Data_Array_Ptr[ data_serialization_result_count ];
		uint8_t *ptr = reinterpret_cast< uint8_t * >( resultPtr );
		for( auto index = 0; index < residueDataSize; ++index )
			ptr[ index ] = serialization_data[ index ];
		data_serialization_result = std::shared_ptr< T_Serialization_Data_Array_Ptr [ ] >( resultPtr, []( T_Serialization_Data_Array_Ptr *p ) {
			delete [] p;
		} );
		return userCount;
		}
	
	
}
	
#endif // UNSERIALIZE_H_H_HEAD__FILE__
