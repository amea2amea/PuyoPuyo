#ifndef PuyoBlock_h
#define PuyoBlock_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"

namespace BlockNS
{
	enum Block_Color									/*	�u���b�N�J���[�̏��						*/
	{
		NON_COLOR,										/*	�F�����ݒ�									*/
		RED,											/*	��											*/
		PURPLE,											/*	��											*/
		YELLOW,											/*	��											*/
		PINK,											/*	�s���N										*/
		GREEN,											/*	��											*/
		BLUE,											/*	��											*/
		CYAN,											/*	�V�A��										*/
		ORANGE,											/*	�I�����W									*/
		BLACK,											/*	��											*/
		WHITE,											/*	��											*/
		DIMGRAY,										/*	�f�B���O���C ( �Â��O���C )					*/
		LIGHTGRAY,										/*	���C�g�O���C ( �W���O���C )					*/
		GRAY											/*	�O���C										*/
	};

	enum Block_State									/*	�u���b�N�̏��								*/
	{
		EXISTENCE	= 1,								/*	�u���b�N����								*/
		EMPTY		= 0,								/*	�u���b�N�Ȃ�								*/
		WALL		= 2									/*	��											*/
	};

	enum Block_Move										/*	�u���b�N�̈ړ�����							*/
	{
		BLOCK_MOVE_LEFT,								/*	�u���b�N�̈ړ�������������					*/
		BLOCK_MOVE_RIGHT,								/*	�u���b�N�̈ړ��������E����					*/
		BLOCK_MOVE_DOWN,								/*	�u���b�N�̈ړ�������������					*/
		BLOCK_MOVE_ROTATE_CW,							/*	�u���b�N�̈ړ�������CW��]					*/
		BLOCK_MOVE_ROTATE_CCW,							/*	�u���b�N�̈ړ�������CCW��]					*/
		BLOCK_MOVE_FALL_MODE,							/*	�u���b�N�̗������[�h						*/
		BLOCK_MOVE_LANDING_MODE							/*	�u���b�N�̒��n�ʒu�\�����[�h				*/
	};

	enum Block_Rotation									/*	�u���b�N�̉�]����							*/
	{
		BLOCK_CW_ROTATION,								/*	�u���b�N�̉�]������CW��]					*/
		BLOCK_CCW_ROTATION								/*	�u���b�N�̉�]������CCW��]					*/
	};

	enum Block_Type										/*	�u���b�N�̎��								*/
	{
		FILED_BLOCK,									/*	�t�B�[���h��̃u���b�N						*/
		CURRENT_BLOCK,									/*	���݂̃u���b�N								*/
		WAIT_BLOCK,										/*	�ҋ@�u���b�N ( ���̃u���b�N )				*/
		WAIT_NEXT_BLOCK,								/*	�ҋ@�u���b�N ( ���̑ҋ@�u���b�N )			*/
		LANDING_BLOCK									/*	���n�_�\���u���b�N							*/
	};

	enum Block_Check									/*	�u���b�N�̃`�F�b�N���						*/
	{
		NON_CHECEKED_BLOCK,								/*	�`�F�b�N����Ă��Ȃ��u���b�N				*/
		CHECEKED_BLOCK,									/*	�`�F�b�N�ς݂̃u���b�N						*/
	};

	enum Block_Connect									/*	�u���b�N�̘A�����							*/
	{
		BLOCK_CONNECT_NONE		= 0,					/*	�A�����Ă��Ȃ��u���b�N						*/
		BLOCK_CONNECT_LEFT		= BIT0,					/*	�A���u���b�N���� ( �� )						*/
		BLOCK_CONNECT_TOP		= BIT1,					/*	�A���u���b�N���� ( �� )						*/
		BLOCK_CONNECT_RIGHT		= BIT2,					/*	�A���u���b�N���� ( �E )						*/
		BLOCK_CONNECT_BOTTOM	= BIT3,					/*	�A���u���b�N���� ( �� )						*/
	};

}

/*--------------*/
/*	�N���X		*/
/*--------------*/
class CPuyoBlock										/*	�e�g���X�̃u���b�N�N���X			*/
{

	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CPuyoBlock();										/* �����Ȃ��R���X�g���N�^				*/
	CPuyoBlock( short, unsigned short );				/* ��������R���X�g���N�^				*/

	/*	�f�X�g���N�^	*/
	~CPuyoBlock();

	/*	�֐�	*/
	unsigned short			GetBlockColor() const;		/* �u���b�N�ʒu�̃J���[���擾			*/
	unsigned short&			SetBlockColor();			/* �u���b�N�ʒu�̃J���[����ݒ�			*/
	unsigned short			GetBlockState() const;		/* �u���b�N�̏�Ԃ��擾					*/
	unsigned short&			SetBlockState();			/* �u���b�N�̏�Ԃ�ݒ�					*/
	unsigned short			GetCheckBlock() const;		/* �u���b�N���`�F�b�N�ς݂ǂ������擾	*/
	unsigned short&			SetCheckBlock();			/* �u���b�N���`�F�b�N�ς݂ɐݒ�			*/
	unsigned short			GetConnectBlock() const;	/* �u���b�N�̘A����Ԃ��擾				*/
	unsigned short&			SetConnectBlock();			/* �u���b�N�̘A����Ԃ�ݒ�				*/

	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
	unsigned short			m_Color;					/* �u���b�N�̐F							*/
	unsigned short			m_BlockState;				/* �u���b�N�̏��						*/
	unsigned short			m_Check;					/* �`�F�b�N�ς݂̃u���b�N				*/
	unsigned short			m_ConnectState;				/* �A���u���b�N�̏��					*/


};
#endif