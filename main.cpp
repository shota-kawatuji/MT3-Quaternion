#include "DxLib.h"
#include "Vector2.h"
#include <cmath>
#include "Quaternion.h"

bool CheckLineCircle(Vector2& lineStart, Vector2& lineEnd, Vector2& circle, int circleR);

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "LE2C_08_�J���c�W�V���E�^:�^�C�g��";

// �E�B���h�E����
const int WIN_WIDTH = 600;

// �E�B���h�E�c��
const int WIN_HEIGHT = 400;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
	_In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) {
		return -1;
	}

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���


	// �Q�[�����[�v�Ŏg���ϐ��̐錾

	Vector2 circle = { WIN_WIDTH / 2,WIN_HEIGHT / 2 };

	Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
	Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };

	Quaternion identity;
	Quaternion conj;
	Quaternion inv;
	Quaternion normal;
	Quaternion mul1;
	Quaternion mul2;

	

	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = { 0 };

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = { 0 };

	// �Q�[�����[�v
	while (true) {
		// �ŐV�̃L�[�{�[�h��񂾂������̂�1�t���[���O�̃L�[�{�[�h���Ƃ��ĕۑ�
		for (int i = 0; i < 256; ++i)
		{
			oldkeys[i] = keys[i];
		}
		// �ŐV�̃L�[�{�[�h�����擾
		GetHitKeyStateAll(keys);

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����



		// �`�揈��

		DrawFormatString(0, 0, GetColor(255, 255, 255), "%f %f %f %f  : identity", identity.x, identity.y, identity.z, identity.w);
		DrawFormatString(0, 20, GetColor(255, 255, 255), "%f %f %f %f  : conj", conj.x, conj.y, conj.z, conj.w);
		DrawFormatString(0, 40, GetColor(255, 255, 255), "%f %f %f %f  : inv", inv.x, inv.y, inv.z, inv.w);
		DrawFormatString(0, 60, GetColor(255, 255, 255), "%f %f %f %f  : normal", normal.x, normal.y, normal.z, normal.w);
		DrawFormatString(0, 80, GetColor(255, 255, 255), "%f %f %f %f  : mul1", mul1.x, mul1.y, mul1.z, mul1.w);
		DrawFormatString(0, 100, GetColor(255, 255, 255), "%f %f %f %f  : mul2", mul2.x, mul2.y, mul2.z, mul2.w);
		//DrawFormatString(0, 120, GetColor(255, 255, 255), "%f  : norm", norm);

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}

bool CheckLineCircle(Vector2& lineStart, Vector2& lineEnd, Vector2& circle, int circleR)
{
	Vector2 lineVec = lineEnd - lineStart;
	Vector2 lineEndCirclVec = circle - lineEnd;

	Vector2 lineStartCirclVec = circle - lineStart;
	Vector2 normLineVec = lineVec.normalize();

	float distance = lineStartCirclVec.cross(normLineVec);

	if (fabs(distance) < circleR)
	{
		float circlVecLineStartVecDot = lineStartCirclVec.dot(lineVec);
		float circlVecLineEndVecDot = lineEndCirclVec.dot(lineVec);

		if (circlVecLineStartVecDot * circlVecLineEndVecDot <= 0)
		{
			return true;
		}
		else if (lineEndCirclVec.length() < circleR || lineStartCirclVec.length() < circleR)
		{
			return true;
		}
	}
	return false;
}