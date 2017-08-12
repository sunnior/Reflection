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
#if defined(REFL_COMPILER_MSVC)
			const char* signature = __FUNCSIG__;
            // sizeof("const char *__cdecl rttr::detail::extract_signature<"), sizeof(">(void)")
            const unsigned int cut_begin = 58;
#elif defined(REFL_COMPILER_CLANG)
            const char* signature = __PRETTY_FUNCTION__;
            //sizeof("const char *Reflection::Detail::extract_signature() [T = "), sizeof(]")
            const unsigned int cut_begin = 56;
#else
#error not supported.
#endif
			return &signature[cut_begin];
		}

		REFL_INLINE size_t get_size(const char* s) REFL_NOEXCEPT
		{
#if defined(REFL_COMPILER_MSVC)
            // sizeof("const char *__cdecl rttr::detail::extract_signature<"), sizeof(">(void)")
            const unsigned int cut_end = 7;
#elif defined(REFL_COMPILER_CLANG)
            //sizeof("const char *Reflection::Detail::extract_signature() [T = "), sizeof(]")
            const unsigned int cut_end = 1;
#else
#error not supported.
#endif

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