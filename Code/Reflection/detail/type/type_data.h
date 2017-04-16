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
			std::string m_Name;
			StringView  m_TypeName;
			size_t		m_SizeOf;
		};

		template<typename T>
		const TypeData& getTypeData() REFL_NOEXCEPT
		{
			static TypeData instance = TypeData{ getTypeName<T>().to_string(), getTypeName<T>(), get_size_of<T>::value()};
			return instance;
		}
	}
}

#endif