cbuffer WorldBuffer : register(b0)
{
	matrix World;
}

cbuffer ViewBuffer : register(b1)
{
	matrix View;
}

cbuffer ProjectionBuffer : register(b2)
{
	matrix Projection;
}

cbuffer ProjectionBuffer : register(b5)
{
	float3 CameraPosition;
}


struct VS_IN
{
	float4 Position : POSITION0;
	float4 Normal : NORMAL0;
	float4 Diffuse : COLOR0;
	float2 TexCoord : TEXCOORD0;
};

struct PS_IN
{
	float4 Position : SV_POSITION;
	float4 WorldPosition : POSITION0;
	float4 Normal : NORMAL0;
	float4 Diffuse : COLOR0;
	float2 TexCoord : TEXCOORD0;
};

struct VS_IN_T
{
	float4 Position : POSITION0;
	float4 Normal : NORMAL0;
	float4 Diffuse : COLOR0;
	float2 TexCoord : TEXCOORD0;
	float4 Tangent : TANGENT0;
};

struct HS_IN_T
{
	float4 Position : SV_POSITION;
	float4 Normal : NORMAL0;
	float4 Diffuse : COLOR0;
	float2 TexCoord : TEXCOORD0;
	float4 Tangent : TANGENT0;
};

struct VS_IN_LINE
{
	float4 Position : POSITION0;
//	float2 Dummy : DUMMY0;
};

struct HS_DS_IN_LINE
{
	float4 Position : SV_POSITION;
};

struct PS_IN_LINE
{
	float4 Position : SV_POSITION;
	float2 TexCoord : TEXCOORD0;
};

struct PS_IN_T
{
	float4 Position : SV_POSITION;
	float4 WorldPosition : POSITION0;
	float4 Normal : NORMAL0;
	float4 Diffuse : COLOR0;
	float2 TexCoord : TEXCOORD0;
	float3x3 TBNmtx : TANGENT0;
};

struct MATERIAL
{
	float4 Ambient;
	float4 Diffuse;
	float4 Specular;
	float4 Emission;
	float Shininess;
	float3 Dummy;
};

cbuffer MaterialBuffer : register(b3)
{
	MATERIAL Material;
}



struct LIGHT
{
	bool Enable;
	bool3 Dummy;
	float4 Direction;
	float4 Diffuse;
	float4 Ambient;
};


cbuffer LightBuffer : register(b4)
{
	LIGHT Light;
}