#ifndef __REFL_TYPE_NAME_H__
#define __REFL_TYPE_NAME_H__

#include "defs.h"
#include "string_view.h"

namespace Reflection
{
	namespace Detail
	{
		template<typename T>
		REFL_INLINE static const char* extract_signature() REFL_NOEXCEPT
		{
			//because signature come from marco, we have to use static inline function
			//to make each translation unit have different definition.
			const char* signature = __FUNCSIG__;
			const unsigned int cut_begin = 58;
			return &signature[cut_begin];
		}

		REFL_INLINE size_t get_size(const char* s) REFL_NOEXCEPT
		{
			const unsigned int cut_end = 7;
			return std::char_traits<char>::length(s) - cut_end;
		}
		template<typename T>
		REFL_INLINE static StringView getTypeName() REFL_NOEXCEPT
		{
			return StringView(extract_signature<T>(), get_size(extract_signature<T>()));
		}
	}
}

#endif