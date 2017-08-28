/**
 * @file   Vertex.cpp
 * @brief  Vertexクラスのcppファイル
 * @author kotani
 */
#include "Vertex.h"
#include "../Math/Math.h"

Lib::Vertex::Vertex(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext, HWND _hWnd) :
m_pDevice(_pDevice),
m_pDeviceContext(_pDeviceContext),
m_hWnd(_hWnd),
m_pVertexShader(nullptr),
m_pVertexCompiledShader(nullptr),
m_pVertexLayout(nullptr),
m_pPixelShader(nullptr),
m_pPixelCompiledShader(nullptr),
m_pBlendState(nullptr),
m_pSamplerState(nullptr),
m_pConstantBuffer(nullptr),
m_pVertexBuffer(nullptr),
m_pTextureResourceView(nullptr),
m_pVertex(nullptr),
m_VertexNum(0),
m_ClientWidth(0),
m_ClientHeight(0)
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool Lib::Vertex::Initialize()
{
	RECT ClientRect;
	GetClientRect(m_hWnd, &ClientRect);
	m_ClientWidth = static_cast<float>(ClientRect.right);
	m_ClientHeight = static_cast<float>(ClientRect.bottom);

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

	if (!InitConstantBuffer())
	{
		ReleaseSamplerState();
		ReleaseBlendState();
		ReleasePixelShader();
		ReleaseVertexLayout();
		ReleaseVertexShader();
		return false;
	}

	return true;
}

void Lib::Vertex::Finalize()
{
	ReleaseConstantBuffer();
	ReleaseSamplerState();
	ReleaseBlendState();
	ReleasePixelShader();
	ReleaseVertexLayout();
	ReleaseVertexShader();
}

bool Lib::Vertex::CreateVertexBuffer(const VERTEX* _pVertex, int _vertexNum)
{
	m_VertexNum = _vertexNum;
	m_pVertex = new VERTEX[m_VertexNum];

	for (int i = 0; i < m_VertexNum; i++)
	{
		m_pVertex[i] = _pVertex[i];
	}

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
	InitVertexData.pSysMem = m_pVertex;

	if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, &InitVertexData, &m_pVertexBuffer)))
	{
		MessageBox(m_hWnd, TEXT("頂点バッファの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	return true;
}

void Lib::Vertex::ReleaseVertexBuffer()
{
	if (m_pVertexBuffer != nullptr)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = nullptr;

		delete[] m_pVertex;
		m_pVertex = nullptr;
		m_VertexNum = 0;
	}
}

bool Lib::Vertex::WriteVertexBuffer(const VERTEX* _pVertex)
{
	D3D11_MAPPED_SUBRESOURCE MappedResource;
	if (SUCCEEDED(m_pDeviceContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource)))
	{
		memcpy_s(
			MappedResource.pData,
			MappedResource.RowPitch,
			_pVertex,
			sizeof(VERTEX) * m_VertexNum);

		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);

		return true;
	}

	return false;
}

bool Lib::Vertex::WriteConstantBuffer(const VECTOR2* _pDrawPos, const VECTOR2* _pScale, float _angle)
{
	MATRIX MatWorld, MatTranslate, MatRotate;
	Math::MatrixIdentity(&MatWorld);
	Math::MatrixScaling(&MatWorld, _pScale->x, _pScale->y, 1.0f);
	Math::MatrixRotationZ(&MatRotate, _angle);
	MatWorld *= MatRotate;
	Math::MatrixTranslation(&MatTranslate, _pDrawPos->x, _pDrawPos->y, 0);
	MatWorld *= MatTranslate;

	D3D11_MAPPED_SUBRESOURCE MappedResource;
	SHADER_CONSTANT_BUFFER ConstantBuffer;
	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource)))
	{
		ConstantBuffer.MatWorld = MatWorld;
		Math::MatrixTranspose(&ConstantBuffer.MatWorld);

		ConstantBuffer.WindowSize.x = m_ClientWidth;
		ConstantBuffer.WindowSize.y = m_ClientHeight;

		memcpy_s(
			MappedResource.pData,
			MappedResource.RowPitch,
			reinterpret_cast<void*>(&ConstantBuffer),
			sizeof(ConstantBuffer));

		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);

		return true;
	}

	return false;
}

