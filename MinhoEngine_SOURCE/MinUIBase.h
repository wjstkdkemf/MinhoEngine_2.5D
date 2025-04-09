#pragma once
#include "MinEntity.h"

namespace min
{
	using namespace enums;
	class UIBase : public Entity
	{
	public:
		struct Event
		{
			void operator=(std::function<void()> func)
			{
				mEvent = std::move(func);
			}
			void operator()()
			{
				if (mEvent)
					mEvent();
			}
			std::function<void()> mEvent;
		};

		UIBase(eUIType type);
		virtual ~UIBase();

		void Initialize();
		void Active();
		void InActive();
		void Update();
		void LateUpdate();
		void Render();
		void UIClear();
		
		virtual void OnInit();
		virtual void OnActive();
		virtual void OnInActive();
		virtual void OnUpdate();
		virtual void OnLateUpdate();
		virtual void OnRender();
		virtual void OnClear();

		eUIType GetType() { return mType; }
		void SetType(eUIType type) {mType = type ; }
		void SetFullScreen(bool enable) { mbFullScreen = enable; }
		bool IsFullScreen() {return mbFullScreen; }
		Vector3 GetPos() { return mPosition; }
		void SetPos(Vector3 pos) { mPosition = pos; }
		Vector3 GetSize() { return mSize; }
		void SetSize(Vector3 size) { mSize = size; }



	protected:
		Vector3 mPosition;
		Vector3 mSize;
		bool mbMouseOn;

	private:
		eUIType mType;
		bool mbFullScreen;
		bool mbEnabled;
		UIBase* mParent;
	};
}

