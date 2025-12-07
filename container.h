#pragma once

#include "allocator.h"

template<typename T, typename Allocator = std::allocator<T>>
class SimpleQueue {
private:
    struct Node {
        T data;
        Node* next;
        
        template <class... Args>
        Node(Args&&... args) :
        data(std::forward<Args>(args)...),
        next(nullptr) 
        {}

    };
  
    Node* front_node;
    Node* back_node;
    size_t queue_size;

    using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
    NodeAllocator alloc;

public:
    SimpleQueue() {
        front_node = nullptr;
        back_node = nullptr;
        queue_size = 0;
        }
    
    ~SimpleQueue() {
        while (!empty()) {
            pop();
        }
    }
    
    // Добавление элемента
    template <class... Args>
    void push(Args&&... args) {
        Node* new_node = std::allocator_traits<NodeAllocator>::allocate(alloc, 1);
        std::allocator_traits<NodeAllocator>::construct(alloc, new_node, std::forward<Args>(args)...);

        new_node->next = nullptr;

        if (empty()) {
            front_node = new_node;
        }
        else {
            back_node->next = new_node;
        }
        back_node = new_node;
        ++queue_size;
    }
    
    // Удаление элемента из начала очереди
    void pop() {
        if (!empty()) {
            Node* temp = front_node;
            front_node = front_node->next;
            if (front_node == nullptr) {
                back_node = nullptr;
            }
            std::allocator_traits<NodeAllocator>::destroy(alloc, temp);
            std::allocator_traits<NodeAllocator>::deallocate(alloc, temp, 1);
            --queue_size;
        }
    }

    // Удаление элемента по значению
    void remove(const T& value) {
        Node* current = front_node;
        Node* prev = nullptr;

        while (current) {
            if (current->data == value) {
                if (prev) {
                    prev->next = current->next;
                }
                else {
                    front_node = current->next;
                }
                if (current == back_node) {
                    back_node = prev;
                }
                std::allocator_traits<NodeAllocator>::destroy(alloc, current);
                std::allocator_traits<NodeAllocator>::deallocate(alloc, current, 1);
                --queue_size;
                return;
            }
            prev = current;
            current = current->next;
        }
    }
    
    // Верхний элемент
    T front() {
        if (!empty()) {
            return front_node->data;
        }
        throw std::runtime_error("Queue is empty");
    }

    
    // Размер очереди
    size_t size() {
        return queue_size;
    }
    // Проверка на пустоту
    bool empty()  { 
        return queue_size == 0 ? true : false;
    
    }

    // Проход по всем элементам от начала с выводом
    void traverse() {
        Node* current = front_node;
        while (current) {
            std::cout << current->data << std::endl;
            current = current->next;
        }
        std::cout << std::endl;
    }
};
