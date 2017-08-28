/**
 * @file   Vertex2D.cpp
 * @brief  Vertex2Dクラスの実装
 * @author kotani
 */
#include "Vertex2D.h"
#include <Windows.h>
#include "../Math/Math.h"


namespace Lib
{
	const int  Vertex2D::m_VertexNum = 4;
	const UINT Vertex2D::m_ColorMask = 0xffffffff;

	Vertex2D::Vertex2D(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext, RECT _windowSize) :
		m_pDevice(_pDevice),
		m_pDeviceContext(_pDeviceContext),
		m_pVertexShader(nullptr),
		m_pVertexCompiledShader(nullptr),
		m_pVertexLayout(nullptr),
		m_pPixelShader(nullptr),
		m_pBlendState(nullptr),
		m_pSamplerState(nullptr),
		m_pVertexBuffer(nullptr),
		m_pConstantBuffer(nullptr),
		m_pTextureResourceView(nullptr),
		m_ClientWidth(static_cast<float>(_windowSize.right)),
		m_ClientHeight(static_cast<float>(_windowSize.bottom))
	{
	}


	//----------------------------------------------------------------------------------------------------
	// Public Functions
	//----------------------------------------------------------------------------------------------------

	bool Vertex2D::Initialize(const VECTOR2& _RectSize, const VECTOR2* _pUV)
	{
		if (!InitVertexShader())
		{
			return false;
		}

		if (!InitVertexLayout())
		{
			ReleaseVertexShader();
			return false;
		}

		if (!InitPixelShader())
		{
			ReleaseVertexLayout();
			ReleaseVertexShader();
			return false;
		}

		if (!InitBlendState())
		{
			ReleasePixelShader();
			ReleaseVertexLayout();
			ReleaseVertexShader();
			return false;
		}

		if (!InitSamplerState())
		{
			ReleaseBlendState();
			ReleasePixelShader();
			ReleaseVertexLayout();
			ReleaseVertexShader();
			return false;
		}

		if (!InitVertexBuffer(_RectSize, _pUV))
		{
			ReleaseSamplerState();
			ReleaseBlendState();
			ReleasePixelShader();
			ReleaseVertexLayout();
			ReleaseVertexShader();
			return false;
		}

		if (!InitConstantBuffer())
		{
			ReleaseVertexBuffer();
			ReleaseSamplerState();
			ReleaseBlendState();
			ReleasePixelShader();
			ReleaseVertexLayout();
			ReleaseVertexShader();
			return false;
		}

		if (!WriteConstantBuffer())
		{
			ReleaseConstantBuffer();
			ReleaseVertexBuffer();
			ReleaseSamplerState();
			ReleaseBlendState();
			ReleasePixelShader();
			ReleaseVertexLayout();
			ReleaseVertexShader();
			return false;

		}

		return true;
	}

	void Vertex2D::Finalize()
	{
		ReleaseConstantBuffer();
		ReleaseVertexBuffer();
		ReleaseSamplerState();
		ReleaseBlendState();
		ReleasePixelShader();
		ReleaseVertexLayout();
		ReleaseVertexShader();
	}

