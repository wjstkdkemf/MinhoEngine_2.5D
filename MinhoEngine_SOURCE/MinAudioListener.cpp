#include "MinAudioListener.h"
#include "MinTransform.h"
#include "minGameObject.h"
#include "MinFmod.h"

namespace min
{
	AudioListener::AudioListener()
		:Component(eComponentType::AudioListener)
	{
	}
	AudioListener::~AudioListener()
	{
	}
	void AudioListener::Initialize()
	{
	}
	void AudioListener::Update()
	{
	}
	void AudioListener::LateUpdate()
	{
		Transform* tr = nullptr;
		tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos;

		Fmod::Set3DListenerAttributes(pos);
	}
	void AudioListener::Render()
	{
	}
}