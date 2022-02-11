Texture2D MainTexture[3] : register(t0);

SamplerState samplerOne : register(s0);

cbuffer MaterialPixelBuffer
{
	float4 ambientColor;
	float4 diffuseColor;
    float4 specularColor;
	float3 lightDirection;
    float specularStrength;
};

struct PS_INPUT
{
	float4 position : SV_POSITION;
	float3 normal : NORMAL;
	float2 uv : TEXCOORD;
    float3 viewDirection : POSITION;
};

float4 main(PS_INPUT _input) : SV_TARGET
{
    float4 firstTexture;
    float4 secondTexture;
    float4 alphaTexture;
	float4 color;
	float3 lightDir;
	float lightIntesity;
    float3 reflection;
    float specular;
	
	firstTexture = MainTexture[0].Sample(samplerOne, _input.uv);
    secondTexture = MainTexture[1].Sample(samplerOne, _input.uv);
    alphaTexture = MainTexture[2].Sample(samplerOne, _input.uv);
	
    color = ((firstTexture * alphaTexture) + (secondTexture * (1.0f - alphaTexture)));
	
	//lightDir = -lightDirection;
	//lightIntesity = saturate(dot(_input.normal, lightDir));
	
	//color = ambientColor;
	
	//if (lightIntesity > 0.0f)
	//{
	//	color += diffuseColor * lightIntesity;
 //       color = saturate(color);
 //       reflection = normalize(2*_input.normal * lightIntesity - lightDir);
		
 //       specular = pow(saturate(dot(reflection, _input.viewDirection)), specularStrength);
		
	//	// R-> = -L-> + N-> * 2 * max((N-> dot L->), 0)
	//	// S = S-Licht * (max(R-> dotN->, 0))^SpecPower
	//}
	
 //   color = color * firstTextur;
	////color = textur * color;
 //       color = saturate(color + specular);
	
	return color;
}