#include <iostream>
#include "reflection.h"

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
public:
	void print(int a, int b)
	{

	}
};

REFL_REGISTRATION
{
	Reflection::Registration::ClassReg<T4>("T4")
	.method("print", &T4::print);
}

int main()
{
	std::is_pod<T4>();
	T4 t4;
	T1* pt1 = Reflection::refl_cast<T1*>(&t4);

}