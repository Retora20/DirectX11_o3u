#pragma once
#include <io.h>
#include <typeinfo>
#include "main.h"
#include "ShaderAseet.h"

#define BONE_BUFFER_MAX (128)

// 頂点構造体
struct VERTEX_3D
{
    D3DXVECTOR3 Position;
    D3DXVECTOR3 Normal;
    D3DXVECTOR4 Diffuse;
    D3DXVECTOR2 TexCoord;
};

// 頂点構造体
struct VERTEX_Positon
{
	D3DXVECTOR4 Position;
};

// マテリアル構造体
struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	float		Dummy[3];//16byte境界用
};

// マテリアル構造体
struct DX11_MODEL_MATERIAL
{
	MATERIAL		Material;
	class CTexture*	Texture;
};

// 描画サブセット構造体
struct DX11_SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	DX11_MODEL_MATERIAL	Material;
};

struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];//16byte境界用
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;
};

struct ShaderTime
{//16biteでもったいないので４つ
	float Time;
	float SinTime;
	float CosTime;
	float DeltaTime;
};

struct ShaderVariable
{//任意の値を代入
	float _1;
	float _2;
	float _3;
	float _4;
};

//曲線制御用コンスタントバッファ構造体
struct Shader_CP
{
	D3DXVECTOR4 CP[63];
	UINT 	CP_Num;
	float	CP_Len = 0.0f;
	float	dummy[2];
};


struct BONE_BUFFER
{
	D3DXMATRIX BoneMatrix[BONE_BUFFER_MAX];
	BONE_BUFFER()
	{
		for (size_t i = 0; i < BONE_BUFFER_MAX; i++)
		{
			D3DXMatrixIdentity(&BoneMatrix[i]);
		}
	}
};

class CVertexBuffer;
class CIndexBuffer;
class CTexture;

class Renderer
{
private:
	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	static ID3D11Device*           m_D3DDevice;
	static ID3D11DeviceContext*    m_ImmediateContext;
	static IDXGISwapChain*         m_SwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;

	//static ID3D11VertexShader*     m_VertexShader;
	//static ID3D11GeometryShader*    m_GeometryShader;
	//static ID3D11PixelShader*      m_PixelShader;
	//static ID3D11InputLayout*      m_VertexLayout;
	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;
	static ID3D11Buffer*			m_MaterialBuffer;
	static ID3D11Buffer*			m_LightBuffer;
	static ID3D11Buffer*			m_Time;
	static ID3D11Buffer*			m_variable;
	static ID3D11Buffer*			m_boneBuffer;
	static ID3D11Buffer*			m_CPbuffer;
	static ID3D11Buffer*			m_PointSpriteSize;

	static float					m_clearColor[4];


	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

public:
	static void Init();
	static void Uninit();
	static void Begin();
	static void End();

	static void ImguiInit();
	static void ImguiUnInit();
	static void ImguiBegin();
	static void ImguiEnd();
	


	static void SetDepthEnable(bool Enable);
//	static void SetWorldViewProjection2D();

	static void SetZTest(bool Enable);

	static void SetViewProjection2D();

	static void SetWorldMatrix(D3DXMATRIX * WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX * ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX * ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);
	static void SetBlendStateDefault();
	static void SetBlendStateAdd();
	static void SetClearColor(float col[4]);
	static void UpdateTime();
	static void UpdateVariable();
	static void UpdateBoneMatrix(BONE_BUFFER* boneBuffer);
	static void UpdateCP(Shader_CP* CPs);

	static ID3D11Device* GetDevice( void ){ return m_D3DDevice; }
	static ID3D11DeviceContext* GetDeviceContext( void ){ return m_ImmediateContext; }

	static ShaderVariable m_shaderVariable;
};