#ifndef __REFL_TYPE_IMPL_H__
#define __REFL_TYPE_IMPL_H__


#include <type_traits>
#include "detail/type/type_register.h"
#include "detail/type/type_data.h"

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
				static const Type instance = TypeRegister::register_type(getTypeData<T>(), &BaseClasses<T>::get_base_classes_info);
				return instance;
			}
		};
		
		template<typename T>
		Type getTypeFromInstance(T* instance)
		{
			return Type::get<T>();
		}
		
		REFL_INLINE Type get_invalid_type() REFL_NOEXCEPT
		{
			return Type();
		}
	}
	
	REFL_TODO;//why need specfication for void and fun ptr
	
	REFL_INLINE Type::Type() REFL_NOEXCEPT
		: m_Data(&Detail::get_invalid_type_data())
	{
	}

	REFL_INLINE Type::Type(Detail::TypeData* data) REFL_NOEXCEPT
		: m_Data(data)
	{};
	
		
	REFL_INLINE const Detail::type_id Type::get_id() const REFL_NOEXCEPT
	{
		return m_Data->m_TypeId;
	}
	
	REFL_INLINE bool Type::isValid() const REFL_NOEXCEPT
	{
		return m_Data->isValid();
	}
	
	template<typename T>
	REFL_INLINE Type Type::get() REFL_NOEXCEPT
	{
		return Detail::TypeGetter<std::remove_cv_t<std::remove_reference_t<T>>>::getType();
	}
	
}

#endif