#ifndef __REFL_TYPE_DATA_H__
#define __REFL_TYPE_DATA_H__

#include <string>
#include <vector>
#include "defs.h"
#include "detail/type/type_id.h"
#include "type_name.h"
#include "detail/misc/misc_type_traits.h"
#include "type.h"

namespace Reflection
{
	template<typename T, typename Enable = void>
	struct get_size_of
	{
		REFL_INLINE REFL_CONSTEXPR static size_t value()
		{
			return sizeof(T);
		}
	};

	namespace Detail
	{
		using refl_cast_func = void*(*)(void*);
		struct ClassData
		{
			std::vector<Type> m_BaseTypes;
			std::vector<Type> m_DerivedTypes;
			std::vector<refl_cast_func> m_cast_funcs;
		};

		struct TypeData
		{
			TypeData* m_RawTypeData;
			std::string m_Name;
			StringView  m_TypeName;
			size_t		m_SizeOf;
			type_id m_TypeId;
			static const type_id s_InvalidTypeId = 0;

			ClassData& (*get_class_data_func)();

			REFL_INLINE bool isValid() const REFL_NOEXCEPT { return m_TypeId != s_InvalidTypeId; }
		};

		template<typename T>
		ClassData& get_type_class_data() REFL_NOEXCEPT
		{
			static ClassData instance;
			return instance;
		}
		
		ClassData& get_invalid_type_class_data() REFL_NOEXCEPT;

        TypeData& get_invalid_type_data_impl() REFL_NOEXCEPT;
    
    
        REFL_INLINE TypeData& get_invalid_type_data() REFL_NOEXCEPT
        {
            static TypeData& instance = get_invalid_type_data_impl();
            return instance;
        }

    
		template<typename T, bool = std::is_same<T, raw_type_t<T>>::value>
		struct raw_type_info
		{
			static TypeData& GetRawTypeInfo()
			{
				return get_invalid_type_data();
			}
		};

        template<typename T>
        TypeData& getTypeData() REFL_NOEXCEPT
        {
            static TypeData instance = TypeData{ &raw_type_info<T>::GetRawTypeInfo(),
                getTypeName<T>().to_string(),
                getTypeName<T>(),
                get_size_of<T>::value(),
                TypeData::s_InvalidTypeId,
                &get_type_class_data<T> };
            return instance;
        }


		template<typename T>
		struct raw_type_info<T, false>
		{
			static TypeData& GetRawTypeInfo()
			{
				return getTypeData<raw_type_t<T>>();
			}
		};


	}
}

#endif