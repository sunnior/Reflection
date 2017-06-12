#ifndef __REFL_TYPE_REGISTER_H__
#define __REFL_TYPE_REGISTER_H__
#include "defs.h"
#include <vector>
#include <map>

#include "string_view.h"
#include "type_data.h"
#include "base_classes.h"

namespace Reflection
{
	class Type;

	namespace Detail
	{
		class TypeRegisterPrivate
		{
		public:
			static Type register_type_impl(TypeData& info, get_base_calsses_info_func) REFL_NOEXCEPT;
			static const bool register_name(type_id& id, TypeData& info) REFL_NOEXCEPT;
			static void register_custom_name(Type& type, StringView name);

			static std::map<std::string, Type>& get_type_custom_name_map();
		private:
			static std::vector<TypeData*>& get_type_data_storage();
			static std::map<StringView, Type>& get_type_name_map();
			static void register_base_classes_info(TypeData& info, get_base_calsses_info_func) REFL_NOEXCEPT;
		};

		class TypeRegister
		{
		public:
			static Type register_type(TypeData& info, get_base_calsses_info_func) REFL_NOEXCEPT;
			static void custom_name(Type& t, StringView name);

		};
	}
}

#endif