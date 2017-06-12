#include "type.h"
#include "detail/type/type_impl.h"
#include "detail/type/type_data.h"
#include <cassert>

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
		assert(source_type.m_Data->m_RawTypeData == source_type.m_Data);
		assert(target_type.m_Data->m_RawTypeData == target_type.m_Data);

		if (ptr == nullptr)
		{
			return ptr;
		}

		REFL_TODO; //use derived info?
		
		Detail::ClassData& classdata = source_type.m_Data->get_class_data_func();
		for (int i = 0; i < classdata.m_BaseTypes.size(); ++i)
		{
			if (classdata.m_BaseTypes[i].m_Data == target_type.m_Data)
			{
				return classdata.m_cast_funcs[i](ptr);
			}
		}
		return nullptr;
	}
}