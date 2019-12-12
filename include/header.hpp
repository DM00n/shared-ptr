// Copyright 2019 DM00n <teamvortex@yandex.ru>
#ifndef INCLUDE_HEADER_HPP_
#define INCLUDE_HEADER_HPP_

#include <atomic>
#include <map>
#include <iostream>

template <typename T>
class SharedPtr{
public:
    SharedPtr(){
        _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
    }
    explicit SharedPtr(T* ptr):_pointer(ptr){
        _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
    }
    SharedPtr(const SharedPtr& r):_pointer(r._pointer){
        _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
    }
    SharedPtr(SharedPtr&& r):_pointer(r->_pointer){
        _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
    }
    ~SharedPtr(){
        _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))--;
        if (_shared_map.
                operator[](reinterpret_cast<int64_t>(_pointer)) == 0){
            auto it = _shared_map.
                    find((reinterpret_cast<int64_t>(_pointer)));
            delete _pointer;
            _shared_map.erase(it);
        }
    }
    auto operator=(const SharedPtr& r) -> SharedPtr& {
        _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))--;
        if (_shared_map.
                operator[](reinterpret_cast<int64_t>(_pointer)) == 0){
            auto it = _shared_map.
                    find((reinterpret_cast<int64_t>(_pointer)));
            delete _pointer;
            _shared_map.erase(it);
        }
        _pointer = r._pointer;
        _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
        return *this;
    }
    auto operator=(SharedPtr&& r) -> SharedPtr& {
        _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))--;
        if (_shared_map.
                operator[](reinterpret_cast<int64_t>(_pointer)) == 0){
            auto it = _shared_map.
                    find((reinterpret_cast<int64_t>(_pointer)));
            delete _pointer;
            _shared_map.erase(it);
        }
        _pointer = r._pointer;
        _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
        return *this;
    }
    operator bool() const {
        return !(_shared_map.operator[]
                (reinterpret_cast<int64_t>(_pointer)) == 0);
    }
    auto operator*() const -> T& {
        return *_pointer;
    }
    auto operator->() const -> T* {
        return _pointer;
    }
    auto get() -> T* {
        return _pointer;
    }
    void reset() {
        _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))--;
        if (_shared_map.
                operator[](reinterpret_cast<int64_t>(_pointer)) == 0){
            auto it = _shared_map.
                    find((reinterpret_cast<int64_t>(_pointer)));
            delete _pointer;
            _shared_map.erase(it);
        }
        _pointer = NULL;
        _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
    }
    void reset(T* ptr){
        _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))--;
        if (_shared_map.
                operator[](reinterpret_cast<int64_t>(_pointer)) == 0){
            auto it = _shared_map.
                    find((reinterpret_cast<int64_t>(_pointer)));
            delete _pointer;
            _shared_map.erase(it);
        }
        _pointer = ptr;
        _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
    }
    void my_swap(SharedPtr& r){
        T* ptrka = NULL;
        ptrka = _pointer;
        _pointer = r._pointer;
        r._pointer = ptrka;
    }
    auto use_count() const -> size_t {
        return SharedPtr::_shared_map.operator[]
                (reinterpret_cast<int64_t>(_pointer));
    }
    static std::map<int64_t, std::atomic_uint> _shared_map;
private:
    T* _pointer;
};

template <typename T>
std::map<int64_t, std::atomic_uint> SharedPtr<T>::_shared_map{};

#endif // INCLUDE_HEADER_HPP_
