/**
* @file   Camera.cpp
* @brief  Cameraクラスの実装
* @author kotani
*/
#include "Camera.h"

namespace Lib
{
	Camera::Camera(float _windowWidth, float _windowHeight, float _nearZ, float _farZ)
	{
		m_WindowWidth = _windowWidth;
		m_WindowHeight = _windowHeight;
		m_NearZ = _nearZ;
		m_FarZ = _farZ;
	}

	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	void Camera::TransformView(VECTOR3 _eyePos, VECTOR3 _lookPos, float _viewAngle)
	{
		// ビュー座標変換行列の作成
		Math::MatrixLookAtLH(&m_MatView, &_eyePos, &_lookPos);

		// プロジェクション座標変換行列の作成
		float Aspect = m_WindowWidth / m_WindowHeight;
		Math::MatrixPerspectiveFovLH(&m_MatProj, static_cast<float>(Math::ToRadian(_viewAngle)), Aspect, m_NearZ, m_FarZ);
	}
}
