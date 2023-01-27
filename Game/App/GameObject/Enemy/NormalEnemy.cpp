#include "NormalEnemy.h"
#include "../../Manager/AssetManager.h"
#include "../../Manager/GameObjectManager.h"
#include "../../Library/Calc3D.h"

namespace My3dApp
{
    NormalEnemy::NormalEnemy(VECTOR pos)
        : BaseEnemy(pos)
    {
        modelHandle = AssetManager::GetMesh("../asset/model/enemy.mv1");

        // ���W�̐ݒ�
        MV1SetPosition(modelHandle, this->pos);

        // ���f���̑傫��
        float modelSize = 0.5f;

        // �傫���̐ݒ�
        MV1SetScale(modelHandle, VGet(modelSize, modelSize, modelSize));

        // �����蔻�苅�̔��a�̐ݒ�
        collisionSphere.radius = 65.0f;

        // �����蔻��̍X�V
        CollisionUpdate();
    }

    NormalEnemy::~NormalEnemy()
    {
        AssetManager::ReleaseMesh(modelHandle);
    }

    void NormalEnemy::Update(float deltaTime)
    {
        // �ړ�
        Move(deltaTime);
    }

    void NormalEnemy::Move(float deltaTime)
    {
        // �v���C���[�̎擾
        GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);

        // �v���C���[�̍��W���玩�g�̍��W�������Č����x�N�g�����v�Z����
        VECTOR tmp = player->GetPos() - pos;

        // �����x�N�g���̖�����
        tmp.y = 0;

        if (VSize(tmp) > 300.0f)
        {
            shotInterval -= deltaTime;

            Shot();

            dir = VNorm(tmp);

            speed = (dir * deltaTime * 300.0f);

            if (onGround)
            {
                pos += speed;
            }
        }
        else
        {
            shotInterval -= deltaTime;

            dir = VNorm(tmp);

            Shot();
        }

        if (!onGround)
        {
            speed = (VGet(0, -1, 0) * 10.0f);

            pos += speed;

            CollisionUpdate();
        }

        // 3D���f���̃|�W�V�����ݒ�
        MV1SetPosition(modelHandle, pos);

        // �����ɍ��킹�ă��f������]
        MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));

        VECTOR negativeVec = VTransform(dir, rotYMat);

        // ���f���ɉ�]���Z�b�g����
        MV1SetRotationZYAxis(modelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

        // �����蔻�胂�f���̈ʒu�X�V
        CollisionUpdate();

        if (pos.y < -500.0f)
        {
            isAlive = false;
        }
    }
}// namespace My3dApp