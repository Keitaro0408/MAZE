/**
 * @file   Math.cpp
 * @brief  計算系ライブラリの実装
 * @author kotani
 */
#include "Math.h"
#include <math.h>

namespace Lib
{
	namespace Math
	{
		float GetDistance(const VECTOR2& _pos1, const VECTOR2& _pos2)
		{
			return sqrt(pow(_pos2.x - _pos1.x, 2) + pow(_pos2.y - _pos1.y, 2));
		}

		float GetDistance(const VECTOR3& _pos1, const VECTOR3& _pos2)
		{
			return sqrt(pow(_pos2.x - _pos1.x, 2) + pow(_pos2.y - _pos1.y, 2) + pow(_pos2.z - _pos1.z, 2));
		}

		float GetAngle(const VECTOR2& _pos1, const VECTOR2& _pos2)
		{
			return ToDegree(atan2(_pos2.y - _pos1.y, _pos2.x - _pos1.x));
		}

		VECTOR2 GetAngleMovePos(float _movement, float _angle)
		{
			VECTOR2 returnVar = {0.f,0.f};
			returnVar.x = _movement * cos(ToRadian(_angle));
			returnVar.y = _movement * sin(ToRadian(_angle));
			return returnVar;
		}


		MATRIX* MatrixIdentity(MATRIX* _pMatrix)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					_pMatrix->m_Matrix[i][j] = 0.f;
				}
			}
			_pMatrix->_11 = 1.f;
			_pMatrix->_22 = 1.f;
			_pMatrix->_33 = 1.f;
			_pMatrix->_44 = 1.f;
			return _pMatrix;
		}

		MATRIX* MatrixTranspose(MATRIX* _pMatrix)
		{
			MATRIX matrix;
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					matrix.m_Matrix[i][j] = _pMatrix->m_Matrix[i][j];
				}
			}

			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					_pMatrix->m_Matrix[i][j] = matrix.m_Matrix[j][i];
				}
			}
			return _pMatrix;
		}

		MATRIX* MatrixTranslation(MATRIX* _pMatrix, float _x, float _y, float _z)
		{
			MatrixIdentity(_pMatrix);
			_pMatrix->_41 = _x;
			_pMatrix->_42 = _y;
			_pMatrix->_43 = _z;
			return _pMatrix;
		}

		MATRIX* MatrixScaling(MATRIX* _pMatrix, float _x, float _y, float _z)
		{
			_pMatrix->_11 = _x;
			_pMatrix->_22 = _y;
			_pMatrix->_33 = _z;
			return _pMatrix;
		}

		MATRIX* MatrixRotationX(MATRIX* _pMatrix, float _angle)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					_pMatrix->m_Matrix[i][j] = 0.f;
				}
			}
			_pMatrix->_11 = 1.f;
			_pMatrix->_44 = 1.f;
			_pMatrix->_22 = cos(ToRadian(_angle));
			_pMatrix->_23 = sin(ToRadian(_angle));
			_pMatrix->_32 = -sin(ToRadian(_angle));
			_pMatrix->_33 = cos(ToRadian(_angle));
			return _pMatrix;
		}

		MATRIX* MatrixRotationY(MATRIX* _pMatrix, float _angle)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					_pMatrix->m_Matrix[i][j] = 0.f;
				}
			}
			_pMatrix->_44 = 1.f;
			_pMatrix->_22 = 1.f;
			_pMatrix->_11 = cos(ToRadian(_angle));
			_pMatrix->_13 = -sin(ToRadian(_angle));
			_pMatrix->_31 = sin(ToRadian(_angle));
			_pMatrix->_33 = cos(ToRadian(_angle));
			return _pMatrix;
		}

		MATRIX* MatrixRotationZ(MATRIX* _pMatrix, float _angle)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					_pMatrix->m_Matrix[i][j] = 0.f;
				}
			}
			_pMatrix->_44 = 1.f;
			_pMatrix->_33 = 1.f;
			_pMatrix->_11 = cos(ToRadian(_angle));
			_pMatrix->_12 = sin(ToRadian(_angle));
			_pMatrix->_21 = -sin(ToRadian(_angle));
			_pMatrix->_22 = cos(ToRadian(_angle));
			return _pMatrix;
		}

		float Vector3Dot(VECTOR3 *_pIn1, VECTOR3 *_pIn2)
		{
			return ((_pIn1->x)*(_pIn2->x) + (_pIn1->y)*(_pIn2->y) + (_pIn1->z)*(_pIn2->z));
		}

		VECTOR3* Vector3Cross(VECTOR3* _pIn1, VECTOR3* _pIn2, VECTOR3* _pOut)
		{
			VECTOR3 tmp;
			tmp.x = (_pIn1->y * _pIn2->z - _pIn1->z * _pIn2->y);
			tmp.y = (_pIn1->z * _pIn2->x - _pIn1->x * _pIn2->z);
			tmp.z = (_pIn1->x * _pIn2->y - _pIn1->y * _pIn2->x);
			*_pOut = tmp;
			return _pOut;
		}

		VECTOR3* Vector3Normalize(VECTOR3* _pVector3)
		{
			float len = sqrt(_pVector3->x * _pVector3->x + _pVector3->y * _pVector3->y + _pVector3->z * _pVector3->z);
			len = 1.f / len;
			_pVector3->x *= len;
			_pVector3->y *= len;
			_pVector3->z *= len;
			return _pVector3;
		}

		MATRIX* MatrixLookAtLH(MATRIX* _pMatrix, VECTOR3* _eyePos, VECTOR3* _atPos, VECTOR3* _up)
		{
			VECTOR3 zaxis = *Vector3Normalize(&VECTOR3(*_atPos - *_eyePos));

			VECTOR3 xaxis;
			Vector3Normalize(Vector3Cross(_up, &zaxis, &xaxis));
			
			VECTOR3 yaxis;
			Vector3Cross(&zaxis, &xaxis, &yaxis);

			_pMatrix->_11 = xaxis.x;
			_pMatrix->_12 = yaxis.x;
			_pMatrix->_13 = zaxis.x;
			_pMatrix->_14 = 0.f;

			_pMatrix->_21 = xaxis.y;
			_pMatrix->_22 = yaxis.y;
			_pMatrix->_23 = zaxis.y;
			_pMatrix->_24 = 0.f;

			_pMatrix->_31 = xaxis.z;
			_pMatrix->_32 = yaxis.z;
			_pMatrix->_33 = zaxis.z;
			_pMatrix->_34 = 0.f;

			_pMatrix->_41 = -Vector3Dot(&xaxis,_eyePos);
			_pMatrix->_42 = -Vector3Dot(&yaxis, _eyePos);
			_pMatrix->_43 = -Vector3Dot(&zaxis, _eyePos);
			_pMatrix->_44 = 1.f;

			return _pMatrix;
		}

		MATRIX* MatrixPerspectiveFovLH(MATRIX* _pMatrix, float _fovY, float _aspect, float _zNear, float _zFar)
		{
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					_pMatrix->m_Matrix[i][j] = 0.f;
				}
			}

			float h = 1 / tan(_fovY / 2);
			float w = h / _aspect;

			_pMatrix->_11 = w;
			_pMatrix->_22 = h;
			_pMatrix->_33 = _zFar / (_zFar - _zNear);
			_pMatrix->_34 = 1.f;
			_pMatrix->_43 = -_zNear* _zFar / (_zFar - _zNear);

			return _pMatrix;
		}
	}
}
