#include "type_register.h"
#include "type.h"
#include "type_data.h"

namespace Reflection
{
	namespace Detail
	{
		std::vector<const TypeData*>& TypeRegisterPrivate::get_type_data_storage()
		{
			static std::vector<const TypeData*> objs = { &get_invalid_type_data() };
			return objs;
		}

		std::map<StringView, Type>& TypeRegisterPrivate::get_type_name_map()
		{
			REFL_TODO;//can I use char* here?
			static std::map<StringView, Type> obj;
			return obj;
		}

		const bool TypeRegisterPrivate::register_name(TypeData::type_id& id, TypeData& info) REFL_NOEXCEPT
		{
			auto& name_map = get_type_name_map();
			auto ret = name_map.find(info.m_TypeName);
			if (ret != name_map.end())
			{
				id = ret->second.get_id();
				return true;
			}

			static TypeData::type_id m_type_id_counter = 0;
			++m_type_id_counter;

			id = m_type_id_counter;
			name_map.insert(std::make_pair(info.m_TypeName, Type(&info)));
			info.m_TypeId = id;
			return false;
		}


		Type TypeRegisterPrivate::register_type(TypeData& info) REFL_NOEXCEPT
		{
			auto& type_data_container = get_type_data_storage();
			TypeData::type_id id = 0;
			const bool isAlreadyRegistered = register_name(id, info);
			if (isAlreadyRegistered)
				return Type(type_data_container[id]);

			type_data_container.push_back(&info);

			return Type(type_data_container[id]);
		}

		Type TypeRegister::type_reg(TypeData& info) REFL_NOEXCEPT
		{
			return TypeRegisterPrivate::register_type(info);
		}
	}
}