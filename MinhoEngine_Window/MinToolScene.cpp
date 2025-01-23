#include "MinToolScene.h"
#include "MinObject.h"
#include "MinResources.h"
#include "MinTexture.h"
#include "MinCamera.h"
#include "MinRenderer.h"
#include "Mininput.h"
#include "MinTile.h"
#include "MinTilemapRender.h"
#include "MinCameraScript.h"


namespace min
{

	ToolScene::ToolScene()
		:mTiles{}
	{
	}

	ToolScene::~ToolScene()
	{
	}

	void ToolScene::Initialize()
	{
		GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(344.0f, 442.0f));
		Camera* cameraComp = camera->AddComponent<Camera>();
		CameraScript* camerastr = camera->AddComponent<CameraScript>();
		renderer::mainCamera = cameraComp;

		//Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
		//TilemapRender* tmr = tile->AddComponent<TilemapRender>();
		//tmr->SetTexture(Resources::Find<graphcis::Texture>(L"SpringFloor"));
		//mTiles.push_back(tile);

		Scene::Initialize();
	}

	void ToolScene::Update()
	{
		Scene::Update();
	}

	void ToolScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (input::GetKeyDown(eKeyCode::Lbutton))
		{
			Vector2 pos = input::GetMousePosition();

			pos = renderer::mainCamera->CalculateMousePosition(pos);

			if (pos.x > 0.0f && pos.y > 0.0f)
			{
				int idxX = pos.x / TilemapRender::TileSize.x;
				int idxY = pos.y / TilemapRender::TileSize.y;

				Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
				TilemapRender* tmr = tile->AddComponent<TilemapRender>();

				tmr->SetTexture(Resources::Find<graphcis::Texture>(L"SpringFloor"));
				tmr->SetIndex(TilemapRender::SelectedIndex);

				tile->SetIndexPosition(idxX, idxY);
				mTiles.push_back(tile);
			}
		}

		if (input::GetKeyDown(eKeyCode::S))
		{
			Save();
		}
		if (input::GetKeyDown(eKeyCode::L))
		{
			Load();
		}
	}

	void ToolScene::Rander(HDC hdc)
	{
		Scene::Rander(hdc);


		for (size_t i = 0; i < 50; i++)
		{
			Vector2 pos = renderer::mainCamera->CalculatePosition(Vector2(TilemapRender::TileSize.x * i, 0.0f));

			MoveToEx(hdc, pos.x, 0, NULL);
			LineTo(hdc, pos.x, 1000);
		}

		for (size_t i = 0; i < 50; i++)
		{
			Vector2 pos = renderer::mainCamera->CalculatePosition(Vector2(0.0f, TilemapRender::TileSize.y * i));

			MoveToEx(hdc, 0, pos.y, NULL);
			LineTo(hdc, 1000, pos.y);
		}
	}

	void ToolScene::OnEnter()
	{
		Scene::OnEnter();
	}

	void ToolScene::OnExit()
	{
		Scene::OnExit();
	}

	void ToolScene::Save()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"Tile\0*.tile*\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"wb");

		for (Tile* tile : mTiles)
		{
			TilemapRender* tmr = tile->GetComponent<TilemapRender>();
			Transform* tr = tile->GetComponent<Transform>();

			Vector2 sourceIndex = tmr->GetIndex();
			Vector2 position = tr->GetPosition();
			
			int x = (int)sourceIndex.x;
			fwrite(&x, sizeof(int), 1, pFile);
			int y = (int)sourceIndex.y;
			fwrite(&y, sizeof(int), 1, pFile);

			x = (int)position.x;
			fwrite(&x, sizeof(int), 1, pFile);
			y = (int)position.y;
			fwrite(&y, sizeof(int), 1, pFile);
		}
		fclose(pFile);
	}

	void ToolScene::Load()
	{
		OPENFILENAME ofn = {};

		wchar_t szFilePath[256] = {};

		ZeroMemory(&ofn, sizeof(ofn));
		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = NULL;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFile[0] = '\0';
		ofn.nMaxFile = 256;
		ofn.lpstrFilter = L"All\0*.*\0Tile\0*.tile*\0";
		ofn.nFilterIndex = 1;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFileTitle = 0;
		ofn.lpstrInitialDir = NULL;
		ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

		if (false == GetSaveFileName(&ofn))
			return;

		FILE* pFile = nullptr;
		_wfopen_s(&pFile, szFilePath, L"rb");

		while (true)
		{
			int idxX = 0;
			int idxY = 0;

			int posX = 0;
			int posY = 0;

			if (fread(&idxX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&idxY, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&posX, sizeof(int), 1, pFile) == NULL)
				break;
			if (fread(&posY, sizeof(int), 1, pFile) == NULL)
				break;
			
			Tile* tile = object::Instantiate<Tile>(eLayerType::Tile, Vector2(posX,posY));
			TilemapRender* tmr = tile->AddComponent<TilemapRender>();
			tmr->SetTexture(Resources::Find<graphcis::Texture>(L"SpringFloor"));
			tmr->SetIndex(Vector2(idxX,idxY));

			mTiles.push_back(tile);
		}

		fclose(pFile);
	}
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		POINT mousePos = {};
		GetCursorPos(&mousePos);
		ScreenToClient(hWnd, &mousePos);

		min::math::Vector2 mousePosition;
		mousePosition.x = mousePos.x;
		mousePosition.y = mousePos.y;

		int idxX = mousePosition.x / min::TilemapRender::OriginTileSize.x;
		int idxY = mousePosition.y / min::TilemapRender::OriginTileSize.y;

		min::TilemapRender::SelectedIndex = Vector2(idxX, idxY);
	}
	break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);


		min::graphcis::Texture* texture
			= min::Resources::Find<min::graphcis::Texture>(L"SpringFloor");

		TransparentBlt(hdc
			, 0, 0
			, texture->GetWidth()
			, texture->GetHeight()
			, texture->GetHdc()
			, 0, 0
			, texture->GetWidth()
			, texture->GetHeight()
			, RGB(255, 0, 255));


		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
