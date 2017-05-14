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

template<typename T>
void test(T t);

template<typename T>
void test<T, std::enable_if_t<std::is_function<std::remove_pointer_t<T>>::value>>(T t)
{
	t();
}

void func()
{

}

template<int N>
void test2();

int main()
{

	Reflection::Type type = Reflection::Type::get<T1>();
	Reflection::Type type2 = Reflection::Type::get<T1>();

	T1 t1;
	Reflection::Type type3 = t1.getType();
	T2 t2;
	T1* pt1 = &t2;
	Reflection::Type type4 = pt1->getType();
	
	Reflection::Type type5 = Reflection::Type::get_by_name("T2");
	Reflection::Type type6 = Reflection::Type::get_by_name("T3");

	T2* pt2 = Reflection::refl_cast<T2*>(pt1);
}