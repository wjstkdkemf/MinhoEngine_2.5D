#include "MinAnimator.h"
#include "MinResources.h"
#include "MinTexture.h"
#include "rapidjson\\writer.h"
#include "rapidjson\\document.h"
#include "rapidjson\\stringbuffer.h"

namespace min
{
	Animator::Animator()
		: Component(enums::eComponentType::Animator)
		, mAnimations{}
		, mEvents{}
		, mActiveAnimation(nullptr)
		, mbLoop(false)
	{
	}
	Animator::~Animator()
	{
		for (auto& iter : mAnimations)
		{
			delete iter.second;
			iter.second = nullptr;
		}

		for (auto& iter : mEvents)
		{
			delete iter.second;
			iter.second = nullptr;
		}
	}
	void Animator::Initialize()
	{
	}
	void Animator::Update()
	{
		if (mActiveAnimation)
		{
			mActiveAnimation->Update();

			Events* events 
				= FindEvents(mActiveAnimation->GetName());

			if (mActiveAnimation->IsComplete() == true)
			{
				if(events)//->CompleteEvent() != nullptr
					events->CompleteEvent();
				
				if(mbLoop == true)
					mActiveAnimation->Reset();
			}
		}
	}
	void Animator::LateUpdate()
	{
	}
	void Animator::Render()
	{
		if(mActiveAnimation)
			mActiveAnimation->Render();
		/*if (mActiveAnimation)
			mActiveAnimation->Render(hdc);*/
	}
	void Animator::CreateAnimation(const std::wstring& name
		, graphics::Texture* spriteSheet 
		, Vector2 leftTop
		, Vector2 size
		, Vector2 offset
		, UINT spriteLength, float duration)
	{
		Animation* animation = nullptr;
		animation = FindAnimation(name);
		if (animation != nullptr)
			return;

		animation = new Animation();
		animation->SetName(name);
		animation->CreateAnimation(name, spriteSheet
			, leftTop, size, offset, spriteLength, duration);
		animation->SetTexture(spriteSheet);

		animation->SetAnimator(this);

		Events* events = new Events();
		mEvents.insert(std::make_pair(name, events));

		mAnimations.insert(std::make_pair(name, animation));
	}
	//void Animator::CreateAnimation(const std::wstring& name
	//	, const DirectX::Image* spriteSheet//ScratchImage* spriteSheet
	//	, Vector2 leftTop
	//	, Vector2 size
	//	, Vector2 offset
	//	, UINT spriteLength, float duration)
	//{
	//	Animation* animation = nullptr;
	//	animation = FindAnimation(name);
	//	if (animation != nullptr)
	//		return;

	//	animation = new Animation();
	//	animation->SetName(name);
	//	animation->CreateAnimation(name, spriteSheet
	//		, leftTop, size, offset, spriteLength, duration);

	//	animation->SetAnimator(this);

	//	Events* events = new Events();
	//	mEvents.insert(std::make_pair(name, events));

