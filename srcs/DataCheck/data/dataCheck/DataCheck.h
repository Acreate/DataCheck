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

	};
}

#endif // DATACHECK_H_H_HEAD__FILE__
