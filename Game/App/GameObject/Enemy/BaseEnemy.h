#pragma once

#include "../GameObject.h"

namespace My3dApp
{
    /// <summary>
    /// エネミーの基底クラス（GameObject継承）
    /// </summary>
    class BaseEnemy : public GameObject
    {
    protected:
        // 向き
        VECTOR dir;

        // 目標向き
        VECTOR aimDir;

        // 速度
        VECTOR speed;

        // 回転中か
        bool isRotate;

        // 発射の間隔
        float shotInterval;

        // ノックバック中か
        bool isNockBack;

        // ノックバックの向き
        VECTOR nockBackDir;

        const float jumpForce = 200.0f;

        // 重さ
        float weight;

        // ノックバック量
        float nockBackPar;

        // 重力
        float gravity;

        bool canShot;

        int enemyType;

        /// <summary>
        /// エネミーの移動
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        virtual void Move(float deltaTime) = 0;

        /// <summary>
        /// 回転の確認
        /// </summary>
        void RotateCheck();

        /// <summary>
        /// 死んでいるかどうかの確認
        /// </summary>
        /// <returns>true 死んでいる false 死んでいない</returns>
        bool IsDead();

        /// <summary>
        /// エネミーの射撃処理
        /// </summary>
        virtual void Shot(float deltaTime);

        /// <summary>
        /// エネミーのノックバック処理
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        void KnockBack(float deltaTime);

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        /// <param name="pos">初期位置</param>
        BaseEnemy(VECTOR pos);

        /// <summary>
        /// デストラクタ
        /// </summary>
        virtual ~BaseEnemy();

        /// <summary>
        /// エネミーの描画
        /// </summary>
        void Draw() override;

        /// <summary>
        /// 他のオブジェクトと衝突したときのリアクション
        /// </summary>
        /// <param name="other">自分とは異なるオブジェクト</param>
        void OnCollisionEnter(const GameObject* other) override;
    };
}