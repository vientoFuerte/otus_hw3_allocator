#pragma once

#include <cstddef> // для size_t
#include <stdexcept> // для std::runtime_error

template<typename T>
class SimpleStack {
private:
    struct Node {
        T data;
        Node* next;
        
        
        Node(const T& value) {
            data = value;   
            next = nullptr;
        }
    };
      
    Node* top_node;
    size_t stack_size;

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
    void push(const T value) {
        Node* new_node = new Node(value);
        new_node->next = top_node;
        top_node = new_node;
        ++stack_size;
    }
    
    // Удаление элемента
    void pop() {
        if (top_node) {
            Node* temp = top_node;
            top_node = top_node->next;
            delete temp;
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
