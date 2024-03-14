#pragma once
#include <algorithm>
#include "exceptions.hpp"


namespace vm {

template<class T = int>
class Stack {
public:
    Stack() = default;

    Stack(const Stack<T>& other) {
        *this = other;
    }

    Stack(Stack<T>&& other) {
        *this = std::move(other);
    }

    Stack<T>& operator = (const Stack<T>& other) {
        T* newData = nullptr;
        if (other.capacity != 0) {
            newData = new T[other.capacity];
            for (int i = 0; i < other.size; i++) {
                newData[i] = other.data[i];
            }
        }

        delete[] data;
        data = newData;
        capacity = other.capacity;
        size = other.size;

        return *this;
    }

    Stack<T>& operator = (Stack<T>&& other) {
        swap(other);
        return *this;
    }

    ~Stack() {
        delete[] data;
    }

    void push(const T& elem) {
        if (size == capacity) resize();
        data[size++] = elem;
    }

    void push(T&& elem) {
        push(elem);
    }

    T pop() {
        if (size == 0) {
            throw EmptyStackError("Вызов метода pop на пустом стэке");
        }
        return data[--size];
    }

    T& top() const {
        if (size == 0) {
            throw EmptyStackError("Вызов метода top на пустом стэке");
        }
        return data[size - 1];
    }

    bool empty() const {
        return size == 0;
    }

    size_t getSize() const {
        return size;
    }

    void clear() {
        delete[] data;
        data = nullptr;
        capacity = 0;
        size = 0;
    }

    void swap(Stack<T>& other) {
        std::swap(data, other.data);
        std::swap(size, other.size);
        std::swap(capacity, other.capacity);
    }

private:
    constexpr static size_t CAPACITY_COEF = 2;
    constexpr static size_t START_CAPACITY = 8;

    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    void resize() {
        size_t newCapacity = std::max(capacity * CAPACITY_COEF, START_CAPACITY);
        T* newData = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

};

}
