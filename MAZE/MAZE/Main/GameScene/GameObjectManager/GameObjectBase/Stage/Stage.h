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
	// 方向をもつオブジェクトの地面についている方向
	enum STAGE_OBJECT
	{
		NON_OBJECT,
		GROUND_OBJECT,
		START_DOOR_OBJECT,
		GOAL_DOOR_OBJECT,
		END_LADDER_OBJECT,
		LADDER_OBJECT,
		NEEDLE_OBJECT,
		TRAMPOLINE_OBJECT,
		COVER_OBJECT,
		COIN_OBJECT
	};

	Stage();
	~Stage();

	void Update() override;
	void Draw() override;


private:
	typedef std::array<Lib::UniquePtr<GameObjectBase>, 7> GameObject;
	enum SPIN_TYPE
	{
		LEFT_SPIN,
		RIGHT_SPIN,
		REVERSAL_SPIN,
		INITIALIZE_SPIN, //!< 初期位置に戻す
		NON_SPIN
	};

	void CreateShaderResorceView();

	int							  m_TextureIndex;
	GameObject					  m_pGameObjectBase;
	SPIN_TYPE					  m_SpinType;
	float						  m_SpinSpeed;
	float						  m_Angle;
	float						  m_AddAngleCount;
	Lib::UniquePtr<Lib::Vertex2D> m_pVertex;
	Lib::VECTOR2				  m_Uv[4];
								  
	ID3D11Texture2D*			  m_pTex;
	ID3D11RenderTargetView*		  m_pTexRTV;
	ID3D11ShaderResourceView*	  m_pTexSRV;

};


#endif
