
cbuffer Transform : register(b0)
{
    row_major matrix WorldMatrix;
    row_major matrix ViewMatrix;
    row_major matrix ProjectionMatrix;
    
}

cbuffer Animation : register(b1)
{
    float offsetX;
    float offsetY;
    float sizeX;
    float sizeY;
    float textureSizeX;
    float textureSizeY;
    float useAni;
}