/**
* @file   MyMatrix.cpp
* @brief  MATRIX構造体の実装
* @author kotani
*/
#include "MyMatrix.h"
#include <windows.h>

namespace Lib
{
	MATRIX::MATRIX(const float* _value)
	{
		if (_value == nullptr) return;

		memcpy(&_11, _value, sizeof(MATRIX));
	}

	MATRIX::MATRIX(const MATRIX& _obj)
	{
		*this = _obj;
	}

	MATRIX::MATRIX(float f11, float f12, float f13, float f14,
		float f21, float f22, float f23, float f24,
		float f31, float f32, float f33, float f34,
		float f41, float f42, float f43, float f44)
	{
		_11 = f11; _12 = f12; _13 = f13; _14 = f14;
		_21 = f21; _22 = f22; _23 = f23; _24 = f24;
		_31 = f31; _32 = f32; _33 = f33; _34 = f34;
		_41 = f41; _42 = f42; _43 = f43; _44 = f44;
	}

	MATRIX::operator float*()
	{
		return static_cast<float*>(&_11);
	}
	
	MATRIX::operator const float*() const
	{
		return static_cast<const float*>(&_11);
	}

	MATRIX& MATRIX::operator *= (const MATRIX& _obj)
	{
		MATRIX matrix;
		for (int i = 0; i< 4; ++i)
		{
			for (int j = 0; j< 4; ++j)
			{
				matrix.m_Matrix[i][j] = 0;
				for (int k = 0; k< 4; ++k)
				{
					matrix.m_Matrix[i][j] += m_Matrix[i][k] * _obj.m_Matrix[k][j];
				}
			}
		}

		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				m_Matrix[i][j] = matrix.m_Matrix[i][j];
			}
		}
		return *this;
	}

	MATRIX& MATRIX::operator += (const MATRIX& _obj)
	{
		_11 += _obj._11; _12 += _obj._12; _13 += _obj._13; _14 += _obj._14;
		_21 += _obj._21; _22 += _obj._22; _23 += _obj._23; _24 += _obj._24;
		_31 += _obj._31; _32 += _obj._32; _33 += _obj._33; _34 += _obj._34;
		_41 += _obj._41; _42 += _obj._42; _43 += _obj._43; _44 += _obj._44;
		return *this;
	}

	MATRIX& MATRIX::operator -= (const MATRIX& _obj)
	{
		_11 -= _obj._11; _12 -= _obj._12; _13 -= _obj._13; _14 -= _obj._14;
		_21 -= _obj._21; _22 -= _obj._22; _23 -= _obj._23; _24 -= _obj._24;
		_31 -= _obj._31; _32 -= _obj._32; _33 -= _obj._33; _34 -= _obj._34;
		_41 -= _obj._41; _42 -= _obj._42; _43 -= _obj._43; _44 -= _obj._44;
		return *this;
	}

	MATRIX& MATRIX::operator *= (float _value)
	{
		_11 *= _value; _12 *= _value; _13 *= _value; _14 *= _value;
		_21 *= _value; _22 *= _value; _23 *= _value; _24 *= _value;
		_31 *= _value; _32 *= _value; _33 *= _value; _34 *= _value;
		_41 *= _value; _42 *= _value; _43 *= _value; _44 *= _value;
		return *this;
	}

	MATRIX& MATRIX::operator /= (float _value)
	{
		/* 掛け算の方が割り算より早い */
		float fInv = 1.0f / _value;
		_11 *= fInv; _12 *= fInv; _13 *= fInv; _14 *= fInv;
		_21 *= fInv; _22 *= fInv; _23 *= fInv; _24 *= fInv;
		_31 *= fInv; _32 *= fInv; _33 *= fInv; _34 *= fInv;
		_41 *= fInv; _42 *= fInv; _43 *= fInv; _44 *= fInv;
		return *this;
	}

	MATRIX MATRIX::operator * (const MATRIX& _obj) const
	{
		MATRIX matrix;
		for (int i = 0; i< 4; ++i)
		{
			for (int j = 0; j< 4; ++j)
			{
				matrix.m_Matrix[i][j] = 0;
				for (int k = 0; k< 4; ++k)
				{
					matrix.m_Matrix[i][j] += m_Matrix[i][k] * _obj.m_Matrix[k][j];
				}
			}
		}
		return matrix;
	}

	MATRIX MATRIX::operator + (const MATRIX& _obj) const
	{
		return MATRIX(_11 + _obj._11, _12 + _obj._12, _13 + _obj._13, _14 + _obj._14,
			_21 + _obj._21, _22 + _obj._22, _23 + _obj._23, _24 + _obj._24,
			_31 + _obj._31, _32 + _obj._32, _33 + _obj._33, _34 + _obj._34,
			_41 + _obj._41, _42 + _obj._42, _43 + _obj._43, _44 + _obj._44);
	}

	MATRIX MATRIX::operator - (const MATRIX& _obj) const
	{
		return MATRIX(_11 - _obj._11, _12 - _obj._12, _13 - _obj._13, _14 - _obj._14,
			_21 - _obj._21, _22 - _obj._22, _23 - _obj._23, _24 - _obj._24,
			_31 - _obj._31, _32 - _obj._32, _33 - _obj._33, _34 - _obj._34,
			_41 - _obj._41, _42 - _obj._42, _43 - _obj._43, _44 - _obj._44);
	}

	MATRIX MATRIX::operator * (float _value) const
	{
		return MATRIX(_11 * _value, _12 * _value, _13 * _value, _14 * _value,
			_21 * _value, _22 * _value, _23 * _value, _24 * _value,
			_31 * _value, _32 * _value, _33 * _value, _34 * _value,
			_41 * _value, _42 * _value, _43 * _value, _44 * _value);
	}

	MATRIX MATRIX::operator / (float _value) const
	{
		FLOAT fInv = 1.0f / _value;
		return MATRIX(_11 * fInv, _12 * fInv, _13 * fInv, _14 * fInv,
			_21 * fInv, _22 * fInv, _23 * fInv, _24 * fInv,
			_31 * fInv, _32 * fInv, _33 * fInv, _34 * fInv,
			_41 * fInv, _42 * fInv, _43 * fInv, _44 * fInv);
	}

	bool MATRIX::operator == (const MATRIX& _obj) const
	{
		return 0 == memcmp(this, &_obj, sizeof(MATRIX));
	}

	bool MATRIX::operator != (const MATRIX& _obj) const
	{
		return 0 != memcmp(this, &_obj, sizeof(MATRIX));
	}
}
