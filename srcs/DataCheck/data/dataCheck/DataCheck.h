#ifndef DATACHECK_H_H_HEAD__FILE__
#define DATACHECK_H_H_HEAD__FILE__
#pragma once

#include "../../nameSpace/cylDataCheck.h"
namespace cylDataCheck {
	class DATACHECK_EXPORT DataCheck {
	public: // - 友元
		template< typename T_Serialization_Data_ >
		friend class Serialization;
		template< typename T_Serialization_Data_ >
		friend class Unserialize;
	private:
		/// <summary>
		/// 判断当前环境是否是大端
		/// </summary>
		/// <returns>返回 true 表示大端</returns>
		static bool isBegEndian( );
	private:
		static bool begEndian; // 大小端识别
	public:
		static bool nativeIsBegEndian( ) {
			return begEndian;
		}

		/// <summary>
		/// 内存翻转，把指向大小的排序进行反序(uint8_t 元素反序)
		/// </summary>
		/// <param name="ptr">内存指针</param>
		/// <param name="size">转换长度</param>
		static void converEndian( uint8_t *ptr, uint64_t size );
	private:
		bool currentEndian;// 当前大小端
		uint64_t dataSize; // 数据占用大小
		uint64_t dataType; // 数据类型
		uint64_t dataArrayCount; // 数据列表个数
		std::shared_ptr< uint8_t[ ] > dataArrayShared; // 数据列表
	public:
		virtual ~DataCheck( );
		/// <summary>
		/// 创建一个校验串
		/// </summary>
		/// <param name="current_endian">大小端，true 表示大端</param>
		/// <param name="data_size">整个数据大小(包含：端/data_size本身/data_type/data_array_shared)</param>
		/// <param name="data_type">数据类型</param>
		/// <param name="data_array_shared">数据指针</param>
		/// <param name="data_array_count">data_array_shared 长度</param>
		DataCheck( bool current_endian, uint64_t data_size, uint64_t data_type, const std::shared_ptr< uint8_t[ ] > &data_array_shared, const uint64_t data_array_count );
		/// <summary>
		/// 从一个已经被序列化的对象初始化校验串
		/// </summary>
		/// <param name="serialization_data">已经被序列化的对象</param>
		DataCheck(uint8_t* serialization_data);
	public:
		/// <summary>
		/// 序列化到大端数据
		/// </summary>
		/// <returns>大端数据序列</returns>
		Data_Array converBegEndian( );
		/// <summary>
		/// 序列化到小端数据
		/// </summary>
		/// <returns>小端数据序列</returns>
		Data_Array converLittleEndian( );

	};
}

#endif // DATACHECK_H_H_HEAD__FILE__
