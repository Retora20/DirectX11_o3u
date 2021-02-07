#include "common.hlsli"


[maxvertexcount(8)]
void main(
	line HS_DS_IN_LINE input[2],
	inout TriangleStream<PS_IN_LINE> output
)
{
	float NOTESIZE = 1 - input[0].Position.w;
	NOTESIZE = pow(NOTESIZE, 500) * 0.5 + 0.05;
	//NOTESIZE = 0.5;
	
	//0番目の頂点
	
	//左上
	PS_IN_LINE tmp;
	//	tmp.Dummy = 0.0f;
	tmp.Position = input[0].Position + float4(-NOTESIZE, NOTESIZE, 0.0, 0.0);
	tmp.Position.w = 1.0;
	tmp.TexCoord = float2(0, 0);
	tmp.Position = mul(tmp.Position, Projection);
	output.Append(tmp);
	
	//右上
	tmp.Position = input[0].Position + float4(NOTESIZE, NOTESIZE, 0.0, 0.0);
	tmp.Position.w = 1.0;
	tmp.TexCoord = float2(1, 0);
	tmp.Position = mul(tmp.Position, Projection);
	output.Append(tmp);
	
	//左下
	tmp.Position = input[0].Position + float4(-NOTESIZE, -NOTESIZE, 0.0, 0.0);
	tmp.Position.w = 1.0;
	tmp.TexCoord = float2(0, 1);
	
	tmp.Position = mul(tmp.Position, Projection);
	output.Append(tmp);
	
	//右下
	tmp.Position = input[0].Position + float4(NOTESIZE, -NOTESIZE, 0.0, 0.0);
	tmp.Position.w = 1.0;
	tmp.TexCoord = float2(1, 1);
	tmp.Position = mul(tmp.Position, Projection);
	output.Append(tmp);

	output.RestartStrip();
	
	//1番目の頂点
	
	////左上
	//tmp.Position = input[1].Position + float4(-NOTESIZE, NOTESIZE, 0.0, 0.0);
	//tmp.Position.w = 1.0;
	//tmp.TexCoord = float2(0, 0);
	//tmp.Position = mul(tmp.Position, Projection);
	//output.Append(tmp);
	
	////右上
	//tmp.Position = input[1].Position + float4(NOTESIZE, NOTESIZE, 0.0, 0.0);
	//tmp.Position.w = 1.0;
	//tmp.TexCoord = float2(1, 0);
	//tmp.Position = mul(tmp.Position, Projection);
	//output.Append(tmp);
	
	////左下
	//tmp.Position = input[1].Position + float4(-NOTESIZE, -NOTESIZE, 0.0, 0.0);
	//tmp.Position.w = 1.0;
	//tmp.TexCoord = float2(0, 1);
	//tmp.Position = mul(tmp.Position, Projection);
	//output.Append(tmp);
	
	////右下
	//tmp.Position = input[1].Position + float4(NOTESIZE, -NOTESIZE, 0.0, 0.0);
	//tmp.Position.w = 1.0;
	//tmp.TexCoord = float2(1, 1);
	//tmp.Position = mul(tmp.Position, Projection);
	//output.Append(tmp);

	//output.RestartStrip();
}