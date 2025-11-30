// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include "allocator.h"
#include "container.h"
#include <iostream>
#include <map>
#include <cstdlib>


int factorial (int n)
{
	if(n>1) {return n * (factorial(n - 1));}
	else return 1;
}

int main()
{

    std::cout << "std::map\n";
	auto m = std::map<int, int>{};
	for (int i=0; i< 10; i++)	{
		m.emplace (i, factorial(i));
	}
    for (const auto& [key, value] : m) {
    std::cout << key << " " << value << std::endl;
    }

	
	std::cout << "\nstd::map with logging_allocator\n";
	auto m2 = std::map<
	int,
	int,
	std::less<int>,
	logging_allocator<
		std::pair<
		const int, int>, 10>>{};

	for (int i=0; i< 10; i++) {
	    m2.emplace (i, factorial(i));
	}
	
    for (const auto& [key, value] : m2) {
    std::cout << key << " " << value << std::endl;
    }


    std::cout << "\nSimpleStack\n";

    SimpleStack<int> stack;
	for (int i = 0; i < 10; i++) {
	    stack.push(factorial(i));
	}
    
    while (!stack.empty()) {
        std::cout << stack.top() << std::endl;
        stack.pop();
    }


    std::cout << "\nSimpleStack with logging_allocator\n";
    // Создаем стек с logging_allocator
    SimpleStack<int, logging_allocator<int, 10>> stack2;
    
    for (int i = 0; i < 10; i++) {
        stack2.push(factorial(i));
    }
    
    while (!stack2.empty()) {
        std::cout << stack2.top() << std::endl;
        stack2.pop();
    }


    return 0;
}

