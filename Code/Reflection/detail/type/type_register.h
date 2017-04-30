#ifndef __REFL_TYPE_REGISTER_H__
#define __REFL_TYPE_REGISTER_H__
#include "defs.h"
#include <vector>
#include <map>

#include "string_view.h"
#include "type_data.h"

namespace Reflection
{
	class Type;

	namespace Detail
	{
		class TypeRegisterPrivate
		{
		public:
			static Type register_type(TypeData& info) REFL_NOEXCEPT;
			static const bool register_name(TypeData::type_id& id, TypeData& info) REFL_NOEXCEPT;
			static void register_custom_name(Type& type, StringView name);
		private:
			static std::vector<const TypeData*>& get_type_data_storage();
			static std::map<StringView, Type>& get_type_name_map();
		};

		class TypeRegister
		{
		public:
			static Type type_reg(TypeData& info) REFL_NOEXCEPT;
			static void custom_name(Type& t, StringView name);

		};
	}
}

#endif