	void Vertex2D::Draw()
	{
		m_pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);
		m_pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);

		m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

		m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		m_pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
		m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureResourceView);

		m_pDeviceContext->OMSetBlendState(m_pBlendState, nullptr, m_ColorMask);

		UINT Stride = sizeof(VERTEX);
		UINT Offset = 0;
		m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Stride, &Offset);

		m_pDeviceContext->Draw(m_VertexNum, 0);
	}

	void Vertex2D::Draw(const VECTOR2& _DrawPos, const VECTOR2* _pUV, float _alpha, const VECTOR2& _Scale, float _angle)
	{
		D3D11_MAPPED_SUBRESOURCE MappedResource;
		if (SUCCEEDED(m_pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource)))
		{
			VERTEX Vertex[] =
			{
				VECTOR3(static_cast<float>(m_RectSize.left), static_cast<float>(m_RectSize.top),0.f), VECTOR2(_pUV[0].x, _pUV[0].y),
				VECTOR3(static_cast<float>(m_RectSize.right), static_cast<float>(m_RectSize.top), 0.f), VECTOR2(_pUV[1].x, _pUV[1].y),
				VECTOR3(static_cast<float>(m_RectSize.left), static_cast<float>(m_RectSize.bottom), 0.f), VECTOR2(_pUV[2].x, _pUV[2].y),
				VECTOR3(static_cast<float>(m_RectSize.right), static_cast<float>(m_RectSize.bottom), 0.f), VECTOR2(_pUV[3].x, _pUV[3].y)
			};
			memcpy_s(MappedResource.pData, MappedResource.RowPitch, reinterpret_cast<void*>(&Vertex), sizeof(Vertex));
			m_pDeviceContext->Unmap(m_pVertexBuffer, 0);
		}
		WriteConstantBuffer(_DrawPos, VECTOR2(_Scale.x, _Scale.y), &VECTOR2(0, 0), static_cast<float>(_angle), _alpha);

		m_pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);
		m_pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);

		m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

		m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		m_pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
		m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureResourceView);

		m_pDeviceContext->OMSetBlendState(m_pBlendState, nullptr, m_ColorMask);

		UINT Stride = sizeof(VERTEX);
		UINT Offset = 0;
		m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Stride, &Offset);

		m_pDeviceContext->Draw(m_VertexNum, 0);
	}

	void Vertex2D::Draw(const VECTOR2& _DrawPos, const RECT& _RectDiff, const VECTOR2* _pUV, float _alpha, const VECTOR2& _Scale, float _angle)
	{
		D3D11_MAPPED_SUBRESOURCE MappedResource;
		if (SUCCEEDED(m_pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource)))
		{
			VERTEX Vertex[] =
			{
				VECTOR3(static_cast<float>(m_RectSize.left + _RectDiff.left), static_cast<float>(m_RectSize.top + _RectDiff.top), 0.f), VECTOR2(_pUV[0].x, _pUV[0].y),
				VECTOR3(static_cast<float>(m_RectSize.right + _RectDiff.right), static_cast<float>(m_RectSize.top + _RectDiff.top), 0.f), VECTOR2(_pUV[1].x, _pUV[1].y),
				VECTOR3(static_cast<float>(m_RectSize.left + _RectDiff.left), static_cast<float>(m_RectSize.bottom + _RectDiff.bottom), 0.f), VECTOR2(_pUV[2].x, _pUV[2].y),
				VECTOR3(static_cast<float>(m_RectSize.right + _RectDiff.right), static_cast<float>(m_RectSize.bottom + _RectDiff.bottom), 0.f), VECTOR2(_pUV[3].x, _pUV[3].y)
			};
			memcpy_s(MappedResource.pData, MappedResource.RowPitch, reinterpret_cast<void*>(&Vertex), sizeof(Vertex));
			m_pDeviceContext->Unmap(m_pVertexBuffer, 0);
		}
		WriteConstantBuffer(_DrawPos, VECTOR2(_Scale.x, _Scale.y), &VECTOR2(0, 0), static_cast<float>(_angle), _alpha);

		m_pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);
		m_pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);

		m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

		m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
		m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

		m_pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
		m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureResourceView);

		m_pDeviceContext->OMSetBlendState(m_pBlendState, nullptr, m_ColorMask);

		UINT Stride = sizeof(VERTEX);
		UINT Offset = 0;
		m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Stride, &Offset);

		m_pDeviceContext->Draw(m_VertexNum, 0);
	}


	bool Vertex2D::WriteConstantBuffer(const VECTOR2& _DrawPos, const VECTOR2& _Scale, const VECTOR2* _pUV, float _angle, float _alpha)
	{
		MATRIX MatWorld, MatTranslate, MatRotate;
		Math::MatrixIdentity(&MatWorld);
		Math::MatrixScaling(&MatWorld, _Scale.x, _Scale.y, 1.0f);
		Math::MatrixRotationZ(&MatRotate, _angle);
		MatWorld *= MatRotate;
		Math::MatrixTranslation(&MatTranslate, _DrawPos.x, _DrawPos.y, 0);
		MatWorld *= MatTranslate;
		
		D3D11_MAPPED_SUBRESOURCE MappedResource;
		SHADER_CONSTANT_BUFFER ConstantBuffer;
		if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource)))
		{
			ConstantBuffer.MatWorld = MatWorld;
			Math::MatrixTranspose(&ConstantBuffer.MatWorld);

			ConstantBuffer.WindowSize.x = m_ClientWidth;
			ConstantBuffer.WindowSize.y = m_ClientHeight;
			ConstantBuffer.TexScroll.x =_pUV->x;
			ConstantBuffer.TexScroll.y =_pUV->y;
			ConstantBuffer.Color.a = _alpha;

			memcpy_s(MappedResource.pData, MappedResource.RowPitch, reinterpret_cast<void*>(&ConstantBuffer), sizeof(ConstantBuffer));
			m_pDeviceContext->Unmap(m_pConstantBuffer, 0);

			return true;
		}

		return false;
	}


	//----------------------------------------------------------------------------------------------------
	// Private Functions
	//----------------------------------------------------------------------------------------------------

	bool Vertex2D::InitVertexShader()
	{
		ID3DBlob* pErrors = nullptr;
		if (FAILED(D3DX11CompileFromFile(
			TEXT("Effect\\Vertex2D.fx"),
			nullptr,
			nullptr,
			"VS",
			"vs_4_0",
			D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
			0,
			nullptr,
			&m_pVertexCompiledShader,
			&pErrors,
			nullptr)))
		{
			OutputDebugString(TEXT("VertexShaderのコンパイルに失敗"));
			pErrors->Release();
			return false;
		}

		m_pDevice->CreateVertexShader(
			m_pVertexCompiledShader->GetBufferPointer(),
			m_pVertexCompiledShader->GetBufferSize(),
			nullptr,
			&m_pVertexShader);

		return true;
	}

	bool Vertex2D::InitVertexLayout()
	{
		D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(VECTOR3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};

		if (FAILED(m_pDevice->CreateInputLayout(
			InputElementDesc,
			sizeof(InputElementDesc) / sizeof(InputElementDesc[0]),
			m_pVertexCompiledShader->GetBufferPointer(),
			m_pVertexCompiledShader->GetBufferSize(),
			&m_pVertexLayout)))
		{
			OutputDebugString(TEXT("CreateInputLayoutに失敗"));
			return false;
		}

		return true;
	}

	bool Vertex2D::InitPixelShader()
	{
		ID3DBlob* pCompiledShader = nullptr;
		ID3DBlob* pErrors = nullptr;
		if (FAILED(D3DX11CompileFromFile(
			TEXT("Effect\\Vertex2D.fx"),
			nullptr,
			nullptr,
			"PS",
			"ps_4_0",
			D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
			0,
			nullptr,
			&pCompiledShader,
			&pErrors,
			nullptr)))
		{
			OutputDebugString(TEXT("PixelShaderのコンパイルに失敗"));
			pErrors->Release();
			return false;
		}

		m_pDevice->CreatePixelShader(
			pCompiledShader->GetBufferPointer(),
			pCompiledShader->GetBufferSize(),
			nullptr,
			&m_pPixelShader);

		pCompiledShader->Release();

		return true;
	}

	bool Vertex2D::InitBlendState()
	{
		D3D11_BLEND_DESC BlendDesc;
		ZeroMemory(&BlendDesc, sizeof(D3D11_BLEND_DESC));
		BlendDesc.AlphaToCoverageEnable = false;
		BlendDesc.IndependentBlendEnable = false;
		BlendDesc.RenderTarget[0].BlendEnable = true;
		BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

		if (FAILED(m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState)))
		{
			OutputDebugString(TEXT("CreateBlendStateに失敗しました"));
			return false;
		}

		return true;
	}

	bool Vertex2D::InitSamplerState()
	{
		D3D11_SAMPLER_DESC SamplerDesc;
		ZeroMemory(&SamplerDesc, sizeof(D3D11_SAMPLER_DESC));
		SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		if (FAILED(m_pDevice->CreateSamplerState(&SamplerDesc, &m_pSamplerState)))
		{
			OutputDebugString(TEXT("CreateSamplerStateに失敗しました"));
			return false;
		}

		return true;
	}

	bool Vertex2D::InitVertexBuffer(const VECTOR2& _RectSize, const VECTOR2* _pUV)
	{
		m_RectSize.top = static_cast<LONG>(-_RectSize.y / 2);
		m_RectSize.bottom = static_cast<LONG>(_RectSize.y / 2);
		m_RectSize.left = static_cast<LONG>(-_RectSize.x / 2);
		m_RectSize.right = static_cast<LONG>(_RectSize.x / 2);

		VERTEX Vertex[] =
		{
			VECTOR3(static_cast<float>(m_RectSize.left), static_cast<float>(m_RectSize.top), 0.f), VECTOR2(_pUV[0].x, _pUV[0].y),
			VECTOR3(static_cast<float>(m_RectSize.right), static_cast<float>(m_RectSize.top), 0.f), VECTOR2(_pUV[1].x, _pUV[1].y),
			VECTOR3(static_cast<float>(m_RectSize.left), static_cast<float>(m_RectSize.bottom), 0.f), VECTOR2(_pUV[2].x, _pUV[2].y),
			VECTOR3(static_cast<float>(m_RectSize.right), static_cast<float>(m_RectSize.bottom), 0.f), VECTOR2(_pUV[3].x, _pUV[3].y)
		};

		D3D11_BUFFER_DESC BufferDesc;
		ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
		BufferDesc.ByteWidth = sizeof(VERTEX) * m_VertexNum;
		BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		BufferDesc.MiscFlags = 0;
		BufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA InitVertexData;
		ZeroMemory(&InitVertexData, sizeof(D3D11_SUBRESOURCE_DATA));
		InitVertexData.pSysMem = Vertex;
		if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, &InitVertexData, &m_pVertexBuffer)))
		{
			OutputDebugString(TEXT("VertexBufferの生成に失敗しました"));
			return false;
		}

		return true;
	}

	bool Vertex2D::InitConstantBuffer()
	{
		D3D11_BUFFER_DESC ConstantBufferDesc;
		ZeroMemory(&ConstantBufferDesc, sizeof(D3D11_BUFFER_DESC));
		ConstantBufferDesc.ByteWidth = sizeof(SHADER_CONSTANT_BUFFER);
		ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		ConstantBufferDesc.MiscFlags = 0;
		ConstantBufferDesc.StructureByteStride = 0;

		if (FAILED(m_pDevice->CreateBuffer(&ConstantBufferDesc, nullptr, &m_pConstantBuffer)))
		{
			OutputDebugString(TEXT("ConstantBufferの生成に失敗しました"));
			return false;
		}

		return true;
	}

	void Vertex2D::ReleaseVertexShader()
	{
		if (m_pVertexShader != nullptr)
		{
			m_pVertexShader->Release();
			m_pVertexShader = nullptr;
		}

		if (m_pVertexCompiledShader != nullptr)
		{
			m_pVertexCompiledShader->Release();
			m_pVertexCompiledShader = nullptr;
		}
	}

	void Vertex2D::ReleaseVertexLayout()
	{
		if (m_pVertexLayout != nullptr)
		{
			m_pVertexLayout->Release();
			m_pVertexLayout = nullptr;
		}
	}

	void Vertex2D::ReleasePixelShader()
	{
		if (m_pPixelShader != nullptr)
		{
			m_pPixelShader->Release();
			m_pPixelShader = nullptr;
		}
	}

	void Vertex2D::ReleaseBlendState()
	{
		if (m_pBlendState != nullptr)
		{
			m_pBlendState->Release();
			m_pBlendState = nullptr;
		}
	}

	void Vertex2D::ReleaseSamplerState()
	{
		if (m_pSamplerState != nullptr)
		{
			m_pSamplerState->Release();
			m_pSamplerState = nullptr;
		}
	}

	void Vertex2D::ReleaseVertexBuffer()
	{
		if (m_pVertexBuffer != nullptr)
		{
			m_pVertexBuffer->Release();
			m_pVertexBuffer = nullptr;
		}
	}

	void Vertex2D::ReleaseConstantBuffer()
	{
		if (m_pConstantBuffer != nullptr)
		{
			m_pConstantBuffer->Release();
			m_pConstantBuffer = nullptr;
		}

	}
}
