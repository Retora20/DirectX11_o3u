#include "main.h"
#include "Time.h"
#include "Renderer.h"
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <io.h>
#include "ImGuizmo.h"
D3D_FEATURE_LEVEL       Renderer::m_FeatureLevel = D3D_FEATURE_LEVEL_11_0;

ID3D11Device*           Renderer::m_D3DDevice = NULL;
ID3D11DeviceContext*    Renderer::m_ImmediateContext = NULL;
IDXGISwapChain*         Renderer::m_SwapChain = NULL;
ID3D11RenderTargetView* Renderer::m_RenderTargetView = NULL;
ID3D11DepthStencilView* Renderer::m_DepthStencilView = NULL;


//ID3D11VertexShader*     Renderer::m_VertexShader = NULL;
//ID3D11GeometryShader*	Renderer::m_GeometryShader = NULL;
//ID3D11PixelShader*      Renderer::m_PixelShader = NULL;
//ID3D11InputLayout*      Renderer::m_VertexLayout = NULL;
ID3D11Buffer*			Renderer::m_WorldBuffer = NULL;
ID3D11Buffer*			Renderer::m_ViewBuffer = NULL;
ID3D11Buffer*			Renderer::m_ProjectionBuffer = NULL;
ID3D11Buffer*			Renderer::m_MaterialBuffer = NULL;
ID3D11Buffer*			Renderer::m_LightBuffer = NULL;
ID3D11Buffer*			Renderer::m_Time = NULL;
ID3D11Buffer*			Renderer::m_variable = NULL;
ID3D11Buffer*			Renderer::m_boneBuffer = NULL;
ID3D11Buffer*			Renderer::m_CPbuffer = NULL;
ID3D11Buffer*			Renderer::m_PointSpriteSize = NULL;

float					Renderer::m_clearColor[4];


ID3D11DepthStencilState* Renderer::m_DepthStateEnable = NULL;
ID3D11DepthStencilState* Renderer::m_DepthStateDisable = NULL;

ShaderVariable Renderer::m_shaderVariable = { 0.0f };



