#pragma once

#include "allocator.h"

template<typename T, typename Allocator = std::allocator<T>>
class SimpleStack {
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
  
    Node* top_node;
    size_t stack_size;
    
    //using NodeAllocator = typename Allocator::template rebind<Node>::other;
    using NodeAllocator = typename std::allocator_traits<Allocator>::template rebind_alloc<Node>;
    NodeAllocator alloc;

public:
    SimpleStack() {
        top_node = nullptr; 
        stack_size = 0;
        }
    
    ~SimpleStack() {
        while (!empty()) {
            pop();
        }
    }
    
    // Добавление элемента
    template <class... Args>
    void push(Args&&... args) {
        Node* new_node = std::allocator_traits<NodeAllocator>::allocate(alloc, 1);
        //Node* new_node = alloc.allocate(1);

        std::allocator_traits<NodeAllocator>::construct(alloc, new_node, std::forward<Args>(args)...);
        //alloc.construct(new_node, std::forward<Args>(args)...); 
        //Node* new_node = new Node(value);
        new_node->next = top_node;
        top_node = new_node;
        ++stack_size;
    }
    
    // Удаление элемента
    void pop() {
        if (top_node) {
            Node* temp = top_node;
            top_node = top_node->next;
            std::allocator_traits<NodeAllocator>::destroy(alloc, temp);
            std::allocator_traits<NodeAllocator>::deallocate(alloc, temp, 1);
           // alloc.destroy(temp);
            //alloc.deallocate(temp, 1);
            //delete temp;
            --stack_size;
        }
    }
    
    // Верхний элемент
    T top() {
        if (top_node) {
            return top_node->data;
        }
        throw std::runtime_error("Stack is empty");
    }

    
    // Размер стека
    size_t size() {
        return stack_size; 
    }
    // Проверка на пустоту
    bool empty()  { 
        return stack_size == 0 ? true : false;
    
    }
};
