#include "MinAudioClip.h"


namespace min
{
	AudioClip::AudioClip()
		:Resource(enums::eResourceType::AudioClip)
		, mSound(nullptr)
		, mChannel(nullptr)
		, mMinDistance(1.0f)
		, mMaxDistance(1000.0f)
		, mbLoop(false)
	{
	}
	AudioClip::~AudioClip()
	{
		mSound->release();
		mSound = nullptr;
	}
	HRESULT AudioClip::Load(const std::wstring path)
	{
		std::string cPath(path.begin(), path.end());
		if (!Fmod::CreateSound(cPath, &mSound))
			return S_FALSE;

		mSound->set3DMinMaxDistance(mMinDistance, mMaxDistance);

		return E_NOTIMPL;
	}
	void AudioClip::Play()
	{
		if (mbLoop)
			mSound->setMode(FMOD_LOOP_NORMAL);
		else
			mSound->setMode(FMOD_LOOP_OFF);

		Fmod::SoundPlay(mSound, &mChannel);
	}
	void AudioClip::Stop()
	{
		mChannel->stop();
	}
	void AudioClip::Set3DAttributes(const Vector2 pos)
	{
		FMOD_VECTOR fmodvel = { 0.0f, 0.0f, 0.0f };
		FMOD_VECTOR fmodlistenerpos = { 0.0f, 0.0f, 0.3f };//pos.x, pos.y

		mChannel->set3DAttributes(&fmodlistenerpos, &fmodvel);
	}
}
