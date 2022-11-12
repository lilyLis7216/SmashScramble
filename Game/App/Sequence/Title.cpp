#include "Title.h"
#include "DxLib.h"

namespace Sequence
{
    Title::Title()
        : SceneBase(SceneType::Scene_Title)
    {
        /** 処理なし*/
    }

    Title::~Title()
    {
        /** 処理なし*/
    }

    SceneType Title::Update()
    {
        nowSceneType = SceneType::Scene_Title;

        if (CheckHitKey(KEY_INPUT_Z))
        {
            nowSceneType = SceneType::Scene_StageSelect;
        }

        return nowSceneType;
    }

    void Title::Draw()
    {
        DrawFormatString(100, 200, GetColor(255, 255, 255), "タイトル");
    }
}/** namespace Sequence*/