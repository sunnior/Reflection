#include "Reflection/type.h"

struct T1
{
	size_t m_num;
};

int main()
{
	Reflection::Type type = Reflection::Type::get<T1>();
}