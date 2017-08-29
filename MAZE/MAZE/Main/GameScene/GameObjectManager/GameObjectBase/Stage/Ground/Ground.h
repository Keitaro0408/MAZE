/**
 * @file   Ground.h
 * @brief  Groundクラスのヘッダファイル
 * @author kotani
 */
#ifndef GROUND_H
#define GROUND_H
#include "..\..\GameObjectBase.h"
#include "..\..\..\..\..\GamePlayManager\GamePlayManager.h"
#include "Vertex2D\Vertex2D.h"
#include "Animation\AnimUvController.h"
#include "SmartPointer\UniquePtr.h"
#include "Dx11\DX11Manager.h"

class Ground : public GameObjectBase
{
public:
	Ground();
	virtual ~Ground();

	void Update() override;
	void Draw() override;

private:
	enum SPIN_TYPE
	{
		LEFT_SPIN,
		RIGHT_SPIN,
		REVERSAL_SPIN,
		NON_SPIN
	};

	void CreateShaderResorceView();

	Lib::VECTOR2						  m_Uv[4];
	GamePlayManager::SELECT_STAGE		  m_Stage;
	Lib::UniquePtr<Lib::Vertex2D>		  m_pVertex;
	Lib::UniquePtr<Lib::Vertex2D>		  m_pGroundVertex;
	Lib::UniquePtr<Lib::AnimUvController> m_pUvController;
	SPIN_TYPE							  m_SpinType;
	float								  m_SpinSpeed;
	float								  m_Angle;

	ID3D11Texture2D*					  m_pTex;
	ID3D11RenderTargetView*				  m_pTexRTV;
	ID3D11ShaderResourceView*			  m_pTexSRV;

};


#endif
