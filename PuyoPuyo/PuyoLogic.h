#ifndef _PuyoLOGIC_H
#define _PuyoLOGIC_H

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "GameLogic.h"
#include "PuyoFiled.h"

/*----------------------------------*/
/*	�v���Z�X�̃R���g���[���N���X	*/
/*----------------------------------*/
class CPuyoLogic : public CGameLogic
{
	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CPuyoLogic();

	/*	�f�X�g���N�^	*/
	virtual	~CPuyoLogic();

	/*	�֐�	*/

protected:

	/*	���z�֐�	*/
	virtual void	Logic(CInput*);

private:
	void			Init();
	void			Update();
	void			UpdateBlock();
	void			CheckBlock();
	void			UpdatePoint();
	bool			UpdateTimer();
	bool			Keydown(CInput*);

	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
	/*	��`�p�ϐ� ( const )	*/
	static const short				PUYO_FALL_TIME				= 300;		/*	�e�g���X�������Ԃ̍X�V����				*/
	static const short				PUYO_NEXTBLOCK_WAIT_TIME	= 300;		/*	�e�g���X�������Ԃ̍X�V����				*/
	static const short				PUYO_FALL_TIME_SPEED_UP		= 100;		/*	�e�g���X�������Ԃ̑��x�X�V				*/
	static const short				PUYO_NEXTBLOCK_WAIT_SLOW	= 100;		/*	�e�g���X�������Ԃ̑��x�X�V				*/
	static const short				PUYO_SINGLE_POINTS			= 40;		/*	�e�g���X���_ ( �V���O�� )				*/
	static const short				PUYO_DOUBLE_POINTS			= 100;		/*	�e�g���X���_ ( �_�u�� )					*/
	static const short				PUYO_TRIPLE_POINTS			= 300;		/*	�e�g���X���_ ( �g���v�� )				*/
	static const short				PUYO_POINTS					= 1200;		/*	�e�g���X���_ ( �e�g���X )				*/
	static const short				PUYO_KEYDOWN_POINTS			= 1;		/*	�e�g���X���_ ( �L�[�_�E�� )				*/

protected:
	CPuyoFiled&						m_PuyoFiled;							/*	�e�g���X�̃u���b�N���					*/

private:
	DWORD 							m_TimeStart;							/*	�X�V�J�n����							*/
	DWORD		 					m_TimeEnd;								/*	�X�V�I������							*/
	bool							m_bInit;									/*	�������t���O							*/
																			/*		true	: �������ς�				*/
																			/*		false	: ���������ĂȂ�			*/

	bool							m_bFinish;								/*	�I���t���O								*/
																			/*		true	: �I���ς�					*/
																			/*		false	: �I�����ĂȂ�				*/

	bool							m_bDroppingBlock;						/*	�u���b�N�������t���O					*/
																			/*		true	: �����I���ς�				*/
																			/*		false	: ������					*/

	bool							m_bCurrentBlockFallTimeMode;			/*	�����������[�h							*/

};
#endif
