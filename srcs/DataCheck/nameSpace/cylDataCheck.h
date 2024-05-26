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
	/// 序列化
	/// </summary>
	class DATACHECK_EXPORT Serialization;
	/// <summary>
	/// 反序列化
	/// </summary>
	class DATACHECK_EXPORT Unserialize;
	/// <summary>
	/// 数据列
	/// </summary>
	using Data_Array = std::shared_ptr< uint8_t[ ] >;
}

#endif // CYLDB_H_H_HEAD__FILE__
