#include "MinBoxCollider2D.h"
#include "MinTransform.h"
#include "minGameObject.h"
#include "MinRenderer.h"
#include "MinCamera.h"
#include "MinSkillManager.h"
#include "MinScript.h"
#include "MinBoxCollider2DOBB.h"

#include "DirectXColors.h"
#include "DirectXMath.h"

namespace min
{
	BoxCollider2D::BoxCollider2D()
		:Collider(eColliderType::Rect2DAABB)
	{
	}
	BoxCollider2D::~BoxCollider2D()
	{
	}
	void BoxCollider2D::Initialize()
	{
        {
            void const* shaderByteCode;
            size_t byteCodeLength;

            renderer::batchEffect->GetVertexShaderBytecode(&shaderByteCode, &byteCodeLength);

            mInputLayout.CreateInputLayout_Const(VertexPositionColor::InputElementCount
                , VertexPositionColor::InputElements
                , shaderByteCode
                , byteCodeLength);
        }
	}
	void BoxCollider2D::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		mBoxCollider2D.Center = tr->GetPosition();
		
        renderer::batchEffect->SetProjection(Camera::GetGpuProjectionMatrix());
        renderer::batchEffect->SetView(Camera::GetGpuViewMatrix());
	}
	void BoxCollider2D::LateUpdate()
	{
        BoxCollider2D* Collider = GetOwner()->GetComponent<BoxCollider2D>();
        Transform* fstr = GetOwner()->GetComponent<Transform>();

        if (GetOwner()->GetName() == L"Player")
        {
            Collider->GetBoxCollider2D().Extents = XMFLOAT3(fstr->GetScale().x / 7.0f, fstr->GetScale().y / 4.5f, 0);
        }
        else
        {
            Collider->GetBoxCollider2D().Extents = XMFLOAT3(fstr->GetScale().x / 2.0f, fstr->GetScale().y / 2.0f, 0);
            
        }
	}
	void BoxCollider2D::Render()
	{
        DrawAabb(mBoxCollider2D, Colors::White);
	}
	bool BoxCollider2D::Intersects(Collider* other)
	{
		if (other->GetColType() == eColliderType::Rect2DAABB)
		{
			if (mBoxCollider2D.Intersects(((BoxCollider2D*)other)->GetBoxCollider2D()))
				return true;
		}
        else if (other->GetColType() == eColliderType::Rect2DOBB)
        {
            if (mBoxCollider2D.Intersects(((BoxCollider2DOBB*)other)->GetBoxCollider2D()))
                return true;
        }
		return false;
	}

    ContainmentType BoxCollider2D::Contain(Collider* other)
    {
        if (other->GetColType() == eColliderType::Rect2DAABB)
        {
            return (mBoxCollider2D.Contains(((BoxCollider2D*)other)->GetBoxCollider2D()));
        }
        return ContainmentType::DISJOINT;
    }

    void BoxCollider2D::OnCollisionEnter(Collider* other)
    {
        if (other->GetName() == L"Floor" || other->GetName() == L"Shadow")
            return;

        Script* script = GetOwner()->GetComponent<Script>();
        script->OnCollisionEnter(other);
    }

    void BoxCollider2D::OnCollisionStay(Collider* other)
    {
    }

    void BoxCollider2D::OnCollisionExit(Collider* other)
    {
    }

    void BoxCollider2D::DrawAabb(BoundingBox box, FXMVECTOR color)
    {
        XMMATRIX matWorld = XMMatrixScaling(box.Extents.x, box.Extents.y, box.Extents.z);
        XMVECTOR position = XMLoadFloat3(&box.Center);
        matWorld.r[3] = XMVectorSelect(matWorld.r[3], position, g_XMSelect1110);

        DrawCube(matWorld, color);
    }

    void BoxCollider2D::DrawCube(CXMMATRIX mWorld, FXMVECTOR color)
    {
        static const XMVECTOR s_verts[8] =
        {
            { -1, -1, -1, 0 },
            { 1, -1, -1, 0 },
            { 1, -1, 1, 0 },
            { -1, -1, 1, 0 },
            { -1, 1, -1, 0 },
            { 1, 1, -1, 0 },
            { 1, 1, 1, 0 },
            { -1, 1, 1, 0 }
        };
        static const WORD s_indices[] =
        {
            0, 1,
            1, 2,
            2, 3,
            3, 0,
            4, 5,
            5, 6,
            6, 7,
            7, 4,
            0, 4,
            1, 5,
            2, 6,
            3, 7
        };

        VertexPositionColor verts[8];
        for (int i = 0; i < 8; ++i)
        {
            XMVECTOR v = XMVector3Transform(s_verts[i], mWorld);
            XMStoreFloat3(&verts[i].position, v);
            XMStoreFloat4(&verts[i].color, color);
        }

        auto context = GetDevice()->GetID3D11DeviceContext().Get();
        renderer::batchEffect->Apply(context);
        context->IASetInputLayout(mInputLayout.GetInputLayout());

        renderer::primitiveBatch->Begin();

        renderer::primitiveBatch->DrawIndexed(D3D11_PRIMITIVE_TOPOLOGY_LINELIST, s_indices, _countof(s_indices), verts, 8);

        renderer::primitiveBatch->End();
    }
}
/*
void DrawAabb( const BoundingBox& box, FXMVECTOR color )
{
	XMMATRIX matWorld = XMMatrixScaling( box.Extents.x, box.Extents.y, box.Extents.z );
	XMVECTOR position = XMLoadFloat3( &box.Center );
	matWorld.r[3] = XMVectorSelect( matWorld.r[3], position, g_XMSelect1110 );

	DrawCube( matWorld, color );
}
*/


/*
std::unique_ptr<CommonStates>                           g_States;
std::unique_ptr<BasicEffect>                            g_BatchEffect;
std::unique_ptr<PrimitiveBatch<VertexPositionColor>>    g_Batch;
*/