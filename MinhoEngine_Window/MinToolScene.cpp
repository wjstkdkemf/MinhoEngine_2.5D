#include "MinToolScene.h"
#include "MinObject.h"
#include "MinResources.h"
#include "MinTexture.h"
#include "MinCamera.h"
#include "MinRenderer.h"
#include "Mininput.h"
#include "MinTile.h"
#include "MinTilemapRender.h"

min::ToolScene::ToolScene()
{
}

min::ToolScene::~ToolScene()
{
}

void min::ToolScene::Initialize()
{
	GameObject* camera = object::Instantiate<GameObject>(enums::eLayerType::Particle, Vector2(344.0f, 442.0f));
	Camera* cameraComp = camera->AddComponent<Camera>();
	renderer::mainCamera = cameraComp;

	Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
	TilemapRender* tmr = tile->AddComponent<TilemapRender>();
	tmr->SetTexture(Resources::Find<graphcis::Texture>(L"SpringFloor"));

	Scene::Initialize();
}

void min::ToolScene::Update()
{
	Scene::Update();
}

void min::ToolScene::LateUpdate()
{
	Scene::LateUpdate();

	if (input::GetKeyDown(eKeyCode::Lbutton))
	{
		Vector2 pos = input::GetMousePosition();

		
		int idxX = pos.x / TilemapRender::TileSize.x;
		int idxY = pos.y / TilemapRender::TileSize.y;

		Tile* tile = object::Instantiate<Tile>(eLayerType::Tile);
		TilemapRender* tmr = tile->AddComponent<TilemapRender>();
		tmr->SetTexture(Resources::Find<graphcis::Texture>(L"SpringFloor"));

		tile->SetPosition(idxX, idxY);
	}
}

void min::ToolScene::Rander(HDC hdc)
{
	Scene::Rander(hdc);

	for (size_t i = 0; i < 50; i++)
	{
		MoveToEx(hdc, TilemapRender::TileSize.x * i, 0, NULL);
		LineTo(hdc, TilemapRender::TileSize.x * i, 1000);
	}

	for (size_t i = 0; i < 50; i++)
	{
		MoveToEx(hdc, 0, TilemapRender::TileSize.y * i, NULL);
		LineTo(hdc, 1000, TilemapRender::TileSize.y * i);
	}
}

void min::ToolScene::OnEnter()
{
	Scene::OnEnter();
}

void min::ToolScene::OnExit()
{
	Scene::OnExit();
}

LRESULT CALLBACK WndTileProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_LBUTTONDOWN:
    {
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
