#ifndef __REFL_TYPE_DATA_H__
#define __REFL_TYPE_DATA_H__

#include <string>
#include "defs.h"
#include "type_name.h"

namespace Reflection
{
	template<typename T, typename Enable = void>
	struct get_size_of
	{
		REFL_INLINE REFL_CONSTEXPR static size_t value()
		{
			return sizeof(T);
		}
	};

	namespace Detail
	{
		struct TypeData
		{
			using type_id = uint16_t;
			std::string m_Name;
			StringView  m_TypeName;
			size_t		m_SizeOf;

			type_id m_TypeId;
			static const type_id s_InvalidTypeId = 0;

			REFL_INLINE bool isValid() const REFL_NOEXCEPT { return m_TypeId != s_InvalidTypeId; }
		};

		REFL_INLINE TypeData get_invalid_type_data() REFL_NOEXCEPT
		{
			static TypeData instance = { std::string(""), StringView(), 0 };
			return instance;
		}

		template<typename T>
		TypeData& getTypeData() REFL_NOEXCEPT
		{
			static TypeData instance = TypeData{ getTypeName<T>().to_string(), getTypeName<T>(), get_size_of<T>::value()};
			return instance;
		}
	}
}

#endif