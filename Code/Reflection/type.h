#ifndef __REFL_TYPE_H__
#define __REFL_TYPE_H__

#include <type_traits>
#include "defs.h"
#include "detail/type/type_data.h"

namespace Reflection
{
	namespace Detail
	{
		template<typename T, typename Enable = void>
		struct TypeGetter;
	}

	class REFL_API Type
	{
	public:
		template<typename T>
		static Type get() REFL_NOEXCEPT;
	};
}

namespace Reflection
{
	namespace Detail
	{
		REFL_TODO;//why need Enable
		template<typename T, typename Enable>
		struct TypeGetter
		{
			static Type getType() REFL_NOEXCEPT
			{
				REFL_TODO;//How type_must_be_complete works?
				getTypeData<T>();
				return Type();
			}
		};

	}

	REFL_TODO;//why need specfication for void and fun ptr

	template<typename T>
	REFL_INLINE Type Type::get() REFL_NOEXCEPT
	{
		return Detail::TypeGetter<std::remove_cv_t<std::remove_reference_t<T>>>::getType();
	}
}

#endif