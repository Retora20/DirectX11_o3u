#include "common.hlsli"


float4 main(in PS_IN_LINE In) : SV_TARGET
{
	clip(0.5 - length(In.TexCoord - float2(0.5, 0.5)));
    return float4(0.03, 0.03, 0.03, 1) * Material.Diffuse;
}