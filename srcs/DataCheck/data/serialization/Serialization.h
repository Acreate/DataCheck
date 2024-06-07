#ifndef SERIALIZATION_H_H_HEAD__FILE__
#define SERIALIZATION_H_H_HEAD__FILE__
#pragma once

#include <cstdint>

#include "../../nameSpace/cylDataCheck.h"
#include "../dataCheck/DataCheck.h"
namespace cylDataCheck {

	template< typename T_Serialization_Data_Unity >
	class DATACHECK_EXPORT Serialization {

	private: // - 静态成员
		static uint64_t firstUnitySize;   // 首个单元大小（首个单元记录元素长度）
		static uint64_t type;   // 可以序列化的类型
	public: // - 成员
		/// <summary>
		/// 序列化数据
		/// </summary>
		/// <param name="serialization_data">被序列化的对象</param>
		/// <param name="data_serialization_result_len">返回序列化数据的长度</param>
		/// <returns>序列化对象，失败返回 nullptr</returns>
		static Data_Array serialization( const T_Serialization_Data_Unity &serialization_data, uint64_t &data_serialization_result_len );
	};


	template< typename T_Serialization_Data_Array_Ptr >
	class DATACHECK_EXPORT Serialization< T_Serialization_Data_Array_Ptr [ ] > {
	private: // - 静态成员
		static uint64_t firstUnitySize;   // 首个单元大小（首个单元记录元素长度）
		static uint64_t type;   // 可以序列化的类型
	public: // - 成员
		/// <summary>
		/// 序列化数据
		/// </summary>
		/// <param name="serialization_data">被序列化的对象</param>
		/// <param name="array_count">序列化数组个数</param>
		/// <param name="data_serialization_result_len">返回序列化数据的长度</param>
		/// <returns>序列化对象，失败返回 nullptr</returns>
		static Data_Array serialization( const T_Serialization_Data_Array_Ptr *serialization_data, const uint64_t &array_count, uint64_t &data_serialization_result_len );
	};
	
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
	
}
	
#endif // SERIALIZATION_H_H_HEAD__FILE__
