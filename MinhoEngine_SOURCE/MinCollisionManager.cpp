#include "MinCollisionManager.h"
#include "MinScene.h"
#include "MinSceneManager.h"
#include "minGameObject.h"
#include "MinCollider.h"
#include "MinTransform.h"
#include "minGameObject.h"
#include "MinSpriteRenderer.h"
#include "MinShadow.h"
#include "..\\MinhoEngine_Window\MinPlayerScript.h"

namespace min
{
    std::bitset<(UINT)eLayerType::Max> CollisionManager::mCollisionLayerMatrix[(UINT)eLayerType::Max] = {};
    std::unordered_map<UINT64, bool> CollisionManager::mCollisionMap = {};

    void CollisionManager::Initialize()
    {
    }
    void CollisionManager::Update()
    {
        for (UINT row = 0; row < (UINT)eLayerType::Max; row++)
        {
            for (UINT col = 0; col < (UINT)eLayerType::Max; col++)
            {
                if (mCollisionLayerMatrix[row][col] == true)
                {
                    LayerCollision((eLayerType)row, (eLayerType)col);
                }
            }
        }
    }
    void CollisionManager::LateUpdate()
    {
    }
    void CollisionManager::Render()
    {
    }
    void CollisionManager::clear()
    {
        mCollisionMap.clear();
        mCollisionLayerMatrix->reset();
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
    void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
    {
       const std::vector<GameObject*>& leftsObjs = SceneManager::GetGameObjects(left);
       const std::vector<GameObject*>& rightsObjs = SceneManager::GetGameObjects(right);

       for (GameObject* leftObj : leftsObjs)
       {
           if (leftObj->IsActive() == false)
               continue;
           Collider* leftCol = leftObj->GetComponent<Collider>();
           if (leftCol == nullptr)
               continue;
           

           for (GameObject* rightObj : rightsObjs)
           {
               if (rightObj->IsActive() == false)
                   continue;

               Collider* rightCol = rightObj->GetComponent<Collider>();
               if (rightCol == nullptr)
                   continue;
               if (leftObj == rightObj)
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
        eColliderType LeftColType = left->GetColType();
        if (left->GetName() == L"Floor")
        {
            switch ((int)LeftColType)
            {
            case 0:
                if (((BoxCollider2D*)left)->Contain(right) == ContainmentType::CONTAINS)//���� ����ġ ������ �����Ͽ� Ȯ���ϰ� ����ϴ°� �� ��������� �����̵�. 
                {
                    right->GetOwner()->SetName(left->GetOwner()->GetComponent<SpriteRenderer>()->GetName());//Shadow�� ������ �ִ� ���ӿ�����Ʈ�� �̸��� ���� ������ �Ͽ� ���ε����ֱ�
                    return true;
                }
                break;
            case 1:
                if ((CircleCollider2D*)left->Contain(right))//���� ����ġ ������ �����Ͽ� Ȯ���ϰ� ����ϴ°� �� ��������� �����̵�.
                {
                    int a = 0;
                    return true;
                }
                return true;
                break;
            }
        }
        else
        {
            switch ((int)LeftColType)
            {
            case 0:
                if ((BoxCollider2D*)left->Intersects(right))//���� ����ġ ������ �����Ͽ� Ȯ���ϰ� ����ϴ°� �� ��������� �����̵�.
                {
                    int a = 0;
                    return true;
                }
                break;
            case 1:
                if ((CircleCollider2D*)left->Intersects(right))//���� ����ġ ������ �����Ͽ� Ȯ���ϰ� ����ϴ°� �� ��������� �����̵�.
                {
                    int a = 0;
                    return true;
                }
                break;
            }
        }

        return false;
    }
}