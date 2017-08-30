/**
 * @file   Stage.h
 * @brief  Stageクラスのヘッダファイル
 * @author kotani
 */
#ifndef STAGE_H
#define STAGE_H
#define STAGE_WIDTH 15
#define STAGE_HEIGHT 15
#include "..\GameObjectBase.h"
#include "Dx11\DX11Manager.h"
#include "Vertex2D\Vertex2D.h"
#include "SmartPointer\UniquePtr.h"
#include <array>

class Stage : public GameObjectBase
{
public:
	enum STAGE_OBJECT
	{
		NON_OBJECT,
		GROUND_OBJECT,
		SPAWN_OBJECT,
		GOAL_OBJECT,
		BOTTOM_LADDER_OBJECT,
		MIDDLE_LADDER_OBJECT,
		TOP_LADDER_OBJECT,
	};
	Stage();
	~Stage();

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

	std::array<Lib::UniquePtr<GameObjectBase>,2>  m_pGameObjectBase;
	SPIN_TYPE					  m_SpinType;
	float						  m_SpinSpeed;
	float						  m_Angle;
	Lib::UniquePtr<Lib::Vertex2D> m_pVertex;
	Lib::VECTOR2				  m_Uv[4];
								  
	ID3D11Texture2D*			  m_pTex;
	ID3D11RenderTargetView*		  m_pTexRTV;
	ID3D11ShaderResourceView*	  m_pTexSRV;

};


#endif
