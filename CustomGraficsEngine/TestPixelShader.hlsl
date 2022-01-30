Texture2D MainTexture : register(t0);

SamplerState samplerOne : register(s0);

cbuffer MaterialPixelBuffer
{
	float4 ambientColor;
	float4 diffuseColor;
	float3 lightDirection;
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
	float4 color : COLOR;
};

float4 main(PS_INPUT _input) : SV_TARGET
{
	float4 textur;
	float4 color;
	float3 lightDir;
	float lightIntesity;
	
	textur = MainTexture.Sample(samplerOne, _input.uv);
	
	lightDir = -lightDirection;
	lightIntesity = saturate(dot(_input.normal, lightDir));
	
	color = ambientColor;
	
	if (lightIntesity > 0.0f)
	{
		color += diffuseColor * lightIntesity;
	}
	
	color = textur * color;
	
	return color;
}