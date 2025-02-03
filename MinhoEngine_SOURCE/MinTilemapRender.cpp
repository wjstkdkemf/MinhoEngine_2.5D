#include "MinTilemapRender.h"
#include "minGameObject.h"
#include "MinTransform.h"
#include "MinTexture.h"
#include "MinRenderer.h"

namespace min
{
    Vector2 TilemapRender::TileSize = Vector2::One;
    Vector2 TilemapRender::OriginTileSize = Vector2::One;
    Vector2 TilemapRender::SelectedIndex = Vector2(-1.0f, -1.0f);

    TilemapRender::TilemapRender()
        : Component(enums::eComponentType::SpriteRenderer)
        , mTileSize(16.0f, 16.0f)
        , mTexture(nullptr)
        , mSize(3.0f, 3.0f)
        , mIndex(0, 0)
    {
        TileSize = mTileSize * mSize;
        OriginTileSize = mTileSize;
    }
    TilemapRender::~TilemapRender()
    {
    }


    void TilemapRender::Initialize()
    {
    }
    void TilemapRender::Update()
    {
    }
    void TilemapRender::LateUpdate()
    {
    }
    void TilemapRender::Render(HDC hdc)
    {
        if (mTexture == nullptr)
            assert(false);

        Transform* tr = GetOwner()->GetComponent<Transform>();
        Vector2 pos = tr->GetPosition();
        float rot = tr->GetRoation();
        Vector2 scale = tr->GetScale();

        pos = renderer::mainCamera->CalculatePosition(pos);
        if (mTexture->GetTextureType()
            == graphics::Texture::eTextureType::Bmp)
        {
            if (mTexture->IsAlpha())
            {
                BLENDFUNCTION func = {};
                func.BlendOp = AC_SRC_OVER;
                func.BlendFlags = 0;
                func.AlphaFormat = AC_SRC_ALPHA;
                func.SourceConstantAlpha = 255; // 0(transparent) ~ 255(Opaque)

                AlphaBlend(hdc
                    , pos.x, pos.y
                    , mTileSize.x * mSize.x * scale.x
                    , mTileSize.y * mSize.y * scale.y
                    , mTexture->GetHdc()
                    , mIndex.x * mTileSize.x, mIndex.y * mTileSize.y
                    , mTileSize.x
                    , mTileSize.y
                    , func);
            }
            else
            {
                TransparentBlt(hdc
                    , pos.x, pos.y
                    , mTileSize.x * mSize.x * scale.x
                    , mTileSize.y * mSize.y * scale.y
                    , mTexture->GetHdc()
                    , mIndex.x * mTileSize.x, mIndex.y * mTileSize.y
                    , mTileSize.x
                    , mTileSize.y
                    , RGB(255, 0, 255));
            }
        }
        else if(mTexture->GetTextureType()
            == graphics::Texture::eTextureType::Png)
        {
            Gdiplus::ImageAttributes imgAtt = {};
            imgAtt.SetColorKey(Gdiplus::Color(230, 230, 230), Gdiplus::Color(255, 255, 255));

            Gdiplus::Graphics graphcis(hdc);

            graphcis.TranslateTransform(pos.x, pos.y);
            graphcis.RotateTransform(rot);
            graphcis.TranslateTransform(-pos.x, -pos.y);

            graphcis.DrawImage(mTexture->GetImage()
                , Gdiplus::Rect
                (
                    pos.x, pos.y
                    , mTexture->GetWidth() * mSize.x * scale.x
                    , mTexture->GetHeight() * mSize.y * scale.y
                )
                , 0, 0
                , mTexture->GetWidth(), mTexture->GetHeight()
                , Gdiplus::UnitPixel
                , nullptr/*&imgAtt*/);
        }
    }
}