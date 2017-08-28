/**
 * @file   MyVector.h
 * @brief  MyVector構造体のヘッダファイル
 * @author kotani
 */
#ifndef MYVECTOR_H
#define MYVECTOR_H

namespace Lib
{
	//--------------------------
	// 2D Vector
	//--------------------------
	typedef struct VECTOR2
	{
	public:
		VECTOR2() {};
		VECTOR2(const float *);
		VECTOR2(float _x, float _y);

		operator float* ();
		operator const float* () const;

		VECTOR2& operator += (const VECTOR2&);
		VECTOR2& operator -= (const VECTOR2&);
		VECTOR2& operator *= (float);
		VECTOR2& operator /= (float);
		
		VECTOR2 operator + (const VECTOR2&) const;
		VECTOR2 operator - (const VECTOR2&) const;
		VECTOR2 operator * (float) const;
		VECTOR2 operator / (float) const;

		bool operator == (const VECTOR2&) const;
		bool operator != (const VECTOR2&) const;


	public:
		float x, y;
	}VECTOR2;

	//--------------------------
	// 3D Vector
	//--------------------------
	typedef struct VECTOR3
	{
	public:
		VECTOR3() {};
		VECTOR3(const float *);
		VECTOR3(float _x, float _y, float _z);

		operator float* ();
		operator const float* () const;

		VECTOR3& operator += (const VECTOR3&);
		VECTOR3& operator -= (const VECTOR3&);
		VECTOR3& operator *= (float);
		VECTOR3& operator /= (float);

		VECTOR3 operator + (const VECTOR3&) const;
		VECTOR3 operator - (const VECTOR3&) const;
		VECTOR3 operator * (float) const;
		VECTOR3 operator / (float) const;

		bool operator == (const VECTOR3&) const;
		bool operator != (const VECTOR3&) const;
		
		float x, y, z;
	}VECTOR3;

	//--------------------------
	// 4D Vector
	//--------------------------
	typedef struct VECTOR4
	{
	public:
		VECTOR4() {};
		VECTOR4(const float *);
		VECTOR4(float _x, float _y, float _z, float _w);

		operator float* ();
		operator const float* () const;

		VECTOR4& operator += (const VECTOR4&);
		VECTOR4& operator -= (const VECTOR4&);
		VECTOR4& operator *= (float);
		VECTOR4& operator /= (float);

		VECTOR4 operator + (const VECTOR4&) const;
		VECTOR4 operator - (const VECTOR4&) const;
		VECTOR4 operator * (float) const;
		VECTOR4 operator / (float) const;

		bool operator == (const VECTOR4&) const;
		bool operator != (const VECTOR4&) const;

		float x, y, z, w;
	}VECTOR4;


	//--------------------------
	// Color
	//--------------------------
	typedef struct COLOR
	{
	public:
		COLOR() {};
		COLOR(const float *);
		COLOR(float _r, float _g, float _b, float _a);

		operator float* ();
		operator const float* () const;

		COLOR& operator += (const COLOR&);
		COLOR& operator -= (const COLOR&);
		COLOR& operator *= (float);
		COLOR& operator /= (float);

		COLOR operator + (const COLOR&) const;
		COLOR operator - (const COLOR&) const;
		COLOR operator * (float) const;
		COLOR operator / (float) const;

		bool operator == (const COLOR&) const;
		bool operator != (const COLOR&) const;

		float r, g, b, a;
	}COLOR;
}


#endif
