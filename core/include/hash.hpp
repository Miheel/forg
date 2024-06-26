#ifndef HASH_HPP
#define HASH_HPP
#include "type_traits.hpp"

namespace forg {

usize hash_FNV_1a(const unsigned char* first, usize count);

template <typename T>
usize hash_funk(T key) {
    return hash_FNV_1a(&reinterpret_cast<const unsigned char&>(key), sizeof(T));
}

template <typename T>
usize hash_funk_arr(T key, usize count) {
    return hash_FNV_1a(&reinterpret_cast<const unsigned char&>(key),
                       count * sizeof(T));
}

template <class T, bool enabled>
struct hash_cond {
    usize operator()(T key) {
        return hash_funk(key);
    }
};
template <class T>
class hash_cond<T, false> {};

template <typename T>
struct Hash : hash_cond<T, IsIntegral_v<T>> {};

template <typename T>
struct Hash<T*> {
    usize operator()(T* key) {
        return hash_funk(key);
    }
};
}  // namespace forg

#endif  // !HASH_HPP
