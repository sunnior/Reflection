#ifndef __REFL_BASE_CLASSES_H__
#define __REFL_BASE_CLASSES_H__

#include <vector>
#include "type.h"

namespace Reflection
{
	namespace Detail
	{
		struct BaseClassInfo
		{
			BaseClassInfo(Type type, void* (*func)(void*))
				: m_BaseType(type)
				, m_ReflCastFunc(func)
				{};

			Type m_BaseType;
			void* (*m_ReflCastFunc)(void*);
		};
		
		using BaseClassInfoContainer = std::vector<BaseClassInfo>;

		template<typename Derived, typename Base>
		void* refl_cast_func_impl(void* p)
		{
			return static_cast<Base*>(static_cast<Derived*>(p));
		}

		template<typename T>
		class has_base_class_list
		{
			typedef char YesType[1];
			typedef char NoType[2];

			template <typename C>
			static YesType& test(typename C::base_class_list*);
			
			template <typename>
			static NoType& test(...);
			
			public:
			static REFL_CONSTEXPR_OR_CONST bool value = (sizeof(YesType) == sizeof(test<T>(0)));
		};

		template<typename T, typename... U>
		struct BaseClassFiller;
		
		template<typename Derived>
		struct BaseClassFiller<Derived>
		{
			static REFL_INLINE void fill(BaseClassInfoContainer& infos)
			{
			}
		};
		
		template<typename...> struct type_list;
		
		template<typename Derived, typename... BaseList>
		struct BaseClassFiller<Derived, type_list<BaseList...>> : public BaseClassFiller<Derived, BaseList...> {};
		
		template<typename Derived, typename Base, typename... U>
		struct BaseClassFiller<Derived, Base, U...>
		{
			static REFL_INLINE void fill(BaseClassInfoContainer& infos)
			{
				static_assert(has_base_class_list<Base>::value, "base class should also have base class list");
				infos.emplace_back(Type::get<Base>(), &refl_cast_func_impl<Derived, Base>);
				
				BaseClassFiller<Derived, Base::base_class_list>::fill(infos);
				BaseClassFiller<Derived, U...>::fill(infos);
			}
		};
		
		template<typename T, typename Enable = void>
		struct BaseClasses
		{
			static BaseClassInfoContainer get_base_classes_info()
			{
				BaseClassInfoContainer infos;
				return infos;
			}
		};

		template<typename T>
		struct BaseClasses<T, std::enable_if_t<has_base_class_list<T>::value>>
		{
			static BaseClassInfoContainer get_base_classes_info()
			{
				BaseClassInfoContainer infos;
				BaseClassFiller<T, typename T::base_class_list>::fill(infos);
				return infos;
			}
		};
		using get_base_calsses_info_func = BaseClassInfoContainer(*)();
	}
}
#endif