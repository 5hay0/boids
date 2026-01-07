//
// Created by lison on 27/11/2025.
//

#ifndef BLOIS_DYNAMICARRAY_HPP
#define BLOIS_DYNAMICARRAY_HPP
#include <iostream>

// DinamicArray créer fonction applyToAll(fonction à appliquer)

template <typename T>
class DynamicArray {
private:
    T* data;
    size_t size; //how many element do I have now
    size_t capacity; //how many elements can I store

    /**
     * Double the capacity of the DynamicArray
     */
    void resize();

public:
    /**
     * Default constructor, capacity of 10
     */
    DynamicArray();

    /**
     * Constructor with a chose capacity
     * @param inititialCapacity How many element can be stored from the start before needing to resize
     */
    DynamicArray(int inititialCapacity);

    /**
     * Constructor by copy
     * @param other Model used by the constructor
     */
    DynamicArray(const DynamicArray& other);

    /**
     * Modify the DynamicArray to fit a model if they are different
     * @param other Model that will be copied
     * @return the modified DynamicArray
     */
    DynamicArray& operator=(const DynamicArray& other);

    ~DynamicArray();

    /**
     * Insert a new element, manage if the DynamicArray is already full
     * @param value element that will be insert
     */
    void add(const T& value);

    /**
     * Get how many elements are inside the DynamicArray, NOT the capacity
     * @return
     */
    size_t getSize() const;

    /**
     * Get the element at a specific place, first place = 0 and not 1
     * This version permit to modify the element
     * @return element
     */
    T& get(size_t);

    /**
     * Get the element at a specific place, first place = 0 and not 1
     * This version do NOT permit to modify the element
     * @return
     */
    const T& get(size_t) const;

    /**
     * Destroy all elements inside the DynamicArray
     */
    void clear();

    /**
     * Destroy the last element of the DynamicArray
     */
    void removeLast();
};

template <typename T>
DynamicArray<T>::DynamicArray() : size(0), capacity(10) {
    data = new T[capacity];
}

template <typename T>
DynamicArray<T>::DynamicArray(int inititialCapacity): size(0),capacity(inititialCapacity) {
    if (inititialCapacity <= 0) {
        throw std::invalid_argument("Capacity must be higher than 0");
    }
    data = new T[capacity];
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray &other): size(other.size), capacity(other.capacity) {
    data = new T[capacity];  // Memory allocation for a new instance

    for (size_t i = 0; i < size; ++i) {
        data[i] = other.data[i];  // Copy elements one by one
    }
}

template<typename T>
DynamicArray<T> &DynamicArray<T>::operator=(const DynamicArray &other) {
    if (this != &other) {  // Stop auto asign
        delete[] data;  // Free old memory

        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];

        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

template<typename T>
void DynamicArray<T>::clear() {
    delete[] data;
    data = new T[capacity];
}

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<typename T>
void DynamicArray<T>::resize() {
    capacity *= 2;
    T* newData = new T[capacity];

    for (size_t i =0; i<size;i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

template<typename T>
void DynamicArray<T>::add(const T &value) {
    if (size >= capacity) {
        resize();
    }
    data[size] = value;
    size = size+1;
}

template<typename T>
size_t DynamicArray<T>::getSize() const {
    return size;
}

template<typename T>
T& DynamicArray<T>::get(size_t i) {
    if(i >= size){
        throw std::out_of_range("DynamicArray out of range");
    }
    return data[i];
}

template<typename T>
const T& DynamicArray<T>::get(size_t i) const {
    if(i >= size){
        throw std::out_of_range("DynamicArray out of range");
    }
    return data[i];
}

template<typename T>
void DynamicArray<T>::removeLast() {
    if (size > 0) { // cannot delete something that does not exist
        T* newData = new T[capacity];

        for (size_t i =0; i<size-1;i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        size = size-1;
    }
}


#endif //BLOIS_DYNAMICARRAY_HPP