/**
* @file   Camera.h
* @brief  Cameraクラスのヘッダファイル
* @author kotani
*/
#ifndef CAMERA_H
#define CAMERA_H
#include "../Math/Math.h"

namespace Lib
{
	/**
	* カメラ情報を管理するクラス
	*/
	class Camera
	{
	public:
		/**
		* Cameraクラスのコンストラクタ
		* @param[in] _windowWidth ウィンドウの幅
		* @param[in] _windowHeight ウィンドウの高さ
		* @param[in] _nearZ カメラの最近点
		* @param[in] _farZ カメラの最遠点
		*/
		Camera(float _windowWidth, float _windowHeight, float _nearZ, float _farZ);

		/**
		* Cameraクラスのデストラクタ
		*/
		~Camera() = default;

		/**
		* 座標変換用の行列を作成する関数
		* @param[in] _eyePos カメラの座標
		* @param[in] _lookPos カメラの注視座標
		* @param[in] _viewAngle カメラの視野角
		*/
		void TransformView(VECTOR3 _eyePos, VECTOR3 _lookPos, float _viewAngle);

		/**
		* Cameraクラスが持つビュー座標変換行列を取得する関数
		* @return ビュー座標変換用行列
		*/
		inline MATRIX GetViewMatrix()
		{
			return m_MatView;
		}

		/**
		* Cameraクラスが持つプロジェクション座標変換行列を取得する関数
		* @return プロジェクション座標変換用行列
		*/
		inline MATRIX GetProjectionMatrix()
		{
			return m_MatProj;
		}

	private:
		MATRIX	m_MatView;
		MATRIX	m_MatProj;
		float	m_WindowWidth;
		float	m_WindowHeight;
		float	m_NearZ;
		float	m_FarZ;

	};
}


#endif
