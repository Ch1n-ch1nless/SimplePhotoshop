#ifndef GRAPHICS_MATH_VECTOR_HPP
#define GRAPHICS_MATH_VECTOR_HPP

namespace psapi
{
    namespace sfm
    {
        template<typename T>
        struct Vec2D
        {
            T x;
            T y;

            Vec2D<T>& operator+=(const Vec2D<T> &other);
            Vec2D<T>& operator-=(const Vec2D<T> &other);
            Vec2D<T>& operator*=(const double cf);
        };

        template<typename T>
        Vec2D<T> operator+(const Vec2D<T> &left, const Vec2D<T> &right);

        template<typename T>
        Vec2D<T> operator-(const Vec2D<T> &left, const Vec2D<T> &right);

        template<typename T>
        Vec2D<T> operator*(const Vec2D<T> &vec,  const double    cf);

        template<typename T>
        Vec2D<T> operator*(const double    cf,   const Vec2D<T> &vec);

    } //sfm

} //psapi


#endif //GRAPHICS_MATH_VECTOR_HPP