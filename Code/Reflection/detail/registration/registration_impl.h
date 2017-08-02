#ifndef __REGISTRATION_IMPL_H__
#define __REGISTRATION_IMPL_H__

#include "detail/registration/bind_impl.h"

namespace Reflection
{
	template<typename Class_Type>
	Registration::ClassReg<Class_Type>::ClassReg(StringView name)
	{
		Type type = Type::get<Class_Type>();
		Detail::TypeRegister::custom_name(type, name);
	}
	
	template<typename Class_Type>
	template<typename F>
	Registration::Bind<Registration::BindType_Method, Class_Type, F> Registration::ClassReg<Class_Type>::method(StringView name, F f)
	{
		REFL_TODO; //check access level. check is functor.
		static_assert(std::is_member_function_pointer<F>::value, "No valid method accessor provided!");
		return{};
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