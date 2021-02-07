#include "common.hlsli"

// 出力パッチ定数データ。
struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[2] : SV_TessFactor;
};

#define NUM_CONTROL_POINTS 1

// パッチ定数関数
HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(
	InputPatch<HS_DS_IN_LINE, NUM_CONTROL_POINTS> ip,
	uint PatchID : SV_PrimitiveID)
{
	HS_CONSTANT_DATA_OUTPUT Output;

	// ここにコードを挿入して出力を計算します
	Output.EdgeTessFactor[0] = 64;
	Output.EdgeTessFactor[1] = 64;

	return Output;
}

[domain("isoline")]
//[partitioning("pow2")]
[partitioning("fractional_even")]
[outputtopology("line")]
[outputcontrolpoints(NUM_CONTROL_POINTS)]
[patchconstantfunc("CalcHSPatchConstants")]
HS_DS_IN_LINE main(
	InputPatch<HS_DS_IN_LINE, NUM_CONTROL_POINTS> ip,
	uint i : SV_OutputControlPointID,
	uint PatchID : SV_PrimitiveID)
{
	HS_DS_IN_LINE Output;

	// ここにコードを挿入して出力を計算します
    {
		Output = ip[i];
	}

	return Output;
}
