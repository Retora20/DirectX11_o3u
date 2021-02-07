//*****************************************************************************
// 定数バッファ
//*****************************************************************************

struct Time
{
	float Time;
	float SinTime;
	float CosTime;
	float DeltaTime;
};

cbuffer TimeBuffer : register(b10)
{
	Time time;
}

//*****************************************************************************
// グローバル変数
//*****************************************************************************
Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);


//=============================================================================
// ピクセルシェーダ
//=============================================================================
void main(in float4 inPosition : POSITION0,
			in float4 inNormal : NORMAL0,
			in float2 inTexCoord : TEXCOORD0,
			in float4 inDiffuse : COLOR0,

			out float4 outDiffuse : SV_Target)
{
	outDiffuse = g_Texture.Sample(g_SamplerState, inTexCoord);
	outDiffuse *= inDiffuse;
	
	outDiffuse *= abs(time.SinTime);
	clip(outDiffuse.a - 0.05f);
}
