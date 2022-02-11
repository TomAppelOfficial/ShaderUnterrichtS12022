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
    float3 tangent : TANGENT;
    float3 binormal : BINORMAL;
    float2 uv : TEXCOORD;
    float3 viewDirection : POSITION;
};

float4 main(PS_INPUT _input) : SV_TARGET
{
    float4 firstTexture;
    float4 secondTexture;
    float4 specularIntensity;
    float4 color;
    float3 lightDir;
    float lightIntesity;
    float3 reflection;
    float specular;
    float4 normalMap;
    float3 bumpNormal;
    
    firstTexture = MainTexture[0].Sample(samplerOne, _input.uv);
    normalMap = MainTexture[1].Sample(samplerOne, _input.uv);
    specularIntensity = MainTexture[2].Sample(samplerOne, _input.uv);
	
    normalMap = (normalMap * 2) - 1;
	
    bumpNormal = (normalMap.x * _input.tangent) + (normalMap.y * _input.binormal) + (normalMap.z * _input.normal);
	
    bumpNormal = normalize(bumpNormal);
	
    lightDir = -lightDirection;
	
    lightIntesity = saturate(dot(bumpNormal, lightDir));
	
    color = ambientColor;
	
    if (lightIntesity > 0)
    {
        float3 reflection;
        color += saturate(diffuseColor * lightIntesity);
	       
        reflection = normalize(2 * lightIntesity * bumpNormal - lightDir);
        specular = pow(saturate(dot(reflection, _input.viewDirection)), specularStrength);
        specular = specular * specularIntensity;
        
        color += saturate(color + specular);
	
    }
    color = color * firstTexture;
	
	//PHONG
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