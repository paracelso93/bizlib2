#ifndef ENGINE_MATHS_H
#define ENGINE_MATHS_H

#include "libs.h"

template <typename T>
struct Vector2 {
public:
    T x, y;
    Vector2() : x(0), y(0) {}
    Vector2(T x, T y) : x(x), y(y) {}
    Vector2(const Vector2<T>& other) : x(other.x), y(other.y) {}
    Vector2(Vector2<T>&& other) noexcept : x(other.x), y(other.y) { other.x = 0; other.y = 0; }

    Vector2<T> operator +(const Vector2<T>& other) {
        return Vector2<T>(x + other.x, y + other.y);
    }

    Vector2<T> operator -(const Vector2<T>& other) {
        return Vector2<T>(x - other.x, y - other.y);
    }

    Vector2<T> operator *(T other) {
        return Vector2<T>(x * other, y * other);
    }

    Vector2<T>& operator =(const Vector2<T>& other) {
        if (this == &other) {
            return *this;
        }

        x = other.x;
        y = other.y;

        return *this;
    }

};

template <typename T>
inline bool operator ==(const Vector2<T>& lhs, const Vector2<T>& rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

#endif // ENGINE_MATHS_H
