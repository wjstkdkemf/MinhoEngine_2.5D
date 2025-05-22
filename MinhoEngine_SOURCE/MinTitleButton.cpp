#include "MinTitleButton.h"
#include "MinResources.h"
#include "MinTransform.h"
#include "MinRenderer.h"
#include "minGameObject.h"
#include "MinUIManager.h"
#include "MinGraphics.h"
#include "Mininput.h"
#include "MinTime.h"
#include "MinApplication.h"
#include "MinSceneManager.h"


extern min::Application application;

namespace min
{
	TitleButton::TitleButton()
		: UIBase(enums::eUIType::TitleButton)
		, mSprite(nullptr)
		, mMainTitleSprite(nullptr)
		, mMaterial(nullptr)
		, mMesh(nullptr)
		, mTitlenfo()
		, mMainTitleMesh(nullptr)
		, mMainTitleMaterial(nullptr)
		, mBeforeResolutionX(1600.0f)
		, mBeforeResolutionY(900.0f)
	{
	}
	TitleButton::~TitleButton()
	{
	}
	void TitleButton::OnInit()
	{
		if(mTitlenfo.size() == 0)
		{

			mMesh = Resources::Find<Mesh>(L"TitleUIMesh"); //추후 수정 예정
			mMainTitleMesh = Resources::Find<Mesh>(L"TitleButtonMesh");

			mSprite = Resources::Find<graphics::Texture>(L"TitleMenu"); // Resources::Find<graphics::Texture>(L"Floor_2")
			mMainTitleSprite = Resources::Find<graphics::Texture>(L"BeforeSelect"); // BeforeSelect AfterSelect

			mMaterial = Resources::Find<Material>(L"UIMaterial");
			mMainTitleMaterial = Resources::Find<Material>(L"TitleMaterial");

			mTitlenfo.resize(3); // 버튼 갯수 (스타트 , 로드 , 종료)
			CreateButtonInfomation();
		}

		//if (mBeforeResolutionX != (float)application.GetWindow().GetWidth() || mBeforeResolutionY != (float)application.GetWindow().GetHeight())
			//ResizeSkillPosition();

		/*
		mMesh = Resources::Find<Mesh>(L"UIMesh"); //추후 수정 예정
		mSprite = Resources::Find<graphics::Texture>(L"HPBAR");//HPBAR
		mMaterial = Resources::Find<Material>(L"UIMaterial");
		
		*/

	}
	void TitleButton::OnActive()
	{
	}
	void TitleButton::OnInActive()
	{
	}
	void TitleButton::OnUpdate()
	{
		if (mBeforeResolutionX != (float)application.GetWindow().GetWidth() || mBeforeResolutionY != (float)application.GetWindow().GetHeight())
			ResizeButtonPosition();

		Vector2 mousePos = input::GetMousePosition();

		for(int i = 0 ; i < mTitlenfo.size() ; i ++)
		{
			if (mTitlenfo[i].TitlePos.x - 50.0f <= mousePos.x && mousePos.x <= mTitlenfo[i].TitlePos.x + 50.0f
				&& mTitlenfo[i].TitlePos.y - 25.0f <= mousePos.y && mousePos.y <= mTitlenfo[i].TitlePos.y + 25.0f)
			{
				mTitlenfo[i].mTouch = true;
			}
			else
			{
				mTitlenfo[i].mTouch = false;
			}

			if (input::GetKeyDown(eKeyCode::LButton))
			{
				if (mTitlenfo[i].mTouch == true)
				{
					mOnClick(mTitlenfo[i].ButtonName);// 추후에 함수 포인터로 수정할 가능성 높음
				}
			}
		}
	}
	void TitleButton::OnLateUpdate()
	{
	}
	void TitleButton::OnRender()
	{
		CreateUIConstantBuffer();

		PrintBGTitle();
		PrintButton();
	}
	void TitleButton::OnClear()
	{
	}
	void TitleButton::PrintButton()
	{
		for (int i = 0; i < mTitlenfo.size(); i++)
		{
			if (mTitlenfo[i].ButtonName == L"")
				continue;

			//mMainTitleSprite = Resources::Find<graphics::Texture>(mTitlenfo[i].ButtonName); // 추후 start , load 와 같은 버튼을 별개로 구현해서 출력하기 위함
			if (mTitlenfo[i].mTouch == true)
				mMainTitleSprite = Resources::Find<graphics::Texture>(L"AfterSelect");
			else
				mMainTitleSprite = Resources::Find<graphics::Texture>(L"BeforeSelect");

			ConstantBufferSetting(i);

			Mesh::MeshData me = mMesh->GetMeshData();

			if (mMainTitleMesh)
				mMainTitleMesh->Bind();

			if (mMainTitleMaterial)
				mMainTitleMaterial->BindShader();

			//if (mSkillInfo[i].mTouch)
			//{
			//	SkillSelecttConstantBufferSetting(i, 10.0f);
			//	ID3D11ShaderResourceView* nullSRV[1] = { nullptr };
			//	graphics::GetDevice()->SetShaderResource(eShaderStage::PS, (UINT)eTextureType::Sprite, nullSRV);
			//	graphics::GetDevice()->DrawIndexed(mSkillMesh->GetIndexCount(), 0, 0);
			//	SkillConstantBufferSetting(i);
			//}

			if (mMainTitleSprite)
				mMainTitleSprite->Bind(eShaderStage::PS, (UINT)eTextureType::Sprite);

			if (mMainTitleMesh)
				graphics::GetDevice()->DrawIndexed(mMainTitleMesh->GetIndexCount(), 0, 0);


			PrintFont(i);
		}
	}
	void TitleButton::PrintBGTitle()
	{
		if (mMesh)
			mMesh->Bind();

		if (mMaterial)
			mMaterial->BindShader();

		if (mSprite)
			mSprite->Bind(eShaderStage::PS, (UINT)eTextureType::Sprite);

		if (mMesh)
			graphics::GetDevice()->DrawIndexed(mMesh->GetIndexCount(), 0, 0);
	}
	void TitleButton::CreateButtonInfomation()
	{
		for (UINT i = 0; i < 3; i++)
		{
			mTitlenfo[i].offset.x = 0;
			mTitlenfo[i].offset.y = 65.0f * i;
			mTitlenfo[i].TitlePos.x = 800.0f;
			mTitlenfo[i].TitlePos.y = 615.0f + (65.0f * i);
		}
		mTitlenfo[0].ButtonName = L"Start";//Start
		mTitlenfo[1].ButtonName = L"Load";//Load
		mTitlenfo[2].ButtonName = L"Exit";//Exit
	}
	void TitleButton::mOnClick(std::wstring name)
	{
		if(name == L"Start")
			SceneManager::LoadScene(L"PlayScene");
	}
	void TitleButton::ConstantBufferSetting(UINT Num)
	{
		graphics::TitleCB cbData = {};
		cbData.offsetX = mTitlenfo[Num].offset.x;
		cbData.offsetY = mTitlenfo[Num].offset.y;
		cbData.isfocus = false;

		graphics::ConstantBuffer* cb = renderer::constantBuffers[CBSLOT_Title];

		cb->SetData(&cbData);
		cb->Bind(eShaderStage::All);
	}
	void TitleButton::ResizeButtonPosition()
	{
		float ScaleX = (float)application.GetWindow().GetWidth() / mBeforeResolutionX;
		float ScaleY = (float)application.GetWindow().GetHeight() / mBeforeResolutionY;

		for (ButtonInfo& Title_Info : mTitlenfo)
		{
			Title_Info.TitlePos.x *= ScaleX;
			Title_Info.TitlePos.y *= ScaleY;
		}
		mBeforeResolutionX = (float)application.GetWindow().GetWidth();
		mBeforeResolutionY = (float)application.GetWindow().GetHeight();
	}
	void TitleButton::PrintFont(UINT num)
	{
		float screenX = mTitlenfo[num].TitlePos.x - 30.0f ; // 위치 맞추기
		float screenY = mTitlenfo[num].TitlePos.y - 20.0f; // Direct2D는 Y축이 아래로 증가하므로 변환 필요


		// 3. Direct2D 렌더링 시작
		GetDevice()->GetID2D1RenderTarget()->BeginDraw();
		GetDevice()->GetID2D1RenderTarget()->SetTransform(D2D1::Matrix3x2F::Identity()); // 기본 변환 초기화

		// 텍스트 그리기
		std::wstring text = mTitlenfo[num].ButtonName;
		D2D1_RECT_F textRect = D2D1::RectF(screenX, screenY, screenX + 100, screenY + 50); // 적절한 크기 설정

		GetDevice()->GetID2D1RenderTarget()->DrawText(
			text.c_str(),
			(UINT32)text.length(),
			GetDevice()->GetIDWriteTextFormat().Get(),
			textRect,
			GetDevice()->GetID2D1SolidColorBrush().Get()
		);

		// 4. Direct2D 렌더링 종료
		GetDevice()->GetID2D1RenderTarget()->EndDraw();
	}
}