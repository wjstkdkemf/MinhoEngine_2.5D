#include "MinUIBase.h"
#include "MinGraphics.h"
#include "MinUIManager.h"
#include "MinRenderer.h"

namespace min
{
    UIBase::UIBase(eUIType type)
        : mType(type)
        , mbMouseOn(false)
    {
    }
    UIBase::~UIBase()
    {
    }
    void UIBase::Initialize()
    {
        OnInit();
    }
    void UIBase::Active()
    {
        mbEnabled = true;
        OnActive();
    }
    void UIBase::InActive()
    {
        mbEnabled = false;
        OnInActive();
    }
    void UIBase::Update()
    {
        if (mbEnabled == true)
            OnUpdate();
    }
    void UIBase::LateUpdate()
    {
        if (mbEnabled == true)
            OnLateUpdate();
    }
    void UIBase::Render()
    {
        if (mbEnabled == true)
            OnRender();
    }
    void UIBase::UIClear()
    {
        OnClear();
    }
    void UIBase::OnInit()
    {
    }
    void UIBase::OnActive()
    {
    }
    void UIBase::OnInActive()
    {
    }
    void UIBase::OnUpdate()
    {
    }
    void UIBase::OnLateUpdate()
    {
    }
    void UIBase::OnRender()
    {
    }
    void UIBase::OnClear()
    {
    }
    void UIBase::CreateUIConstantBuffer()
    {
        graphics::UICB cbData = {};
        cbData.view = UIManager::mUIViewMatrix;
        cbData.projection = UIManager::mUIMatrix;

        graphics::ConstantBuffer* cb = renderer::constantBuffers[CBSLOT_UI];

        cb->SetData(&cbData);
        cb->Bind(eShaderStage::All);
    }
}
