cbuffer MaterialVertexBuffer {
	float4x4 worldPositon;
	float4x4 wvp;
	float3 cameraPosition;
	float padding;
};

struct VS_INPUT {
    float4 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
    float4 color : COLOR;
};

struct VS_OUTPUT {
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
    float4 color : COLOR;
};

VS_OUTPUT main( VS_INPUT _input )
{
    VS_OUTPUT output;
	_input.position.w = 1.0f;
	output.position = mul(_input.position, wvp);
	output.normal = _input.normal;
	output.uv = _input.uv;
	output.color = _input.color;
	return output;
}