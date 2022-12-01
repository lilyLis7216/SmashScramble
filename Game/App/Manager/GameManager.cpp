#include "GameManager.h"
#include "../Dxlib_h/DxLib.h"
#include "../Scene/SceneBase.h"
#include "../Scene/Title.h"
#include "../Scene/StageSelect.h"
#include "../Scene/Play.h"
#include "../Scene/Result.h"

namespace My3dApp
{
    /** インスタンスへのポインタ*/
    GameManager* GameManager::instance = nullptr;

    SceneBase* GameManager::nowScene = nullptr;

    GameManager::GameManager()
        : screenWidth(0)
        , screenHeight(0)
        , fullScreen(false)
    {
        Init();
    }

    GameManager::~GameManager()
    {
        /** 処理なし*/
    }

    void GameManager::CreateInstance()
    {
        if (!instance)
        {
            instance = new GameManager();
        }
    }

    void GameManager::DeleteInstance()
    {
        if (instance)
        {
            delete instance;
            instance = nullptr;
        }
    }

    bool GameManager::ProcessInput()
    {
        /** エラーがでた、もしくはウィンドウが閉じられたら*/
        if (ProcessMessage() != 0)
        {
            /** ループのフラグを倒す*/
            return false;
        }

        /** エスケープキーが押されたら*/
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            /** ループのフラグを倒す*/
            return false;
        }

        return true;
    }

    void GameManager::Init()
    {
        /** 画面の横幅を1920に設定*/
        screenWidth = 1920;

        /** 画面の縦幅を1080に設定*/
        screenHeight = 1080;

        /** 全画面にする*/
        fullScreen = true;

        /** 全画面のフラグが立っていないとき*/
        if (!fullScreen)
        {
            ChangeWindowMode(TRUE);
        }

        /** 画面モードの設定*/
        SetGraphMode(screenWidth, screenHeight, 32);

        /** DxLibの初期化処理*/
        DxLib_Init();

        /** マウスカーソルを表示しない*/
        SetMouseDispFlag(false);

        /** Zバッファを有効にする*/
        SetUseZBuffer3D(true);

        /** Zバッファへの書き込みを有効にする*/
        SetWriteZBuffer3D(true);

        /** */
        SetCameraNearFar(10.0f, 30000.0f);

        /** */
        SetCameraPositionAndTarget_UpVecY(VGet(0, 80, -200), VGet(0.0f, 80.0f, 0.0f));
    }

    void GameManager::Loop()
    {
        /** ループフラグ*/
        bool gameLoop = true;

        /** 現フレームのカウント*/
        LONGLONG nowCount = GetNowHiPerformanceCount();

        /** 前フレームのカウント*/
        LONGLONG prevCount = nowCount;

        /**
        * 待機フレーム時間（60fps想定）
        * 1/60 = 1.66666...
        * 16000マイクロ秒 = 16ミリ秒 = 0.016秒
        */
        float waitFrameTime = 15900;

        /** ループ本体*/
        while (gameLoop)
        {
            /** 現フレームと前フレームとの差分*/
            float deltaTime;

            /** 現フレームカウントの更新*/
            nowCount = GetNowHiPerformanceCount();

            /** 差分を100万分の1にして保存する（マイクロ秒換算）*/
            deltaTime = (nowCount - prevCount) / 1000000.0f;

            /** ループ継続の確認*/
            gameLoop = ProcessInput();

            SceneBase* tmpScene;

            /** シーンの更新と現在のシーンの保存*/
            tmpScene = nowScene->Update();

            /** 画面の初期化*/
            ClearDrawScreen();

            /** シーンの描画*/
            nowScene->Draw();

            /** fps確認用（後で消す）*/
            DrawFormatString(100, 100, GetColor(255, 255, 255), "fps:%f", deltaTime);

            /** 裏画面の内容を表画面に反映させる*/
            ScreenFlip();

            /** 更新前のシーンと更新後のシーンが異なったら*/
            if (nowScene != tmpScene)
            {
                /** シーンを解放*/
                delete nowScene;

                /** 新しいシーンを入れる*/
                nowScene = tmpScene;
            }

            /** 60fps制御用ループ*/
            while (GetNowHiPerformanceCount() - nowCount < waitFrameTime);

            /** 現在のカウントを保存する*/
            prevCount = nowCount;
        }

        /** シーンの解放*/

        /** DxLibの使用終了処理*/
        DxLib_End();
    }

}/** namespace My3dApp*/