void Lib::Vertex::Draw()
{
	m_pDeviceContext->VSSetShader(m_pVertexShader, nullptr, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, nullptr, 0);

	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureResourceView);

	m_pDeviceContext->OMSetBlendState(m_pBlendState, nullptr, 0xffffffff);

	UINT Stride = sizeof(VERTEX);
	UINT Offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Stride, &Offset);

	m_pDeviceContext->Draw(m_VertexNum, 0);
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

bool Lib::Vertex::InitVertexShader()
{
	ID3DBlob* pErrors = nullptr;
	if (FAILED(D3DX11CompileFromFile(
		TEXT("Library\\Vertex\\Effect\\Vertex.fx"),
		nullptr,
		nullptr,
		"VS",
		"vs_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		nullptr,
		&m_pVertexCompiledShader,
		&pErrors,
		nullptr)))
	{
		MessageBox(0, TEXT("VertexShaderのコンパイルに失敗"), TEXT("エラー"), MB_ICONSTOP);
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

bool Lib::Vertex::InitVertexLayout()
{
	D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	if (FAILED(m_pDevice->CreateInputLayout(
		InputElementDesc,
		sizeof(InputElementDesc) / sizeof(InputElementDesc[0]),
		m_pVertexCompiledShader->GetBufferPointer(),
		m_pVertexCompiledShader->GetBufferSize(),
		&m_pVertexLayout)))
	{
		MessageBox(m_hWnd, TEXT("CreateInputLayoutに失敗"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	return true;
}

bool Lib::Vertex::InitPixelShader()
{
	ID3DBlob* pErrors = nullptr;
	if (FAILED(D3DX11CompileFromFile(
		TEXT("Library\\Vertex\\Effect\\Vertex.fx"),
		nullptr,
		nullptr,
		"PS",
		"ps_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		nullptr,
		&m_pPixelCompiledShader,
		&pErrors,
		nullptr)))
	{
		MessageBox(m_hWnd, TEXT("PixelShaderのコンパイルに失敗"), TEXT("エラー"), MB_ICONSTOP);
		pErrors->Release();
		return false;
	}

	m_pDevice->CreatePixelShader(
		m_pPixelCompiledShader->GetBufferPointer(),
		m_pPixelCompiledShader->GetBufferSize(),
		nullptr,
		&m_pPixelShader);

	return true;
}

bool Lib::Vertex::InitBlendState()
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
		MessageBox(m_hWnd, TEXT("CreateBlendStateに失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	return true;
}

bool Lib::Vertex::InitSamplerState()
{
	D3D11_SAMPLER_DESC SamplerDesc;
	ZeroMemory(&SamplerDesc, sizeof(D3D11_SAMPLER_DESC));
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	if (FAILED(m_pDevice->CreateSamplerState(&SamplerDesc, &m_pSamplerState)))
	{
		MessageBox(m_hWnd, TEXT("CreateSamplerStateに失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	return true;
}

bool Lib::Vertex::InitConstantBuffer()
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
		MessageBox(m_hWnd, TEXT("ConstantBufferの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	return true;
}

void Lib::Vertex::ReleaseVertexShader()
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

void Lib::Vertex::ReleaseVertexLayout()
{
	if (m_pVertexLayout != nullptr)
	{
		m_pVertexLayout->Release();
		m_pVertexLayout = nullptr;
	}
}

void Lib::Vertex::ReleasePixelShader()
{
	if (m_pPixelShader != nullptr)
	{
		m_pPixelShader->Release();
		m_pPixelShader = nullptr;
	}

	if (m_pPixelCompiledShader != nullptr)
	{
		m_pPixelCompiledShader->Release();
		m_pPixelCompiledShader = nullptr;
	}
}

void Lib::Vertex::ReleaseBlendState()
{
	if (m_pBlendState != nullptr)
	{
		m_pBlendState->Release();
		m_pBlendState = nullptr;
	}
}

void Lib::Vertex::ReleaseSamplerState()
{
	if (m_pSamplerState != nullptr)
	{
		m_pSamplerState->Release();
		m_pSamplerState = nullptr;
	}
}

void Lib::Vertex::ReleaseConstantBuffer()
{
	if (m_pConstantBuffer != nullptr)
	{
		m_pConstantBuffer->Release();
		m_pConstantBuffer = nullptr;
	}
}
