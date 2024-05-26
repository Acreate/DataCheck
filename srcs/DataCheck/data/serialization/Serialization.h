#ifndef SERIALIZATION_H_H_HEAD__FILE__
#define SERIALIZATION_H_H_HEAD__FILE__
#pragma once

#include <cstdint>

#include "../../nameSpace/cylDB.h"
namespace cylDB {
	class QTEXTENDDB_EXPORT Serialization {
	private: // - 成员
		bool begEndian;
	public:
		virtual ~Serialization( );
	private: // - 构造器
		Serialization( );
	private: // - 静态成员
		static Serialization instance;
	public: // - 静态类
		/// <summary>
		/// 获取实例
		/// </summary>
		/// <returns>实例对象指针</returns>
		static Serialization * getInstance( );
	public: // - 成员
		/// <summary>
		/// 判断当前环境是否是大端
		/// </summary>
		/// <returns>返回 true 表示大端</returns>
		bool isBegEndian( ) {
			return begEndian;
		}
		/// <summary>
		/// 序列化数据
		/// </summary>
		/// <param name="serialization_data">被序列化的对象</param>
		/// <param name="data_serialization_result_len">返回序列化数据的长度</param>
		/// <returns>序列化对象，失败返回 nullptr</returns>
		Data_Array serialization( const bool &serialization_data, uint64_t &data_serialization_result_len );
		/// <summary>
		/// 序列化数据
		/// </summary>
		/// <param name="serialization_data">被序列化的对象</param>
		/// <param name="data_serialization_result_len">返回序列化数据的长度</param>
		/// <returns>序列化对象，失败返回 nullptr</returns>
		Data_Array serialization( const short &serialization_data, uint64_t &data_serialization_result_len );
		/// <summary>
		/// 序列化数据
		/// </summary>
		/// <param name="serialization_data">被序列化的对象</param>
		/// <param name="data_serialization_result_len">返回序列化数据的长度</param>
		/// <returns>序列化对象，失败返回 nullptr</returns>
		Data_Array serialization( const int &serialization_data, uint64_t &data_serialization_result_len );
		/// <summary>
		/// 序列化数据
		/// </summary>
		/// <param name="serialization_data">被序列化的对象</param>
		/// <param name="data_serialization_result_len">返回序列化数据的长度</param>
		/// <returns>序列化对象，失败返回 nullptr</returns>
		Data_Array serialization( const long &serialization_data, uint64_t &data_serialization_result_len );
		/// <summary>
		/// 序列化数据
		/// </summary>
		/// <param name="serialization_data">被序列化的对象</param>
		/// <param name="data_serialization_result_len">返回序列化数据的长度</param>
		/// <returns>序列化对象，失败返回 nullptr</returns>
		Data_Array serialization( const long long &serialization_data, uint64_t &data_serialization_result_len );
		/// <summary>
		/// 序列化数据
		/// </summary>
		/// <param name="serialization_data">被序列化的对象</param>
		/// <param name="data_serialization_result_len">返回序列化数据的长度</param>
		/// <returns>序列化对象，失败返回 nullptr</returns>
		Data_Array serialization( const unsigned short &serialization_data, uint64_t &data_serialization_result_len );
		/// <summary>
		/// 序列化数据
		/// </summary>
		/// <param name="serialization_data">被序列化的对象</param>
		/// <param name="data_serialization_result_len">返回序列化数据的长度</param>
		/// <returns>序列化对象，失败返回 nullptr</returns>
		Data_Array serialization( const unsigned int &serialization_data, uint64_t &data_serialization_result_len );
		/// <summary>
		/// 序列化数据
		/// </summary>
		/// <param name="serialization_data">被序列化的对象</param>
		/// <param name="data_serialization_result_len">返回序列化数据的长度</param>
		/// <returns>序列化对象，失败返回 nullptr</returns>
		Data_Array serialization( const unsigned long &serialization_data, uint64_t &data_serialization_result_len );
		/// <summary>
		/// 序列化数据
		/// </summary>
		/// <param name="serialization_data">被序列化的对象</param>
		/// <param name="data_serialization_result_len">返回序列化数据的长度</param>
		/// <returns>序列化对象，失败返回 nullptr</returns>
		Data_Array serialization( const unsigned long long &serialization_data, uint64_t &data_serialization_result_len );
		/// <summary>
		/// 序列化数据
		/// </summary>
		/// <param name="serialization_data">被序列化的对象</param>
		/// <param name="data_serialization_result_len">返回序列化数据的长度</param>
		/// <returns>序列化对象，失败返回 nullptr</returns>
		Data_Array serialization( const float &serialization_data, uint64_t &data_serialization_result_len );
		/// <summary>
		/// 序列化数据
		/// </summary>
		/// <param name="serialization_data">被序列化的对象</param>
		/// <param name="data_serialization_result_len">返回序列化数据的长度</param>
		/// <returns>序列化对象，失败返回 nullptr</returns>
		Data_Array serialization( const double &serialization_data, uint64_t &data_serialization_result_len );
	};
}

#endif // SERIALIZATION_H_H_HEAD__FILE__
