#include <iostream>
#include "Reflection/reflection.h"

struct T1
{
	size_t m_num;
	REFL_ENABLE();
};

struct T2
{
	REFL_ENABLE();
};

struct T3 : public T2
{
	REFL_ENABLE(T2);
};

struct T4 : public T1, T3
{
	REFL_ENABLE(T1, T3);
};

REFL_REGISTRATION
{
	Reflection::registration::classReg<T4>("T4");
}

template<typename T>
void test(T t);

template<typename T>
void test<T, std::enable_if_t<std::is_function<std::remove_pointer_t<T>>::value>>(T t)
{
	t();
}

int main()
{
	std::is_pod<T4>();
	T4 t4;
	T1* pt1 = Reflection::refl_cast<T1*>(&t4);

}