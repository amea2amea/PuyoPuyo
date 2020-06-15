/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"
#include "PuyoManger.h"
#include "PuyoFallingBlock.h"

/*----------------------------------------------------------------------*/
/*																		*/
/*	[関数]	CPuyoFalling_Block	:	引数なしコンストラクタ				*/
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
/*	[関数]	CPuyoFalling_Block	:	引数ありコンストラクタ				*/
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
/*	[関数]	~CPuyoFalling_Block	:	デストラクタ				*/
/*																*/
/*--------------------------------------------------------------*/
CPuyoFalling_Block::~CPuyoFalling_Block()
{
	Clear();													/*	メモリ解放			*/
	m_FallingBlockLeft		= 0;
	m_FallingBlockTop		= 0;
	m_FallingBlockRight		= 0;
	m_FallingBlockBottom	= 0;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetFallingBlockState	:	落下ブロックの状態					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CPuyoFalling_Block::Clear()
{
	m_FallingBlock.Clear();									/*	メモリ解放			*/
}

/*==============================================================================*/
/*																				*/
/*	[関数]		FallingBlockInit		:	落下ブロックの初期化				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
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
/*	[関数]		SetSize					:	落下ブロックのサイズ				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		unsigned short			:	ブロックサイズ ( 横 )				*/
/*										:	ブロックサイズ ( 縦 )				*/
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
/*	[関数]		GetFallingBlockState	:	落下ブロックの状態					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CPuyoFalling_Block::SetFallingBlockState()
{
	int x_filed = 0;
	int y_filed = 0;

	/****************************/
	/*	ブロックの状態を初期化	*/
	/****************************/
	m_FallingBlockLeft		= 0;
	m_FallingBlockTop		= 0;
	m_FallingBlockRight		= 0;
	m_FallingBlockBottom	= 0;

	/****************************/
	/*	ブロックの位置を取得	*/
	/****************************/
	for (y_filed = 0; y_filed < m_FallingBlockY; y_filed++)
	{
		for (x_filed = 0; x_filed < m_FallingBlockX; x_filed++)
		{
			if (	(m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_FallingBlockLeft >(x_filed + 1) || (m_FallingBlockLeft == 0)))
			{
				/****************************/
				/*	ブロックの左端			*/
				/****************************/
				m_FallingBlockLeft = x_filed + 1;
			}

			if (	(m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_FallingBlockRight < (x_filed + 1)))
			{
				/****************************/
				/*	ブロックの右端			*/
				/****************************/
				m_FallingBlockRight = x_filed + 1;
			}

			if ((m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&& (m_FallingBlockTop >(y_filed + 1) || (m_FallingBlockTop == 0)))
			{
				/****************************/
				/*	ブロックの上端			*/
				/****************************/
				m_FallingBlockTop = y_filed + 1;
			}

			if (	(m_FallingBlock(x_filed, y_filed).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_FallingBlockBottom < (y_filed + 1)))
			{
				/****************************/
				/*	ブロックの下端			*/
				/****************************/
				m_FallingBlockBottom = y_filed + 1;
			}
		}
	}

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		CreateFallingBlock		:	現在のブロックを作成				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		char					:	作成するブロックの色 				*/
/*				unsigned charr			:	作成するブロックの段数				*/
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
		/*	紫	*/
		/********/
	case 0:
		Puyoblock.SetBlockColor() = BlockNS::PURPLE;
		m_FallingBlock(1, num - 1) = Puyoblock;
		break;

		/********/
		/*	赤	*/
		/********/
	case 1:
		Puyoblock.SetBlockColor() = BlockNS::RED;
		m_FallingBlock(1, num - 1) = Puyoblock;
		break;

		/********/
		/*	青	*/
		/********/
	case 2:
		Puyoblock.SetBlockColor() = BlockNS::BLUE;
		m_FallingBlock(1, num - 1) = Puyoblock;
		break;

		/********/
		/*	緑	*/
		/********/
	case 3:
		Puyoblock.SetBlockColor() = BlockNS::GREEN;
		m_FallingBlock(1, num - 1) = Puyoblock;
		break;

		/********/
		/*	黄	*/
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
/*	[関数]		GetFallingBlockLeft		:	現在のブロックの左端位置を取得		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short			:										*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
unsigned short CPuyoFalling_Block::GetFallingBlockLeft() const
{
	return m_FallingBlockLeft;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetFallingBlockTop		:	現在のブロックの最上端位置を取得	*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short			:										*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
unsigned short CPuyoFalling_Block::GetFallingBlockTop() const
{
	return m_FallingBlockTop;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetFallingBlockRight	:	現在のブロックの右端位置を取得		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short			:										*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
unsigned short CPuyoFalling_Block::GetFallingBlockRight() const
{
	return m_FallingBlockRight;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetFallingBlockBottom	:	現在のブロックの最下端位置を取得	*/
/*				unsigned short			:										*/
/*	[引数]																		*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]							:	なし								*/
/*																				*/
/*==============================================================================*/
unsigned short CPuyoFalling_Block::GetFallingBlockBottom() const
{
	return m_FallingBlockBottom;
}


/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetBlockState			:	ブロックを取得						*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックを取得						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
CPuyoBlock CPuyoFalling_Block::GetBlock(long x, long y) const
{
	return m_FallingBlock(x, y);
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetBlock				:	ブロックを設定						*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックを設定						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
CPuyoBlock& CPuyoFalling_Block::SetBlock(long x, long y)
{
	return m_FallingBlock(x, y);
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetBlockColor		:	ブロックの色を取得						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short		:	ブロックの色を取得						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFalling_Block::GetBlockColor(long x, long y)
{
	return m_FallingBlock(x, y).GetBlockColor();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetBlockColor		:	ブロックの色を設定						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short		:	ブロックの色を設定						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CPuyoFalling_Block::SetBlockColor(long x, long y)
{
	return m_FallingBlock(x, y).SetBlockColor();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetBlockState			:	ブロックがあるかどうかを取得		*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFalling_Block::GetBlockState(long x, long y)
{
	return m_FallingBlock(x, y).GetBlockState();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetBlock				:	ブロックの状態を設定				*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CPuyoFalling_Block::SetBlockState(long x, long y)
{
	return m_FallingBlock(x, y).SetBlockState();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetCheckBlock			:	ブロックがチェック済みどうかを取得	*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFalling_Block::GetCheckBlock(long x, long y)
{
	return m_FallingBlock(x, y).GetCheckBlock();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetCheckBlock			:	ブロックをチェック済みに設定		*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CPuyoFalling_Block::SetCheckBlock(long x, long y)
{
	return m_FallingBlock(x, y).SetCheckBlock();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetConnectBlock			:	ブロックの連結状態を取得			*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	const unsigned short&	:	ブロックの連結状態					*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFalling_Block::GetConnectBlock(long x, long y)
{
	return m_FallingBlock(x, y).GetConnectBlock();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetConnectBlock			:	ブロックの連結状態を設定			*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	const unsigned short&	:	ブロックの連結状態					*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CPuyoFalling_Block::SetConnectBlock(long x, long y)
{
	return m_FallingBlock(x, y).SetConnectBlock();
}
