/**
 * @file   Math.h
 * @brief  計算系ライブラリのヘッダ
 * @author kotani
 */
#ifndef MATH_H
#define MATH_H
#include "MyMatrix.h"
#include "MyVector.h"

#define MyLib_PI 3.14159265358979323846f

namespace Lib
{
	/**
	 * 計算系ライブラリ
	 */
	namespace Math
	{
		/**
		 * 2点間の距離を求める(2次元座標)
		 * @param[in] _pos1 1つ目の座標
		 * @param[in] _pos2 2つ目の座標
		 * @return 距離
		 */
		float GetDistance(const VECTOR2& _pos1, const VECTOR2& _pos2);

		/**
		 * 2点間の距離を求める(3次元座標)
		 * @param[in] _pos1 1つ目の座標
		 * @param[in] _pos2 2つ目の座標
		 * @return 距離
		 */
		float GetDistance(const VECTOR3& _pos1, const VECTOR3& _pos2);

		/**
		 * 2点間の角度を求める
		 * @param[in] _pos1 1つ目の座標
		 * @param[in] _pos2 2つ目の座標
		 * @return 角度(degree値)
		 */
		float GetAngle(const VECTOR2& _pos1, const VECTOR2& _pos2);

		/**
		 * radianをdegreeに変換する
		 * @param[in] _radian 角度(radian値)
		 */
		inline float ToDegree(float _radian)
		{
			return _radian * (180.0f / MyLib_PI);
		}

		/**
		 * degreeをradianに変換する
		 * @param[in] _degree 角度(_degree値)
		 */
		inline float ToRadian(float _degree)
		{
			return _degree * (MyLib_PI / 180.0f);
		}

		/**
		 * 設定した角度の距離分の移動量を求める
		 * @param[in] _movement 移動量
		 * @param[in] _angle 角度(degree値)
		 * @return 移動量
		 */
		VECTOR2 GetAngleMovePos(float _movement, float _angle);

		/**
		 * 単位行列を作成する
		 * @param[in,out] _pMatrix 単位行列の入るMATRIX構造体のポインタ
		 * @return 単位行列のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixIdentity(MATRIX* _pMatrix);

		/**
		 * 内積を求める
		 * @param[in] _pIn1 基になるVector3
		 * @param[in] _pIn2 基になるVector3
		 * @return 内積
		 */
		float Vector3Dot(VECTOR3 *_pIn1, VECTOR3 *_pIn2);

		/**
		 * 3dベクトルを正規化する
		 * @param[in,out] _pVector3 基になるVector3。計算結果も入る
		 * @return 正規化されたvectorへのポインタ
		 */
		VECTOR3* Vector3Normalize(VECTOR3* _pVector3);

		/**
		 * 外積を求める
		 * @param[in] _pIn1 基になるVector3
		 * @param[in] _pIn2 基になるVector3
		 * @param[out] _pOut 計算結果へのポインタ
		 * @return 外積のvectorへのポインタ
		 */
		VECTOR3* Vector3Cross(VECTOR3* _pIn1, VECTOR3* _pIn2, VECTOR3* _pOut);

		/**
		 * 転置行列を返す
		 * @param[in,out] _pMatrix 転置行列の入るMATRIX構造体のポインタ
		 * @return 転置行列のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixTranspose(MATRIX* _pMatrix);

		/**
		 * 平行移動行列を作成する
		 * @param[in,out] _pMatrix 平行移動行列の入るMATRIX構造体のポインタ
		 * @param[in] _x x座標
		 * @param[in] _y y座標
		 * @param[in] _z z座標
		 * @return 平行移動行列のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixTranslation(MATRIX* _pMatrix, float _x, float _y, float _z);
		
		/**
		 * スケーリング行列を作成する
		 * @param[in,out] _pMatrix スケーリング行列の入るMATRIX構造体のポインタ
		 * @param[in] _x x座標
		 * @param[in] _y y座標
		 * @param[in] _z z座標
		 * @return スケーリング行列のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixScaling(MATRIX* _pMatrix, float _x, float _y, float _z);

		/**
		 * X軸を回転軸にして回転する行列を作成する
		 * @param[in,out] _pMatrix 計算結果の入るMATRIX構造体のポインタ
		 * @param[in] _angle 回転角度(degree値)
		 * @return 計算結果のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixRotationX(MATRIX* _pMatrix, float _angle);

		/**
		 * Y軸を回転軸にして回転する行列を作成する
		 * @param[in,out] _pMatrix 計算結果の入るMATRIX構造体のポインタ
		 * @param[in] _angle 回転角度(degree値)
		 * @return 計算結果のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixRotationY(MATRIX* _pMatrix, float _angle);

		/**
		 * Z軸を回転軸にして回転する行列を作成する
		 * @param[in,out] _pMatrix 計算結果の入るMATRIX構造体のポインタ
		 * @param[in] _angle 回転角度(degree値)
		 * @return 計算結果のMATRIX構造体のポインタ
		 */
		MATRIX* MatrixRotationZ(MATRIX* _pMatrix, float _angle);

		/**
		 * 左手系ビュー行列を作成する
		 * @param[in, out] _pMatrix 計算結果が入るMATRIX構造体のポインタ
		 * @param[in] _eyePos 視点の座標
		 * @param[in] _atPos 注視点座標
		 * @param[in] _up 上方向を指定する
		 * @return 左手座標系ビュー行列のポインタ
		 */
		MATRIX* MatrixLookAtLH(MATRIX* _pMatrix, VECTOR3* _eyePos, VECTOR3* _atPos, VECTOR3* _up = &VECTOR3(0.f,1.f,0.f));

		/**
		 * 左手座標系パースペクティブ射影行列を作成する。
		 */
		MATRIX* MatrixPerspectiveFovLH(MATRIX* _pMatrix, float _fovY, float _aspect, float _zNear, float _zFar);

	}
}


#endif
