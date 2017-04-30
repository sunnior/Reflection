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
		REFL_INLINE Type() REFL_NOEXCEPT;
		REFL_INLINE Type(Detail::TypeData* data) REFL_NOEXCEPT;

		template<typename T>
		static Type get() REFL_NOEXCEPT;
		static Type get_by_name(std::string name) REFL_NOEXCEPT;

		REFL_INLINE const Detail::TypeData::type_id get_id() const REFL_NOEXCEPT;
		REFL_INLINE bool isValid() const REFL_NOEXCEPT;

		friend class Detail::TypeRegisterPrivate;
	private:
		Detail::TypeData* m_Data;
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

	template<typename T>
	REFL_INLINE Type Type::get() REFL_NOEXCEPT
	{
		return Detail::TypeGetter<std::remove_cv_t<std::remove_reference_t<T>>>::getType();
	}

	REFL_INLINE Type Type::get_by_name(std::string name) REFL_NOEXCEPT
	{
		std::map<std::string, Type>& custom_map = Detail::TypeRegisterPrivate::get_type_custom_name_map();
		auto& it = custom_map.find(name);
		if (it != custom_map.end())
		{
			return it->second;
		}

		return Detail::get_invalid_type();
	}


	REFL_INLINE const Detail::TypeData::type_id Type::get_id() const REFL_NOEXCEPT
	{
		return m_Data->m_TypeId;
	}

	REFL_INLINE bool Type::isValid() const REFL_NOEXCEPT
	{
		return m_Data->isValid();
	}

}

#endif