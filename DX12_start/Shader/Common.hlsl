


cbuffer EnvConstantBuffer : register(b0)
{
    float4		LightDirection;
    float4		LightColor;
};


cbuffer CameraConstantBuffer : register(b1)
{
    float4x4    View;
    float4x4    Projection;
	float4      CameraPosition;

};


cbuffer ObjectConstantBuffer : register(b2)
{
    float4x4    World;
};


cbuffer SubsetConstantBuffer : register(b3)
{
    struct MATERIAL
    {
        float4 BaseColor;
        float4 EmissionColor;
       
        float Metallic;
        float Specular;
        float Roughness;
        float NormalWeight;
    } Material;
};






struct VS_INPUT
{
    float3 Position : POSITION;
    float3 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
    float4 Color : COLOR;
};


struct PS_INPUT
{
    float4 Position : SV_POSITION;
	float4 WorldPosition : POSITION;
    float4 Normal : NORMAL;
    float2 TexCoord : TEXCOORD;
    float4 Color : COLOR;
};

struct PS_OUTPUT_GEOMETRY
{
	float4 Color : SV_TARGET0;
    float4 Normal : SV_TARGET1;
    float4 Position : SV_TARGET2;
    float4 Arm : SV_TARGET3;
    float4 Emission : SV_TARGET4;
};


struct PS_OUTPUT
{
    float4 Color : SV_TARGET0;
};


Texture2D<float4> TextureBaseColor : register(t0);
Texture2D<float4> TextureNormal : register(t1);
Texture2D<float4> TexturePosition : register(t2);
Texture2D<float4> TextureArm : register(t3);
Texture2D<float4> TextureEnvironment : register(t4);
Texture2D<float4> TextureEmission : register(t5);


SamplerState Sampler : register(s0);

static float PI = 3.141592653589;

