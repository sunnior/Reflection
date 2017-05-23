#ifndef __MISC_TYPE_TRAITS_H__
#define __MISC_TYPE_TRAITS_H__

#include <type_traits>
#include <functional>

namespace Reflection
{

	namespace Detail
	{
		template<typename T, typename Enable = void>
		struct pointer_count_impl
		{
			static REFL_CONSTEXPR_OR_CONST std::size_t size = 0;
		};

		template<typename T>
		struct pointer_count_impl < T, std::enable_if_t<std::is_pointer<T>::value &&
									//here I didn't use is_function_ptr. REFL_TODO;
									!std::is_function<T>::value &&
									!std::is_member_pointer<T>::value>>
		{
			static REFL_CONSTEXPR_OR_CONST std::size_t size = pointer_count_impl<std::remove_pointer_t<T>>::size + 1;
		};

		template<typename T>
		using pointer_count = std::integral_constant<std::size_t, pointer_count_impl<T>::size>;
	
		template<typename T, typename Enable = void>
		struct raw_type
		{
			using type = std::remove_cv_t<T>;
		};
		
		template<typename T>
		struct raw_type<T, std::enable_if_t<std::is_pointer<T>::value>> //REFL_TODO: check is function ptr
		{
		using type = typename raw_type<std::remove_pointer_t<T>>::type;
		};
		
		template<typename T>
		struct raw_type<T, std::enable_if_t<std::is_reference<T>::value>>
		{
		using type = typename raw_type<std::remove_reference_t<T>>::type;
		};
		
		template<typename T>
		using raw_type_t = typename raw_type<T>::type;
	}
}

#endif