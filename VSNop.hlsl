#include "Header.hlsli"

void main(in  float4 inPosition		: POSITION0,
	in  float4 inNormal : NORMAL0,
	in  float4 inDiffuse : COLOR0,
	in  float2 inTexCoord : TEXCOORD0,

	out float4 outPosition : SV_POSITION,
	out float4 outNormal : NORMAL0,
	out float2 outTexCoord : TEXCOORD0,
	out float4 outDiffuse : COLOR0)
{
	outPosition		=	inPosition;
	outNormal		=	inNormal;
	outDiffuse		=	inDiffuse;
	outTexCoord		=	inDiffuse;
}