/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"
#include "PuyoManger.h"
#include "PuyoFallingBlock.h"

/*----------------------------------------------------------------------*/
/*																		*/
/*	[�֐�]	CPuyoFalling_Block	:	�����Ȃ��R���X�g���N�^				*/
/*																		*/
/*----------------------------------------------------------------------*/
CPuyoFalling_Block::CPuyoFalling_Block()
{
	CPuyoFalling_Block::SetSize(3, 3);
	m_FallingBlockLeft		= 0;
	m_FallingBlockTop		= 0;
	m_FallingBlockRight		= 0;
	m_FallingBlockBottom	= 0;
}

/*----------------------------------------------------------------------*/
/*																		*/
/*	[�֐�]	CPuyoFalling_Block	:	��������R���X�g���N�^				*/
/*																		*/
/*----------------------------------------------------------------------*/
CPuyoFalling_Block::CPuyoFalling_Block(unsigned short x, unsigned short y)
{
	CPuyoFalling_Block::SetSize(x, y);
	m_FallingBlockLeft		= 0;
	m_FallingBlockTop		= 0;
	m_FallingBlockRight		= 0;
	m_FallingBlockBottom	= 0; 

}

/*--------------------------------------------------------------*/
/*																*/
/*	[�֐�]	~CPuyoFalling_Block	:	�f�X�g���N�^				*/
/*																*/
/*--------------------------------------------------------------*/
CPuyoFalling_Block::~CPuyoFalling_Block()
{
	Clear();													/*	���������			*/
	m_FallingBlockLeft		= 0;
	m_FallingBlockTop		= 0;
	m_FallingBlockRight		= 0;
	m_FallingBlockBottom	= 0;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetFallingBlockState	:	�����u���b�N�̏��					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CPuyoFalling_Block::Clear()
{
	m_FallingBlock.Clear();									/*	���������			*/
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		FallingBlockInit		:	�����u���b�N�̏�����				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CPuyoFalling_Block::FallingBlockInit()
{
	CPuyoBlock	Puyoblock(BlockNS::BLACK, BlockNS::EMPTY);

	for (int y = 0; y < m_FallingBlockY; y++)
	{
		for (int x = 0; x < m_FallingBlockX; x++)
		{
			SetBlock(x, y) = Puyoblock;
		}
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetSize					:	�����u���b�N�̃T�C�Y				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]		unsigned short			:	�u���b�N�T�C�Y ( �� )				*/
/*										:	�u���b�N�T�C�Y ( �c )				*/
/*																				*/
/*==============================================================================*/
void CPuyoFalling_Block::SetSize(unsigned short x, unsigned short y)
{
	m_FallingBlock.SetSize(x, y);
	m_FallingBlockX = x;
	m_FallingBlockY = y;
	
	return;
}


/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetFallingBlockState	:	�����u���b�N�̏��					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
void CPuyoFalling_Block::SetFallingBlockState()
{
	int x_filed = 0;
	int y_filed = 0;

	/****************************/
	/*	�u���b�N�̏�Ԃ�������	*/
	/****************************/
	m_FallingBlockLeft		= 0;
	m_FallingBlockTop		= 0;
	m_FallingBlockRight		= 0;
	m_FallingBlockBottom	= 0;

	/****************************/
	/*	�u���b�N�̈ʒu���擾	*/
	/****************************/
	for (y_filed = 0; y_filed < m_FallingBlockY; y_filed++)
	{
		for (x_filed = 0; x_filed < m_FallingBlockX; x_filed++)
		{
			if (	(m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_FallingBlockLeft >(x_filed + 1) || (m_FallingBlockLeft == 0)))
			{
				/****************************/
				/*	�u���b�N�̍��[			*/
				/****************************/
				m_FallingBlockLeft = x_filed + 1;
			}

			if (	(m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_FallingBlockRight < (x_filed + 1)))
			{
				/****************************/
				/*	�u���b�N�̉E�[			*/
				/****************************/
				m_FallingBlockRight = x_filed + 1;
			}

			if ((m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&& (m_FallingBlockTop >(y_filed + 1) || (m_FallingBlockTop == 0)))
			{
				/****************************/
				/*	�u���b�N�̏�[			*/
				/****************************/
				m_FallingBlockTop = y_filed + 1;
			}

			if (	(m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_FallingBlockBottom < (y_filed + 1)))
			{
				/****************************/
				/*	�u���b�N�̉��[			*/
				/****************************/
				m_FallingBlockBottom = y_filed + 1;
			}
		}
	}

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CreateFallingBlock		:	���݂̃u���b�N���쐬				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void					:	�Ȃ�								*/
/*	[����]		char					:	�쐬����u���b�N�̐F 				*/
/*				unsigned charr			:	�쐬����u���b�N�̒i��				*/
/*																				*/
/*==============================================================================*/
void CPuyoFalling_Block::CreateFallingBlock(char block_type, unsigned char num)
{
	CPuyoBlock	Puyoblock(BlockNS::RED, BlockNS::EXISTENCE);

	if (num == 0)			
		num = 1;

	switch (block_type)
	{
		/********/
		/*	��	*/
		/********/
	case 0:
		Puyoblock.SetBlockColor() = BlockNS::PURPLE;
		m_FallingBlock(1, num - 1) = Puyoblock;
		break;

		/********/
		/*	��	*/
		/********/
	case 1:
		Puyoblock.SetBlockColor() = BlockNS::RED;
		m_FallingBlock(1, num - 1) = Puyoblock;
		break;

		/********/
		/*	��	*/
		/********/
	case 2:
		Puyoblock.SetBlockColor() = BlockNS::BLUE;
		m_FallingBlock(1, num - 1) = Puyoblock;
		break;

		/********/
		/*	��	*/
		/********/
	case 3:
		Puyoblock.SetBlockColor() = BlockNS::GREEN;
		m_FallingBlock(1, num - 1) = Puyoblock;
		break;

		/********/
		/*	��	*/
		/********/
	case 4:
		Puyoblock.SetBlockColor() = BlockNS::YELLOW;
		m_FallingBlock(1, num - 1) = Puyoblock;
		break;

	}

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetFallingBlockLeft		:	���݂̃u���b�N�̍��[�ʒu���擾		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short			:										*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
unsigned short CPuyoFalling_Block::GetFallingBlockLeft() const
{
	return m_FallingBlockLeft;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetFallingBlockTop		:	���݂̃u���b�N�̍ŏ�[�ʒu���擾	*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short			:										*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
unsigned short CPuyoFalling_Block::GetFallingBlockTop() const
{
	return m_FallingBlockTop;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetFallingBlockRight	:	���݂̃u���b�N�̉E�[�ʒu���擾		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short			:										*/
/*	[����]								:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
unsigned short CPuyoFalling_Block::GetFallingBlockRight() const
{
	return m_FallingBlockRight;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetFallingBlockBottom	:	���݂̃u���b�N�̍ŉ��[�ʒu���擾	*/
/*				unsigned short			:										*/
/*	[����]																		*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]							:	�Ȃ�								*/
/*																				*/
/*==============================================================================*/
unsigned short CPuyoFalling_Block::GetFallingBlockBottom() const
{
	return m_FallingBlockBottom;
}


/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetBlockState			:	�u���b�N���擾						*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N���擾						*/
/*	[����]		unsigned short			:	�u���b�N�̈ʒu ( �����W )			*/
/*				unsigned short			:	�u���b�N�̈ʒu ( �c���W )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
CPuyoBlock CPuyoFalling_Block::GetBlock(long x, long y) const
{
	return m_FallingBlock(x, y);
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetBlock				:	�u���b�N��ݒ�						*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N��ݒ�						*/
/*	[����]		unsigned short			:	�u���b�N�̈ʒu ( �����W )			*/
/*				unsigned short			:	�u���b�N�̈ʒu ( �c���W )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
CPuyoBlock& CPuyoFalling_Block::SetBlock(long x, long y)
{
	return m_FallingBlock(x, y);
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetBlockColor		:	�u���b�N�̐F���擾						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short		:	�u���b�N�̐F���擾						*/
/*	[����]		unsigned short			:	�u���b�N�̈ʒu ( �����W )			*/
/*				unsigned short			:	�u���b�N�̈ʒu ( �c���W )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFalling_Block::GetBlockColor(long x, long y)
{
	return m_FallingBlock(x, y).GetBlockColor();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetBlockColor		:	�u���b�N�̐F��ݒ�						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short		:	�u���b�N�̐F��ݒ�						*/
/*	[����]		unsigned short			:	�u���b�N�̈ʒu ( �����W )			*/
/*				unsigned short			:	�u���b�N�̈ʒu ( �c���W )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CPuyoFalling_Block::SetBlockColor(long x, long y)
{
	return m_FallingBlock(x, y).SetBlockColor();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetBlockState			:	�u���b�N�����邩�ǂ������擾		*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N�̏��						*/
/*	[����]		unsigned short			:	�u���b�N�̈ʒu ( �����W )			*/
/*				unsigned short			:	�u���b�N�̈ʒu ( �c���W )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFalling_Block::GetBlockState(long x, long y)
{
	return m_FallingBlock(x, y).GetBlockState();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetBlock				:	�u���b�N�̏�Ԃ�ݒ�				*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N�̏��						*/
/*	[����]		unsigned short			:	�u���b�N�̈ʒu ( �����W )			*/
/*				unsigned short			:	�u���b�N�̈ʒu ( �c���W )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CPuyoFalling_Block::SetBlockState(long x, long y)
{
	return m_FallingBlock(x, y).SetBlockState();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetCheckBlock			:	�u���b�N���`�F�b�N�ς݂ǂ������擾	*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N�̏��						*/
/*	[����]		unsigned short			:	�u���b�N�̈ʒu ( �����W )			*/
/*				unsigned short			:	�u���b�N�̈ʒu ( �c���W )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFalling_Block::GetCheckBlock(long x, long y)
{
	return m_FallingBlock(x, y).GetCheckBlock();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetCheckBlock			:	�u���b�N���`�F�b�N�ς݂ɐݒ�		*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	unsigned short&			:	�u���b�N�̏��						*/
/*	[����]		unsigned short			:	�u���b�N�̈ʒu ( �����W )			*/
/*				unsigned short			:	�u���b�N�̈ʒu ( �c���W )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CPuyoFalling_Block::SetCheckBlock(long x, long y)
{
	return m_FallingBlock(x, y).SetCheckBlock();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetConnectBlock			:	�u���b�N�̘A����Ԃ��擾			*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	const unsigned short&	:	�u���b�N�̘A�����					*/
/*	[����]		unsigned short			:	�u���b�N�̈ʒu ( �����W )			*/
/*				unsigned short			:	�u���b�N�̈ʒu ( �c���W )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFalling_Block::GetConnectBlock(long x, long y)
{
	return m_FallingBlock(x, y).GetConnectBlock();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetConnectBlock			:	�u���b�N�̘A����Ԃ�ݒ�			*/
/*	---------------------------------------------------------------------------	*/
/*	[�߂�l]	const unsigned short&	:	�u���b�N�̘A�����					*/
/*	[����]		unsigned short			:	�u���b�N�̈ʒu ( �����W )			*/
/*				unsigned short			:	�u���b�N�̈ʒu ( �c���W )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CPuyoFalling_Block::SetConnectBlock(long x, long y)
{
	return m_FallingBlock(x, y).SetConnectBlock();
}
