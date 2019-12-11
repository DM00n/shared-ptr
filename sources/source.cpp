// Copyright 2019 DM00n <teamvortex@yandex.ru>

#include "header.hpp"
template <typename T>
std::map<int64_t, std::atomic_uint> SharedPtr<T>::_shared_map{};
template<typename T>
SharedPtr<T>::SharedPtr():_pointer(nullptr) {
    _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
}

template<typename T>
SharedPtr<T>::SharedPtr(T* ptr):_pointer(ptr){
    _shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
}

template<typename T>
SharedPtr<T>::SharedPtr(const SharedPtr& SP):_pointer(SP._pointer){
    SharedPtr::_shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
}

template<typename T>
SharedPtr<T>::SharedPtr(SharedPtr&& SP):_pointer(SP->_pointer){
    SharedPtr::_shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
}

template<typename T>
SharedPtr<T>::~SharedPtr(){
    SharedPtr::_shared_map.operator[](reinterpret_cast<int64_t>(_pointer))--;
    if (SharedPtr::_shared_map.
            operator[](reinterpret_cast<int64_t>(_pointer)) == 0){
        auto it = SharedPtr::_shared_map.
                find((reinterpret_cast<int64_t>(_pointer)));
        SharedPtr::_shared_map.erase(it);
        delete _pointer;
    }
}

template<typename T>
auto SharedPtr<T>::operator=(const SharedPtr &r) -> SharedPtr & {
    SharedPtr::_shared_map.operator[](reinterpret_cast<int64_t>(_pointer))--;
    if (SharedPtr::_shared_map.
            operator[](reinterpret_cast<int64_t>(_pointer)) == 0){
        auto it = SharedPtr::_shared_map.
                find((reinterpret_cast<int64_t>(_pointer)));
        SharedPtr::_shared_map.erase(it);
        delete _pointer;
    }
    _pointer = r._pointer;
    SharedPtr::_shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
    return *this;
}

template<typename T>
auto SharedPtr<T>::operator=(SharedPtr &&r) -> SharedPtr & {
    SharedPtr::_shared_map.operator[](reinterpret_cast<int64_t>(_pointer))--;
    if (SharedPtr::_shared_map.
            operator[](reinterpret_cast<int64_t>(_pointer)) == 0){
        auto it = SharedPtr::_shared_map.
                find((reinterpret_cast<int64_t>(_pointer)));
        SharedPtr::_shared_map.erase(it);
        delete _pointer;
    }
    _pointer = r._pointer;
    SharedPtr::_shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
    return *this;
}

template<typename T>
SharedPtr<T>::operator bool() const {
    return !(SharedPtr::_shared_map.operator[]
            (reinterpret_cast<int64_t>(_pointer)) == 0);
}

template<typename T>
auto SharedPtr<T>::operator*() const -> T & {
    return *_pointer;
}

template<typename T>
auto SharedPtr<T>::operator->() const -> T * {
    return _pointer;
}

template<typename T>
auto SharedPtr<T>::get() -> T* {
    return _pointer;
}

template<typename T>
auto SharedPtr<T>::use_count() const -> size_t {
    return SharedPtr::_shared_map.operator[]
            (reinterpret_cast<int64_t>(_pointer));
}

template<typename T>
void SharedPtr<T>::reset() {
    SharedPtr::_shared_map.operator[](reinterpret_cast<int64_t>(_pointer))--;
    if (SharedPtr::_shared_map.
            operator[](reinterpret_cast<int64_t>(_pointer)) == 0){
        auto it = SharedPtr::_shared_map.
                find((reinterpret_cast<int64_t>(_pointer)));
        SharedPtr::_shared_map.erase(it);
        delete _pointer;
    }
    _pointer = NULL;
    SharedPtr::_shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
}

template<typename T>
void SharedPtr<T>::reset(T *ptr) {
    SharedPtr::_shared_map.operator[](reinterpret_cast<int64_t>(_pointer))--;
    if (SharedPtr::_shared_map.
            operator[](reinterpret_cast<int64_t>(_pointer)) == 0){
        auto it = SharedPtr::_shared_map.
                find((reinterpret_cast<int64_t>(_pointer)));
        SharedPtr::_shared_map.erase(it);
        delete _pointer;
    }
    _pointer = ptr;
    SharedPtr::_shared_map.operator[](reinterpret_cast<int64_t>(_pointer))++;
}

template<typename T>
void SharedPtr<T>::my_swap(SharedPtr &r) {
    T* ptrka = NULL;
    ptrka = _pointer;
    _pointer = r._pointer;
    r._pointer = ptrka;
}

