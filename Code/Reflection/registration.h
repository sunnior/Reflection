#ifndef __REGISTRATION_H__
#define __REGISTRATION_H__

#include "defs.h"
#include "string_view.h"
#include "type.h"

#define REFL_CAT(a, b) a##b

namespace Reflection
{
	class REFL_API Registration
	{
	private:
		enum BindType
		{
			BindType_Method,
		};

		template<BindType Type, typename... T>
		class Bind;

	public:
		template<typename Class_Type>
		class ClassReg
		{
		public:
			ClassReg(StringView name);
			
			REFL_TODO; //access level
			template<typename F>
			Bind<BindType_Method, Class_Type, F> method(StringView name, F f);

		};
	};
}

#include "detail/registration/registration_impl.h"

#endif