struct VERTEX
{
	float4 position	: POSITION0;
	float4 normal	: NORMAL0;
	float2 texCoord	: TEXCOORD0;
	float4 diffuse	: COLOR0;
};

struct Time
{
	float Time;
	float SinTime;
	float CosTime;
	float DeltaTime;
};

struct Variable
{
	float _1;
	float _2;
	float _3;
	float _4;
};