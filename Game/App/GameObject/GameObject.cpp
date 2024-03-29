#include "GameObject.h"

namespace My3dApp
{
    GameObject::GameObject(ObjectTag tag)
        : GameObject(tag, VGet(0, 0, 0))
    {
    }

    GameObject::GameObject(ObjectTag tag, VECTOR pos)
        : tag(tag)
        , modelHandle(-1)
        , isVisible(true)
        , isAlive(true)
        , onGround(true)
        , collisionType()
        , collisionLine()
        , collisionSphere()
        , collisionCapsule()
        , collisionModel()
        , damagePar(0.0f)
    {
        this->pos = pos;
        dir = VGet(0, 1, 0);
    }

    GameObject::~GameObject()
    {
        // モデルの後始末
        if (modelHandle != -1)
        {
            MV1DeleteModel(modelHandle);
            modelHandle = -1;
        }
    }

    void GameObject::Draw()
    {
        // 処理なし
    }

    void GameObject::DrawCollider()
    {
        // 線分当たり判定の描画
        DrawLine3D(collisionLine.worldStart, collisionLine.worldEnd, GetColor(255, 255, 0));

        // 球体当たり判定の描画
        DrawSphere3D(collisionSphere.worldCenter, collisionSphere.radius, 10, GetColor(0, 255, 255), GetColor(0, 0, 0), FALSE);

        // カプセル当たり判定の描画
        DrawCapsule3D(collisionCapsule.worldStart, collisionCapsule.worldEnd, collisionCapsule.radius, 8, GetColor(255, 0, 255), GetColor(0, 0, 0), FALSE);

        // 当たり判定モデルがある場合
        if (collisionModel != -1)
        {
            // 半透明にして描画する
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
            MV1DrawModel(collisionModel);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        }
    }

    void GameObject::CollisionUpdate()
    {
        collisionSphere.Move(pos);

        collisionLine.Move(pos);

        collisionCapsule.Move(pos);

        // モデルの当たり判定情報を再構築
        if (collisionModel != -1)
        {
            MV1SetPosition(collisionModel, pos);

            MV1SetupCollInfo(collisionModel);
        }
    }
    void GameObject::DamageParView(int obj)
    {
        int cr = GetColor(255, 255, 255);

        if (damagePar >= 100)
        {
            cr = GetColor(161, 21, 8);
        }
        else if (damagePar >= 80)
        {
            cr = GetColor(219, 78, 10);
        }
        else if (damagePar >= 60)
        {
            cr = GetColor(255, 142, 61);
        }
        else if (damagePar >= 40)
        {
            cr = GetColor(252, 167, 10);
        }
        else if (damagePar >= 20)
        {
            cr = GetColor(254, 222, 10);
        }

        if (obj == 0)
        {
            SetFontSize(85);
            DrawFormatString(890, 900, cr, "%3.0f％", damagePar);
        }
        else if (obj == 1)
        {
            VECTOR screenPos = ConvWorldPosToScreenPos(pos);

            SetFontSize(25);

            DrawFormatString((int)screenPos.x - 20, (int)screenPos.y - 50, cr, "%1.0f％", damagePar);
        }
    }
}// namespace My3dApp