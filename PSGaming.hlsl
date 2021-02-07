//*****************************************************************************
// �萔�o�b�t�@
//*****************************************************************************

struct Time
{
	float Time;
	float SinTime;
	float CosTime;
	float DeltaTime;
};

cbuffer TimeBuffer : register(b0)
{
	Time time;
}

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);


//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
void main(in  float4 inPosition	: POSITION0,
	in  float4 inNormal : NORMAL0,
	in  float2 inTexCoord : TEXCOORD0,
	in  float4 inDiffuse : COLOR0,

	out float4 outDiffuse : SV_Target)
{
	outDiffuse = g_Texture.Sample(g_SamplerState, (inTexCoord + time.Time * 0.1)*2.0);

	float rgbsum = outDiffuse.r + outDiffuse.g + outDiffuse.b;
	rgbsum += time.Time * 0.3;

	const float PI = 3.14159265;
	
	outDiffuse.r = abs(sin(rgbsum));
	outDiffuse.g = abs(sin(rgbsum + PI / 3));
	outDiffuse.b = abs(sin(rgbsum + PI / 3 * 2));

	clamp(outDiffuse, 0, 1);
}
