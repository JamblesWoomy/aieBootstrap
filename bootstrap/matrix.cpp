#include "matrix.h"
#include "pch.h"
#include <cassert>

Matrix2::Matrix2()
{
	xAxis = { 0,0 };
	yAxis = { 0,0 };
	memset(this, 0, sizeof(float) * 4);
}

Matrix2::Matrix2(float _00, float _01, float _10, float _11)
{
	data[0][0] = _00;
	data[0][1] = _01;
	data[1][0] = _10;
	data[1][1] = _11;
}

Matrix2::Matrix2(const Matrix2& other)
{
	memcpy(this, &other, 4 * sizeof(float));
}

Matrix2& Matrix2::operator = (const Matrix2& other)
{
	// TODO: insert return statement here
	memcpy(this, &other, 4 * sizeof(float));
	return *this;
}

Vector2& Matrix2::operator[](int index)
{
	// TODO: insert return statement here
	return axis[index];
}

const Vector2& Matrix2::operator[](int index) const
{
	// TODO: insert return statement here
	return axis[index];
}

void Matrix2::setIdentity()
{
	// clear the matrix values
	memset(this, 0, sizeof(float) * 4);
	// set the diagonal values to 1
	for (int i = 0;i < 2;i++)
	{
		data[i][i] += 1;
	}
}

Matrix2 Matrix2::transposed() const
{
	Matrix2 result;
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			result.data[row][column] = data[column][row];
		}
	}
	return result;
}

Matrix2 Matrix2::operator*(const Matrix2& other) const
{
	// reserve memory for our result
	Matrix2 result; // calls default constructor which clears matrix
	// iterate through the rows in the first matrix
	for (int row = 0; row < 2; ++row) {
		// iterate through the columns in the other matrix
		for (int column = 0; column < 2; ++column) {
			// iterate over the components for a dot product
			for (int component = 0; component < 2; ++component)
			{
				result.data[column][row] += data[component][row] * other.data[column][component];
			}
		}
	}
	return result;
}

Vector2 Matrix2::operator*(const Vector2& v) const
{
	Vector2 result;
	for (int row = 0; row < 2; ++row) {
		for (int component = 0; component < 2; ++component) {
			result[row] += data[component][row] * v[component];
		}
	}
	return result;
}

void Matrix2::setRotate(float radians)
{
	xAxis = { cosf(radians), -sinf(radians) };
	yAxis = { sinf(radians), cosf(radians) };
}

void Matrix2::rotate(float radians)
{
	Matrix2 m;
	m.setRotate(radians);
	*this = *this * m;
}

void Matrix2::setScaled(float x, float y)
{
	xAxis = { x, 0 };
	yAxis = { 0, y };
}

void Matrix2::setScaled(const Vector2& v)
{
	xAxis = { v.x, 0 };
	yAxis = { 0, v.y };
}

void Matrix2::scale(float x, float y)
{
	Matrix2 m;
	m.setScaled(x, y);
	*this = *this * m;
}

void Matrix2::scale(const Vector2& v)
{
	Matrix2 m;
	m.setScaled(v);
	*this = *this * m;
}

std::ostream& operator<<(std::ostream& os, const Matrix2& m)
{
	// TODO: insert return statement here
	for (int r = 0; r < 2; ++r) {
		for (int c = 0; c < 2; ++c) {
			os << m.data[c][r] << ",";
		}
		os << std::endl;
	}
	return os;
}

//MATRIX 3

Matrix3::Matrix3()
{
	xAxis = { 0,0,0 };
	yAxis = { 0,0,0 };
	zAxis = { 0,0,0 };
	memset(this, 0, sizeof(float) * 9);
}

Matrix3::Matrix3(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22)
{
	data[0][0] = _00;
	data[0][1] = _01;
	data[0][2] = _02;
	data[1][0] = _10;
	data[1][1] = _11;
	data[1][2] = _12;
	data[2][0] = _20;
	data[2][1] = _21;
	data[2][2] = _22;
}

Matrix3::Matrix3(const Matrix3& other)
{
	memcpy(this, &other, 9 * sizeof(float));
}

Matrix3& Matrix3::operator=(const Matrix3& other)
{
	// TODO: insert return statement here
	memcpy(this, &other, 9 * sizeof(float));
	return *this;
}

Vector3& Matrix3::operator[](int index)
{
	// TODO: insert return statement here
	return axis[index];
}

const Vector3& Matrix3::operator[](int index) const
{
	// TODO: insert return statement here
	return axis[index];
}

