#ifndef CYLDB_H_H_HEAD__FILE__
#define CYLDB_H_H_HEAD__FILE__
#pragma once

#include "../auto_generate_files/export/DataCheck_export.h"
#include <memory>
namespace cylDataCheck {
	/// <summary>
	/// 校验类
	/// </summary>
	class DATACHECK_EXPORT DataCheck;
	/// <summary>
	/// 文件系统
	/// </summary>
	class DATACHECK_EXPORT FileSystem;
	/// <summary>
	/// 文件
	/// </summary>
	class DATACHECK_EXPORT File;
	/// <summary>
	/// 目录
	/// </summary>
	class DATACHECK_EXPORT Dir;
	/// <summary>
	/// 序列化
	/// </summary>
	template< typename T_Serialization_Data_Unity >
	class DATACHECK_EXPORT Serialization;
	/// <summary>
	/// 反序列化
	/// </summary>
	template< typename T_Serialization_Data_Unity >
	class DATACHECK_EXPORT Unserialize;
	/// <summary>
	/// 数据列
	/// </summary>
	using Data_Array = std::shared_ptr< uint8_t[ ] >;
	/// <summary>
	/// 数据串
	/// </summary>
	using DataCheck_Shared = std::shared_ptr< DataCheck >;
}

#endif // CYLDB_H_H_HEAD__FILE__
