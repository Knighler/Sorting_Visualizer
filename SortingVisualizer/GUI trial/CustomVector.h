#pragma once
#include <stdexcept> // For std::out_of_range
#include <iostream>  // For debugging (optional, can remove later)
using namespace std;

template <typename T>
class Vector {
private:
    size_t m_size;        // Number of elements in the vector
    size_t m_capacity;    // Allocated capacity of the vector
    T* data;              // Pointer to the dynamic array

    // Reallocate the vector with a new capacity
    void reallocate(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < m_size; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        m_capacity = newCapacity;
    }

public:
    // Default constructor
    Vector() : m_size(0), m_capacity(0), data(nullptr) {}

    // Constructor with size
    Vector(size_t size) : m_size(size), m_capacity(size*2) {
        data = new T[m_capacity];
    }

    // Constructor with size and fill value
    Vector(size_t size, const T& fill) : m_size(size), m_capacity(size*2) {
        data = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            data[i] = fill;
        }
    }

    // Copy constructor
    Vector(const Vector& other) : m_size(other.m_size), m_capacity(other.m_capacity) {
        data = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            data[i] = other.data[i];
        }
    }

 

    // Destructor
    ~Vector() {
        delete[] data;
    }

    // Copy assignment operator
    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;

        delete[] data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        data = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    // Move assignment operator
    Vector& operator=(Vector&& other) noexcept {
        if (this == &other) return *this;

        delete[] data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        data = other.data;

        other.data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;

        return *this;
    }

 
    void push_back(const T& value) {
        if (m_size == m_capacity) {
            size_t newCapacity = m_capacity == 0 ? 1 : m_capacity * 2;
            reallocate(newCapacity);
        }
        data[m_size++] = value;
    }

    // Access element at index
    T& operator[](size_t index) {
        if (index >= m_size) {
            exit(1);
        }
        return data[index];
    }

 

    // Get current size of the vector
    size_t getSize() const {
        return m_size;
    }

    // Get capacity of the vector
    size_t capacity() const {
        return m_capacity;
    }

    // Check if the vector is empty
    bool empty() const {
        return m_size == 0;
    }

    // Get pointer to the beginning of the vector
    T* begin() {
        return data;
    }

    const T* begin() const {
        return data;
    }

    // Get pointer to the end of the vector
    T* end() {
        return data + m_size;
    }

    const T* end() const {
        return data + m_size;
    }
    int findIndex( T& value) const {
        for (size_t i = 0; i < m_size; ++i) {
            if (data[i] == value) {
                return i; // Return index if found
            }
        }
        throw std::out_of_range("Element not found in the vector");
    }
    void clear() {
        delete[] data;  // Deallocate memory
        data = nullptr; // Reset data pointer
        m_size = 0;     // Reset size
        m_capacity = 0; // Reset capacity
    }
};