void Matrix3::setIdentity()
{
	// clear the matrix values
	memset(this, 0, sizeof(float) * 9);
	// set the diagonal values to 1
	for (int i = 0;i < 3;i++)
	{
		data[i][i] = 1;
	}
}

Matrix3 Matrix3::transposed() const
{
	Matrix3 result;
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column) {
			result.data[row][column] += data[column][row];
		}
	}
	return result;
}

void Matrix3::setTranslate(float x, float y)
{
	translation.x = x;
	translation.y = y;
}

void Matrix3::setTranslate(const Vector2& other)
{
	translation.x = other.x;
	translation.y = other.y;
}

void Matrix3::translate(float x, float y)
{
	translation.x += x;
	translation.y += y;
}

void Matrix3::translate(const Vector2& other)
{
	translation.x += other.x;
	translation.y += other.y;
}

void Matrix3::setEuler(float pitch, float yaw, float roll)
{
	setRotateZ(roll);
	rotateY(yaw);
	rotateX(pitch);
}

void Matrix3::setRotateX(float radians)
{
	xAxis = { 1, 0, 0 };
	yAxis = { 0, cosf(radians), -sinf(radians)};
	zAxis = { 0, sinf(radians), cosf(radians)};
}

void Matrix3::setRotateY(float radians)
{
	xAxis = { cosf(radians), 0, sinf(radians) };
	yAxis = { 0, 1, 0 };
	zAxis = { -sinf(radians), 0, cosf(radians) };
}

void Matrix3::setRotateZ(float radians)
{
	xAxis = { cosf(radians), -sinf(radians), 0 };
	yAxis = { sinf(radians), cosf(radians), 0 };
	zAxis = { 0, 0, 1 };
}

void Matrix3::rotateX(float radians)
{
	Matrix3 m;
	m.setRotateX(radians);
	*this = *this * m;
}

void Matrix3::rotateY(float radians)
{
	Matrix3 m;
	m.setRotateY(radians);
	*this = *this * m;
}

void Matrix3::rotateZ(float radians)
{
	Matrix3 m;
	m.setRotateZ(radians);
	*this = *this * m;
}

void Matrix3::setScaled(float x, float y, float z)
{
	xAxis = { x, 0, 0 };
	yAxis = { 0, y, 0 };
	zAxis = { 0, 0, z };
}

void Matrix3::setScaled(const Vector3& v)
{
	xAxis = { v.x, 0, 0 };
	yAxis = { 0, v.y, 0 };
	zAxis = { 0, 0, v.z };
}

void Matrix3::scale(float x, float y, float z)
{
	Matrix3 m;
	m.setScaled(x, y, z);
	*this = *this * m;
}

void Matrix3::scale(const Vector3& v)
{
	Matrix3 m;
	m.setScaled(v);
	*this = *this * m;
}

Matrix3 Matrix3::operator*(const Matrix3& other) const
{
	// reserve memory for our result
	Matrix3 result; // calls default constructor which clears matrix
	// iterate through the rows in the first matrix
	for (int row = 0; row < 3; ++row) {
		// iterate through the columns in the other matrix
		for (int column = 0; column < 3; ++column) {
			// iterate over the components for a dot product
			for (int component = 0; component < 3; ++component)
			{
				result.data[column][row] += data[component][row] * other.data[column][component];
			}
		}
	}
	return result;
}

Vector3 Matrix3::operator*(const Vector3& v) const
{
	Vector3 result;
	for (int row = 0; row < 3; ++row) {
		for (int component = 0; component < 3; ++component) {
			result[row] += data[component][row] * v[component];
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix3& m)
{
	for (int r = 0; r < 3; ++r) {
		for (int c = 0; c < 3; ++c) {
			os << m.data[c][r] << ",";
		}
		os << std::endl;
	}
	return os;
}

//MATRIX 4

Matrix4::Matrix4()
{
	xAxis = { 0,0,0,0 };
	yAxis = { 0,0,0,0 };
	zAxis = { 0,0,0,0 };
	memset(this, 0, sizeof(float) * 16);
}

Matrix4::Matrix4(const Matrix4& other)
{
	memcpy(this, &other, 16 * sizeof(float));
}

Matrix4::Matrix4(float _00, float _01, float _02, float _03, float _10, float _11, float _12, float _13, float _20, float _21, float _22, float _23, float _30, float _31, float _32, float _33)
{
	data[0][0] = _00;
	data[0][1] = _01;
	data[0][2] = _02;
	data[0][3] = _03;
	data[1][0] = _10;
	data[1][1] = _11;
	data[1][2] = _12;
	data[1][3] = _13;
	data[2][0] = _20;
	data[2][1] = _21;
	data[2][2] = _22;
	data[2][3] = _23;
	data[3][0] = _30;
	data[3][1] = _31;
	data[3][2] = _32;
	data[3][3] = _33;
}

Matrix4& Matrix4::operator=(const Matrix4& other)
{
	axis[0] = other.axis[0];
	axis[1] = other.axis[1];
	axis[2] = other.axis[2];
	axis[3] = other.axis[3];
	return *this;
}

Vector4& Matrix4::operator[](int index)
{
	return axis[index];
}

const Vector4& Matrix4::operator[](int index) const
{
	return axis[index];
}

void Matrix4::setIdentity()
{
	// clear the matrix values
	memset(this, 0, sizeof(float) * 16);
	// set the diagonal values to 1
	for (int i = 0;i < 4;i++)
	{
		data[i][i] += 1;
	}
}

Matrix4 Matrix4::transposed() const
{
	Matrix4 result;
	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			result.data[row][column] = data[column][row];
		}
	}
	return result;
}

