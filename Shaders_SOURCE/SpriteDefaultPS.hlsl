#include "Samplers.hlsli"
#include "Textures.hlsli"

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
    float4 color = sprite.Sample(pointSampler, input.uv);
    
    if (color.r == 1.0f && color.g == 0.0f && color.b == 1.0f)
        color.a = 0.0f;
    
    color.rgb *= color.a;
    
    clip(color.a - 0.01f);
    
    return color;
}