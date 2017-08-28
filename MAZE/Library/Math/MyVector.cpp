/**
 * @file   MyVector.cpp
 * @brief  MyVector構造体の実装
 * @author kotani
 */
#include "MyVector.h"


namespace Lib
{
	//--------------------------
	// 2D Vector
	//--------------------------
	VECTOR2::VECTOR2(const float* _value)
	{
		x = *_value;
		y = *_value;
	}

	VECTOR2::VECTOR2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	VECTOR2::operator float*()
	{
		return static_cast<float*>(&x);
	}

	VECTOR2::operator const float*() const
	{
		return static_cast<const float*>(&x);
	}

	VECTOR2& VECTOR2::operator += (const VECTOR2& _obj)
	{
		x += _obj.x;
		y += _obj.y;
		return *this;
	}

	VECTOR2& VECTOR2::operator -= (const VECTOR2& _obj)
	{
		x -= _obj.x;
		y -= _obj.y;
		return *this;
	}

	VECTOR2& VECTOR2::operator *= (float _value)
	{
		x *= _value;
		y *= _value;
		return *this;
	}

	VECTOR2& VECTOR2::operator /= (float _value)
	{
		x /= _value;
		y /= _value;
		return *this;
	}

	VECTOR2 VECTOR2::operator + (const VECTOR2& _obj) const
	{
		return VECTOR2(x + _obj.x, y + _obj.y);
	}

	VECTOR2 VECTOR2::operator - (const VECTOR2& _obj) const
	{
		return VECTOR2(x - _obj.x, y - _obj.y);
	}

	VECTOR2 VECTOR2::operator * (float _value) const
	{
		return VECTOR2(x * _value, y * _value);
	}

	VECTOR2 VECTOR2::operator / (float _value) const
	{
		return VECTOR2(x / _value, y / _value);
	}

	bool VECTOR2::operator == (const VECTOR2& _obj) const
	{
		return (_obj.x == x && _obj.y == y);
	}
	bool VECTOR2::operator != (const VECTOR2& _obj) const
	{
		return (_obj.x != x && _obj.y != y);
	}

	//--------------------------
	// 3D Vector
	//--------------------------
	VECTOR3::VECTOR3(const float* _value)
	{
		x = *_value;
		y = *_value;
		z = *_value;
	}
	
	VECTOR3::VECTOR3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	VECTOR3::operator float*()
	{
		return static_cast<float*>(&x);
	}

	VECTOR3::operator const float*() const
	{
		return static_cast<const float*>(&x);
	}

	VECTOR3& VECTOR3::operator += (const VECTOR3& _obj)
	{
		x += _obj.x;
		y += _obj.y;
		return *this;
	}

	VECTOR3& VECTOR3::operator -= (const VECTOR3& _obj)
	{
		x -= _obj.x;
		y -= _obj.y;
		return *this;
	}

	VECTOR3& VECTOR3::operator *= (float _value)
	{
		x *= _value;
		y *= _value;
		return *this;
	}

	VECTOR3& VECTOR3::operator /= (float _value)
	{
		x /= _value;
		y /= _value;
		return *this;
	}

	VECTOR3 VECTOR3::operator + (const VECTOR3& _obj) const
	{
		return VECTOR3(x + _obj.x, y + _obj.y, z + _obj.z);
	}

	VECTOR3 VECTOR3::operator - (const VECTOR3& _obj) const
	{
		return VECTOR3(x - _obj.x, y - _obj.y, z - _obj.z);
	}

	VECTOR3 VECTOR3::operator * (float _value) const
	{
		return VECTOR3(x * _value, y * _value, z - _value);
	}

	VECTOR3 VECTOR3::operator / (float _value) const
	{
		return VECTOR3(x / _value, y / _value, z / _value);
	}

	bool VECTOR3::operator == (const VECTOR3& _obj) const
	{
		return (_obj.x == x && _obj.y == y && _obj.z == z);
	}
	bool VECTOR3::operator != (const VECTOR3& _obj) const
	{
		return (_obj.x != x && _obj.y != y && _obj.z != z);
	}


	//--------------------------
	// 4D Vector
	//--------------------------

	VECTOR4::VECTOR4(const float* _value)
	{
		x = *_value;
		y = *_value;
		z = *_value;
		w = *_value;
	}

