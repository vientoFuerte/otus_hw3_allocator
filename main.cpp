
// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.


#include "allocator.h"
#include "container.h"
#include <iostream>
#include <map>

int factorial (int n)
{
	if(n>1) {return n * (factorial(n -1));}
	else return 1;
}

int main()
{

	auto m = std::map<int, int>{};
	for (int i=0; i< 10; i++)
	{
		m.emplace (i, factorial(i));
	}
	for (int i=0; i< 10; i++)
	{
		std::cout << m[i] << "\n";
	}


    return 0;
}


