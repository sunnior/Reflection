#ifndef __REFL_ENABLE_H__
#define __REFL_ENABLE_H__

#include "defs.h"
#include "type.h"

namespace Reflection
{
	namespace Detail
	{
		template<typename... U> struct type_list;
	}
}

#define REFL_ENABLE(...) \
public:\
	virtual REFL_INLINE Reflection::Type getType() const { return Reflection::Detail::getTypeFromInstance(this); } \
	virtual REFL_INLINE void* getPtr() { return reinterpret_cast<void*>(this); } \
    using base_class_list = Reflection::Detail::type_list<__VA_ARGS__>; \
private:

#endif