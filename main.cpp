// main.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.


//#include "allocator.h"
//#include "container.h"
#include <iostream>
#include <map>
#include <cstdlib>


#define USE_LOG
#undef USE_LOG 

template <typename T, std::size_t Count>
struct logging_allocator {
	using value_type = T;

	using pointer = T *;
	using const_pointer = const T *;
	using reference = T &;
	using const_reference = const T &;

	template <typename U>
	struct rebind {
		using other = logging_allocator<U, Count>;
	}

	logging_allocator() = default;
	~logging_allocator() = default;

	template <typename U>
	logging_allocator(const logging_allocator<U, Count> &) {
	}

	T *allocate(std::size_t n) {
	    if (used_elements + n > Count) {
	      throw std::bad_alloc();
	    }
#ifdef USE_LOG
		std::cout << "allocate: [n = " << n << "]" << std::endl;
#endif
        if (!buff_ptr) 
        {
           buff_ptr= reinterpret_cast<pointer>(std::malloc(Count * sizeof(T)));
        }
		
		if (!buff_ptr){
			throw std::bad_alloc();
		}
		
		pointer result_ptr = buff_ptr + used_elements;
		used_elements += n;	
		return result_ptr;
	}

	void deallocate(T *p, std::size_t n) {
#ifdef USE_LOG
		std::cout << "deallocate: [n  = " << n << "] " << std::endl;
#endif 
        used_elements -= n; 
        if (used_elements == 0) {
    		std::free(p);	
    		buff_ptr = nullptr;
        }
	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args) {
#ifdef USE_LOG
		std::cout << "construct" << std::endl;
#endif
		new (p) U(std::forward<Args>(args)...);
	};

	template <typename U>
	void destroy(U *p) {
#ifdef USE_LOG
		std::cout << "destroy" << std::endl;
#endif
		p->~U();
	}
	
	private:
	pointer buff_ptr = nullptr; //Указатель на начало буфера выделенной памяти
	size_t  used_elements  = 0; // Счетчик использованных элементов в буфере
};



int factorial (int n)
{
	if(n>1) {return n * (factorial(n - 1));}
	else return 1;
}

int main()
{

	auto m = std::map<int, int>{};
	for (int i=0; i< 10; i++)
	{
		m.emplace (i, factorial(i));
	}
        for (const auto& [key, value] : m) {
	    std::cout << key << " " << value << std::endl;
        }

	
	auto m2 = std::map<
	int,
	int,
	std::less<int>,
	logging_allocator<
		std::pair<
		const int, int>, 10>>{};

	for (int i=0; i< 10; i++)
	{
	    m2.emplace (i, factorial(i));
	}
	
        for (const auto& [key, value] : m2) {
	    std::cout << key << " " << value << std::endl;
        }


    return 0;
}


