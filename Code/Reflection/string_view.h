#ifndef __STRING_VIEW_H__
#define __STRING_VIEW_H__

#include "defs.h"

namespace Reflection
{
	REFL_TODO;//why we use Traits here?
	template<typename CharT, typename Traits = std::char_traits<CharT>>
	class BasicStringView
	{
	public:
		using size_type = size_t;
		using value_type = CharT;
		using pointer_type = CharT*;
		using const_pointer = const CharT*;
		using const_iterator = const_pointer;

		REFL_CONSTEXPR BasicStringView() REFL_NOEXCEPT;
		REFL_CONSTEXPR BasicStringView(const CharT* str, size_type len) REFL_NOEXCEPT;

		REFL_CONSTEXPR const_iterator begin() const REFL_NOEXCEPT;
		REFL_CONSTEXPR const_iterator end() const REFL_NOEXCEPT;

		template<typename Allocator = std::allocator<CharT>>
		std::basic_string<CharT, Traits> to_string(const Allocator& a = Allocator()) const;

	private:
		const_pointer m_data;
		size_type m_size;
	};

	using StringView = BasicStringView<char>;
}

namespace Reflection
{
	template<typename CharT, typename Traits>
	REFL_CONSTEXPR BasicStringView<CharT, Traits>::BasicStringView() REFL_NOEXCEPT
		: m_data(nullptr)
		, m_size(0)
	{
	}

	REFL_TODO;//why I need add tyname after class name.
	template<typename CharT, typename Traits>
	REFL_CONSTEXPR BasicStringView<CharT, Traits>::BasicStringView(const CharT* str, size_type len)
		: m_data(str)
		, m_size(len)
	{
	
	}

	template<typename CharT, typename Traits>
	template<typename Allocator>
	std::basic_string<CharT, Traits> BasicStringView<CharT, Traits>::to_string(const Allocator& allocator) const
	{
		return std::basic_string<CharT, Traits, Allocator>(begin(), end(), allocator);
	}

	template<typename CharT, typename Traits>
	REFL_CONSTEXPR typename BasicStringView<CharT, Traits>::const_iterator BasicStringView<CharT, Traits>::begin() const REFL_NOEXCEPT
	{
		return m_data;
	}

	template<typename CharT, typename Traits>
	REFL_CONSTEXPR typename BasicStringView<CharT, Traits>::const_iterator BasicStringView<CharT, Traits>::end() const REFL_NOEXCEPT
	{
		return m_data + m_size;
	}
}

#endif