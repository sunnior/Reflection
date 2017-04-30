#ifndef __REGISTRATION_H__
#define __REGISTRATION_H__

#include "defs.h"
#include "string_view.h"
#include "type.h"

#define REFL_CAT(a, b) a##b

namespace Reflection
{
	class REFL_API registration
	{
	public:
		template<typename T>
		class classReg
		{
		public:
			classReg(StringView name);
		};
	};
}

namespace Reflection
{
	template<typename T>
	registration::classReg<T>::classReg(StringView name)
	{
		Type type = Type::get<T>();
		Detail::TypeRegister::custom_name(type, name);
	}
}

#define REFL_REGISTRATION												\
static void refl_auto_register_reflection_function_();					\
namespace																\
{																		\
	struct refl_auto_register											\
	{																	\
		refl_auto_register()											\
		{																\
			refl_auto_register_reflection_function_();					\
		}																\
	};																	\
}																		\
static const refl_auto_register  REFL_CAT(auto_register_, __LINE__);	\
static void refl_auto_register_reflection_function_()

#endif