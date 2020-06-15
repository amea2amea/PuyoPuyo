/*------------------*/
/* インクルード		*/
/*------------------*/
#include "PuyoManger.h"
#include "PuyoDraw.h"

/*==============================================================================*/
/*																				*/
/*	[関数]		CPuyoDraw			:	コンストラクタ ( 引数なし )				*/
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
/*	[関数]		~CPuyoDraw		:	デストラクタ								*/
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
/*	[関数]		Draw				:	描画									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoDraw::Draw()
{
	/****************************/
	/*	テキストの描画			*/
	/****************************/
	SetPuyoText();

	/****************************/
	/*	描画の設定				*/
	/****************************/
	SetPuyoColor();

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		LoadBitmapPuyo		:	ビットマップ情報を読み込む				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]		HINSTANCE			:											*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoDraw::LoadBitmapPuyo(HINSTANCE hInstance)
{	
	/********************************/
	/*	ビットマップ情報を読み込む	*/
	/********************************/
	m_PuyoBitmapInfo.LoadBitmapPuyo(hInstance);

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetPuyoText			:	ぷよぷよのテキスト設定					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
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
	/*	タイトル表示	*/
	/********************/
	SetTextOut(x_start, PuyoDrawNS::SCORE_TITLE, str_score, 0, color);
	SetTextOut(x_start, PuyoDrawNS::FALL_TIME_TITLE, str_falling_time, 0, color);
	SetTextOut(x_start, PuyoDrawNS::NEXT_BLOCK_TITLE, str_next_block, 0, color);
	SetTextOut(x_start, PuyoDrawNS::NEXT_WAIT_BLOCK_TITLE, str_next_wait_block, 0, color);

	/****************/
	/*	得点表示	*/
	/****************/
	sprintf_s(Puyodisp, cbDest, "%lu", points);
	SetTextOut(x_start, PuyoDrawNS::SCORE, Puyodisp, 0, color);

	/********************/
	/*	落下時間表示	*/
	/********************/
	sprintf_s(Puyodisp, cbDest, "%lu ms",falling_time);
	SetTextOut(x_start, PuyoDrawNS::FALL_TIME, Puyodisp, 0, color);

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetPuyoColor		:	ぷよぷの描画設定						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoDraw::SetPuyoColor()
{
	unsigned long	line_color	= RGB(255, 255, 255);

	/************************************/
	/*	描画の設定 ( 落下中ブロック )	*/
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
	/*	描画の設定 ( フィールド )	*/
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
	/*	描画の設定 ( 待機ブロック )		*/
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
	/*	描画の設定 ( 次の待機ブロック )		*/
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
/*	[関数]		GetColor			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short		:	ブロックの色を取得						*/
/*	[引数]							:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
COLORREF CPuyoDraw::GetColor(long x, long y, char type)
{
	unsigned long block_color		= 0;
	unsigned long color				= 0;

	/****************************/
	/*	各種ブロックの色を取得	*/
	/****************************/
	block_color = m_PuyoFiled.GetBlockColor(x, y, type);

	switch (block_color)
	{
		case BlockNS::BLACK:					/*	黒							*/
			color = RGB(0, 0, 0);
			break;

		case BlockNS::WHITE:					/*	白							*/
			color = RGB(255, 255, 255);
			break;

		case BlockNS::LIGHTGRAY:				/*	ライトグレイ ( 淡いグレイ )	*/
			color = RGB(200, 200, 200);
			break;

		case BlockNS::DIMGRAY:					/*	ディムグレイ ( 暗いグレイ )	*/
			color = RGB(105, 105, 105);
			break;

		case BlockNS::GRAY:						/*	グレイ						*/
			color = RGB(128, 128, 128);
			break;

		case BlockNS::RED:						/*	赤							*/
			color = RGB(255, 0, 0);
			break;

		case BlockNS::YELLOW:					/*	黄							*/
			color = RGB(255, 255, 0);
			break;

		case BlockNS::PURPLE:					/*	紫							*/
			color = RGB(130, 49, 142);
			break;

		case BlockNS::PINK:						/*	ピンク						*/
			color = RGB(255, 20, 147);
			break;
			
		case BlockNS::GREEN:					/*	緑							*/
			color = RGB(0, 255, 0);
			break;

		case BlockNS::BLUE:						/*	青							*/
			color = RGB(0, 0, 255);
			break;

		case BlockNS::CYAN:						/*	シアン						*/
			color = RGB(0, 255, 255);
			break;

		case BlockNS::ORANGE:					/*	オレンジ					*/
			color = RGB(255, 165, 0);
			break;

		default:
			break;
	}

	return color;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetBitmapHandle		:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short		:	ビットマップのタイプを取得				*/
/*	[引数]							:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
HBITMAP CPuyoDraw::GetBitmapHandle(long x, long y, char type)
{
	HBITMAP						hbitmap			= 0;
	unsigned long				color			= 0;
	BitmapNS::Puyo_Bitmap		connect_type	= BitmapNS::PUYOPUYO_NORMAL_TYPE;

	/****************************/
	/*	各種ブロックの色を取得	*/
	/****************************/
	color = m_PuyoFiled.GetBlockColor(x, y, type);

	/****************************/
	/*	結合状態を取得			*/
	/****************************/
	connect_type = GetConnectType(x, y, type);

	/****************************/
	/*	各種ブロックの色を取得	*/
	/****************************/
	switch (color)
	{
	case BlockNS::DIMGRAY:						/*	グレイ						*/
		hbitmap = m_PuyoBitmapInfo.GetBitmapHandleBlackPuyo(connect_type);
		break;

	case BlockNS::RED:						/*	赤							*/
		hbitmap = m_PuyoBitmapInfo.GetBitmapHandleRedPuyo(connect_type);
		break;

	case BlockNS::YELLOW:					/*	黄							*/
		hbitmap = m_PuyoBitmapInfo.GetBitmapHandleYellowPuyo(connect_type);
		break;

	case BlockNS::PURPLE:					/*	紫							*/
		hbitmap = m_PuyoBitmapInfo.GetBitmapHandlePurplePuyo(connect_type);
		break;

	case BlockNS::GREEN:					/*	緑							*/
		hbitmap = m_PuyoBitmapInfo.GetBitmapHandleGreenPuyo(connect_type);
		break;

	case BlockNS::BLUE:						/*	青							*/
		hbitmap = m_PuyoBitmapInfo.GetBitmapHandleBluePuyo(connect_type);
		break;

	default:
		break;
	}

	return hbitmap;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetConnectType		:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short		:	ビットマップのタイプを取得				*/
/*	[引数]							:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
BitmapNS::Puyo_Bitmap CPuyoDraw::GetConnectType(long x, long y, char type)
{
	/****************************/
	/*	結合状態を取得			*/
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
/*	[関数]		InitBlockRect		:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]		void				:	なし									*/
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
/*	[関数]		GetRectAngle		:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	Block_Rect			:											*/
/*	[引数]		long 				:											*/
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
/*	[関数]		SetRectAngle		:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]		long 				:											*/
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