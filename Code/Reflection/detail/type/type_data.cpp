#include "type_data.h"

namespace Reflection
{
	namespace Detail
	{
		TypeData& get_invalid_type_data_impl() REFL_NOEXCEPT
		{
			static TypeData instance = TypeData{ nullptr, std::string(""), StringView(), 0, TypeData::s_InvalidTypeId };
			instance.m_RawTypeData = &instance;
			return instance;
		}
	}
}