#include "common.hlsli"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

float4 main(in PS_IN_LINE In) : SV_TARGET
{
	return g_Texture.Sample(g_SamplerState, In.TexCoord);
}