void Renderer::Init()
{
	HRESULT hr = S_OK;

	auto hdc = GetDC(GetWindow());
	float refreshRate = (float)GetDeviceCaps(hdc, VREFRESH);





	// デバイス、スワップチェーン、コンテキスト生成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory( &sd, sizeof( sd ) );
	sd.BufferCount = 1;
	sd.BufferDesc.Width = SCREEN_WIDTH;
	sd.BufferDesc.Height = SCREEN_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = refreshRate;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = GetWindow();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	

	hr = D3D11CreateDeviceAndSwapChain( NULL,
										D3D_DRIVER_TYPE_HARDWARE,
										NULL,
										0,
										NULL,
										0,
										D3D11_SDK_VERSION,
										&sd,
										&m_SwapChain,
										&m_D3DDevice,
										&m_FeatureLevel,
										&m_ImmediateContext );


	// レンダーターゲットビュー生成、設定
	ID3D11Texture2D* pBackBuffer = NULL;
	m_SwapChain->GetBuffer( 0, __uuidof( ID3D11Texture2D ), ( LPVOID* )&pBackBuffer );
	m_D3DDevice->CreateRenderTargetView( pBackBuffer, NULL, &m_RenderTargetView );
	pBackBuffer->Release();



	//Zステンシル用テクスチャー作成
	ID3D11Texture2D* depthTexture = NULL;
	D3D11_TEXTURE2D_DESC td;
	ZeroMemory( &td, sizeof(td) );
	td.Width			= sd.BufferDesc.Width;
	td.Height			= sd.BufferDesc.Height;
	td.MipLevels		= 1;
	td.ArraySize		= 1;
	td.Format			= DXGI_FORMAT_D24_UNORM_S8_UINT;
	td.SampleDesc		= sd.SampleDesc;
	td.Usage			= D3D11_USAGE_DEFAULT;
	td.BindFlags		= D3D11_BIND_DEPTH_STENCIL;
    td.CPUAccessFlags	= 0;
    td.MiscFlags		= 0;
	m_D3DDevice->CreateTexture2D( &td, NULL, &depthTexture );

	//Zステンシルターゲット作成
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	ZeroMemory( &dsvd, sizeof(dsvd) );
	dsvd.Format			= td.Format;
	dsvd.ViewDimension	= D3D11_DSV_DIMENSION_TEXTURE2D;
	dsvd.Flags			= 0;
	m_D3DDevice->CreateDepthStencilView( depthTexture, &dsvd, &m_DepthStencilView );


	m_ImmediateContext->OMSetRenderTargets( 1, &m_RenderTargetView, m_DepthStencilView );


	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;
	vp.Height = (FLOAT)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_ImmediateContext->RSSetViewports( 1, &vp );



	// ラスタライザステート設定
	D3D11_RASTERIZER_DESC rd; 
	ZeroMemory( &rd, sizeof( rd ) );
	rd.FillMode = D3D11_FILL_SOLID; 
	rd.CullMode = D3D11_CULL_BACK; 
	rd.DepthClipEnable = TRUE; 
	rd.MultisampleEnable = FALSE; 

	ID3D11RasterizerState *rs;
	m_D3DDevice->CreateRasterizerState( &rd, &rs );

	m_ImmediateContext->RSSetState( rs );


	// ブレンドステート設定
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = {0.0f, 0.0f, 0.0f, 0.0f};
	ID3D11BlendState* blendState = NULL;
	m_D3DDevice->CreateBlendState( &blendDesc, &blendState );
	m_ImmediateContext->OMSetBlendState( blendState, blendFactor, 0xffffffff );



	// 深度ステンシルステート設定
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory( &depthStencilDesc, sizeof( depthStencilDesc ) );
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.StencilEnable = FALSE;

	m_D3DDevice->CreateDepthStencilState( &depthStencilDesc, &m_DepthStateEnable );//深度有効ステート

	//depthStencilDesc.DepthEnable = FALSE;
	depthStencilDesc.DepthWriteMask	= D3D11_DEPTH_WRITE_MASK_ZERO;
	m_D3DDevice->CreateDepthStencilState( &depthStencilDesc, &m_DepthStateDisable );//深度無効ステート

	m_ImmediateContext->OMSetDepthStencilState( m_DepthStateEnable, NULL );




	// サンプラーステート設定
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory( &samplerDesc, sizeof( samplerDesc ) );
	samplerDesc.Filter = D3D11_FILTER_ANISOTROPIC;
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.MipLODBias = 0;
	samplerDesc.MaxAnisotropy = 16;
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	samplerDesc.MinLOD = 0;
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	ID3D11SamplerState* samplerState = NULL;
	m_D3DDevice->CreateSamplerState( &samplerDesc, &samplerState );

	m_ImmediateContext->PSSetSamplers( 0, 1, &samplerState );


	// 定数バッファ生成
	D3D11_BUFFER_DESC hBufferDesc;
	hBufferDesc.ByteWidth = sizeof(D3DXMATRIX);
	hBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	hBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	hBufferDesc.CPUAccessFlags = 0;
	hBufferDesc.MiscFlags = 0;
	hBufferDesc.StructureByteStride = sizeof(float);

	m_D3DDevice->CreateBuffer( &hBufferDesc, NULL, &m_WorldBuffer );
	m_ImmediateContext->VSSetConstantBuffers( 0, 1, &m_WorldBuffer);
	m_ImmediateContext->GSSetConstantBuffers(0, 1, &m_WorldBuffer);
	m_ImmediateContext->DSSetConstantBuffers(0, 1, &m_WorldBuffer);


	m_D3DDevice->CreateBuffer( &hBufferDesc, NULL, &m_ViewBuffer );
	m_ImmediateContext->VSSetConstantBuffers( 1, 1, &m_ViewBuffer );
	m_ImmediateContext->GSSetConstantBuffers(1, 1, &m_ViewBuffer);
	m_ImmediateContext->DSSetConstantBuffers(1, 1, &m_ViewBuffer);

	m_D3DDevice->CreateBuffer( &hBufferDesc, NULL, &m_ProjectionBuffer );
	m_ImmediateContext->VSSetConstantBuffers( 2, 1, &m_ProjectionBuffer );
	m_ImmediateContext->GSSetConstantBuffers(2, 1, &m_ProjectionBuffer);
	m_ImmediateContext->DSSetConstantBuffers(2, 1, &m_ProjectionBuffer);



	hBufferDesc.ByteWidth = sizeof(MATERIAL);

	m_D3DDevice->CreateBuffer( &hBufferDesc, NULL, &m_MaterialBuffer );
	m_ImmediateContext->VSSetConstantBuffers( 3, 1, &m_MaterialBuffer );
	m_ImmediateContext->PSSetConstantBuffers( 3, 1, &m_MaterialBuffer );


	hBufferDesc.ByteWidth = sizeof(LIGHT);

	m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_LightBuffer);
	m_ImmediateContext->VSSetConstantBuffers( 4, 1, &m_LightBuffer );

	hBufferDesc.ByteWidth = sizeof(BONE_BUFFER);
	m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_boneBuffer);
	m_ImmediateContext->VSSetConstantBuffers(5, 1, &m_boneBuffer);

	//ps

	hBufferDesc.ByteWidth = sizeof(ShaderTime);						//たした

	m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_Time);
	m_ImmediateContext->PSSetConstantBuffers(10, 1, &m_Time);
	m_ImmediateContext->DSSetConstantBuffers(10, 1, &m_Time);
	m_ImmediateContext->VSSetConstantBuffers(10, 1, &m_Time);

	hBufferDesc.ByteWidth = sizeof(ShaderVariable);
	m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_variable);
	m_ImmediateContext->PSSetConstantBuffers(11, 1, &m_variable);
	m_ImmediateContext->DSSetConstantBuffers(11, 1, &m_variable);

	//line_CP
	hBufferDesc.ByteWidth = sizeof(Shader_CP);						//たした
	m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_CPbuffer);
	m_ImmediateContext->DSSetConstantBuffers(3, 1, &m_CPbuffer);

	//line_CP
	hBufferDesc.ByteWidth = sizeof(D3DXVECTOR2);						//たした
	m_D3DDevice->CreateBuffer(&hBufferDesc, NULL, &m_PointSpriteSize);
	m_ImmediateContext->GSSetConstantBuffers(6, 1, &m_PointSpriteSize);




	//// 入力レイアウト設定
	//m_ImmediateContext->IASetInputLayout( m_VertexLayout );

	//// シェーダ設定
	//m_ImmediateContext->VSSetShader( m_VertexShader, NULL, 0 );
	//m_ImmediateContext->PSSetShader( m_PixelShader, NULL, 0 );
	//m_ImmediateContext->GSSetShader(m_GeometryShader, NULL, 0);




	// ライト無効化
	LIGHT light;
	light.Enable = false;
	SetLight(light);


	// マテリアル初期化
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	SetMaterial(material);

	m_clearColor[0] = 0.1f;
	m_clearColor[1] = 0.1f;
	m_clearColor[2] = 0.1f;
	m_clearColor[3] = 1.0f;

	//imguiコンテキスト初期化
	ImguiInit();
}



