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
    float3 lightDir;
    float lightIntesity;
    float4 color;
    float4 specular;
    float angle;
    float3 reflectionDir;
    
    firstTexture = MainTexture[0].Sample(samplerOne, _input.uv);
    //secondTexture = MainTexture[1].Sample(samplerOne, _input.uv);
    //alphaTexture = MainTexture[2].Sample(samplerOne, _input.uv);
    //color = ((firstTexture * alphaTexture) + (secondTexture * (1.0f - alphaTexture)));
    
    color = ambientColor;
    specular = 0;
    
    lightDir = -lightDirection;
    
    lightIntesity = saturate(dot(_input.normal, lightDir));
    
    if (lightIntesity > 0.0f)
    {
        
        color += diffuseColor * lightIntesity;
        
        color = saturate(color);

        reflectionDir = normalize(2 * lightIntesity * _input.normal - lightDir);
        specular = pow(saturate(dot(reflectionDir, _input.viewDirection)), specularStrength);
        specular = specularColor * specular;
    }
    
    color = color * firstTexture;
    color = saturate(color + specular);
	
    return color;
}