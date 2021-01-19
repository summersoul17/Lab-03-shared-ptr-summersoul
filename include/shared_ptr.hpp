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

    auto operator=(const SharedPtr& r) -> SharedPtr&{
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
    auto operator=(SharedPtr&& r) -> SharedPtr&{
        if(this != &r){
            std::swap(pointer, r.pointer);
            std::swap(counter, r.counter);
            }
        return *this;
    };

    // проверяет, указывает ли указатель на объект
    operator bool() const{
        return(pointer)?true:false;
    };
    auto operator*() const -> T&{
        return *pointer;
    };
    auto operator->() const -> T*{
        return pointer;
    };

    auto get() -> T*{
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
    // возвращает количество объектов SharedPtr, которые ссылаются на тот же управляемый объект
    auto use_count() const -> size_t{
        return(counter)?((size_t)*counter):(0);
    };
private:
    T* pointer;
    atomic_uint* counter;
};

#endif // INCLUDE_SHARED_PTR_HPP_
