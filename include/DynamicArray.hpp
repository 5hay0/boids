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

    void resize();

public:
    DynamicArray();
    DynamicArray(int inititialCapacity);
    ~DynamicArray();
    void add(const T& value);
    void print();
    int getSize() const;
    T get(int) const;
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

template <typename T>
DynamicArray<T>::~DynamicArray() {
    delete[] data;
}

template<typename T>
void DynamicArray<T>::resize() {
    capacity *= 2;
    T* newData = new T[capacity];

    for (int i =0; i<size;i++) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

template<typename T>
void DynamicArray<T>::add(const T &value) {
    if (size == capacity) {
        resize();
        std::cout<<"DynamicArray resized"<<std::endl;
    }
    data[size++] = value;
}

template<typename T>
void DynamicArray<T>::print() {
    for (int i = 0; i<size;i++) {
        std::cout<<data[i]<<std::endl;
    }
}

template<typename T>
int DynamicArray<T>::getSize() const {
    return size;
}

template<typename T>
T DynamicArray<T>::get(int i) const {
    if(i < 0 || static_cast<size_t>(i) >= size){
        throw std::out_of_range("DynamicArray out of range");
    }
    return data[i];
}

#endif //BLOIS_DYNAMICARRAY_HPP