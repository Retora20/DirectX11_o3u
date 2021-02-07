#include "Header.hlsli"

// マトリクスバッファ
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

//struct GSInput
//{
//	float4 pos		: POSITION;
//	float3 normal	: NORMAL0;
//	float4 diffuse	: COLOR0;
//};
//
struct GSOutput
{
	float4 pos		: SV_POSITION;
	float4 normal	: NORMAL0;
	float2 texCoord : TEXCOORD0;
	float4 diffuse	: COLOR0;
};

[maxvertexcount(4)]
void main(
	point VERTEX input[1] ,
	inout TriangleStream< GSOutput > output
)
{
	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	//入力posを中心に□ポリゴンを作る
	VERTEX o;
	o.normal = input[0].normal;
	o.diffuse = input[0].diffuse;

	//o.pos.w = 0;
	//左上
	o.position = input[0].position + float4(-0.5, 0.5, 0, 0);
	o.texCoord = float2(0, 0);

	o.position = mul(o.position, wvp);
	//float w = o.position.w;
	output.Append(o);

	//右上
	o.position = input[0].position + float4(0.5, 0.5, 0, 0);
	o.texCoord = float2(1, 0);

	o.position = mul(o.position, wvp);
//	o.position.w = w;
	output.Append(o);

	//左下
	o.position = input[0].position + float4(-0.5, -0.5, 0, 0);
	o.texCoord = float2(0, 1);

	o.position = mul(o.position, wvp);
//	o.position.w = w;
	output.Append(o);

	//右下
	o.position = input[0].position + float4(0.5, -0.5, 0, 0);
	o.texCoord = float2(1, 1);

	o.position = mul(o.position, wvp);
//	o.position.w = w;
	output.Append(o);

	output.RestartStrip();
}