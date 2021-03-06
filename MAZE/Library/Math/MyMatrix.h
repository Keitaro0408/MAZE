﻿/**
 * @file   MyMatrix.h
 * @brief  MATRIX構造体のヘッダファイル
 * @author kotani
 */
#ifndef MYMATRIX_H
#define MYMATRIX_H

namespace Lib
{
	/**
	 * 4*4の行列構造体
	 */
	typedef struct MATRIX
	{
		MATRIX() {};
		MATRIX(const float *);
		MATRIX(const MATRIX&);
		MATRIX(float _11, float _12, float _13, float _14,
			float _21, float _22, float _23, float _24,
			float _31, float _32, float _33, float _34,
			float _41, float _42, float _43, float _44);

		operator float*();
		operator const float*() const;
		
		MATRIX& operator *= (const MATRIX&);
		MATRIX& operator += (const MATRIX&);
		MATRIX& operator -= (const MATRIX&);
		MATRIX& operator *= (float);
		MATRIX& operator /= (float);


		MATRIX operator * (const MATRIX&) const;
		MATRIX operator + (const MATRIX&) const;
		MATRIX operator - (const MATRIX&) const;
		MATRIX operator * (float) const;
		MATRIX operator / (float) const;

		/* 比較演算子 */
		bool operator == (const MATRIX&) const;
		bool operator != (const MATRIX&) const;

		union
		{
			struct 
			{
				float        _11, _12, _13, _14;
				float        _21, _22, _23, _24;
				float        _31, _32, _33, _34;
				float        _41, _42, _43, _44;
			};
			float m_Matrix[4][4];
		};
	} MATRIX;
}


#endif
