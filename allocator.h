#pragma once

#ifdef ENABLE_DEBUG_LOGGING
    #ifndef USE_LOG
        #define USE_LOG
    #endif
#endif

#include <cstdlib>
#include <iostream>

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
	};

	    logging_allocator() {
#ifdef USE_LOG
        std::cout << "Allocator created with pool size: " 
                  << Count * sizeof(T) << " bytes" << std::endl;
#endif

        for (size_t i = 0; i < Count; ++i) {
            used_slots[i] = false;
        }
    }
	~logging_allocator() = default;

	template <typename U>
	logging_allocator(const logging_allocator<U, Count> &) {
	}

	T *allocate(std::size_t n) {

		if (n != 1) {  //поддерживаем только одиночные выделения
		    throw std::bad_alloc();
		}

         // Ищем свободный слот
        for (size_t i = 0; i < Count; ++i) {
            if (!used_slots[i]) {
                used_slots[i] = true;
                pointer result_ptr = reinterpret_cast<pointer>(pool + i * sizeof(T));
                return result_ptr;
            }
        }
		
		throw std::bad_alloc();
		
#ifdef USE_LOG
		std::cout << "allocate: [n = " << n << "]" << std::endl;
#endif

	}

	void deallocate(T *p, std::size_t n) {
	 if (n != 1) return; // поддерживаем только одиночные освобождения

    // Находим индекс освобождаемого слота
    std::byte* ptr_byte = reinterpret_cast<std::byte*>(p);
    size_t offset = ptr_byte - pool;
    size_t slot_index = offset / sizeof(T);
    
    if (slot_index < Count && used_slots[slot_index]) {
        used_slots[slot_index] = false;
    }
#ifdef USE_LOG
		std::cout << "deallocate: [n  = " << n << "] " << std::endl;
#endif 
	}

	template <typename U, typename... Args>
	void construct(U *p, Args &&...args) {
#ifdef USE_LOG
		std::cout << "construct" << std::endl;
#endif
		new (p) U(std::forward<Args>(args)...);
	}

	template <typename U>
	void destroy(U *p) {
#ifdef USE_LOG
		std::cout << "destroy" << std::endl;
#endif
		p->~U();
	}
	
	private:
		std::byte pool[Count * sizeof(T)]; // Основной пул памяти (статический массив)
		bool used_slots[Count];            // Массив свободных ячеек.

};

