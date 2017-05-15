#ifndef __REFL_CAST_H__
#define __REFL_CAST_H__

#include "defs.h"

namespace Reflection
{
	template<typename TargetType, typename SourceType>
	REFL_INLINE TargetType refl_cast(SourceType object) REFL_NOEXCEPT;
}

#include "detail/misc/misc_type_traits.h"

namespace Reflection
{
	template<typename TargetType, typename SourceType>
	REFL_INLINE TargetType refl_cast(SourceType object) REFL_NOEXCEPT
	{
		static_assert(detail::pointer_count<SourceType>::value == 1, "Argument type must be a pointer");
		static_assert(detail::pointer_count<TargetType>::value == 1, "Return type must be a pointer");
		REFL_TODO;//has_get_type_func

		using ReturnType = std::remove_pointer_t<TargetType>;
		using ArgType = std::remove_extent_t<SourceType>;
		REFL_TODO;//volatile, const match.
		
		using source_type_no_cv = std::remove_cv_t<std::remove_pointer_t<SourceType>>;
		return static_cast<TargetType>(Type::apply_offset(const_cast<source_type_no_cv*>(object)->getPtr(), const_cast<source_type_no_cv*>(object)->getType(), Type::get<TargetType>()));
	}
}

#endif