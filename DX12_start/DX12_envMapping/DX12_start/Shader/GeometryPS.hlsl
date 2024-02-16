#include "Common.hlsl"

[earlydepthstencil]

PS_OUTPUT_GEOMETRY main(PS_INPUT input)
{
    PS_OUTPUT_GEOMETRY output;
       
    float4 baseColor;
    baseColor = TextureBaseColor.Sample(Sampler, input.TexCoord);
    output.Color = baseColor;
  
    float3 normal = input.Normal;
    normal = normalize(normal);
    output.Normal.rgb = normal;
    output.Normal.a = 1.0f;
    
    float3 position = input.WorldPosition.xyz;
    output.Position.rgb = position;
    output.Position.a = 1.0f;
      
    float4 arm = TextureArm.Sample(Sampler, input.TexCoord);
    output.Arm = arm;
    
    return output;
}
