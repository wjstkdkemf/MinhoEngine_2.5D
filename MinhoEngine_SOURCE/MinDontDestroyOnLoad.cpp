#include "MinDontDestroyOnLoad.h"


namespace min
{
	DontDestroyOnLoad::DontDestroyOnLoad()
	{
	}
	DontDestroyOnLoad::~DontDestroyOnLoad()
	{
	}
	void DontDestroyOnLoad::Initialize()
	{
		Scene::Initialize();
	}
	void DontDestroyOnLoad::Update()
	{
		Scene::Update();
	}
	void DontDestroyOnLoad::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void DontDestroyOnLoad::Rander(HDC hdc)
	{
		Scene::Rander(hdc);
	}
	void DontDestroyOnLoad::OnEnter()
	{
		Scene::OnEnter();
	}
	void DontDestroyOnLoad::OnExit()
	{
		Scene::OnExit();
	}
}