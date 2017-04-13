#ifndef __REFL_TYPE_DATA_H__
#define __REFL_TYPE_DATA_H__

#include <string>
#include "defs.h"
#include "type_name.h"

namespace Reflection
{
	namespace Detail
	{
		struct TypeData
		{
			std::string m_Name;
			size_t		m_SizeOf;
		};

		template<typename T>
		const TypeData& getTypeData() REFL_NOEXCEPT
		{
			static TypeData instance = TypeData{};
			getTypeName<T>();
			return instance;
		}
	}
}

#endif