#include "common.hlsli"
#include "Header.hlsli"

#define MAX_CP_NUM 63

struct CP_LINE
{
	float4 CP[MAX_CP_NUM];
	uint CP_num;
	float Len;
	float2 dummmy;
};

cbuffer TimeBuffer : register(b10)
{
	Time time;
}


cbuffer CPBuffer : register(b3)
{
	CP_LINE CP;
}

// 出力パッチ定数データ。
struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[2] : SV_TessFactor;
};

#define NUM_CONTROL_POINTS 1


float3 CalcBezierPoint(float4 CP[MAX_CP_NUM], int CPnum, float t)
{
	for (int i = 0; i < CPnum - 1; i++)
	{
		for (int j = 0; j < CPnum - 1 - i; j++)
		{
			CP[j] = lerp(CP[j], CP[j + 1], t);
		}
	}
	return CP[0].xyz;
}


[domain("isoline")]
HS_DS_IN_LINE main(
	HS_CONSTANT_DATA_OUTPUT input,
	float2 domain : SV_DomainLocation,
	const OutputPatch<HS_DS_IN_LINE, NUM_CONTROL_POINTS> patch)
{
	HS_DS_IN_LINE output;
	
	float uv = saturate(domain.x + 1.0 / 64.0 * domain.y * (1 - saturate(abs(CP.Len))) + CP.Len);
//	float uv = saturate(domain.x + 1.0 / 64.0 * domain.y );


	//wにドメインuvをいれておく
	output.Position = float4(
	   CalcBezierPoint(CP.CP, CP.CP_num, uv), 1);
	
	matrix wv;
	wv = mul(World, View);
	output.Position = mul(output.Position, wv);
	output.Position.w = uv;
	return output;
}


