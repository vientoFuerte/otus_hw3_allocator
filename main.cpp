// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.


#include "allocator.h"
#include "container.h"
#include <iostream>
#include <map>
#include <cstdlib>


int factorial(int n)
{
    if (n > 1) { return n * (factorial(n - 1)); }
    else return 1;
}

int main()
{

    std::cout << "std::map\n";
    auto m = std::map<int, int>{};
    for (int i = 0; i < 10; i++) {
        m.emplace(i, factorial(i));
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

    for (int i = 0; i < 10; i++) {
        m2.emplace(i, factorial(i));
    }

    for (const auto& [key, value] : m2) {
        std::cout << key << " " << value << std::endl;
    }


    std::cout << "\nSimpleQueue\n";

    SimpleQueue<int> queue;
    for (int i = 0; i < 10; i++) {
        queue.push(factorial(i));
    }

    queue.traverse();


    std::cout << "\nSimpleQueue with logging_allocator\n";
    // Создаем очередь с logging_allocator
    SimpleQueue<int, logging_allocator<int, 10>> queue2;

    for (int i = 0; i < 10; i++) {
        queue2.push(factorial(i));
    }

    queue.traverse();

    return 0;
}