	VECTOR4::VECTOR4(float _x, float _g, float _b, float _a)
	{
		x = _x;
		y = _g;
		z = _b;
		w = _a;
	}

	VECTOR4::operator float*()
	{
		return static_cast<float*>(&x);
	}

	VECTOR4::operator const float*() const
	{
		return static_cast<const float*>(&x);
	}

	VECTOR4& VECTOR4::operator += (const VECTOR4& _obj)
	{
		x += _obj.x;
		y += _obj.y;
		z += _obj.z;
		w += _obj.w;
		return *this;
	}

	VECTOR4& VECTOR4::operator -= (const VECTOR4& _obj)
	{
		x -= _obj.x;
		y -= _obj.y;
		z -= _obj.z;
		w -= _obj.w;
		return *this;
	}

	VECTOR4& VECTOR4::operator *= (float _value)
	{
		x *= _value;
		y *= _value;
		z *= _value;
		w *= _value;
		return *this;
	}

	VECTOR4& VECTOR4::operator /= (float _value)
	{
		x /= _value;
		y /= _value;
		z /= _value;
		w /= _value;
		return *this;
	}

	VECTOR4 VECTOR4::operator + (const VECTOR4& _obj) const
	{
		return VECTOR4(x + _obj.x, y + _obj.y, z + _obj.z, w + _obj.w);
	}

	VECTOR4 VECTOR4::operator - (const VECTOR4& _obj) const
	{
		return VECTOR4(x - _obj.x, y - _obj.y, z - _obj.z, w - _obj.w);
	}

	VECTOR4 VECTOR4::operator * (float _value) const
	{
		return VECTOR4(x * _value, y * _value, z * _value, w * _value);
	}

	VECTOR4 VECTOR4::operator / (float _value) const
	{
		return VECTOR4(x / _value, y / _value, z / _value, w / _value);
	}

	bool VECTOR4::operator == (const VECTOR4& _obj) const
	{
		return (x == _obj.x && y == _obj.y && z == _obj.z && w == _obj.w);
	}
	bool VECTOR4::operator != (const VECTOR4& _obj) const
	{
		return (x != _obj.x && y != _obj.y && z != _obj.z && w != _obj.w);
	}


	//--------------------------
	// Color
	//--------------------------

	COLOR::COLOR(const float* _value)
	{
		r = *_value;
		g = *_value;
		b = *_value;
	}

	COLOR::COLOR(float _r, float _g, float _b, float _a)
	{
		r = _r;
		g = _g;
		b = _b;
		a = _a;
	}

	COLOR::operator float*()
	{
		return static_cast<float*>(&r);
	}

	COLOR::operator const float*() const
	{
		return static_cast<const float*>(&r);
	}

	COLOR& COLOR::operator += (const COLOR& _obj)
	{
		r += _obj.r;
		g += _obj.g;
		b += _obj.b;
		a += _obj.a;
		return *this;
	}

	COLOR& COLOR::operator -= (const COLOR& _obj)
	{
		r -= _obj.r;
		g -= _obj.g;
		b -= _obj.b;
		a -= _obj.a;
		return *this;
	}

	COLOR& COLOR::operator *= (float _value)
	{
		r *= _value;
		g *= _value;
		b *= _value;
		a *= _value;
		return *this;
	}

	COLOR& COLOR::operator /= (float _value)
	{
		r /= _value;
		g /= _value;
		b /= _value;
		a /= _value;
		return *this;
	}

	COLOR COLOR::operator + (const COLOR& _obj) const
	{
		return COLOR(r + _obj.r, g + _obj.g, b + _obj.b, a + _obj.a);
	}

	COLOR COLOR::operator - (const COLOR& _obj) const
	{
		return COLOR(r - _obj.r, g - _obj.g, b - _obj.b, a - _obj.a);
	}

	COLOR COLOR::operator * (float _value) const
	{
		return COLOR(r * _value, g * _value, b * _value, a * _value);
	}

	COLOR COLOR::operator / (float _value) const
	{
		return COLOR(r / _value, g / _value, b / _value, a / _value);
	}

	bool COLOR::operator == (const COLOR& _obj) const
	{
		return (r == _obj.r && g == _obj.g && b == _obj.b && a == _obj.a);
	}
	bool COLOR::operator != (const COLOR& _obj) const
	{
		return (r != _obj.r && g != _obj.g && b != _obj.b && a != _obj.a);
	}
}
