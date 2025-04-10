#pragma once
#include "MinUIBase.h"
#include "MinTexture.h"
#include "MinMesh.h"
#include "MinMaterial.h"
#include "MinTransform.h"

namespace min
{
	class UIHUd : public UIBase
	{
	public:
		struct Vertex {
			XMFLOAT3 position;  // (x, y, z) ? ȭ�� �ȼ� ���� ��ǥ
			XMFLOAT2 uv;        // �ؽ�ó ��ǥ (0~1)
		};

		UIHUd();
		~UIHUd();

		virtual void OnInit() override;
		virtual void OnActive() override;
		virtual void OnInActive() override;
		virtual void OnUpdate() override;
		virtual void OnLateUpdate() override;
		virtual void OnRender() override;
		virtual void OnClear() override;

	private:
		Transform* mHptr;
		graphics::Texture* mSprite;
		Material* mMaterial;
		Mesh* mMesh;
	};
}

