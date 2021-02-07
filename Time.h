//---------------------------------------------------------
//	Time							Date	2020/7/18
//									Author	�{�����		
//	Unity�Q�l
//---------------------------------------------------------
#pragma once
#include <chrono>
class Time
{
public:

	//�Q�[�����N�����Ă���̎��Ԃ��擾���܂�
	//���̒l�͓��t���[�����œ����l��Ԃ��܂�
	static float	GetTime(/*�K�v�ɂȂ�����unScale����*/);

	//�O�L���t���[������̌o�ߎ��Ԃ�Ԃ��܂�
	//unScaled��true�ɂ����TimeScale�̉e�����󂯂܂���
	static float	GetDeltaTime(bool unScaled = false);

	//�Q�[�����N�����Ă���̎��Ԃ��擾���܂�
	//���̊֐����Ă΂ꂽ�u�ԂɌv�������l��Ԃ��܂�
	static float	GetRawTime();

	//�Ō��Update()��Init()���Ă΂�Ă���̌o�ߎ��Ԃ�Ԃ��܂�
	//���̊֐����Ă΂ꂽ�u�ԂɌv�������l��Ԃ��܂�
	static float	GetRawDeltaTime();

	//���Ԃ̑��x�{����ύX���܂�
	static void		SetTimeScale(float scale);

	//�v���O�����J�n���ɌĂяo���܂�
	static void		Init();

	//�L���t���[�����̍ŏ��ɌĂяo���܂�
	static void		Update();

private:
	static constexpr float m_MaxDeltaTime = 1.0f / 10;	//�Œ�10fps

	static float m_time, m_deltaTime;	//�����Ԃ�
	static float m_timeScale;
	static std::chrono::high_resolution_clock::time_point m_start, m_last;
};