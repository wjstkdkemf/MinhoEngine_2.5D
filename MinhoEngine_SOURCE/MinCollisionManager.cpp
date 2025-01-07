#include "MinCollisionManager.h"
#include "MinScene.h"
#include "MinSceneManager.h"
#include "minGameObject.h"
#include "MinCollider.h"

namespace min
{
    std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};

    void CollisionManager::Initialize()
    {
    }
    void CollisionManager::Update()
    {
        Scene* scene = SceneManager::GetActiveScene();
        for (UINT row = 0; row < (UINT)eLayerType::Max; row++)
        {
            for (UINT col = 0; col < (UINT)eLayerType::Max; col++)
            {
                if (mCollisionLayerMatrix[row][col] == true)
                {
                    LayerCollision(scene, (eLayerType)row, (eLayerType)col);
                }
            }

        }
    }
    void CollisionManager::LateUpdate()
    {
    }
    void CollisionManager::Render(HDC hdc)
    {
    }
    void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
    {
        int row = 0;
        int col = 0;

        if (left <= right)
        {
            row = (UINT)left;
            col = (UINT)right;
        }
        else
        {
            row = (UINT)right;
            col = (UINT)left;
        }

        mCollisionLayerMatrix[row][col] = enable;
    }
    void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
    {
       const std::vector<GameObject*>& lefts = scene->GetLayer(left)->GetGameObjects();
       const std::vector<GameObject*>& rights = scene->GetLayer(right)->GetGameObjects();

       for (GameObject* left : lefts)
       {
           if (left->IsActive() == false)
               continue;
           Collider* leftCol = left->GetComponent<Collider>();
           if (leftCol == nullptr)
               continue;
           

           for (GameObject* right : rights)
           {
               if (right->IsActive() == false)
                   continue;

               Collider* rightCol = right->GetComponent<Collider>();
               if (rightCol == nullptr)
                   continue;
               if (left == right)
                   continue;

               ColliderCollision(leftCol, rightCol);
           }
       }
    }
    void CollisionManager::ColliderCollision(Collider* left, Collider* right)
    {
    }
}