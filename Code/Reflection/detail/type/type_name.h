#ifndef __REFL_TYPE_NAME_H__
#define __REFL_TYPE_NAME_H__

#include "defs.h"
#include "string_view.h"

namespace Reflection
{
	namespace Detail
	{
		template<typename T>
		REFL_INLINE static StringView getTypeName() REFL_NOEXCEPT
		{
			return StringView("null", 0);
		}
	}
}

#endif