#ifndef __RTTR_BIND_IMPL_H__
#define __RTTR_BIND_IMPL_H__

namespace Reflection
{
	
	template<Registration::BindType type, typename... T>
	class Registration::Bind {};

	template<typename Class_Type, typename F>
	class Registration::Bind<Registration::BindType_Method, Class_Type, F>
	{

	};
}

#endif