#include "vector.h"
#include "pch.h"
#include <cassert>

void test() {
    Vector2 v1;
    float f = v1[0];
}

//Vector 2

//Constructors
Vector2::Vector2()
{
    x = 0;
    y = 0;
}
Vector2::Vector2(float _x, float _y)
{
    x = _x;
    y = _y;
}
Vector2::Vector2(const Vector2& other)
{
    *this = other;
}

Vector2& Vector2::operator=(const Vector2& other)
{
    x = other.x;
    y = other.y;
    return *this;
}

float Vector2::operator[](int index) const
{
    return data[index];
}

float& Vector2::operator[](int index)
{
    return data[index];
}

float Vector2::dot(const Vector2& other) const
{
    float xTerm = (x * other.x);
    float yTerm = (y * other.y);
    return xTerm + yTerm;
}

float Vector2::angleBetween(const Vector2& other) const
{
    Vector2 v1 = normalised();
    Vector2 v2 = other.normalised();
    float cosineAngle = v1.dot(v2);
    return acos(cosineAngle);
}

float Vector2::magnitude() const
{
    return pow(magnitudeSqr(), 0.5f);
}

float Vector2::magnitudeSqr() const
{
    return dot(*this);
}

void Vector2::normalise()
{
    *this = this->normalised();
}

Vector2 Vector2::normalised() const
{
    return *this / this->magnitude();
}

Vector2 Vector2::operator + (const Vector2& other) const
{
    return { x + other.x,y + other.y };
}
Vector2& Vector2::operator += (const Vector2& other)
{
    *this = *this + other;
    return *this;
}

Vector2 Vector2::operator - (const Vector2& other) const
{
    return { x - other.x,y - other.y };
}

Vector2& Vector2::operator -= (const Vector2& other)
{
    *this = *this - other;
    return *this;
}

Vector2 Vector2::operator * (float scalar) const
{
    return { x * scalar, y * scalar};
}

Vector2& Vector2::operator *= (float scalar)
{
    *this = *this * scalar;
    return *this;
}

Vector2 Vector2::operator / (float scalar) const
{
    return { x / scalar, y / scalar };
}

Vector2& Vector2::operator /= (float scalar)
{
    *this = *this / scalar;
    return *this;
}

float Vector2::distanceTo(const Vector2& other) const
{
    return (other - *this).magnitude();
}

float Vector2::distanceToSqr(const Vector2& other) const
{
    return (other - *this).magnitudeSqr();
}



Vector3::Vector3()
{
    x = 0;
    y = 0;
    z = 0;
}
Vector3::Vector3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;
}
Vector3::Vector3(const Vector3& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
}

Vector3& Vector3::operator=(const Vector3& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    return *this;
}

float Vector3::operator[](int index) const
{
    return data[index];
}

float& Vector3::operator[](int index)
{
    return data[index];
}

float Vector3::dot(const Vector3& other) const
{
    float xTerm = (x * other.x);
    float yTerm = (y * other.y);
    float zTerm = (z * other.z);
    return xTerm + yTerm + zTerm;
}

Vector3 Vector3::cross(const Vector3& other) const
{
    float x1 = y * other.z - z * other.y;
    float y1 = z * other.x - x * other.z;
    float z1 = x * other.y - y * other.x;
    return { x1, y1, z1 };
}

static Vector3 cross(const Vector3& v1, const Vector3& v2)
{
    float x1 = v1.y * v2.z - v1.z * v2.y;
    float y1 = v1.z * v2.x - v1.x * v2.z;
    float z1 = v1.x * v2.y - v1.y * v2.x;
    return { x1, y1, z1 };
}

float Vector3::angleBetween(const Vector3& other) const
{
    Vector3 v1 = normalised();
    Vector3 v2 = other.normalised();
    float cosineAngle = v1.dot(v2);
    return acos(cosineAngle);
}

float Vector3::magnitude() const
{
    return pow(magnitudeSqr(), 0.5f);
}

float Vector3::magnitudeSqr() const
{
    return dot(*this);
}

void Vector3::normalise()
{
    *this = this->normalised();
}

