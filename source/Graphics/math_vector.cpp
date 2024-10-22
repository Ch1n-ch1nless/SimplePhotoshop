#include "math_vector.hpp"

template <typename T>
inline psapi::sfm::Vec2D<T> &psapi::sfm::Vec2D<T>::operator+=(const Vec2D<T> &other)
{
    x += other.x;
    y += other.y;

    return *this;
}

template <typename T>
inline psapi::sfm::Vec2D<T> &psapi::sfm::Vec2D<T>::operator-=(const Vec2D<T> &other)
{
    x -= other.x;
    y -= other.y;

    return *this;
}

template <typename T>
inline psapi::sfm::Vec2D<T> &psapi::sfm::Vec2D<T>::operator*=(const double cf)
{
    x *= cf;
    y *= cf;

    return *this;
}

template <typename T>
inline psapi::sfm::Vec2D<T> psapi::sfm::operator+(const Vec2D<T> &left, const Vec2D<T> &right)
{
    Vec2D<T> temp = left;
    temp += right;

    return temp;
}

template <typename T>
inline psapi::sfm::Vec2D<T> psapi::sfm::operator-(const Vec2D<T> &left, const Vec2D<T> &right)
{
    Vec2D<T> temp = left;
    temp -= right;

    return temp;
}

template <typename T>
inline psapi::sfm::Vec2D<T> psapi::sfm::operator*(const Vec2D<T> &vec, const double cf)
{
    Vec2D<T> temp = vec;
    temp *= cf;

    return temp;
}

template <typename T>
inline psapi::sfm::Vec2D<T> psapi::sfm::operator*(const double cf, const Vec2D<T> &vec)
{
    return vec * cf;
}
