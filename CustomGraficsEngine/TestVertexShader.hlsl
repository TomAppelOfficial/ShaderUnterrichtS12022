cbuffer ObjectBuffer {
	matrix worldMatrix;
    matrix ViewProjectionMatrix;
	float4 worldPositon;
};
cbuffer SceneBuffer
{
	float3 cameraPosition;
    float padding;
};

struct VS_INPUT {
    float4 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

struct VS_OUTPUT {
    float4 position : SV_POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
    float3 viewDirection : POSITION;
};

VS_OUTPUT main( VS_INPUT _input )
{
    VS_OUTPUT output;
	_input.position.w = 1.0f;
    
    output.position = mul(_input.position, worldMatrix);
    output.position = mul(output.position, ViewProjectionMatrix);
    
	output.uv = _input.uv;
    
    output.normal = normalize(mul(_input.normal, (float3x3) worldMatrix));
    
    output.viewDirection = normalize(cameraPosition.xyz - worldPositon.xyz);
	return output;
}