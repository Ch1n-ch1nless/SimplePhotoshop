#include "math_vector.hpp"
#include <cmath>

using namespace Math;

/*============================================================================*/

Vector2d::Vector2d() :
    x_  (0),
    y_  (0)
{
}

Vector2d::Vector2d(int x, int y) :
    x_  (x),
    y_  (y)
{
}

Vector2d::Vector2d(const Vector2d& other) :
    x_  (other.x_),
    y_  (other.y_)
{
}

Vector2d::~Vector2d()
{
}

Vector2d& Vector2d::operator+=(const Vector2d& other)
{
    this->x_ += other.x_;
    this->y_ += other.y_;
    return *this;
}

Vector2d& Vector2d::operator-=(const Vector2d& other)
{
    this->x_ -= other.x_;
    this->y_ -= other.y_;
    return *this;
}

int Vector2d::GetX() const
{
    return x_;
}

int Vector2d::GetY() const
{
    return y_;
}

Vector2d operator + (const Vector2d& left, const Vector2d& right)
{
    Vector2d result = left;
    result += right;
    return result;
}

Vector2d operator - (const Vector2d& left, const Vector2d& right)
{
    Vector2d result = left;
    result -= right;
    return result;
}

/*============================================================================*/

Vector2f::Vector2f() :
    x_  (0.0),
    y_  (0.0)
{
}

Vector2f::Vector2f(double x, double y) :
    x_  (x),
    y_  (y)
{
}

Vector2f::Vector2f(const Vector2f& other) :
    x_  (other.x_),
    y_  (other.y_)
{
}

Vector2f::Vector2f(const Vector2d& other) :
    x_  ((double)other.GetX()),
    y_  ((double)other.GetY())
{
}

Vector2f::~Vector2f()
{
}

Vector2f& Vector2f::operator += (const Vector2f& other)
{
    this->x_ += other.x_;
    this->y_ += other.y_;
    return *this;
}

Vector2f& Vector2f::operator -= (const Vector2f& other)
{
    this->x_ -= other.x_;
    this->y_ -= other.y_;
    return *this;
}

Vector2f& Vector2f::operator *= (const double coefficient)
{
    this->x_ *= coefficient;
    this->y_ *= coefficient;
    return *this;
}

void Vector2f::Normalize()
{
    double len = Length();
    x_ /= len;
    y_ /= len;
}

void Vector2f::Orthogonalize()
{
    double temp_var = x_;
    x_ = -y_;
    y_ = temp_var;
}

void Vector2f::Rotate(double angle)
{
    double old_x = x_;
    double old_y = y_;

    x_ = old_x * cos(angle) - old_y * sin(angle);
    y_ = old_y * cos(angle) + old_x * sin(angle);
}

double Vector2f::Length2()
{
    return x_ * x_ + y_ * y_;
}

const double Vector2f::Length2() const
{
    return x_ * x_ + y_ * y_;
}

double Vector2f::Length()
{
    return sqrt(Length2());
}

const double Vector2f::Length() const
{
    return sqrt(Length2());
}

double Vector2f::GetX()
{
    return x_;
}

const double Vector2f::GetX() const
{
    return x_;
}

double Vector2f::GetY()
{
    return y_;
}

const double Vector2f::GetY() const
{
    return y_;
}

double Vector2f::GetAngle()
{   
    return atan2(y_, x_);
}

const double Vector2f::GetAngle() const
{   
    return atan2(y_, x_);
}

Vector2f operator + (const Vector2f& left, const Vector2f& right)
{
    Vector2f result = left;
    result += right;
    return result;
}

Vector2f operator - (const Vector2f& left, const Vector2f& right)
{
    Vector2f result = left;
    result -= right;
    return result;
}

Vector2f operator * (const double coefficient, const Vector2f& vec)
{
    Vector2f result = vec;
    result *= coefficient;
    return result;
}

Vector2f operator * (const Vector2f& vec, const double coefficient)
{
    Vector2f result = vec;
    result *= coefficient;
    return result;
}

double operator * (const Vector2f& left, const Vector2f& right)
{
    return left.GetX() * right.GetX() + left.GetY() * right.GetY();
}

/*============================================================================*/