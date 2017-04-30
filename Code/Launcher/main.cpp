#include <iostream>
#include "Reflection/reflection.h"

struct T1
{
	size_t m_num;
	REFL_ENABLE();
};

struct T2 : public T1
{
	REFL_ENABLE();
};

REFL_REGISTRATION
{
	Reflection::registration::classReg<T2>("T2");
}

int main()
{
	Reflection::Type type = Reflection::Type::get<T1>();
	Reflection::Type type2 = Reflection::Type::get<T1>();

	T1 t1;
	Reflection::Type type3 = t1.getType();
	T2 t2;
	T1* t2_1 = &t2;
	Reflection::Type type4 = t2_1->getType();
	
	Reflection::Type type5 = Reflection::Type::get_by_name("T2");
	Reflection::Type type6 = Reflection::Type::get_by_name("T3");

}