Vector3 Vector3::normalised() const
{
    return *this / this->magnitude();
}

Vector3 Vector3::operator+(const Vector3& other) const
{
    return { x + other.x,y + other.y,z + other.z };
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    *this = *this + other;
    return *this;
}

Vector3 Vector3::operator-(const Vector3& other) const
{
    return { x - other.x,y - other.y,z - other.z };
}

Vector3& Vector3::operator-=(const Vector3& other)
{
    *this = *this - other;
    return *this;
}

Vector3 Vector3::operator*(float scalar) const
{
    return { x * scalar, y * scalar, z * scalar };
}

Vector3& Vector3::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}

Vector3 Vector3::operator/(float scalar) const
{
    return { x / scalar, y / scalar, z / scalar };
}

Vector3& Vector3::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}

float Vector3::distanceTo(const Vector3& other) const
{
    return (*this - other).magnitude();
}

float Vector3::distanceToSqr(const Vector3& other) const
{
    return (*this - other).magnitudeSqr();
}

Vector4::Vector4()
{
    x = 0;
    y = 0;
    z = 0;
    w = 0;
}
Vector4::Vector4(float _x, float _y, float _z, float _w)
{
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}
Vector4::Vector4(const Vector4& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
}

Vector4& Vector4::operator=(const Vector4& other)
{
    x = other.x;
    y = other.y;
    z = other.z;
    w = other.w;
    return *this;
}

float Vector4::operator[](int index) const
{
    return data[index];
}

float& Vector4::operator[](int index)
{
    return data[index];
}

float Vector4::dot(const Vector4& other) const
{
    return  (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
}

float Vector4::angleBetween(const Vector4& other) const
{
    Vector4 v1 = normalised();
    Vector4 v2 = other.normalised();
    float cosineAngle = v1.dot(v2);
    return acos(cosineAngle);
}

Vector4 Vector4::cross(const Vector4& other) const
{
    assert((w == 0) && (other.w == 0));
    float x1 = y * other.z - z * other.y;
    float y1 = z * other.x - x * other.z;
    float z1 = x * other.y - y * other.x;
    return { x1, y1, z1, 0 };
}

static Vector4 cross(const Vector4& v1, const Vector4& v2)
{
    assert((v1.w == 0) && (v2.w == 0));
    float x1 = v1.y * v2.z - v1.z * v2.y;
    float y1 = v1.z * v2.x - v1.x * v2.z;
    float z1 = v1.x * v2.y - v1.y * v2.x;
    return { x1, y1, z1, 0 };
}

float Vector4::magnitude() const
{
    return pow(magnitudeSqr(), 0.5f);
}

float Vector4::magnitudeSqr() const
{
    return dot(*this);
}

void Vector4::normalise()
{
    *this = this->normalised();
}

Vector4 Vector4::normalised() const
{
    return *this / this->magnitude();
}

Vector4 Vector4::operator+(const Vector4& other) const
{
    return { x + other.x,y + other.y,z + other.z, w + other.w };
}

Vector4& Vector4::operator+=(const Vector4& other)
{
    *this = *this + other;
    return *this;
}

Vector4 Vector4::operator-(const Vector4& other) const
{
    return { x - other.x,y - other.y,z - other.z, w - other.w };
}

Vector4& Vector4::operator-=(const Vector4& other)
{
    *this = *this - other;
    return *this;
}

Vector4 Vector4::operator*(float scalar) const
{
    return { x * scalar, y * scalar, z * scalar, w * scalar };
}

Vector4& Vector4::operator*=(float scalar)
{
    *this = *this * scalar;
    return *this;
}

Vector4 Vector4::operator/(float scalar) const
{
    return { x / scalar, y / scalar, z / scalar, w / scalar };
}

Vector4& Vector4::operator/=(float scalar)
{
    *this = *this / scalar;
    return *this;
}

float Vector4::distanceTo(const Vector4& other) const
{
    return (*this - other).magnitude();
}

float Vector4::distanceToSqr(const Vector4& other) const
{
    return (*this - other).magnitudeSqr();
}

Vector4::operator Vector3() const
{
    return {x,y,z};
}

