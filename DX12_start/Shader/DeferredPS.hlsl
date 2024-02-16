
#include "Common.hlsl"

PS_OUTPUT main(PS_INPUT input)
{
    PS_OUTPUT output;
	
    float2 texCoord = input.TexCoord;
	
    //get color and normal and position
    float4 baseColor = TextureBaseColor.Sample(Sampler, texCoord).rgba;
    float4 normal = TextureNormal.Sample(Sampler, texCoord).rgba;
    float4 position = TexturePosition.Sample(Sampler, texCoord).rgba;
    float4 arm = TextureArm.Sample(Sampler, texCoord).rgba;
    float4 emission = TextureEmission.Sample(Sampler, texCoord).rgba;
    
    float3 normalDirection = normalize(normal.xyz);
    float3 lightDirection = normalize(LightDirection.xyz);
    
    float3 eye = CameraPosition.xyz - position.xyz;
    eye = normalize(eye);
    float3 ref = reflect(-eye, normalDirection);
    
    //half vector
    float3 halfVector = normalize(lightDirection + eye);
    
    //material
    float metallic = arm.b;
    float spec = Material.Specular; //arm.g;
    float roughness = arm.g;
    float ao = arm.r;
    
    
    //set diffuse
    float3 diffuse;
    {
        float3 light = saturate(dot(lightDirection, normalDirection));
        light *= LightColor.rgb;
        diffuse = baseColor.rgb * light / PI;
    }
    {
            //IBL
        float2 iblTexCoord;
        iblTexCoord.x = atan2(normal.x, normal.z) / (PI * 2);
        iblTexCoord.y = acos(normal.y) / PI;
            
        float3 light = TextureEnvironment.SampleLevel(
        Sampler, iblTexCoord, 9).rgb;
            
        diffuse += baseColor.rgb * light * ao;
    }
  
    //set lambert
    float3 lambert;
    {
        float3 lightDirection = LightDirection;
        float3 light = saturate(dot(lightDirection, normalDirection));
        lambert = baseColor.rgb * light * LightColor.rgb / PI;
        
        //スペキュラの計算
	    //カメラからピクセルへ向かうベクトル
        float3 worldPosition = position.xyz; //input.Position.xyz;
        float3 eyev = worldPosition - CameraPosition.xyz;
        eyev = normalize(eyev);
        
        //光の反射ベクトルを計算
        float3 refv = reflect(lightDirection, normal.xyz);
        refv = normalize(refv); //正規化する
        
        float specular = -dot(eyev, refv); //鏡面反射の計算
        specular = saturate(specular); //値をサチュレート
        specular = pow(specular, 20); //ここでは３０乗してみる
        
        lambert += specular;
    }
    
    //specular
    float3 specular2;
    {
        float ndv = saturate(dot(normalDirection, eye));
        float ndl = saturate(dot(normalDirection, lightDirection));
        float hdv = saturate(dot(halfVector, eye));
        float hdn = saturate(dot(halfVector, normalDirection));
        
        float d;
        {
            float alpha = roughness * roughness;
            float alpha2 = alpha * alpha;
            float t = ((hdn * hdn) * (alpha2 - 1.0) + 1.0);
            d = alpha2 / (PI * t * t);
        }
        
        float g;
        {
            float k = (roughness + 1) * (roughness + 1) / 8.0; //0<<1
            float gl = ndl / (ndl * (1.0 - k) + k);
            float gv = ndv / (ndv * (1.0 - k) + k);
            g = gl * gv;
        }
        
        float f;
        {
            float3 f0 = lerp(0.08 * spec, baseColor.rgb, metallic);
            f = f0 + (1.0 - f0) * pow(1.0 - hdv, 5);
        }
        if (ndv <= 0)
        {
            //ndv = 1;
        }
        specular2 = (d * f * g) / (4.0f * ndv * ndl);
        specular2 = saturate(specular2);
        specular2 *= LightColor.rgb;
    }
        
    //set environment mapping
    {
        float2 envTexCoord;
        envTexCoord.x = atan2(ref.x, ref.z) / (PI * 2);
        envTexCoord.y = acos(ref.y) / PI;
        specular2 += TextureEnvironment.SampleBias(Sampler,
        envTexCoord, roughness * 20).rgb 
        * (1 - roughness) * ao;
    }
    
    
    output.Color.rgb = diffuse.rgb + specular2.rgb +emission.rgb;
    output.Color.a = 1.0;
   
	
    return output;
}
