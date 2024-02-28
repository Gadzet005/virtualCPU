#pragma once

#include <algorithm>


namespace vm {

class EmptyStackError : public std::exception {
public:
    EmptyStackError(const char* message) : msg(message) {}
    const char* what() const noexcept override { return msg; }
private:
    const char* msg;
};

template<class T = int>
class Stack {
public:
    Stack() = default;

    Stack(const Stack<T>& other) {
        *this = other;
    }

    Stack(Stack<T>&& other) {
        *this = other;
    }

    Stack<T>& operator = (const Stack<T>& other) {
        resizeAndCopy(other.capacity, other);
        return *this;
    }

    Stack<T>& operator = (Stack<T>&& other) {
        std::swap(data, other.data);
        size = other.size;
        capacity = other.capacity;

        return *this;
    }

    ~Stack() {
        delete[] data;
    }

    void push(const T& elem) {
        _push();
        data[size++] = elem;
    }

    void push(T&& elem) {
        _push();
        std::swap(data[size++], elem);
    }

    void pop() {
        if (size != 0) {
            size--;
        }
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

private:
    constexpr static size_t capacityIncrease = 2;
    constexpr static size_t startCapacity = 8;

    T* data = nullptr;
    size_t size = 0;
    size_t capacity = 0;

    // Расширяет массив как минимум до newCapacity и копирует данные из toCopy (можно из самого себя)
    void resizeAndCopy(size_t newCapacity, const Stack<T>& toCopy) {
        newCapacity = std::max(newCapacity, toCopy.capacity);

        if (capacity >= newCapacity) {
            for (int i = 0; i < toCopy.size; i++) {
                data[i] = toCopy.data[i];
            }
        } else {
            T* newData = new T[newCapacity];
            for (int i = 0; i < toCopy.size; i++) {
                newData[i] = toCopy.data[i];
            }

            std::swap(newData, data);
            delete[] newData;
            capacity = newCapacity;
        }

        size = toCopy.size;
    }

    void _push() {
        if (size == capacity) {
            resizeAndCopy(
                std::max(startCapacity, capacity * capacityIncrease), *this
            );
        }
    }

};

}
