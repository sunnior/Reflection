#include "type_register.h"

#include <algorithm>
#include <cassert>

#include "type.h"
#include "type_data.h"
#include "type_impl.h"


namespace Reflection
{
	class Type;

	namespace Detail
	{
		std::vector<TypeData*>& TypeRegisterPrivate::get_type_data_storage()
		{
			static std::vector<TypeData*> objs = { &get_invalid_type_data() };
			return objs;
		}

		std::map<StringView, Type>& TypeRegisterPrivate::get_type_name_map()
		{
			REFL_TODO;//can I use char* here?
			REFL_TODO;//use flat map, we don't need tree structure.
			static std::map<StringView, Type> obj;
			return obj;
		}

		std::map<std::string, Type>& TypeRegisterPrivate::get_type_custom_name_map()
		{
			static std::map<std::string, Type> obj;
			return obj;
		}


		const bool TypeRegisterPrivate::register_name(type_id& id, TypeData& info) REFL_NOEXCEPT
		{
			auto& name_map = get_type_name_map();
			auto ret = name_map.find(info.m_TypeName);
			if (ret != name_map.end())
			{
				id = ret->second.get_id();
				return true;
			}

			static type_id m_type_id_counter = 0;
			++m_type_id_counter;

			id = m_type_id_counter;
			name_map.insert(std::make_pair(info.m_TypeName, Type(&info)));
			get_type_custom_name_map().insert(std::make_pair(info.m_Name, Type(&info)));
			info.m_TypeId = id;
			return false;
		}


		Type TypeRegisterPrivate::register_type_impl(TypeData& info, get_base_calsses_info_func func) REFL_NOEXCEPT
		{
			auto& type_data_container = get_type_data_storage();
			type_id id = 0;
			const bool isAlreadyRegistered = register_name(id, info);
			if (isAlreadyRegistered)
				return Type(type_data_container[id]);

			info.m_RawTypeData = info.m_RawTypeData->isValid() ? info.m_RawTypeData : &info;
			type_data_container.push_back(&info);

			register_base_classes_info(info, func);

			return Type(type_data_container[id]);
		}

		void TypeRegisterPrivate::register_base_classes_info(TypeData& info, get_base_calsses_info_func func) REFL_NOEXCEPT
		{
			BaseClassInfoContainer base_classes_info = func();
			
			REFL_TODO; //remove double entries
			std::sort(base_classes_info.begin(), base_classes_info.end(), [](const BaseClassInfo& left, BaseClassInfo& right) { return left.m_BaseType.get_id() < right.m_BaseType.get_id(); });
			
			ClassData& classdata = info.get_class_data_func();
			for (const auto& t : base_classes_info)
			{
				classdata.m_BaseTypes.push_back(t.m_BaseType);
				classdata.m_cast_funcs.push_back(t.m_ReflCastFunc);
				
				REFL_TODO;//I believe these two are equal.
				assert(t.m_BaseType.m_Data == t.m_BaseType.m_Data->m_RawTypeData);
				t.m_BaseType.m_Data->get_class_data_func().m_DerivedTypes.push_back(Type(&info));
			}
		}

		void TypeRegisterPrivate::register_custom_name(Type& type, StringView name)
		{
			if (!type.isValid())
			{
				return;
			}

			Detail::TypeData& type_data = *type.m_Data;
			const std::string& orig_name = type_data.m_Name;
			std::map<std::string, Type>& custom_name_map = get_type_custom_name_map();
			custom_name_map.erase(orig_name);

			REFL_TODO;//why I can't use baseview here directly?
			type_data.m_Name = name.to_string();
			custom_name_map.insert(std::make_pair(type_data.m_Name, type));

			REFL_TODO;//change raw name.
		}

		Type TypeRegister::register_type(TypeData& info, get_base_calsses_info_func func) REFL_NOEXCEPT
		{
			return TypeRegisterPrivate::register_type_impl(info, func);
		}

		void TypeRegister::custom_name(Type& t, StringView name)
		{
			TypeRegisterPrivate::register_custom_name(t, name);
		}

	}
}