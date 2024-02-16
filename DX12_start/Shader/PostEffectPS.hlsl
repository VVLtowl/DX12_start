
#include "Common.hlsl"

PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
	
    float2 texCoord = input.TexCoord;
  
	
    //露出補正
    //baseColor.rgb *= 1.0;
    
    //モノクロ
    //baseColor.rgb = (baseColor.r + baseColor.g + baseColor.b) / 3.0;
    
    //ポスタリゼーション
    
    //色調補正
    
    //色収差
    
    //other
    float4 baseColor;
    {
        float x = texCoord.x - 0.5;
        float y = texCoord.y -  0.5;
        float d = pow(x * x + y * y, 0.5);
        float dRate = d / 0.5;
        
        float x1 = texCoord.x;
        float y1 = texCoord.y;
        texCoord.x = x1 *  floor((1 - dRate) * 100)/100 ;
        texCoord.y = y1 *  floor((1 - dRate) * 100)/100 ;
        
        baseColor = TextureBaseColor.Sample(Sampler, texCoord).rgba;
        baseColor.rgb *= floor(pow(0.7, d / 0.5) * 20) / 20;
    }
    
    output.Color.rgb = baseColor.rgb;
    output.Color.a = 1.0;
	
    return output;
}
