#pragma once

#include "SceneBase.h"

namespace My3dApp
{
    /// <summary>
    /// プレイシーン（派生クラス、継承元：シーンベース）
    /// </summary>
    class Play : public SceneBase
    {
    private:

        // タイマー
        float timer;

        /*const int gaugeWidth = 440;
        const int gaugeHeight = 80;
        const int gaugeX = 1410;
        const int gaugeY = 170;*/

        const int gaugeWidth = 440;
        const int gaugeHeight = 80;
        const int gaugeX = 210;
        const int gaugeY = 50;

        static int gaugeValue;
        int gaugeMax = 500;
        int prevComb;

        int countImage[12];

        void GaugeUpdate(float deltaTime);

        int startCount;
        float startCountTimer;
        bool countSE1;
        int endCount;

        int playerBar;

        class GameObject* player;

    public:
        /// <summary>
        /// コンストラクタ
        /// </summary>
        Play();

        /// <summary>
        /// デストラクタ
        /// </summary>
        ~Play();

        /// <summary>
        /// プレイシーンの更新
        /// </summary>
        /// <param name="deltaTime">1フレームの経過時間</param>
        /// <returns>現在のシーン、または遷移予定のシーン</returns>
        SceneBase* Update(float deltaTime) override;

        /// <summary>
        /// プレイシーンの描画
        /// </summary>
        void Draw() override;

        static int GetGauge() { return gaugeValue; }
        static void AddGauge(int set) { gaugeValue += set; }
        static void SetMaxGauge() { gaugeValue = 500; }

    };
}// namespace My3dApp