#include "Samplers.hlsli"
#include "Textures.hlsli"
#include "ConstantBuffers.hlsli"

struct VSInput
{
    float3 pos : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};
struct VSOutput
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};
float4 main(VSOutput input) : SV_Target
{
    float4 color = sprite.Sample(anisotropicSampler, input.uv);
    
    if (isSelect)
    {
        color.rgb = lerp(color.rgb, float3(1, 0, 0), 0.4);
    }
    
    return color;
}