void Renderer::Uninit()
{
	// オブジェクト解放
	m_WorldBuffer->Release();
	m_ViewBuffer->Release();
	m_ProjectionBuffer->Release();
	m_LightBuffer->Release();
	m_MaterialBuffer->Release();

	//m_VertexLayout->Release();
	//m_VertexShader->Release();
	//m_PixelShader->Release();

	ImguiUnInit();

	m_ImmediateContext->ClearState();
	m_RenderTargetView->Release();
	m_SwapChain->Release();
	m_ImmediateContext->Release();
	m_D3DDevice->Release();
}



void Renderer::Begin()
{
	// バックバッファクリア
	//float ClearColor[4] = { 0.10f, 0.10f, 0.10f, 1.0f };
	//m_ImmediateContext->ClearRenderTargetView( m_RenderTargetView, ClearColor );

	ImGui::Render();

	m_ImmediateContext->ClearRenderTargetView( m_RenderTargetView, m_clearColor );
	m_ImmediateContext->ClearDepthStencilView( m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

}



void Renderer::End()
{
	m_SwapChain->Present( 1, 0 );
}

void Renderer::ImguiInit()
{
	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	// Setup Platform/Renderer bindings
	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(m_D3DDevice, m_ImmediateContext);

}

void Renderer::ImguiUnInit()
{
	// Cleanup
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Renderer::ImguiBegin()
{
	// Start the Dear ImGui frame
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGuizmo::BeginFrame();
}

void Renderer::ImguiEnd()
{
	// Rendering
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	ImGui::Render();
}




void Renderer::SetDepthEnable( bool Enable )
{
	if( Enable )
		m_ImmediateContext->OMSetDepthStencilState( m_DepthStateEnable, NULL );
	else
		m_ImmediateContext->OMSetDepthStencilState( m_DepthStateDisable, NULL );

}

void Renderer::SetZTest(bool Enable)
{
	// ラスタライザステート設定
	//D3D11_RASTERIZER_DESC rd;
	//ZeroMemory(&rd, sizeof(rd));
	//rd.FillMode = D3D11_FILL_SOLID;
	//rd.CullMode = D3D11_CULL_BACK;
	//rd.DepthClipEnable = Enable;
	//rd.MultisampleEnable = FALSE;

	//ID3D11RasterizerState* rs;
	//m_D3DDevice->CreateRasterizerState(&rd, &rs);

	//m_ImmediateContext->RSSetState(rs);
	if (Enable)
	{
		m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, nullptr);
	}
	else
	{
		m_ImmediateContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);
	}
}

