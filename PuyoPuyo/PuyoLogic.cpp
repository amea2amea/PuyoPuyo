/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "PuyoManger.h"
#include "PuyoLogic.h"

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CPuyoLogic		:	�R���X�g���N�^ ( �����Ȃ� )					*/
/*																				*/
/*==============================================================================*/
CPuyoLogic::CPuyoLogic():m_PuyoFiled(CPuyoManger::Instance()->GetPuyoFiled())
{
	CPuyoManger::Instance()->SetPuyoFallingTime()		= PUYO_FALL_TIME;
	CPuyoManger::Instance()->SetPuyoNextBlockWaitTime() = PUYO_NEXTBLOCK_WAIT_TIME;
	m_TimeStart	= timeGetTime();
	m_bCurrentBlockFallTimeMode	= false;
	m_bInit						= false;
	m_bFinish					= false;
	m_bDroppingBlock			= false;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		~CPuyoLogic		:	�f�X�g���N�^								*/
/*																				*/
/*==============================================================================*/
CPuyoLogic::~CPuyoLogic()
{
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		Logic				:	���W�b�N								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
void CPuyoLogic::Logic(CInput* input)
{
	/************************/
	/*	�I������			*/
	/************************/
	if (m_bFinish == true)
		return;
	
	/************************/
	/*	����������			*/
	/************************/
	if (m_bInit == false)
	{
		Init();					/*	����������			*/
	}

	/************************/
	/*	�L�[����			*/
	/************************/
	if (Keydown(input))
	{
		UpdateBlock();
	}

	/************************/
	/*	�X�V����			*/
	/************************/
	Update();

	return;

}
/*==============================================================================*/
/*																				*/
/*	[�֐�]		Init				:	�����ݒ�								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
void CPuyoLogic::Init()
{
	/********************/
	/*	�Ղ�Ղ���쐬	*/
	/********************/
	m_PuyoFiled.Init();

	/****************************/
	/*	���̃u���b�N�̏����ݒ�	*/
	/****************************/
	m_PuyoFiled.NextWaitBlockInit();

	/********************************/
	/*	���݂̃u���b�N��Ԃ�ݒ�	*/
	/********************************/
	m_PuyoFiled.SetCurrentBlockState();

	/************************************/
	/*	�u���b�N���t�B�[���h�ɃR�s�[	*/
	/************************************/
	m_PuyoFiled.CurrentBlockToBoard(2);

	/************************/
	/*	�ҋ@�u���b�N���쐬	*/
	/************************/
	m_PuyoFiled.NextWaitBlock();

	/****************/
	/*	����������	*/
	/****************/
	m_bInit = true;

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		Keydown				:	�L�[�_�E������							*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
bool CPuyoLogic::Keydown(CInput* input)
{
	char keycord		= input->GetKeyPressed();
	char ctrl_keydown	= input->isKeyDown(VK_CONTROL);
	bool block_move = false;

	/****************************************/
	/*	���n��̗������̓L�[���������Ȃ�	*/
	/****************************************/
	if (m_bDroppingBlock == true)
		return block_move;

	/********************************/
	/*	�������[�h�̏�ԃ`�F�b�N	*/
	/********************************/
	if (!ctrl_keydown)
	{
		m_bCurrentBlockFallTimeMode = false;
	}

	switch (keycord)
	{
	case VK_LEFT:
		block_move = m_PuyoFiled.CurrentMoveBlock(BlockNS::BLOCK_MOVE_LEFT);
		break;

	case VK_RIGHT:
		block_move = m_PuyoFiled.CurrentMoveBlock(BlockNS::BLOCK_MOVE_RIGHT);
		break;

	case VK_DOWN:
		CPuyoManger::Instance()->SetPuyoPoint() += PUYO_KEYDOWN_POINTS;
		block_move = m_PuyoFiled.CurrentMoveBlock(BlockNS::BLOCK_MOVE_DOWN);
		break;

	case VK_SPACE:
   		block_move = m_PuyoFiled.CurrentMoveBlock(BlockNS::BLOCK_MOVE_ROTATE_CW);
		break;

	case VK_B:	/* B	*/
	case VK_C:	/* C	*/
	case VK_V:	/* V	*/
		block_move = m_PuyoFiled.CurrentMoveBlock(BlockNS::BLOCK_MOVE_ROTATE_CCW);
		break;
		
	case VK_CONTROL:
		if (!m_bCurrentBlockFallTimeMode)
		{
			unsigned short FiledY = m_PuyoFiled.GetFiledSizeY();
			unsigned short PosY = m_PuyoFiled.GetBlockTopPosY(BlockNS::CURRENT_BLOCK);
			CPuyoManger::Instance()->SetPuyoPoint() += PUYO_KEYDOWN_POINTS * (FiledY - PosY);
			block_move = m_PuyoFiled.CurrentMoveBlock(BlockNS::BLOCK_MOVE_FALL_MODE);
			m_bCurrentBlockFallTimeMode = true;
		}
		break;

	default:
		break;
	}

	return block_move;
}
/*==============================================================================*/
/*																				*/
/*	[�֐�]		Update				:	�X�V����								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
void CPuyoLogic::Update()
{
	/************************/
	/*	�X�V�^�C�}�[����	*/
	/************************/
	if (!UpdateTimer())
		return;

	/****************************/
	/*	���n��̗������̔���	*/
	/****************************/
	if (m_bDroppingBlock == false)														/*	�u���b�N�`�F�b�N�������ł͂Ȃ��Ȃ��	*/
	{
		/************************/
		/*	�u���b�N�X�V����	*/
		/************************/
		if (m_PuyoFiled.CurrentMoveBlock(BlockNS::BLOCK_MOVE_DOWN))
		{
			UpdateBlock();

		}
		else
		{
			/****************************/
			/*	�Q�[���I���̔���		*/
			/****************************/
			if (m_PuyoFiled.isGameOver())
			{
				m_bFinish = true;
			}
			else																			/*	���̃u���b�N�֐i�ނȂ��				*/
			{
				/****************************/
				/*	�u���b�N�`�F�b�N����	*/
				/*	(���n��̂P��ڂ̏��� )	*/
				/****************************/
				CheckBlock();
			}
		}
	}
	else																				/*	�u���b�N�`�F�b�N�������Ȃ��			*/
	{
		/****************************/
		/*	�u���b�N�`�F�b�N����	*/
		/*	(�������̏��� )			*/
		/****************************/
		CheckBlock();
	}

	/********************/
	/*	���Ԃ̍X�V		*/
	/********************/
	m_TimeStart = m_TimeEnd;

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		UpdateBlock			:	�u���b�N�X�V����						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
void CPuyoLogic::UpdateBlock()
{
	/********************************/
	/*	���݂̃u���b�N��Ԃ�ݒ�	*/
	/********************************/
	m_PuyoFiled.SetCurrentBlockState();

	/************************************/
	/*	�u���b�N���t�B�[���h�ɃR�s�[	*/
	/************************************/
	m_PuyoFiled.CurrentBlockToBoard(0);

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CheckBlock			:	�u���b�N�`�F�b�N����					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
void CPuyoLogic::CheckBlock()
{
	/********************************/
	/*	�u���b�N�̃`�F�b�N����		*/
	/********************************/
	if (m_PuyoFiled.CheckBlockState() == true)						/*	�u���b�N�`�F�b�N�����������ςȂ��		*/
	{
		/************************/
		/*	���_�̍X�V����		*/
		/************************/
		UpdatePoint();

		/****************************/
		/*	���̃u���b�N���쐬		*/
		/****************************/
		m_PuyoFiled.NextCurrentBlock();
		m_PuyoFiled.NextWaitBlock();

		/****************************************/
		/*	���̃u���b�N���t�B�[���h�ɃR�s�[	*/
		/****************************************/
		m_PuyoFiled.CurrentBlockToBoard(2);

		/****************************/
		/*	���̃u���b�N�̑҂�����	*/
		/****************************/
		m_bDroppingBlock = false;
		Sleep(CPuyoManger::Instance()->GetPuyoNextBlockWaitTime());
	}
	else																/*	�u���b�N�`�F�b�N�������������Ȃ��		*/
	{
		m_bDroppingBlock = true;
	}

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		UpdatePoint			:	���_�̍X�V����							*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
void CPuyoLogic::UpdatePoint()
{
	unsigned char block_delete = m_PuyoFiled.GetBlockDeleteInfo();

	/************************/
	/*	���_���� ( �A�i )	*/
	/************************/
	if (block_delete & BIT0)
	{
		CPuyoManger::Instance()->SetPuyoPoint() += PUYO_SINGLE_POINTS;
	}
	else if (block_delete & BIT1)
	{
		CPuyoManger::Instance()->SetPuyoPoint() += PUYO_DOUBLE_POINTS;
	}
	else if (block_delete & BIT2)
	{
		CPuyoManger::Instance()->SetPuyoPoint() += PUYO_TRIPLE_POINTS;
	}
	else if (block_delete & BIT3)
	{
		CPuyoManger::Instance()->SetPuyoPoint() += PUYO_POINTS;
	}

	/************************/
	/*	�V���O�� ( ���� )	*/
	/************************/
	if (block_delete & BIT4)
	{
		CPuyoManger::Instance()->SetPuyoPoint() += PUYO_SINGLE_POINTS * 2;
	}

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		UpdateTimer			:	�X�V�^�C�}�[����						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*==============================================================================*/
bool CPuyoLogic::UpdateTimer()
{
	/************************************/
	/*	�X�V�^�C�}�[�̃X�s�[�h�A�b�v	*/
	/************************************/
	unsigned long	points			= CPuyoManger::Instance()->GetPuyoPoint();
	unsigned long	falling_time	= CPuyoManger::Instance()->GetPuyoFallingTime();
	
	if (	(falling_time == PUYO_FALL_TIME)
		&&	(points > PUYO_POINTS))
	{
		CPuyoManger::Instance()->SetPuyoFallingTime()		-= PUYO_FALL_TIME_SPEED_UP;
		CPuyoManger::Instance()->SetPuyoNextBlockWaitTime() += PUYO_NEXTBLOCK_WAIT_SLOW;
	}
	else if (	(falling_time == PUYO_FALL_TIME - PUYO_FALL_TIME_SPEED_UP)
			&&	(points > PUYO_POINTS * 2))
	{
		CPuyoManger::Instance()->SetPuyoFallingTime()		-= PUYO_FALL_TIME_SPEED_UP;
		CPuyoManger::Instance()->SetPuyoNextBlockWaitTime() += PUYO_NEXTBLOCK_WAIT_SLOW;
	}

	/************************/
	/*	�X�V�^�C�}�[����	*/
	/************************/
	DWORD UpDateTimer = 0;
	m_TimeEnd = timeGetTime();
	UpDateTimer = m_TimeEnd - m_TimeStart;

	if (UpDateTimer < falling_time)
	{
		return false;
	}
	else
	{
		return true;
	}

}

