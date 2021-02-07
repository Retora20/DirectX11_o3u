#include "common.hlsli"

[maxvertexcount(4)]
void main(
	point VS_IN_LINE input[1],
	inout TriangleStream<PS_IN_LINE> output
)
{
	const float NOTESIZE = 1;
	const float2 Offset = { NOTESIZE, NOTESIZE };
	matrix wv = mul(World, View);
	
	//ç∂è„
	PS_IN_LINE tmp;
	//	tmp.Dummy = 0.0f;
	tmp.Position = mul(input[0].Position, wv);
	tmp.Position.xy += Offset;
	tmp.Position.xyz += mul(float3(-NOTESIZE, NOTESIZE, 0.0), (float3x3) World);
	tmp.TexCoord = float2(0, 0);
	tmp.Position = mul(tmp.Position, Projection);
	output.Append(tmp);
	
	//âEè„
	tmp.Position = mul(input[0].Position, wv);
	tmp.Position.xy += Offset;
	tmp.Position.xyz += mul(float3(NOTESIZE, NOTESIZE, 0.0), (float3x3) World);
	tmp.TexCoord = float2(1, 0);
	tmp.Position = mul(tmp.Position, Projection);
	output.Append(tmp);
	
	//ç∂â∫
	tmp.Position = mul(input[0].Position, wv);
	tmp.Position.xy += Offset;
	tmp.Position.xyz += mul(float3(-NOTESIZE, -NOTESIZE, 0.0), (float3x3) World);
	tmp.TexCoord = float2(0, 1);
	tmp.Position = mul(tmp.Position, Projection);
	output.Append(tmp);
	
	//âEâ∫
	tmp.Position = mul(input[0].Position, wv);
	tmp.Position.xy += Offset;
	tmp.Position.xyz += mul(float3(NOTESIZE, -NOTESIZE, 0.0), (float3x3) World);
	tmp.TexCoord = float2(1, 1);
	tmp.Position = mul(tmp.Position, Projection);
	output.Append(tmp);

	output.RestartStrip();
}