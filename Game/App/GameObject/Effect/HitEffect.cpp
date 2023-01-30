#include "HitEffect.h"
#include "EffekseerForDXLib.h"

namespace My3dApp
{
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    /// <param name="pos">�����ʒu</param>
    HitEffect::HitEffect(VECTOR pos)
        : BaseEffect(pos)
    {
        // �G�t�F�N�g�̓ǂݍ���
        effectHandle = LoadEffekseerEffect("../asset/effect/hit.efkefc", 1.0f);
    }

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    HitEffect::~HitEffect()
    {
        // �G�t�F�N�g�̌�n��
        DeleteEffekseerEffect(effectHandle);
    }

    /// <summary>
    /// �q�b�g�G�t�F�N�g�̍X�V
    /// </summary>
    /// <param name="deltaTime">1�t���[���̌o�ߎ���</param>
    void HitEffect::Update(float deltaTime)
    {
        // �Đ����Ă��Ȃ����
        if (!isPlay)
        {
            // �Đ����ɂ���
            isPlay = true;

            // �Đ�����G�t�F�N�g������
            playEffect = PlayEffekseer3DEffect(effectHandle);
        }

        // �G�t�F�N�g�̈ʒu�ݒ�
        SetPosPlayingEffekseer3DEffect(playEffect, pos.x, pos.y, pos.z);

        // �G�t�F�N�V�A�̍X�V
        UpdateEffekseer3D();

        if (IsEffekseer3DEffectPlaying(playEffect) == -1)
        {
            isAlive = false;
        }
    }
}// namespace My3dApp