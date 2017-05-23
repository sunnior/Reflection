#include "type.h"

namespace Reflection
{
	Type Type::get_by_name(std::string name) REFL_NOEXCEPT
	{
		std::map<std::string, Type>& custom_map = Detail::TypeRegisterPrivate::get_type_custom_name_map();
		auto& it = custom_map.find(name);
		if (it != custom_map.end())
		{
			return it->second;
		}

		return Detail::get_invalid_type();
	}

	void* Type::apply_offset(void* ptr, const Type& source_type, const Type& target_type) REFL_NOEXCEPT
	{
		if (ptr == nullptr)
		{
			return ptr;
		}

		Detail::TypeData* src_raw_type = source_type.m_Data->m_RawTypeData;
		Detail::TypeData* tar_raw_type = target_type.m_Data->m_RawTypeData;
		if (src_raw_type == tar_raw_type)
		{
			return ptr;
		}
		return ptr;
	}
}