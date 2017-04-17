#ifndef __REFL_TYPE_H__
#define __REFL_TYPE_H__

#include <type_traits>
#include "defs.h"
#include "detail/type/type_data.h"
#include "detail/type/type_register.h"

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
		REFL_INLINE Type(const Detail::TypeData* data) REFL_NOEXCEPT;

		template<typename T>
		static Type get() REFL_NOEXCEPT;

		REFL_INLINE const Detail::TypeData::type_id get_id() const REFL_NOEXCEPT;
	private:
		const Detail::TypeData* m_Data;
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
				static const Type instance = TypeRegister::type_reg(getTypeData<T>());
				return instance;
			}
		};

	}

	REFL_TODO;//why need specfication for void and fun ptr


	REFL_INLINE Type::Type(const Detail::TypeData* data)
		: m_Data(data)
	{};

	template<typename T>
	REFL_INLINE Type Type::get() REFL_NOEXCEPT
	{
		return Detail::TypeGetter<std::remove_cv_t<std::remove_reference_t<T>>>::getType();
	}

	REFL_INLINE const Detail::TypeData::type_id Type::get_id() const REFL_NOEXCEPT
	{
		return m_Data->m_TypeId;
	}

}

#endif