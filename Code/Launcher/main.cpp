#include "Reflection/type.h"

struct T1
{

};

int main()
{
	Reflection::Type type = Reflection::Type::get<T1>();
}