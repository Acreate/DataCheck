#ifndef UNSERIALIZE_H_H_HEAD__FILE__
#define UNSERIALIZE_H_H_HEAD__FILE__
#pragma once
#include "../../nameSpace/cylDataCheck.h"
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
}


#endif // UNSERIALIZE_H_H_HEAD__FILE__
