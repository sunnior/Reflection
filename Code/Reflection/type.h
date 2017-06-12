#ifndef __REFL_TYPE_H__
#define __REFL_TYPE_H__

#include <string>
#include "defs.h"
#include "detail/type/type_id.h"

namespace Reflection
{
	namespace Detail
	{
		template<typename T, typename Enable = void>
		struct TypeGetter;
		struct TypeData;
		class TypeRegisterPrivate;
	}

	class REFL_API Type
	{
	public:
		REFL_INLINE Type() REFL_NOEXCEPT;
		REFL_INLINE Type(Detail::TypeData* data) REFL_NOEXCEPT;

		REFL_INLINE const Detail::type_id get_id() const REFL_NOEXCEPT;
		REFL_INLINE bool isValid() const REFL_NOEXCEPT;

	public:
		template<typename T>
		REFL_INLINE static Type get() REFL_NOEXCEPT;
		static Type get_by_name(std::string name) REFL_NOEXCEPT;
	
	private:
		static void* apply_offset(void* ptr, const Type& source_type, const Type& target_type) REFL_NOEXCEPT;

	private:
		Detail::TypeData* m_Data;

	private:
		friend Detail::TypeRegisterPrivate;
		template<typename TargetType, typename SourceType>
		friend TargetType refl_cast(SourceType object) REFL_NOEXCEPT;
	};
}

#endif