/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "PuyoManger.h"
#include "PuyoDraw.h"

/*==============================================================================*/
/*																				*/
/*	[�֐�]		CPuyoDraw			:	�R���X�g���N�^ ( �����Ȃ� )				*/
/*																				*/
/*==============================================================================*/
CPuyoDraw::CPuyoDraw() :m_PuyoFiled(CPuyoManger::Instance()->GetPuyoFiled())
{
	m_BlockRect.SetSize(m_PuyoFiled.PUYO_FILED_SIZE_X + m_PuyoFiled.PUYO_FILED_START_X + 2, m_PuyoFiled.PUYO_FILED_SIZE_Y + m_PuyoFiled.PUYO_FILED_START_Y + 2);
	m_WaitBlockRect.SetSize(m_PuyoFiled.CURRENT_BLOCK_X, m_PuyoFiled.CURRENT_BLOCK_Y);
	m_WaitNextBlockRect.SetSize(m_PuyoFiled.CURRENT_BLOCK_X, m_PuyoFiled.CURRENT_BLOCK_Y);
	m_LandingBlockRect.SetSize(m_PuyoFiled.CURRENT_BLOCK_X, m_PuyoFiled.CURRENT_BLOCK_Y);
	InitBlockRect();
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		~CPuyoDraw		:	�f�X�g���N�^								*/
/*																				*/
/*==============================================================================*/
CPuyoDraw::~CPuyoDraw()
{
	m_BlockRect.Clear();
	m_WaitBlockRect.Clear();
	m_WaitNextBlockRect.Clear();
	m_LandingBlockRect.Clear();
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		Draw				:	�`��									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoDraw::Draw()
{
	/****************************/
	/*	�e�L�X�g�̕`��			*/
	/****************************/
	SetPuyoText();

	/****************************/
	/*	�`��̐ݒ�				*/
	/****************************/
	SetPuyoColor();

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		LoadBitmapPuyo		:	�r�b�g�}�b�v����ǂݍ���				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]		HINSTANCE			:											*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoDraw::LoadBitmapPuyo(HINSTANCE hInstance)
{	
	/********************************/
	/*	�r�b�g�}�b�v����ǂݍ���	*/
	/********************************/
	m_PuyoBitmapInfo.LoadBitmapPuyo(hInstance);

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetPuyoText			:	�Ղ�Ղ�̃e�L�X�g�ݒ�					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoDraw::SetPuyoText()
{
	unsigned long	x_start					= (m_PuyoFiled.PUYO_FILED_SIZE_X + m_PuyoFiled.PUYO_FILED_START_X + 2) * PUYO_BLOCK_PIXEL_SIZE_X;
	unsigned long	y_start					= 2;
	unsigned long	color					= RGB(255, 255, 255);
	unsigned long	points					= CPuyoManger::Instance()->GetPuyoPoint();
	unsigned long	falling_time			= CPuyoManger::Instance()->GetPuyoFallingTime();
	int const		arraysize				= 8;
	char			Puyodisp[arraysize] = {};
	size_t			cbDest					= arraysize * sizeof(char);
	std::string		str_score("[ SCORE ] ");
	std::string		str_falling_time("[ Falling Time ] ");
	std::string		str_next_block("[ Next Block1 ] ");
	std::string		str_next_wait_block("[ Next Block2 ] ");

	/********************/
	/*	�^�C�g���\��	*/
	/********************/
	SetTextOut(x_start, PuyoDrawNS::SCORE_TITLE, str_score, 0, color);
	SetTextOut(x_start, PuyoDrawNS::FALL_TIME_TITLE, str_falling_time, 0, color);
	SetTextOut(x_start, PuyoDrawNS::NEXT_BLOCK_TITLE, str_next_block, 0, color);
	SetTextOut(x_start, PuyoDrawNS::NEXT_WAIT_BLOCK_TITLE, str_next_wait_block, 0, color);

	/****************/
	/*	���_�\��	*/
	/****************/
	sprintf_s(Puyodisp, cbDest, "%lu", points);
	SetTextOut(x_start, PuyoDrawNS::SCORE, Puyodisp, 0, color);

	/********************/
	/*	�������ԕ\��	*/
	/********************/
	sprintf_s(Puyodisp, cbDest, "%lu ms",falling_time);
	SetTextOut(x_start, PuyoDrawNS::FALL_TIME, Puyodisp, 0, color);

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetPuyoColor		:	�Ղ�Ղ̕`��ݒ�						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoDraw::SetPuyoColor()
{
	unsigned long	line_color	= RGB(255, 255, 255);

	/************************************/
	/*	�`��̐ݒ� ( �������u���b�N )	*/
	/************************************/
	for (int y_filed = 0; y_filed < m_PuyoFiled.CURRENT_BLOCK_Y; y_filed++)
	{
		for (int x_filed = 0; x_filed < m_PuyoFiled.CURRENT_BLOCK_X; x_filed++)
		{
			if (m_PuyoFiled.GetBlockState(x_filed, y_filed, BlockNS::LANDING_BLOCK) == BlockNS::EXISTENCE)
			{
				m_LandingBlockRect(x_filed, y_filed).left	= (x_filed + m_PuyoFiled.GetBlockTopPosX(BlockNS::LANDING_BLOCK)) * PUYO_BLOCK_PIXEL_SIZE_X;
				m_LandingBlockRect(x_filed, y_filed).right	= m_LandingBlockRect(x_filed, y_filed).left + PUYO_BLOCK_PIXEL_SIZE_X;
				m_LandingBlockRect(x_filed, y_filed).top	= (y_filed + m_PuyoFiled.GetBlockTopPosY(BlockNS::LANDING_BLOCK)) * PUYO_BLOCK_PIXEL_SIZE_Y;
				m_LandingBlockRect(x_filed, y_filed).bottom = m_LandingBlockRect(x_filed, y_filed).top + PUYO_BLOCK_PIXEL_SIZE_Y;

				SetBitmap(		m_LandingBlockRect(x_filed, y_filed).left
							,	m_LandingBlockRect(x_filed, y_filed).top
							,	m_LandingBlockRect(x_filed, y_filed).right
							,	m_LandingBlockRect(x_filed, y_filed).bottom
							,	ImageNS::TRANSPARENT_MODE
							,	GetBitmapHandle(x_filed, y_filed, BlockNS::LANDING_BLOCK)
							,	RGB(0, 0, 255)
					);
/*
				SetRectAngle(	m_LandingBlockRect(x_filed, y_filed).left + PUYO_BLOCK_MARGIN_LEFT
							,	m_LandingBlockRect(x_filed, y_filed).top + PUYO_BLOCK_MARGIN_TOP
							,	m_LandingBlockRect(x_filed, y_filed).right - PUYO_BLOCK_MARGIN_RIGHT
							,	m_LandingBlockRect(x_filed, y_filed).bottom - PUYO_BLOCK_MARGIN_BOTTOM
							,	PS_SOLID
							,	1
							,	line_color
							,	GetColor(x_filed, y_filed, BlockNS::LANDING_BLOCK)
					);
*/
			}
		}
	}

	/********************************/
	/*	�`��̐ݒ� ( �t�B�[���h )	*/
	/********************************/
	for (int y_filed = 0; y_filed < (m_PuyoFiled.PUYO_FILED_SIZE_Y + m_PuyoFiled.PUYO_FILED_START_Y + 2); y_filed++)
	{
		for (int x_filed = 0; x_filed < (m_PuyoFiled.PUYO_FILED_SIZE_X + m_PuyoFiled.PUYO_FILED_START_X + 2); x_filed++)
		{
			if(m_PuyoFiled.GetBlockState(x_filed, y_filed, BlockNS::FILED_BLOCK) == BlockNS::EXISTENCE)
			{ 
				SetBitmap(		m_BlockRect(x_filed, y_filed).left
							,	m_BlockRect(x_filed, y_filed).top
							,	m_BlockRect(x_filed, y_filed).right
							,	m_BlockRect(x_filed, y_filed).bottom
							,	ImageNS::TRANSPARENT_MODE
							,	GetBitmapHandle(x_filed, y_filed, BlockNS::FILED_BLOCK)
							,	RGB(0, 0, 255)
					);
/*
				SetArc(			m_BlockRect(x_filed, y_filed).left + PUYO_BLOCK_MARGIN_LEFT
							,	m_BlockRect(x_filed, y_filed).top + PUYO_BLOCK_MARGIN_TOP
							,	m_BlockRect(x_filed, y_filed).right	- PUYO_BLOCK_MARGIN_RIGHT
							,	m_BlockRect(x_filed, y_filed).bottom - PUYO_BLOCK_MARGIN_BOTTOM
							,	PS_SOLID
							,	1
							,	line_color
							,	GetColor(x_filed, y_filed, BlockNS::FILED_BLOCK)
						);
*/
			}
			else if (m_PuyoFiled.GetBlockState(x_filed, y_filed, BlockNS::FILED_BLOCK) == BlockNS::WALL)
			{
				SetRectAngle(	m_BlockRect(x_filed, y_filed).left + PUYO_BLOCK_MARGIN_LEFT
							,	m_BlockRect(x_filed, y_filed).top + PUYO_BLOCK_MARGIN_TOP
							,	m_BlockRect(x_filed, y_filed).right - PUYO_BLOCK_MARGIN_RIGHT
							,	m_BlockRect(x_filed, y_filed).bottom - PUYO_BLOCK_MARGIN_BOTTOM
							,	PS_SOLID
							,	1
							,	line_color
							,	GetColor(x_filed, y_filed, BlockNS::FILED_BLOCK)
					);
			}
		}
	}

	/************************************/
	/*	�`��̐ݒ� ( �ҋ@�u���b�N )		*/
	/************************************/
	for (int y_filed = 0; y_filed < m_PuyoFiled.CURRENT_BLOCK_Y; y_filed++)
	{
		for (int x_filed = 0; x_filed < m_PuyoFiled.CURRENT_BLOCK_X; x_filed++)
		{
			if (m_PuyoFiled.GetBlockState(x_filed, y_filed, BlockNS::WAIT_BLOCK) == BlockNS::EXISTENCE)
			{
				SetBitmap(		m_WaitBlockRect(x_filed, y_filed).left
						,		m_WaitBlockRect(x_filed, y_filed).top
						,		m_WaitBlockRect(x_filed, y_filed).right
						,		m_WaitBlockRect(x_filed, y_filed).bottom
						,		ImageNS::TRANSPARENT_MODE
						,		GetBitmapHandle(x_filed, y_filed, BlockNS::WAIT_BLOCK)
						,		RGB(0, 0, 255)
					);

/*
				SetArc(			m_WaitBlockRect(x_filed, y_filed).left + PUYO_BLOCK_MARGIN_LEFT
							,	m_WaitBlockRect(x_filed, y_filed).top + PUYO_BLOCK_MARGIN_TOP
							,	m_WaitBlockRect(x_filed, y_filed).right - PUYO_BLOCK_MARGIN_RIGHT
							,	m_WaitBlockRect(x_filed, y_filed).bottom - PUYO_BLOCK_MARGIN_BOTTOM
							,	PS_SOLID
							,	1
							,	line_color
							,	GetColor(x_filed, y_filed, BlockNS::WAIT_BLOCK)
					);
*/
			}
		}
	}

	/****************************************/
	/*	�`��̐ݒ� ( ���̑ҋ@�u���b�N )		*/
	/****************************************/
	for (int y_filed = 0; y_filed < m_PuyoFiled.CURRENT_BLOCK_Y; y_filed++)
	{
		for (int x_filed = 0; x_filed < m_PuyoFiled.CURRENT_BLOCK_X; x_filed++)
		{
			if (m_PuyoFiled.GetBlockState(x_filed, y_filed, BlockNS::WAIT_NEXT_BLOCK) == BlockNS::EXISTENCE)
			{
				SetBitmap(	m_WaitNextBlockRect(x_filed, y_filed).left
						,	m_WaitNextBlockRect(x_filed, y_filed).top
						,	m_WaitNextBlockRect(x_filed, y_filed).right
						,	m_WaitNextBlockRect(x_filed, y_filed).bottom
						,	ImageNS::TRANSPARENT_MODE
						,	GetBitmapHandle(x_filed, y_filed, BlockNS::WAIT_NEXT_BLOCK)
						,	RGB(0, 0, 255)
				);
/*
				SetArc(			m_WaitNextBlockRect(x_filed, y_filed).left + PUYO_BLOCK_MARGIN_LEFT
							,	m_WaitNextBlockRect(x_filed, y_filed).top + PUYO_BLOCK_MARGIN_TOP
							,	m_WaitNextBlockRect(x_filed, y_filed).right - PUYO_BLOCK_MARGIN_RIGHT
							,	m_WaitNextBlockRect(x_filed, y_filed).bottom - PUYO_BLOCK_MARGIN_BOTTOM
							,	PS_SOLID
							,	1
							,	line_color
							,	GetColor(x_filed, y_filed, BlockNS::WAIT_NEXT_BLOCK)
					);
*/
			}
		}
	}

	return;

}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetColor			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short		:	�u���b�N�̐F���擾						*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
COLORREF CPuyoDraw::GetColor(long x, long y, char type)
{
	unsigned long block_color		= 0;
	unsigned long color				= 0;

	/****************************/
	/*	�e��u���b�N�̐F���擾	*/
	/****************************/
	block_color = m_PuyoFiled.GetBlockColor(x, y, type);

	switch (block_color)
	{
		case BlockNS::BLACK:					/*	��							*/
			color = RGB(0, 0, 0);
			break;

		case BlockNS::WHITE:					/*	��							*/
			color = RGB(255, 255, 255);
			break;

		case BlockNS::LIGHTGRAY:				/*	���C�g�O���C ( �W���O���C )	*/
			color = RGB(200, 200, 200);
			break;

		case BlockNS::DIMGRAY:					/*	�f�B���O���C ( �Â��O���C )	*/
			color = RGB(105, 105, 105);
			break;

		case BlockNS::GRAY:						/*	�O���C						*/
			color = RGB(128, 128, 128);
			break;

		case BlockNS::RED:						/*	��							*/
			color = RGB(255, 0, 0);
			break;

		case BlockNS::YELLOW:					/*	��							*/
			color = RGB(255, 255, 0);
			break;

		case BlockNS::PURPLE:					/*	��							*/
			color = RGB(130, 49, 142);
			break;

		case BlockNS::PINK:						/*	�s���N						*/
			color = RGB(255, 20, 147);
			break;
			
		case BlockNS::GREEN:					/*	��							*/
			color = RGB(0, 255, 0);
			break;

		case BlockNS::BLUE:						/*	��							*/
			color = RGB(0, 0, 255);
			break;

		case BlockNS::CYAN:						/*	�V�A��						*/
			color = RGB(0, 255, 255);
			break;

		case BlockNS::ORANGE:					/*	�I�����W					*/
			color = RGB(255, 165, 0);
			break;

		default:
			break;
	}

	return color;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetBitmapHandle		:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short		:	�r�b�g�}�b�v�̃^�C�v���擾				*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
HBITMAP CPuyoDraw::GetBitmapHandle(long x, long y, char type)
{
	HBITMAP						hbitmap			= 0;
	unsigned long				color			= 0;
	BitmapNS::Puyo_Bitmap		connect_type	= BitmapNS::PUYOPUYO_NORMAL_TYPE;

	/****************************/
	/*	�e��u���b�N�̐F���擾	*/
	/****************************/
	color = m_PuyoFiled.GetBlockColor(x, y, type);

	/****************************/
	/*	������Ԃ��擾			*/
	/****************************/
	connect_type = GetConnectType(x, y, type);

	/****************************/
	/*	�e��u���b�N�̐F���擾	*/
	/****************************/
	switch (color)
	{
	case BlockNS::DIMGRAY:						/*	�O���C						*/
		hbitmap = m_PuyoBitmapInfo.GetBitmapHandleBlackPuyo(connect_type);
		break;

	case BlockNS::RED:						/*	��							*/
		hbitmap = m_PuyoBitmapInfo.GetBitmapHandleRedPuyo(connect_type);
		break;

	case BlockNS::YELLOW:					/*	��							*/
		hbitmap = m_PuyoBitmapInfo.GetBitmapHandleYellowPuyo(connect_type);
		break;

	case BlockNS::PURPLE:					/*	��							*/
		hbitmap = m_PuyoBitmapInfo.GetBitmapHandlePurplePuyo(connect_type);
		break;

	case BlockNS::GREEN:					/*	��							*/
		hbitmap = m_PuyoBitmapInfo.GetBitmapHandleGreenPuyo(connect_type);
		break;

	case BlockNS::BLUE:						/*	��							*/
		hbitmap = m_PuyoBitmapInfo.GetBitmapHandleBluePuyo(connect_type);
		break;

	default:
		break;
	}

	return hbitmap;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetConnectType		:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned short		:	�r�b�g�}�b�v�̃^�C�v���擾				*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
BitmapNS::Puyo_Bitmap CPuyoDraw::GetConnectType(long x, long y, char type)
{
	/****************************/
	/*	������Ԃ��擾			*/
	/****************************/
	unsigned short			connect_block = m_PuyoFiled.GetConnectBlock(x, y, type);
	BitmapNS::Puyo_Bitmap	connect_type = BitmapNS::PUYOPUYO_NORMAL_TYPE;

	if (connect_block == (BlockNS::BLOCK_CONNECT_LEFT | BlockNS::BLOCK_CONNECT_TOP | BlockNS::BLOCK_CONNECT_RIGHT | BlockNS::BLOCK_CONNECT_BOTTOM))
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_ALL_TYPE;
	}
	else if (connect_block == (BlockNS::BLOCK_CONNECT_LEFT | BlockNS::BLOCK_CONNECT_TOP | BlockNS::BLOCK_CONNECT_RIGHT))
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_RIGHT_TYPE;
	}
	else if (connect_block == (BlockNS::BLOCK_CONNECT_LEFT | BlockNS::BLOCK_CONNECT_TOP | BlockNS::BLOCK_CONNECT_BOTTOM))
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM_TYPE;
	}
	else if (connect_block == (BlockNS::BLOCK_CONNECT_LEFT | BlockNS::BLOCK_CONNECT_RIGHT | BlockNS::BLOCK_CONNECT_BOTTOM))
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM_TYPE;
	}
	else if (connect_block == (BlockNS::BLOCK_CONNECT_TOP | BlockNS::BLOCK_CONNECT_RIGHT | BlockNS::BLOCK_CONNECT_BOTTOM))
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM_TYPE;
	}
	else if (connect_block == (BlockNS::BLOCK_CONNECT_LEFT | BlockNS::BLOCK_CONNECT_TOP))
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_TYPE;
	}
	else if (connect_block == (BlockNS::BLOCK_CONNECT_LEFT | BlockNS::BLOCK_CONNECT_RIGHT))
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_LEFT_RIGHT_TYPE;
	}
	else if (connect_block == (BlockNS::BLOCK_CONNECT_LEFT | BlockNS::BLOCK_CONNECT_BOTTOM))
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_LEFT_BOTTOM_TYPE;
	}
	else if (connect_block == (BlockNS::BLOCK_CONNECT_TOP | BlockNS::BLOCK_CONNECT_RIGHT))
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_TOP_RIGHT_TYPE;
	}
	else if (connect_block == (BlockNS::BLOCK_CONNECT_TOP | BlockNS::BLOCK_CONNECT_BOTTOM))
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_TOP_BOTTOM_TYPE;
	}
	else if (connect_block == (BlockNS::BLOCK_CONNECT_RIGHT | BlockNS::BLOCK_CONNECT_BOTTOM))
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_RIGHT_BOTTOM_TYPE;
	}
	else if (connect_type == BlockNS::BLOCK_CONNECT_LEFT)
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_LEFT_TYPE;
	}
	else if (connect_block == BlockNS::BLOCK_CONNECT_TOP)
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_TOP_TYPE;
	}
	else if (connect_block == BlockNS::BLOCK_CONNECT_RIGHT)
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_RIGHT_TYPE;
	}
	else if (connect_block == BlockNS::BLOCK_CONNECT_BOTTOM)
	{
		connect_type = BitmapNS::PUYOPUYO_CONNECT_BOTTOM_TYPE;
	}
	else
	{
		connect_type = BitmapNS::PUYOPUYO_NORMAL_TYPE;
	}

	return connect_type;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		InitBlockRect		:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]		void				:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoDraw::InitBlockRect()
{
	unsigned long	x_start = (m_PuyoFiled.PUYO_FILED_SIZE_X + m_PuyoFiled.PUYO_FILED_START_X + 2) * PUYO_BLOCK_PIXEL_SIZE_X;
	unsigned long	y_start = PuyoDrawNS::NEXT_BLOCK;

	for (int y_filed = 0; y_filed < m_PuyoFiled.PUYO_FILED_SIZE_Y + m_PuyoFiled.PUYO_FILED_START_Y + 2; y_filed++)
	{
		for (int x_filed = 0; x_filed < m_PuyoFiled.PUYO_FILED_SIZE_X + m_PuyoFiled.PUYO_FILED_START_X + 2; x_filed++)
		{
			m_BlockRect(x_filed, y_filed).left		= x_filed * PUYO_BLOCK_PIXEL_SIZE_X;
			m_BlockRect(x_filed, y_filed).right		= m_BlockRect(x_filed, y_filed).left + PUYO_BLOCK_PIXEL_SIZE_X;
			m_BlockRect(x_filed, y_filed).top		= y_filed * PUYO_BLOCK_PIXEL_SIZE_Y;
			m_BlockRect(x_filed, y_filed).bottom	= m_BlockRect(x_filed, y_filed).top + PUYO_BLOCK_PIXEL_SIZE_Y;
		}
	}

	for (int y_filed = 0; y_filed < m_PuyoFiled.CURRENT_BLOCK_Y; y_filed++)
	{
		for (int x_filed = 0; x_filed < m_PuyoFiled.CURRENT_BLOCK_X; x_filed++)
		{
			m_WaitBlockRect(x_filed, y_filed).left		= x_filed * PUYO_BLOCK_PIXEL_SIZE_X + x_start;
			m_WaitBlockRect(x_filed, y_filed).right		= m_WaitBlockRect(x_filed, y_filed).left + PUYO_BLOCK_PIXEL_SIZE_X;
			m_WaitBlockRect(x_filed, y_filed).top		= ( y_filed + PuyoDrawNS::NEXT_BLOCK) * PUYO_BLOCK_PIXEL_SIZE_Y;
			m_WaitBlockRect(x_filed, y_filed).bottom	= m_WaitBlockRect(x_filed, y_filed).top + PUYO_BLOCK_PIXEL_SIZE_Y;
		}
	}
	
	for (int y_filed = 0; y_filed < m_PuyoFiled.CURRENT_BLOCK_Y; y_filed++)
	{
		for (int x_filed = 0; x_filed < m_PuyoFiled.CURRENT_BLOCK_X; x_filed++)
		{
			m_WaitNextBlockRect(x_filed, y_filed).left		= x_filed * PUYO_BLOCK_PIXEL_SIZE_X + x_start;
			m_WaitNextBlockRect(x_filed, y_filed).right		= m_WaitNextBlockRect(x_filed, y_filed).left + PUYO_BLOCK_PIXEL_SIZE_X;
			m_WaitNextBlockRect(x_filed, y_filed).top		= (y_filed + PuyoDrawNS::NEXT_WAIT_BLOCK) * PUYO_BLOCK_PIXEL_SIZE_Y;
			m_WaitNextBlockRect(x_filed, y_filed).bottom	= m_WaitNextBlockRect(x_filed, y_filed).top + PUYO_BLOCK_PIXEL_SIZE_Y;
		}
	}

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		GetRectAngle		:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	Block_Rect			:											*/
/*	[����]		long 				:											*/
/*				long 				:											*/
/*																				*/
/*------------------------------------------------------------------------------*/
Block_Rect CPuyoDraw::GetBlockRect(long x_index, long y_index)
{
	Block_Rect block_rect;

	block_rect.left		= m_BlockRect(x_index, y_index).left;
	block_rect.right	= m_BlockRect(x_index, y_index).right;
	block_rect.top		= m_BlockRect(x_index, y_index).top;
	block_rect.bottom	= m_BlockRect(x_index, y_index).bottom;
	
	return block_rect;
}


/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		SetRectAngle		:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]		long 				:											*/
/*				long 				:											*/
/*				Block_Rect			:											*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoDraw::SetBlockRect(long x_index, long y_index, Block_Rect block_rect)
{
	m_BlockRect(x_index, y_index).left		= block_rect.left;
	m_BlockRect(x_index, y_index).right		= block_rect.right;
	m_BlockRect(x_index, y_index).top		= block_rect.top;
	m_BlockRect(x_index, y_index).bottom	= block_rect.bottom;

	return;
}