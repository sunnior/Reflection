#include "Reflection/type.h"

struct T1
{
	size_t m_num;
};

int main()
{
	Reflection::Type type = Reflection::Type::get<T1>();
	Reflection::Type type2 = Reflection::Type::get<T1>();
}