void Matrix4::setTranslate(float x, float y, float z)
{
	translation.x = x;
	translation.y = y;
	translation.z = z;
}

void Matrix4::setTranslate(const Vector3& other)
{
	translation.x = other.x;
	translation.y = other.y;
	translation.z = other.z;
}

void Matrix4::translate(float x, float y, float z)
{
	translation.x += x;
	translation.y += y;
	translation.z += z;
}

void Matrix4::translate(const Vector3& other)
{
	translation.x += other.x;
	translation.y += other.y;
	translation.z += other.z;
}

void Matrix4::setEuler(float pitch, float yaw, float roll)
{
	setRotateZ(roll);
	rotateY(yaw);
	rotateX(pitch);
}

void Matrix4::setRotateX(float radians)
{
	xAxis = { 1, 0, 0, 0 };
	yAxis = { 0, cosf(radians), -sinf(radians), 0 };
	zAxis = { 0, sinf(radians), cosf(radians), 0 };
}

void Matrix4::setRotateY(float radians)
{
	xAxis = { cosf(radians), 0, sinf(radians), 0 };
	yAxis = { 0, 1, 0, 0 };
	zAxis = { -sinf(radians), 0, cosf(radians), 0 };
}

void Matrix4::setRotateZ(float radians)
{
	xAxis = { cosf(radians), -sinf(radians), 0, 0 };
	yAxis = { sinf(radians), cosf(radians), 0, 0 };
	zAxis = { 0, 0, 1, 0 };
}

void Matrix4::rotateX(float radians)
{
	Matrix3 m;
	m.setRotateX(radians);
}

void Matrix4::rotateY(float radians)
{
	Matrix3 m;
	m.setRotateY(radians);
}

void Matrix4::rotateZ(float radians)
{
	Matrix4 m;
	m.setRotateZ(radians);
}

void Matrix4::setScaled(float x, float y, float z)
{
	xAxis = { x, 0, 0, 0 };
	yAxis = { 0, y, 0, 0 };
	zAxis = { 0, 0, z, 0 };
}

void Matrix4::setScaled(const Vector3& v)
{
	xAxis = { v.x, 0, 0, 0 };
	yAxis = { 0, v.y, 0, 0 };
	zAxis = { 0, 0, v.z, 0 };
}

void Matrix4::scale(float x, float y, float z)
{
	Matrix4 m;
	m.setScaled(x, y, z);
	*this = *this * m;
}

void Matrix4::scale(const Vector3& v)
{
	Matrix4 m;
	m.setScaled(v);
	*this = *this * m;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const
{
	// reserve memory for our result
	Matrix4 result; // calls default constructor which clears matrix
	// iterate through the rows in the first matrix
	for (int row = 0; row < 4; ++row) {
		// iterate through the columns in the other matrix
		for (int column = 0; column < 4; ++column) {
			//iterate over the components for a dot product
			for (int component = 0; component < 4; ++component)
			{
				result.data[column][row] += data[component][row] * other.data[column][component];
			}
		}
	}
	return result;
}

Vector4 Matrix4::operator*(const Vector4& v) const
{
	Vector4 result;
	for (int row = 0; row < 4; ++row) {
		result[row] = data[0][row] * v[0] + data[1][row] * v[1] + data[2][row] * v[2] + data[3][row] * v[3];;
		//for (int component = 0; component < 4; ++component) {
		//	result[row] += data[component][row] * v[component];
		//}
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix4& m)
{
	for (int r = 0; r < 4; ++r) {
		for (int c = 0; c < 4; ++c) {
			os << m.data[c][r] << ",";
		}
		os << std::endl;
	}
	return os;
}