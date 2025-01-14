#include "MinCollisionManager.h"
#include "MinScene.h"
#include "MinSceneManager.h"
#include "minGameObject.h"
#include "MinCollider.h"
#include "MinTransform.h"
#include "minGameObject.h"

namespace min
{
    std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};
    std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};

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
        CollisionID id = {};
        id.left = left->GetID();
        id.right = right->GetID();

        auto iter = mCollisionMap.find(id.id);
        if (iter == mCollisionMap.end())
        {
            mCollisionMap.insert(std::make_pair(id.id, false));
            iter = mCollisionMap.find(id.id);
        }

        if (Intersect(left, right))
        {
            if (iter->second == false)
            {
                left->OnCollisionEnter(right);
                right->OnCollisionEnter(left);
                iter->second = true;
            }
            else
            {
                left->OnCollisionStay(right);
                right->OnCollisionStay(left);
            }
        }
        else
        {
            if (iter->second == true)
            {
                left->OnCollisionExit(right);
                right->OnCollisionExit(left);

                iter->second = false;
            }
        }
    }
    bool CollisionManager::Intersect(Collider* left, Collider* right)
    {
        Transform* leftTr = left->GetOwner()->GetComponent<Transform>();
        Transform* rightTr = right->GetOwner()->GetComponent<Transform>();

        Vector2 leftPos = leftTr->GetPosition() + left->GetOffset();
        Vector2 rightPos = rightTr->GetPosition() + right->GetOffset();

        Vector2 leftSize = left->GetSize() * 100.0f;
        Vector2 rightSize = right->GetSize() * 100.0f;

        enums::eColliderType leftType = left->GetColType();
        enums::eColliderType rightType = right->GetColType();

        if (leftType == enums::eColliderType::Rect2D// rect - rect
            && rightType == enums::eColliderType::Rect2D)
        {
            if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
                && fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
            {
                return true;
            }
        }

        if (leftType == enums::eColliderType::Circle2D//circle - circle
            && rightType == enums::eColliderType::Circle2D)
        {
            Vector2 leftCirclePos = leftPos + (leftSize / 2.0f);
            Vector2 rightCirclePos = rightPos + (rightSize / 2.0f);
            float distance = (leftCirclePos - rightCirclePos).length();
            if (distance <= (leftSize.x / 2.0f + rightSize.x / 2.0f))
            {
                return true;
            }
        }

        if (leftType == enums::eColliderType::Rect2D && rightType == enums::eColliderType::Circle2D
            || leftType == enums::eColliderType::Circle2D && rightType == enums::eColliderType::Rect2D)
        {
        }
        

        
        return false;
    }
}