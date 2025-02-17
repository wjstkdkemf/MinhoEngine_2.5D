#pragma once
#include "MinFmod.h"
#include "MinResource.h"

namespace min
{
	class AudioClip : public Resource
	{
	public:
		AudioClip();
		virtual ~AudioClip();

		virtual HRESULT Save(const std::wstring path) override;
		virtual HRESULT Load(const std::wstring path) override;

		void Play();
		void Stop();
		void Set3DAttributes(const Vector3 pos);
		void SetLoop(bool loop) { mbLoop = loop; }

	private:
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;
		float mMinDistance;
		float mMaxDistance;
		bool mbLoop;
	};
}

