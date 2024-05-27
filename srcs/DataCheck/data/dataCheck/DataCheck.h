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
		static uint8_t begEndian; // 大小端识别
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
		uint8_t currentEndian;// 当前大小端
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
		DataCheck( uint8_t *serialization_data );
		/// <summary>
		/// 从一个已经被序列化的对象初始化校验串
		/// </summary>
		/// <param name="serialization_data">已经被序列化的对象</param>
		DataCheck( std::shared_ptr< uint8_t[ ] > serialization_data ): DataCheck( serialization_data.get( ) ) {
		}
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
		/// <summary>
		/// 小端序列化内容
		/// </summary>
		/// <returns>被序列化的串</returns>
		Data_Array littleEndianSerialization( );
		/// <summary>
		/// 大端序列化内容
		/// </summary>
		/// <returns>被序列化的串</returns>
		Data_Array bigEndianSerialization( );
	public: // - 属性

		/// <summary>
		/// 获取串的大小端信息
		/// </summary>
		/// <returns>等于0表示小端，否则等于大端</returns>
		uint8_t getCurrentEndian( ) const { return currentEndian; }
		/// <summary>
		/// 数据串的总数据占用
		/// </summary>
		/// <returns>总长度</returns>
		uint64_t getDataSize( ) const { return dataSize; }
		/// <summary>
		/// 获取数据串的类型
		/// </summary>
		/// <returns>类型 1 为单元素对象， 2 为数组元素对象</returns>
		uint64_t getDataType( ) const { return dataType; }
		/// <summary>
		/// 获取数据串中的数据个数
		/// </summary>
		/// <returns>单元数对象总是小于或者等于1，数据元素对象大于或者等于0</returns>
		uint64_t getDataArrayCount( ) const { return dataArrayCount; }
		/// <summary>
		/// 获取数据段的起始地址
		/// </summary>
		/// <returns>指向数据段的起始指针</returns>
		const uint8_t * getDataArrayPtr( ) const { return dataArrayShared.get( ); }
		/// <summary>
		/// 获取数据段数据的个数
		/// </summary>
		/// <returns>个数</returns>
		uint64_t getDataArrayLen( ) const {
			return dataSize - sizeof( currentEndian ) - sizeof( dataSize ) - sizeof( dataType ) - sizeof( dataArrayCount );
		}
	};
}

#endif // DATACHECK_H_H_HEAD__FILE__
