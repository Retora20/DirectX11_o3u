#include "common.hlsli"

float4 main(in PS_IN_LINE In) : SV_TARGET
{
	float len = length(In.TexCoord - float2(0.5, 0.5));
	
	//��
	clip(len - 0.47);
	//�O
	clip(0.5 - len);
	return float4(1, 1, 1, 1);
}