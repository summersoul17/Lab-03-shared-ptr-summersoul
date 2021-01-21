// Copyright 2021 Summersoul17 <17summersoul17@gmail.com>

#ifndef INCLUDE_SHARED_PTR_HPP_
#define INCLUDE_SHARED_PTR_HPP_

#include <iostream>
#include <atomic>
#include <utility>

using std::move;
using std::atomic_uint;
using std::swap;

template <typename T>
class SharedPtr {
public:
    SharedPtr()
        :pointer(nullptr), counter(nullptr){};
    explicit SharedPtr(T* ptr)
        :pointer(ptr){
        if(ptr == nullptr)
            counter = nullptr;
        else{
            counter = new atomic_uint;
            *counter = 1;
        }
    };
    SharedPtr(const SharedPtr& r){
        if(r.pointer){
            pointer = r.pointer;
            counter = r.counter;
            if(pointer){
                *counter = *counter+1;
            }
            else
                counter = nullptr;
        }
    };
    SharedPtr(SharedPtr&& r){
        pointer = nullptr;
        counter = nullptr;
        if(r.pointer){
            std::swap(pointer, r.pointer);
            std::swap(counter, r.counter);
        }
    };
    ~SharedPtr(){
        if(counter){
            if(!--*counter){
                delete pointer;
                delete counter;
            }
        }
    };
    SharedPtr& operator=(const SharedPtr& r){//PROVERKA NA SAMOPRISVAIVANIE
        if(this != &r){
            pointer = r.pointer;
            counter = r.counter;
            if(pointer){
                *counter = *counter+1;
            }
            else
                counter = nullptr;
        }
        return *this;
    };
    SharedPtr& operator=(SharedPtr&& r){
        if(this != &r){
            std::swap(pointer, r.pointer);
            std::swap(counter, r.counter);
            }
        return *this;
    };
    operator bool() const{
        return(pointer)?true:false;
    };
    T& operator*() const{
        return *pointer;
    };
    T* operator->() const{
        return pointer;
    };
    T* get(){
        return pointer;
    };
    void reset() {
        if(*counter == 1){
            delete pointer;
            delete counter;
        }else{
            *counter = *counter-1;
        }
        pointer=nullptr;
        counter=nullptr;
    }
    void reset(T* ptr){
        if(*counter == 1){
            delete pointer;
            delete counter;
        }else {
            *counter = *counter - 1;
        }
        pointer = ptr;
        if(ptr == nullptr){
            counter = nullptr;
        }else{
            counter = new atomic_uint;
            *counter = 1;
        }
    };
    void swap(SharedPtr& r){
        std::swap(pointer, r.pointer);
        std::swap(counter, r.counter);
    };
    size_t use_count() const{
        return(counter)?((size_t)*counter):(0);
    };
private:
    T* pointer;
    atomic_uint* counter;
};
#endif // INCLUDE_SHARED_PTR_HPP_