void Renderer::SetViewProjection2D()
{
	D3DXMATRIX projectionMatrix;
	D3DXMatrixOrthoLH(&projectionMatrix, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0,1);
	Renderer::SetProjectionMatrix(&projectionMatrix);

	D3DXMATRIX view;
	D3DXMatrixIdentity(&view);
	D3DXMatrixTranspose(&view, &view);
	m_ImmediateContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);
}

//void Renderer::SetWorldViewProjection2D()
//{
//	D3DXMATRIX world;
//	D3DXMatrixIdentity(&world);
//	D3DXMatrixTranspose(&world, &world);
//
//	m_ImmediateContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);
//
//	D3DXMATRIX view;
//	D3DXMatrixIdentity(&view);
//	D3DXMatrixTranspose(&view, &view);
//	m_ImmediateContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);
//
//	D3DXMATRIX projection;
//	D3DXMatrixOrthoOffCenterLH(&projection, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f);
//	D3DXMatrixTranspose(&projection, &projection);
//	m_ImmediateContext->UpdateSubresource( m_ProjectionBuffer, 0, NULL, &projection, 0, 0 );
//
//}


void Renderer::SetWorldMatrix( D3DXMATRIX *WorldMatrix )
{
	D3DXMATRIX world;
	D3DXMatrixTranspose(&world, WorldMatrix);
	m_ImmediateContext->UpdateSubresource(m_WorldBuffer, 0, NULL, &world, 0, 0);
}

void Renderer::SetViewMatrix( D3DXMATRIX *ViewMatrix )
{
	D3DXMATRIX view;
	D3DXMatrixTranspose(&view, ViewMatrix);
	m_ImmediateContext->UpdateSubresource(m_ViewBuffer, 0, NULL, &view, 0, 0);
}

void Renderer::SetProjectionMatrix( D3DXMATRIX *ProjectionMatrix )
{
	D3DXMATRIX projection;
	D3DXMatrixTranspose(&projection, ProjectionMatrix);
	m_ImmediateContext->UpdateSubresource(m_ProjectionBuffer, 0, NULL, &projection, 0, 0);
}



void Renderer::SetMaterial( MATERIAL Material )
{

	m_ImmediateContext->UpdateSubresource( m_MaterialBuffer, 0, NULL, &Material, 0, 0 );

}

void Renderer::SetLight( LIGHT Light )
{

	m_ImmediateContext->UpdateSubresource(m_LightBuffer, 0, NULL, &Light, 0, 0);

}

void Renderer::SetBlendStateDefault()
{
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ID3D11BlendState* blendState = NULL;
	m_D3DDevice->CreateBlendState(&blendDesc, &blendState);
	m_ImmediateContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);
}

void Renderer::SetBlendStateAdd()
{
	//加算
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	ID3D11BlendState* blendState = NULL;
	m_D3DDevice->CreateBlendState(&blendDesc, &blendState);
	m_ImmediateContext->OMSetBlendState(blendState, blendFactor, 0xffffffff);
}

void Renderer::SetClearColor(float col[4])
{
	for (size_t i = 0; i < 4; i++)
	{
		m_clearColor[i] = col[i];
	}
}

void Renderer::UpdateTime()
{
	ShaderTime tmp;
	tmp.Time = Time::GetTime();
	tmp.SinTime = sinf(tmp.Time);
	tmp.CosTime = cosf(tmp.Time);
	tmp.DeltaTime = Time::GetDeltaTime();

	m_ImmediateContext->UpdateSubresource(m_Time, 0, NULL, &tmp, 0, 0);
}

void Renderer::UpdateVariable()
{
	m_ImmediateContext->UpdateSubresource(m_variable, 0, NULL, &m_shaderVariable, 0, 0);
}

void Renderer::UpdateBoneMatrix(BONE_BUFFER* boneBuffer)
{
	m_ImmediateContext->UpdateSubresource(m_boneBuffer, 0, NULL, boneBuffer, 0, 0);
}

void Renderer::UpdateCP(Shader_CP* CPs)
{
	m_ImmediateContext->UpdateSubresource(m_CPbuffer, 0, NULL, CPs, 0, 0);
}
