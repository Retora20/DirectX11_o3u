#include "common.hlsli"

// �o�̓p�b�`�萔�f�[�^�B
struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[2] : SV_TessFactor;
};

#define NUM_CONTROL_POINTS 1

// �p�b�`�萔�֐�
HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(
	InputPatch<HS_DS_IN_LINE, NUM_CONTROL_POINTS> ip,
	uint PatchID : SV_PrimitiveID)
{
	HS_CONSTANT_DATA_OUTPUT Output;

	// �����ɃR�[�h��}�����ďo�͂��v�Z���܂�
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

	// �����ɃR�[�h��}�����ďo�͂��v�Z���܂�
    {
		Output = ip[i];
	}

	return Output;
}
