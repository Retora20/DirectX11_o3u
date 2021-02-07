#include "Header.hlsli"

cbuffer VariableBuffer : register(b11)
{
	Variable var;
}

Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);

void main(in  float4 inPosition		: POSITION0,
		in  float4 inNormal : NORMAL0,
		in  float2 inTexCoord : TEXCOORD0,
		in  float4 inDiffuse : COLOR0,

		out float4 outDiffuse : SV_Target)
{
	outDiffuse = float4(0, 0, 0, 1);

	float4 tmp = g_Texture.Sample(g_SamplerState, inTexCoord);

	float test = (tmp.r + tmp.g + tmp.b) / 2.8;

	clip(test - var._1);
}