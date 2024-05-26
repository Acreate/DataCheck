#ifndef SERIALIZATION_H_H_HEAD__FILE__
#define SERIALIZATION_H_H_HEAD__FILE__
#pragma once

#include <cstdint>

#include "../../nameSpace/cylDataCheck.h"
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
}

#endif // SERIALIZATION_H_H_HEAD__FILE__
