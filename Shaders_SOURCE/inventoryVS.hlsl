#include "ConstantBuffers.hlsli"


struct VSInput
{
    float3 pos : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct VSINSTANCE
{
    float2 offset : OFFSET;
    float4 color : COLOR;
};

struct VSOutput
{
    float4 pos : SV_Position;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

VSOutput main(VSInput input, VSINSTANCE Inst)
{
    VSOutput output = (VSOutput) 0.0f;
    
    float4 pos = float4(input.pos.x + Inst.offset.x, input.pos.y + Inst.offset.y, input.pos.z, 1.0f);
    float4 viewPos = mul(pos, view);
    float4 projPos = mul(viewPos, projection);
    
    
    output.pos = projPos;
    output.color = input.color;
    output.uv = input.uv;
    return output;
}