	//	mAnimations.insert(std::make_pair(name, animation));
	//}
	void Animator::CreateAnimationByFolder(const std::wstring& name, const std::vector <std::wstring>& path, Vector2 offset, float duration)
	{
		//Animation* animation = nullptr;
		//animation = FindAnimation(name);
		//if (animation != nullptr)
		//	return;
		//
		//int fileCount = 0;

		//std::filesystem::path fs(path);
		//std::vector<graphics::Texture*> Teximages = {};

		//for (auto& p : std::filesystem::recursive_directory_iterator(fs))
		//{
		//	std::wstring fileName = p.path().filename();
		//	std::wstring fullName = p.path();

		//	graphics::Texture* texture = Resources::Load<graphics::Texture>(fileName, fullName);
		//	Teximages.push_back(texture);
		//	fileCount++;
		//}
		//const DirectX::TexMetadata& metaData = Teximages[0]->GetTextureImage().GetMetadata();

		//UINT sheetWidth = metaData.width * fileCount;
		//UINT sheetHeight = metaData.height;
		//graphics::Texture* spriteSheet = graphics::Texture::Create(name, sheetWidth, sheetHeight);
		//

		//UINT imageWidth = metaData.width;
		//UINT imageHeight = metaData.height;
		//for (size_t i = 0; i < Teximages.size(); i++)
		//{
		//	BitBlt(spriteSheet->GetHdc(), i * imageWidth, 0
		//		, imageWidth, imageHeight
		//		, Teximages[i]->GetHdc(), 0, 0
		//		, SRCCOPY);
		//}

		//CreateAnimation(name, spriteSheet, Vector2::Zero, Vector2(imageWidth, imageHeight), offset, fileCount, duration);

		//std::wstring ext = path.substr(path.find_last_of(L".") + 1);

		//if (ext == L".dds" || ext == L".DDS")
		//{
		//	if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
		//		return S_FALSE;
		//}
		//else if (ext == L".tga" || ext == L".TGA")
		//{
		//	if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
		//		return S_FALSE;
		//}
		//else // WIC (png, jpg, jpeg, bmp )
		//{
		//	if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
		//		return S_FALSE;
		//}



		DirectX::ScratchImage spriteSheet;
		DirectX::ScratchImage frame;
		DirectX::TexMetadata metadata;

		LoadFromWICFile(path[0].c_str(), WIC_FLAGS::WIC_FLAGS_NONE, &metadata, frame);

		spriteSheet.Initialize2D(metadata.format, metadata.width * path.size(), metadata.height, 1, 1);

		for (size_t i = 0; i < path.size(); ++i) {
			LoadFromWICFile(path[i].c_str(), DirectX::WIC_FLAGS_NONE, nullptr, frame);
			DirectX::CopyRectangle(*frame.GetImages(), DirectX::Rect(0, 0, metadata.width, metadata.height),
				*spriteSheet.GetImages(), DirectX::TEX_FILTER_DEFAULT,
				i * metadata.width, 0);
		}


		//CreateAnimation(name, spriteSheet.GetImages() , Vector2::Zero, Vector2(metadata.width, metadata.height), offset, path.size(), duration);
	}
	Animation* Animator::FindAnimation(const std::wstring& name)
	{
		auto iter = mAnimations.find(name);
		if(iter == mAnimations.end())
			return nullptr;

		return iter->second;
	}
	void Animator::PlayAnimation(const std::wstring& name, bool loop)
	{
		Animation* animation = FindAnimation(name);
		if (animation == nullptr)
			return;

		if (mActiveAnimation)
		{
			Events* currentEvents
				= FindEvents(mActiveAnimation->GetName());
			if (currentEvents)
				currentEvents->EndEvent();
		}
		Events* nextEvents
			= FindEvents(animation->GetName());
		if(nextEvents)
			nextEvents->StartEvent();

		mActiveAnimation = animation;
		mActiveAnimation->Reset();
		mbLoop = loop;
	}
	Animator::Events* Animator::FindEvents(const std::wstring& name)
	{
		auto iter = mEvents.find(name);
		if(iter == mEvents.end())
			return nullptr;

		return iter->second;
	}
	std::function<void()>& Animator::GetStartEvent(const std::wstring& name)
	{
		// TODO: 여기에 return 문을 삽입합니다.
		Events* events = FindEvents(name);
		return events->StartEvent.mEvent;
	}
	std::function<void()>& Animator::GetCompleteEvent(const std::wstring& name)
	{
		// TODO: 여기에 return 문을 삽입합니다.
		Events* events = FindEvents(name);
		return events->CompleteEvent.mEvent;
	}
	std::function<void()>& Animator::GetEndEvent(const std::wstring& name)
	{
		// TODO: 여기에 return 문을 삽입합니다.
		Events* events = FindEvents(name);
		return events->EndEvent.mEvent;
	}
}
