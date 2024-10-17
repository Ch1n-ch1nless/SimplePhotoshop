#ifndef GRAPHICS_LIBRARY_VECTOR_HPP
#define GRAPHICS_LIBRARY_VECTOR_HPP

namespace Graphics
{
    class Vector2d
    {
    public:
         Vector2d();
         Vector2d(int x, int y);
         Vector2d(const Vector2d& other);

        ~Vector2d();

        Vector2d& operator +=   (const Vector2d& other);
        Vector2d& operator -=   (const Vector2d& other);

        int GetX() const;
        int GetY() const;

    private:
        int x_;
        int y_;
    };

    Vector2d operator + (const Vector2d& left, const Vector2d& right);
    Vector2d operator - (const Vector2d& left, const Vector2d& right);

    class Vector2f
    {
    public:
         Vector2f();
         Vector2f(double x, double y);
         Vector2f(const Vector2f& other);
         Vector2f(const Vector2d& other);

        ~Vector2f();

        Vector2f& operator += (const Vector2f& other);
        Vector2f& operator -= (const Vector2f& other);
        Vector2f& operator *= (const double coefficient);

        void Normalize();

        void Rotate(const double angle);

        void Orthogonalize();

              double Length2();
        const double Length2() const;

              double Length();
        const double Length() const; 

              double GetX();
        const double GetX() const;

              double GetY();
        const double GetY() const;

              double GetAngle();
        const double GetAngle() const;

    private:
        double x_;
        double y_;
    };

    Vector2f operator + (const Vector2f& left,        const Vector2f& right);
    Vector2f operator - (const Vector2f& left,        const Vector2f& right);
    Vector2f operator * (const double    coefficient, const Vector2f& vec);
    Vector2f operator * (const Vector2f& vec,         const double coefficient);
    double   operator * (const Vector2f& left,        const Vector2f& right);

} //namespace Graphics

#endif //GRAPHICS_LIBRARY_VECTOR_HPP