#ifndef __STRING_VIEW_H__
#define __STRING_VIEW_H__

#include "defs.h"

namespace Reflection
{
	template<typename CharT>
	class BasicStringView
	{
	public:
		using size_type = size_t;
		REFL_CONSTEXPR BasicStringView(const CharT* str, size_type len);
	};

	using StringView = BasicStringView<char>;
}

namespace Reflection
{
	template<typename CharT>
	REFL_CONSTEXPR BasicStringView<CharT>::BasicStringView(const CharT* str, size_type len)
	{

	}
}

#endif