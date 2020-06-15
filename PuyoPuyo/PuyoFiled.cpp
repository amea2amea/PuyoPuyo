/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"
#include "PuyoManger.h"
#include "PuyoFiled.h"

/*--------------------------------------------------------------*/
/*																*/
/*	[関数]	CPuyoFiled	:	const引数なしコンストラクタ			*/
/*																*/
/*--------------------------------------------------------------*/
CPuyoFiled::CPuyoFiled()
{
	m_Block.SetSize(PUYO_FILED_SIZE_X + PUYO_FILED_START_X + 2, PUYO_FILED_SIZE_Y + PUYO_FILED_START_Y + 2);
	m_CurrentBlock.SetSize(CURRENT_BLOCK_X, CURRENT_BLOCK_Y);
	m_WaitBlock.SetSize(CURRENT_BLOCK_X, CURRENT_BLOCK_Y);
	m_WaitNextBlock.SetSize(CURRENT_BLOCK_X, CURRENT_BLOCK_Y);
	m_LandingBlock.SetSize(CURRENT_BLOCK_X, CURRENT_BLOCK_Y);
	m_CurrentBlockTopPosX			= 0;
	m_CurrentBlockTopPosY			= 0;
	m_LandingBlockTopPosX			= 0;
	m_LandingBlockTopPosY			= 0;
	m_CurrentBlockRotatinAngle		= 0;
	m_BlockColorNum					= PUYO_COLOR_NUM;
	m_DeleteChainBlockCount			= 0;
	m_DeleteChainBlockCurrentCount	= 0;
	m_DeleteChainBlockMaxCount		= 0;
	Init();
}

/*--------------------------------------------------------------*/
/*																*/
/*	[関数]	~CPuyoFiled	:	デストラクタ						*/
/*																*/
/*--------------------------------------------------------------*/
CPuyoFiled::~CPuyoFiled()
{
	m_Block.Clear();						/*				*/
	m_CurrentBlock.Clear();					/*				*/
	m_WaitBlock.Clear();					/*				*/
	m_WaitNextBlock.Clear();				/*				*/
	m_LandingBlock.Clear();					/*				*/
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		Init				:	初期化									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]		void				:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoFiled::Init()
{
	CPuyoBlock	Puyoblock(BlockNS::BLACK, BlockNS::EMPTY);
	CPuyoBlock	Puyowall(BlockNS::GRAY, BlockNS::WALL);

	/********************************/
	/*	フィールド位置の初期化		*/
	/********************************/
	for (int x = PUYO_FILED_START_X; x < PUYO_FILED_START_X + PUYO_FILED_SIZE_X; x++)
	{
		for (int y = PUYO_FILED_START_Y; y < PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y; y++)
		{
			m_Block(x, y) = Puyoblock;																/*	フィールド位置の情報を初期化					*/
		}
	}

	/************************/
	/*	壁の設定			*/
	/************************/
	for (int x = PUYO_FILED_START_X - 1; x <= PUYO_FILED_START_X + PUYO_FILED_SIZE_X; x++)
	{
		m_Block(x, PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y) = Puyowall;							/*	壁の設定 ( 1番下 )								*/
	}

	for (int y = PUYO_FILED_START_Y; y <= PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y; y++)
	{
		m_Block(PUYO_FILED_START_X - 1, y) = Puyowall;											/*	壁の設定 ( 左端 )								*/
		m_Block(PUYO_FILED_START_X + PUYO_FILED_SIZE_X, y) = Puyowall;							/*	壁の設定 ( 右端 )								*/
	}

	/************************/
	/*	乱数の初期化		*/
	/************************/
	srand((unsigned int)time(NULL));

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		isGameOver			:											*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool				:	ゲーム終了( 0:しない	1:する )		*/
/*	[引数]							:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CPuyoFiled::isGameOver()
{
	bool			GameOver		= false;
	char			block_count		= 0;
	CPuyoBlock		Puyoblock(BlockNS::BLACK, BlockNS::EMPTY);

	/********************************/
	/*	1列ブロックの埋まりを判定	*/
	/********************************/
	for (int x = PUYO_FILED_START_X; x < PUYO_FILED_START_X + PUYO_FILED_SIZE_X; x++)
	{
		block_count = 0;

		for (int y = PUYO_FILED_START_Y; y < PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y; y++)
		{
			if (m_Block(x, y).GetBlockState() == BlockNS::EXISTENCE)
			{
				block_count++;												

				if (	(block_count == PUYO_FILED_SIZE_Y)													/*	縦列にブロックが埋まっており			*/
					&&	(m_Block(x, PUYO_FILED_START_Y - 1).GetBlockState() == BlockNS::EXISTENCE))			/*	フィールド外にブロックがあるならば		*/
				{
						GameOver = true;
						break;
				}
			}
		}
	}

	/********************************/
	/*	ゲームオーバー処理			*/
	/********************************/
	if (GameOver)
	{
		/********************************/
		/*	ブロックをグレイ色に設定	*/
		/********************************/
		for (int x = PUYO_FILED_START_X; x < PUYO_FILED_START_X + PUYO_FILED_SIZE_X; x++)
		{
			for (int y = 0; y < PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y; y++)
			{
				if (m_Block(x, y).GetBlockState() == BlockNS::EXISTENCE)
				{
					m_Block(x, y).SetBlockColor() = BlockNS::DIMGRAY;												/*	フィールド位置の情報を初期化					*/
				}
			}
		}
	}

	return GameOver;
}

/*======================================================================================*/
/*																						*/
/*	[関数]		FallingBlockToBoard		:	落下ブロックをフィールドにコピー			*/
/*																						*/
/*	------------------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし										*/
/*	[引数]		CTetris_Falling_Block&	:	落下ブロックのクラス						*/
/*				char					:	フィールド上へのコピーモード				*/
/*												0	-> 消去　 							*/
/*												1	-> 現在のブロックをコピー			*/
/*												2	-> 次のブロックを開始位置にコピー	*/
/*				unsigned short			:	落下ブロックの開始位置 ( 横座標 )			*/
/*				unsigned short			:	落下ブロックの開始位置 ( 縦座標 )			*/
/*																						*/
/*======================================================================================*/
void CPuyoFiled::FallingBlockToBoard(CPuyoFalling_Block& PuyoFalling_Block, char mode, unsigned short x_filed, unsigned short y_filed)
{
	CPuyoBlock	Puyoblock(BlockNS::BLACK, BlockNS::EMPTY);

	/************************************/
	/*	ブロックをフィールドにコピー	*/
	/************************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		int startblockY = 0;

		if (y_filed + y < CURRENT_BLOCK_START_Y)
			break;

		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			if (x_filed + x > PUYO_FILED_START_X + PUYO_FILED_SIZE_X)
				break;

			if (PuyoFalling_Block.GetBlockState(x, y) == BlockNS::EXISTENCE)
			{
				if (mode == 0)
				{
 					m_Block(x_filed + x, y_filed + y) = PuyoFalling_Block.GetBlock(x, y);
				}
				if (mode == 1)
				{
					m_Block(x_filed + x, y_filed + y) = Puyoblock;
				}
				else if (mode == 2)
				{
					m_Block(x_filed + x, y_filed + startblockY) = Puyoblock;
					startblockY++;
				}
				else
				{
 					m_Block(x_filed + x, y_filed + y) = PuyoFalling_Block.GetBlock(x, y);
				}
			}
		}
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		NextWaitBlockInit		:	次のブロックの初期化処理			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CPuyoFiled::NextWaitBlockInit()
{
	char		block_type = 0;
	CPuyoBlock	Puyoblock(BlockNS::BLACK, BlockNS::EMPTY);

	/****************************/
	/*	ブロック情報を初期化	*/
	/****************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			m_WaitBlock.SetBlock(x, y)		= Puyoblock;
			m_WaitNextBlock.SetBlock(x, y)	= Puyoblock;
		}
	}

	/********************************************/
	/*	ブロックの種類を乱数で設定 ( 1段目 )	*/
	/********************************************/
	block_type = (char)(((double)rand() / (RAND_MAX + 1)) * m_BlockColorNum);
	CreateCurrentBlock(block_type, 1);

	/********************************************/
	/*	ブロックの種類を乱数で設定 ( 2段目 )	*/
	/********************************************/
	block_type = (char)(((double)rand() / (RAND_MAX + 1)) * m_BlockColorNum);
	CreateCurrentBlock(block_type, 2);


	/****************************/
	/*	ブロック情報を初期化	*/
	/****************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			m_WaitBlock.SetBlock(x, y)		= m_WaitNextBlock.SetBlock(x, y);
			m_WaitNextBlock.SetBlock(x, y)	= Puyoblock;
		}
	}

	/************************************************/
	/*	次のブロックの種類を乱数で設定 ( 1段目 )	*/
	/************************************************/
	block_type = (char)(((double)rand() / (RAND_MAX + 1)) * m_BlockColorNum);
	CreateCurrentBlock(block_type, 1);

	/************************************************/
	/*	次のブロックの種類を乱数で設定 ( 2段目 )	*/
	/************************************************/
	block_type = (char)(((double)rand() / (RAND_MAX + 1)) * m_BlockColorNum);
	CreateCurrentBlock(block_type, 2);

	/****************************/
	/*	次のブロックを作成		*/
	/****************************/
	NextCurrentBlock();

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		NextWaitBlock			:	次のブロックを作成 ( 待機用 )		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CPuyoFiled::NextWaitBlock()
{
	char		block_type = 0;
	CPuyoBlock	Puyoblock(BlockNS::BLACK, BlockNS::EMPTY);

	/****************************/
	/*	ブロック情報を設定		*/
	/****************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			m_WaitBlock.SetBlock(x, y)		= m_WaitNextBlock.SetBlock(x, y);
			m_WaitNextBlock.SetBlock(x, y)	= Puyoblock;
			m_LandingBlock.SetBlock(x, y)	= Puyoblock;
		}
	}

	/************************************************/
	/*	次のブロックの種類を乱数で設定 ( 1段目 )	*/
	/************************************************/
	block_type = (char)(((double)rand() / (RAND_MAX + 1)) * m_BlockColorNum);
	CreateCurrentBlock(block_type, 1);

	/************************************************/
	/*	次のブロックの種類を乱数で設定 ( 2段目 )	*/
	/************************************************/
	block_type = (char)(((double)rand() / (RAND_MAX + 1)) * m_BlockColorNum);
	CreateCurrentBlock(block_type, 2);

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		NextCurrentBlock		:	次のブロックを作成					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*==============================================================================*/
void CPuyoFiled::NextCurrentBlock()
{
	/********************************/
	/*	現在のブロック情報の設定	*/
	/********************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			m_CurrentBlock.SetBlock(x, y) = m_WaitBlock.SetBlock(x, y);
			m_LandingBlock.SetBlock(x, y) = m_WaitBlock.SetBlock(x, y);
		}
	}

	/****************************/
	/*	ブロックの開始位置		*/
	/****************************/
	m_CurrentBlockTopPosX = CURRENT_BLOCK_START_X;
	m_CurrentBlockTopPosY = CURRENT_BLOCK_START_Y;

	/********************************/
	/*	ブロックの回転角度をクリア	*/
	/********************************/
	m_CurrentBlockRotatinAngle = 0;

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		CreateCurrentBlock		:	現在のブロックを作成				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		char					:	作成するブロックの色 				*/
/*				unsigned char			:	作成するブロックの段数				*/
/*																				*/
/*==============================================================================*/
void CPuyoFiled::CreateCurrentBlock(char block_type, unsigned char num)
{
	/****************************/
	/*	ブロックの作成			*/
	/****************************/
	m_WaitNextBlock.CreateFallingBlock(block_type, num);

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		MoveBlock				:	ブロックの移動処理					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	long					:	なし								*/
/*	[引数]		CPuyoFalling_Block&		:	落下ブロックのクラス				*/
/*				char					:	ブロックの処理方法					*/
/*																				*/
/*==============================================================================*/
bool CPuyoFiled::MoveBlock(CPuyoFalling_Block& PuyoFalling_Block, char next_block_direction)
{
	bool			block_move	= false;
	unsigned short	x_filed		= m_CurrentBlockTopPosX;
	unsigned short	y_filed		= m_CurrentBlockTopPosY;

	switch (next_block_direction)
	{
		/************************************/
		/*	ブロックの移動方向が左方向		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_LEFT:
		block_move = MoveBlockLeft(PuyoFalling_Block, x_filed, y_filed);
		break;

		/************************************/
		/*	ブロックの移動方向が右方向		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_RIGHT:
		block_move = MoveBlockRight(PuyoFalling_Block, x_filed, y_filed);
		break;

		/************************************/
		/*	ブロックの移動方向が下方向		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_DOWN:
		block_move = MoveBlockDown(PuyoFalling_Block, x_filed, y_filed);
		break;

		/************************************/
		/*	ブロックの移動方向がCCW回転		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_ROTATE_CW:
 		block_move = RotateBlock(PuyoFalling_Block, BlockNS::BLOCK_CCW_ROTATION);
		break;

		/************************************/
		/*	ブロックの移動方向がCW回転		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_ROTATE_CCW:
		block_move = RotateBlock(PuyoFalling_Block, BlockNS::BLOCK_CW_ROTATION);
		break;

		/************************************/
		/*	ブロックの落下モード			*/
		/************************************/
	case BlockNS::BLOCK_MOVE_FALL_MODE:
		MoveBlockFallMode(PuyoFalling_Block);
		break;

	}

	/************************************/
	/*	ブロック移動の更新処理			*/
	/************************************/
	if (block_move)
	{
		MoveBlockUpdate(PuyoFalling_Block, next_block_direction);
	}

	return block_move;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		MoveBlockUpdate			:	ブロック移動の更新処理				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		CTetris_Falling_Block&	:	落下ブロックのクラス				*/
/*				char					:	ブロックの処理方法					*/
/*																				*/
/*==============================================================================*/
void CPuyoFiled::MoveBlockUpdate(CPuyoFalling_Block& PuyoFalling_Block, char next_block_direction)
{

	unsigned short	x_filed = m_CurrentBlockTopPosX;
	unsigned short	y_filed = m_CurrentBlockTopPosY;

	/************************************/
	/*	フィールド上のブロックをクリア	*/
	/************************************/
	FallingBlockToBoard(PuyoFalling_Block, 1, x_filed, y_filed);

	/************************************/
	/*	フィールド上のブロックを進める	*/
	/************************************/
	switch (next_block_direction)
	{
		/************************************/
		/*	ブロックの移動方向が左方向		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_LEFT:
		m_CurrentBlockTopPosX--;
		break;

		/************************************/
		/*	ブロックの移動方向が右方向		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_RIGHT:
		m_CurrentBlockTopPosX++;
		break;

		/************************************/
		/*	ブロックの移動方向が下方向		*/
		/************************************/
	case BlockNS::BLOCK_MOVE_DOWN:
		m_CurrentBlockTopPosY++;
		break;
	
	default:
		break;

	}

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		CurrentMoveBlock		:	現在のブロックの移動処理			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool					:	true	->	移動可能				*/
/*											false	->	移動不可				*/
/*	[引数]		char					:	ブロック処理方法					*/
/*																				*/
/*==============================================================================*/
bool CPuyoFiled::CurrentMoveBlock(char next_block_direction)
{
	bool block_move = false;
	block_move		= MoveBlock(m_CurrentBlock, next_block_direction);
	return block_move;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		MoveBlockLeft			:	ブロックの移動処理 ( 左 )			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool					:	true	->	移動可能				*/
/*											false	->	移動不可				*/
/*	[引数]		CTetris_Falling_Block&	:	落下ブロックのクラス				*/
/*				unsigned short			:	落下ブロックの位置 ( 横座標 )		*/
/*				unsigned short			:	落下ブロックの位置 ( 縦座標 )		*/
/*																				*/
/*==============================================================================*/
bool CPuyoFiled::MoveBlockLeft(CPuyoFalling_Block& PuyoFalling_Block, unsigned short x_filed, unsigned short y_filed)
{
	/*
		Note 1:
		ブロックが左方向に移動できるか判定
			フィールド上にある現在のブロック領域の1つ左においてブロックが
			存在しないならば、右に進める
	*/

	char			left_block	= 0;
	unsigned short	block_top	= PuyoFalling_Block.GetFallingBlockTop() - 1;
	unsigned short	block_left	= PuyoFalling_Block.GetFallingBlockLeft() - 1;

	if ((x_filed + block_left) > PUYO_FILED_START_X)
	{
		/************************************/
		/*	ブロックが左端に進める場合		*/
		/************************************/
		for (int y = block_top; y < CURRENT_BLOCK_Y; y++)
		{
			for (int x = PUYO_FILED_START_X - 1; x >= 0; x--)
			{
				if (	(PuyoFalling_Block.GetBlockState(x, y))						/*	現在のブロック情報にブロックがあり				*/
					&&	(m_Block(x_filed + x - 1, y_filed + y).GetBlockState()))		/*	フィールド上の一つ左にもブロックがあるならば	*/
				{
					if (x == 0)															/*	一番左のブロック情報であるならば				*/
					{
						left_block++;													/*	左にブロックが存在する							*/
					}
					else if (!PuyoFalling_Block.GetBlockState(x - 1, y))				/*	現在のブロック情報の左にブロックがないならば	*/
					{
						left_block++;													/*	左にブロックが存在する							*/
					}
				}
			}

			if (y_filed + y > PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y)
				break;
		}

		/****************************/
		/*	ブロックの移動判定		*/
		/****************************/
		if (	(!left_block)															/*	左にブロックが存在しないならば					*/
			&&	(m_CurrentBlockTopPosX > 0))
		{
			return true;
		}
	}

	return false;
}


/*==============================================================================*/
/*																				*/
/*	[関数]		MoveBlockRight			:	ブロックの移動処理 ( 右 )			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool					:	true	->	移動可能				*/
/*											false	->	移動不可				*/
/*	[引数]		CTetris_Falling_Block&	:	落下ブロックのクラス				*/
/*				unsigned short			:	落下ブロックの位置 ( 横座標 )		*/
/*				unsigned short			:	落下ブロックの位置 ( 縦座標 )		*/
/*																				*/
/*==============================================================================*/
bool CPuyoFiled::MoveBlockRight(CPuyoFalling_Block& PuyoFalling_Block, unsigned short x_filed, unsigned short y_filed)
{
	/*
		Note 1:
			ブロックが右方向に移動できるか判定
				フィールド上にある現在のブロック領域の1つ右においてブロックが
				存在しないならば、右に進める
	*/

	char			right_block = 0;
	unsigned short	block_top	= PuyoFalling_Block.GetFallingBlockTop() - 1;
	unsigned short	block_right	= PuyoFalling_Block.GetFallingBlockRight() - 1;

	if ((m_CurrentBlockTopPosX < PUYO_FILED_START_X + PUYO_FILED_SIZE_X))
	{
		/************************************/
		/*	ブロックが右端に進める場合		*/
		/************************************/
		for (int y = block_top; y < CURRENT_BLOCK_Y; y++)
		{
			for (int x = 0; x < CURRENT_BLOCK_X; x++)
			{
				if (x_filed + x > PUYO_FILED_START_X + PUYO_FILED_SIZE_X)
					break;

				if (	(PuyoFalling_Block.GetBlockState(x, y))						/*	現在のブロック情報にブロックがあり				*/
					&&	(m_Block(x_filed + x + 1, y_filed + y).GetBlockState()))		/*	フィールド上の一つ右にもブロックがあるならば	*/
				{	
					if (x == CURRENT_BLOCK_X - 1)										/*	一番右のブロック情報であるならば				*/
					{
						right_block++;													/*	右にブロックが存在する							*/
					}
					else if (!PuyoFalling_Block.GetBlockState(x + 1, y))				/*	現在のブロック情報の右にブロックがないならば	*/
					{
						right_block++;													/*	右にブロックが存在する							*/
					}
				}
			}

			if (y_filed + y > PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y)
				break;
		}

		/****************************/
		/*	ブロックの移動判定		*/
		/****************************/
		if (!right_block)																/*	右にブロックが存在しないならば					*/
		{
			return true;
		}
	}

	return false;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		MoveBlockDown			:	ブロックの移動処理 ( 下 )			*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool					:	true	->	移動可能				*/
/*											false	->	移動不可				*/
/*	[引数]		CTetris_Falling_Block&	:	落下ブロックのクラス				*/
/*				unsigned short			:	落下ブロックの位置 ( 横座標 )		*/
/*				unsigned short			:	落下ブロックの位置 ( 縦座標 )		*/
/*																				*/
/*==============================================================================*/
bool CPuyoFiled::MoveBlockDown(CPuyoFalling_Block& PuyoFalling_Block, unsigned short x_filed, unsigned short y_filed)
{
	/*
		Note 1:
			ブロックの最下端の判定	
				現在のブロック領域の先頭からブロックの最下端位置を加算した値が
				フィールドより小さいならば、下に進める

		Note 2:
			ブロックが下方向に移動できるか判定
				フィールド上にある現在のブロック領域の1つ下においてブロックが
				存在しないならば、下に進める
	*/

	char			below_block		= 0;
	unsigned short	block_bottom	= PuyoFalling_Block.GetFallingBlockBottom() - 1;
	unsigned short	block_left		= PuyoFalling_Block.GetFallingBlockLeft() - 1;

	if((y_filed + block_bottom + 1) < PUYO_FILED_SIZE_Y + PUYO_FILED_START_Y)
	{
		/************************************/
		/*	ブロックが下端に進める場合		*/
		/************************************/
		for (int y = 0; y < CURRENT_BLOCK_Y; y++)
		{
			for (int x = block_left; x < CURRENT_BLOCK_X; x++)
			{
				if (x_filed + x > PUYO_FILED_START_X + PUYO_FILED_SIZE_X)
					break;

				if (	(PuyoFalling_Block.GetBlockState(x, y))							/*	現在のブロック情報にブロックがあり				*/
					&&	(m_Block(x_filed + x, y_filed + y + 1).GetBlockState()))		/*	フィールド上の一つ下にもブロックがあるならば	*/
				{
					if(y == CURRENT_BLOCK_Y - 1)										/*	一番下のブロック情報であるならば				*/
					{
						below_block++;													/*	下にブロックが存在する							*/
					}
					else if (!PuyoFalling_Block.GetBlockState(x, y + 1))				/*	現在のブロック情報の下にブロックがないならば	*/
					{
						below_block++;													/*	下にブロックが存在する							*/
					}
				}
			}

			if (y_filed + y > PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y)
				break;
		}

		/****************************/
		/*	ブロックの移動判定		*/
		/****************************/
		if (!below_block)																/*	下にブロックが存在しないならば					*/
		{
			return true;
		}

	}

	return false;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		RotateBlock				:	ブロックの回転処理					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	long					:	なし								*/
/*	[引数]		CPuyoFalling_Block&		:	落下ブロック情報					*/
/*				char 					:	回転方向 ( 0:CW 1:CCW )				*/
/*																				*/
/*==============================================================================*/
bool CPuyoFiled::RotateBlock(CPuyoFalling_Block& PuyoFalling_Block, char type)
{
	unsigned short				x_filed = m_CurrentBlockTopPosX;
	unsigned short				y_filed = m_CurrentBlockTopPosY;
	short						shift_x = 0;
	short						shift_y = 0;
	Array2D< CPuyoBlock >		Puyoblock(CURRENT_BLOCK_X, CURRENT_BLOCK_Y);

	/********************************/
	/*	現在のブロック情報を回転	*/
	/********************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			if (type == BlockNS::BLOCK_CW_ROTATION)
			{
				Puyoblock((CURRENT_BLOCK_Y - 1) - y, x) = PuyoFalling_Block.GetBlock(x, y);
			}
			else if (type == BlockNS::BLOCK_CCW_ROTATION)
			{
				Puyoblock(y, (CURRENT_BLOCK_X - 1) - x) = PuyoFalling_Block.GetBlock(x, y);
			}
		}
	}

	/********************************/
	/*	回転可能か判定				*/
	/*		フィールド幅の判定		*/
	/********************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			if (Puyoblock(x, y).GetBlockState() == BlockNS::EXISTENCE)
			{
				unsigned int x_rotate = x + x_filed;
				unsigned int y_rotate = y + y_filed;

				if (x_rotate < PUYO_FILED_START_X)												/*	左端のフィールドを超えるならば	*/
				{
					shift_x = PUYO_FILED_START_X - x_rotate;
				}
				else if (x_rotate > PUYO_FILED_START_X + PUYO_FILED_SIZE_X - 1)					/*	右端のフィールドを超えるならば	*/
				{
					shift_x = (PUYO_FILED_START_X + PUYO_FILED_SIZE_X - 1) - x_rotate;
				}
				else if (y_rotate > PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y - 1)					/*	下端のフィールドを超えるならば	*/
				{
					shift_y = (PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y - 1) - y_rotate;
				}
			}
		}
	}

	/************************************/
	/*	フィールド上のブロックをシフト	*/
	/************************************/
	if ((shift_x != 0) || (shift_y != 0))														/*	そのまま回転できないならば		*/
	{	
		m_CurrentBlockTopPosX += shift_x;
		m_CurrentBlockTopPosY += shift_y;
	}

	/************************************/
	/*	フィールド上のブロックをクリア	*/
	/************************************/
	FallingBlockToBoard(PuyoFalling_Block, 1, x_filed, y_filed);

	/****************************************/
	/*	回転可能か判定						*/
	/*		フィールド上のブロックの判定	*/
	/****************************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			if(		(Puyoblock(x, y).GetBlockState() == BlockNS::EXISTENCE)
				&&	(m_Block(x_filed + x, y_filed + y).GetBlockState() == BlockNS::EXISTENCE))
			{
				FallingBlockToBoard(PuyoFalling_Block, 0, x_filed, y_filed);
   				return false;
			}
		}
	}

	/********************************/
	/*	回転したブロックをコピー	*/
	/********************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			PuyoFalling_Block.SetBlock(x, y) = Puyoblock(x, y);
		}
	}

	if (type == BlockNS::BLOCK_CW_ROTATION)
	{
		m_CurrentBlockRotatinAngle += -90;
	}
	else if (type == BlockNS::BLOCK_CCW_ROTATION)
	{
		m_CurrentBlockRotatinAngle += 90;
	}

	return true;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		MoveBlockFallMode		:	ブロックの落下モード				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CPuyoFiled::MoveBlockFallMode(CPuyoFalling_Block& PuyoFalling_Block)
{
	unsigned short	x_filed = m_CurrentBlockTopPosX;
	unsigned short	y_filed = m_CurrentBlockTopPosY;

	while (MoveBlockDown(PuyoFalling_Block, x_filed, y_filed))
	{
		/********************************/
		/*	現在ブロックの位置を更新	*/
		/********************************/
		MoveBlockUpdate(PuyoFalling_Block, BlockNS::BLOCK_MOVE_DOWN);
		x_filed = m_CurrentBlockTopPosX;
		y_filed = m_CurrentBlockTopPosY;

		/****************************/
		/*	ブロック状態を設定		*/
		/****************************/
		SetCurrentBlockState();

		/************************************/
		/*	ブロックをフィールドにコピー	*/
		/************************************/
		FallingBlockToBoard(PuyoFalling_Block, 0, x_filed, y_filed);

	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		LandingBlockPos			:	落下ブロックの着地位置				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	long					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CPuyoFiled::LandingBlockPos()
{
	unsigned short	x_filed = m_CurrentBlockTopPosX;
	unsigned short	y_filed = m_CurrentBlockTopPosY;

	/********************************/
	/*	着地ブロックの色の設定		*/
	/********************************/
	for (int y = 0; y < CURRENT_BLOCK_Y; y++)
	{
		for (int x = 0; x < CURRENT_BLOCK_X; x++)
		{
			m_LandingBlock.SetBlock(x, y) = m_CurrentBlock.SetBlock(x, y);
			m_LandingBlock.SetBlockColor(x, y) = BlockNS::LIGHTGRAY;
		}
	}

	/********************************/
	/*	着地ブロック状態を設定		*/
	/********************************/
	m_LandingBlock.SetFallingBlockState();

	/************************/
	/*	落下地点まで処理	*/
	/************************/
	while (MoveBlockDown(m_LandingBlock, x_filed, y_filed))
	{
		/********************************/
		/*	現在ブロックの位置を更新	*/
		/********************************/
		y_filed++;
	}

	/************************************/
	/*	ブロックをフィールドにコピー	*/
	/************************************/
	m_LandingBlockTopPosX = x_filed;
	m_LandingBlockTopPosY = y_filed;
	
	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		LandingBlockClear		:	落下ブロックの着地位置のクリア		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	long					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void CPuyoFiled::LandingBlockClear()
{
	m_LandingBlock.FallingBlockInit();
	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		CheckBlockState			:	ブロックの状態を調べる				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool					:	ブロックチェックの処理の状態		*/
/*												true	-> 完了済				*/
/*												false	-> 未完了				*/
/*																				*/
/*	※　消去ブロックがある場合は連鎖処理を行うためブロックチェック処理が未完了	*/
/*																				*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*==============================================================================*/
bool CPuyoFiled::CheckBlockState()
{
	bool	bDropBlock		= false;
	bool	bDeleteBlock	= false;
	bool	bCheckBlockEnd	= false;

	/****************************/
	/*	落下ブロックの処理		*/
	/****************************/
	bDropBlock = CheckDropBlock();

	/****************************/
	/*	連結ブロックを調べる	*/
	/****************************/
	if (bDropBlock == false)													/*	ブロックの落下処理が完了したら				*/
	{
		bDeleteBlock = CheckConnectingBlock();									/*	連結ブロックを調べる						*/
		
		if (bDeleteBlock == true)												/*	消去ブロックがあれば						*/
		{
			m_DeleteChainBlockCount++;											/*	消去中のブロック連鎖数をカウント			*/
		}
	}

	if (	(bDropBlock == false)												/*	落下ブロックがないならば					*/
		&&	(bDeleteBlock == false))											/*	消去ブロックがないならば					*/
	{
		bCheckBlockEnd = true;													/*	ブロックチェックの処理が完了済み			*/
		m_DeleteChainBlockCurrentCount = m_DeleteChainBlockCount;				/*	連鎖数を取得								*/
		m_DeleteChainBlockCount = 0;											/*	連鎖数のカウント処理用をクリア				*/

		if (m_DeleteChainBlockMaxCount < m_DeleteChainBlockCurrentCount)		/*	最大連鎖数より現在の連鎖数が大きいならば	*/
		{
			m_DeleteChainBlockMaxCount = m_DeleteChainBlockCurrentCount;		/*	連鎖数の最大数を更新						*/
		}
	}

	return bCheckBlockEnd;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		CheckBlockDown			:	ブロックが落下できるか調べる		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool					:	ブロックを落下させるかどうか		*/
/*												true	-> 落下あり				*/
/*												false	-> 落下なし				*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*==============================================================================*/
bool CPuyoFiled::CheckDropBlock()
{
	CPuyoBlock		Puyoblock(BlockNS::BLACK, BlockNS::EMPTY);
	bool			bDropBlock = false;

	/********************************/
	/*	ブロックの位置を更新		*/
	/********************************/
	for (int y_filed = PUYO_FILED_START_Y; y_filed < (PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y - 1); y_filed++)
	{
		for (int x_filed = PUYO_FILED_START_X; x_filed < (PUYO_FILED_START_X + PUYO_FILED_SIZE_X); x_filed++)
		{
			if (	(CPuyoFiled::GetBlockState(x_filed, y_filed, BlockNS::FILED_BLOCK) == BlockNS::EXISTENCE)
				&&	(CPuyoFiled::GetBlockState(x_filed, y_filed + 1, BlockNS::FILED_BLOCK) == BlockNS::EMPTY))
			{
				/********************************/
				/*	ブロックを1つ下に落下させる	*/
				/********************************/
				m_Block(x_filed, y_filed + 1) = m_Block(x_filed, y_filed);
				m_Block(x_filed, y_filed) = Puyoblock;
				bDropBlock = true;
			}
		}
	}

	return bDropBlock;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		CheckConnectingBlock	:	連結ブロックを調べる				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool					:	ブロックを消去させたかどうか		*/
/*												true	-> 消去あり				*/
/*												false	-> 				*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*==============================================================================*/
bool CPuyoFiled::CheckConnectingBlock()
{
	bool	bDeleteBlock = false;

	/****************************************/
	/*	現在のブロックが同じ色か調べる		*/
	/****************************************/
	for (int y_filed = PUYO_FILED_START_Y; y_filed < (PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y); y_filed++)
	{
		for (int x_filed = PUYO_FILED_START_X; x_filed < (PUYO_FILED_START_X + PUYO_FILED_SIZE_X); x_filed++)
		{
			if (	(CPuyoFiled::GetBlockState(x_filed, y_filed, BlockNS::FILED_BLOCK) == BlockNS::EXISTENCE)
				&&	(CPuyoFiled::GetCheckBlock(x_filed, y_filed, BlockNS::FILED_BLOCK) == BlockNS::NON_CHECEKED_BLOCK))
			{
				/****************************************/
				/*	同じ色のブロックの連結数を調べる	*/
				/****************************************/
				unsigned short count		= 0;
				unsigned short color		= CheckSameColorBlock(x_filed, y_filed, &count);

				/****************************************/
				/*	4以上連結していたらブロックを消去	*/
				/****************************************/
				if (count >= PUYO_DELETE_NUM)
				{
					DeleteBlock(color);
					bDeleteBlock = true;
				}

				/****************************************/
				/*	ブロックのチェック済みフラグを解除	*/
				/****************************************/
				UnCheckedBlock();
				
				/****************************************/
				/*	ブロックを消去したら一度抜ける		*/
				/****************************************/
				if (bDeleteBlock)
					return bDeleteBlock;
			}
		}
	}

	return bDeleteBlock;
}

/*==========================================================================================*/
/*																							*/
/*	[関数]		CheckSameColorBlockCount	:	同じ色のブロックを調べる					*/
/*																							*/
/*	----------------------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short				:	連結数を調べたブロックの色					*/
/*	[引数]		unsigned short				:	ブロックの位置 ( 横座標 )					*/
/*				unsigned short				:	ブロックの位置 ( 縦座標 )					*/
/*				unsigned short*				:	連結したブロックの個数						*/
/*																							*/
/*==========================================================================================*/
unsigned short CPuyoFiled::CheckSameColorBlock(unsigned short x_filed, unsigned short y_filed, unsigned short* count)
{
	unsigned short color = CPuyoFiled::GetBlockColor(x_filed, y_filed, BlockNS::FILED_BLOCK);
	
	/********************************/
	/*	ブロックの連結情報を更新	*/
	/********************************/
	*count = *count + 1;																			/* 連結の個数を更新						*/
	CPuyoFiled::SetCheckBlock(x_filed, y_filed, BlockNS::FILED_BLOCK) = BlockNS::CHECEKED_BLOCK;	/* ブロックをチェック済みに設定			*/

	/****************************************/
	/*	隣接するブロックが同じ色か調べる	*/
	/****************************************/
	if (	(x_filed + 1 < (PUYO_FILED_START_X + PUYO_FILED_SIZE_X))
		&&	(CPuyoFiled::GetBlockState(x_filed + 1, y_filed, BlockNS::FILED_BLOCK) == BlockNS::EXISTENCE)
		&&	(CPuyoFiled::GetCheckBlock(x_filed + 1, y_filed, BlockNS::FILED_BLOCK) == BlockNS::NON_CHECEKED_BLOCK)
		&&	(CPuyoFiled::GetBlockColor(x_filed + 1, y_filed, BlockNS::FILED_BLOCK) == color))
	{
		CPuyoFiled::SetConnectBlock(x_filed, y_filed, BlockNS::FILED_BLOCK) |= BlockNS::BLOCK_CONNECT_RIGHT;
		CPuyoFiled::CheckSameColorBlock(x_filed + 1, y_filed, count);
	}

	if (	(y_filed + 1 < (PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y))
		&&	(CPuyoFiled::GetBlockState(x_filed, y_filed + 1, BlockNS::FILED_BLOCK) == BlockNS::EXISTENCE)
		&&	(CPuyoFiled::GetCheckBlock(x_filed, y_filed + 1, BlockNS::FILED_BLOCK) == BlockNS::NON_CHECEKED_BLOCK)
		&&	(CPuyoFiled::GetBlockColor(x_filed, y_filed + 1, BlockNS::FILED_BLOCK) == color))
	{
		CPuyoFiled::SetConnectBlock(x_filed, y_filed, BlockNS::FILED_BLOCK) |= BlockNS::BLOCK_CONNECT_BOTTOM;
		CPuyoFiled::CheckSameColorBlock(x_filed, y_filed + 1, count);
	}

	if(		(x_filed - 1 >= PUYO_FILED_START_X)
		&&	(CPuyoFiled::GetBlockState(x_filed - 1, y_filed, BlockNS::FILED_BLOCK) == BlockNS::EXISTENCE)
		&&	(CPuyoFiled::GetCheckBlock(x_filed - 1, y_filed, BlockNS::FILED_BLOCK) == BlockNS::NON_CHECEKED_BLOCK)
		&&	(CPuyoFiled::GetBlockColor(x_filed - 1, y_filed, BlockNS::FILED_BLOCK) == color))
	{
		CPuyoFiled::SetConnectBlock(x_filed, y_filed, BlockNS::FILED_BLOCK) |= BlockNS::BLOCK_CONNECT_LEFT;
		CPuyoFiled::CheckSameColorBlock(x_filed - 1, y_filed, count);
	}
		
	if (	(y_filed - 1 >= PUYO_FILED_START_Y)
		&&	(CPuyoFiled::GetBlockState(x_filed, y_filed - 1, BlockNS::FILED_BLOCK) == BlockNS::EXISTENCE)
		&&	(CPuyoFiled::GetCheckBlock(x_filed, y_filed - 1, BlockNS::FILED_BLOCK) == BlockNS::NON_CHECEKED_BLOCK)
		&&	(CPuyoFiled::GetBlockColor(x_filed, y_filed - 1, BlockNS::FILED_BLOCK) == color))
	{
		CPuyoFiled::SetConnectBlock(x_filed, y_filed, BlockNS::FILED_BLOCK) |= BlockNS::BLOCK_CONNECT_TOP;
		CPuyoFiled::CheckSameColorBlock(x_filed, y_filed - 1, count);
	}

	return color;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		DeleteBlock				:	ブロックを消去						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		unsigned short			:	消去するブロックの色				*/
/*																				*/
/*==============================================================================*/
void CPuyoFiled::DeleteBlock(unsigned short color)
{
	CPuyoBlock		Puyoblock(BlockNS::BLACK, BlockNS::EMPTY);

	/********************************/
	/*	連結したブロックを消去		*/
	/********************************/
	for (int y_filed = PUYO_FILED_START_Y; y_filed < (PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y); y_filed++)
	{
		for (int x_filed = PUYO_FILED_START_X; x_filed < (PUYO_FILED_START_X + PUYO_FILED_SIZE_X); x_filed++)
		{
			if (	(CPuyoFiled::GetCheckBlock(x_filed, y_filed, BlockNS::FILED_BLOCK) == BlockNS::CHECEKED_BLOCK)
				&&	(CPuyoFiled::GetBlockColor(x_filed, y_filed, BlockNS::FILED_BLOCK) == color))
			{
				m_Block(x_filed, y_filed) = Puyoblock;
			}
		}
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		UnCheckedBlock			:	ブロックのチェック済みフラグを解除	*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*==============================================================================*/
void CPuyoFiled::UnCheckedBlock()
{
	/****************************************/
	/*	ブロックのチェック済みフラグを解除	*/
	/****************************************/
	for (int y_filed = PUYO_FILED_START_Y; y_filed < (PUYO_FILED_START_Y + PUYO_FILED_SIZE_Y); y_filed++)
	{
		for (int x_filed = PUYO_FILED_START_X; x_filed < (PUYO_FILED_START_X + PUYO_FILED_SIZE_X); x_filed++)
		{
			CPuyoFiled::SetCheckBlock(x_filed, y_filed, BlockNS::FILED_BLOCK) = BlockNS::NON_CHECEKED_BLOCK;
		}
	}

	return;
}

/*======================================================================================*/
/*																						*/
/*	[関数]		CurrentBlockToBoard		:	現在のブロックをフィールドにコピー			*/
/*																						*/
/*	------------------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし										*/
/*				char					:	フィールド上へのコピーモード				*/
/*												0	-> 消去　 							*/
/*												1	-> 現在のブロックをコピー			*/
/*												2	-> 次のブロックを開始位置にコピー	*/
/*																						*/
/*======================================================================================*/
void CPuyoFiled::CurrentBlockToBoard(char mode)
{
	unsigned short	x_filed = m_CurrentBlockTopPosX;
	unsigned short	y_filed = m_CurrentBlockTopPosY;
	FallingBlockToBoard(m_CurrentBlock, mode, x_filed, y_filed);
	return;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetCurrentBlockState	:	現在ブロックの位置情報を設定		*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
void  CPuyoFiled::SetCurrentBlockState()
{
	m_CurrentBlock.SetFallingBlockState();
	return;
}
/*==============================================================================*/
/*																				*/
/*	[関数]		GetBlockDeleteInfo		:	ブロック消去情報					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned char			:										*/
/*	[引数]								:	なし								*/
/*																				*/
/*==============================================================================*/
unsigned char CPuyoFiled::GetBlockDeleteInfo() const
{
	return m_BlockDeleteInfo;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetBlockColor		:	ブロックの色を取得						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short		:	ブロックの色を取得						*/
/*	[引数]		unsigned short		:	ブロックの位置 ( 横座標 )				*/
/*				unsigned short		:	ブロックの位置 ( 縦座標 )				*/
/*				char				:	落下ブロックのタイプ					*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFiled::GetBlockColor(long x, long y, char type)
{
	if (type == BlockNS::FILED_BLOCK)
	{
		return m_Block(x, y).GetBlockColor();
	}
	else if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlock.GetBlockColor(x, y);
	}
	else if (type == BlockNS::WAIT_BLOCK)
	{
		return m_WaitBlock.GetBlockColor(x, y);
	}
	else if (type == BlockNS::WAIT_NEXT_BLOCK)
	{
		return m_WaitNextBlock.GetBlockColor(x, y);
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlock.GetBlockColor(x, y);
	}
	else
	{
		return m_Block(x, y).GetBlockColor();
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetBlockColor		:	ブロックの色を設定						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	unsigned short		:	ブロックの色を設定						*/
/*	[引数]		unsigned short		:	ブロックの位置 ( 横座標 )				*/
/*				unsigned short		:	ブロックの位置 ( 縦座標 )				*/
/*				char				:	落下ブロックのタイプ					*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CPuyoFiled::SetBlockColor(long x, long y, char type)
{
	if (type == BlockNS::FILED_BLOCK)
	{
		return m_Block(x, y).SetBlockColor();
	}
	else if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlock.SetBlockColor(x, y);
	}
	else if (type == BlockNS::WAIT_BLOCK)
	{
		return m_WaitBlock.SetBlockColor(x, y);
	}
	else if (type == BlockNS::WAIT_NEXT_BLOCK)
	{
		return m_WaitNextBlock.SetBlockColor(x, y);
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlock.SetBlockColor(x, y);
	}
	else
	{
		return m_Block(x, y).SetBlockColor();
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetBlockState			:	ブロックがあるかどうかを取得		*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*				char					:	落下ブロックのタイプ				*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFiled::GetBlockState(long x, long y, char type)
{
	if (type == BlockNS::FILED_BLOCK)
	{
		return m_Block(x, y).GetBlockState();
	}
	else if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlock.GetBlockState(x, y);
	}
	else if (type == BlockNS::WAIT_BLOCK)
	{
		return m_WaitBlock.GetBlockState(x, y);
	}
	else if (type == BlockNS::WAIT_NEXT_BLOCK)
	{
		return m_WaitNextBlock.GetBlockState(x, y);
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlock.GetBlockState(x, y);
	}
	else
	{
		return 0;
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetBlockState			:	ブロックの状態を設定				*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*				char					:	落下ブロックのタイプ				*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CPuyoFiled::SetBlockState(long x, long y, char type)
{

	if (type == BlockNS::FILED_BLOCK)
	{
		return m_Block(x, y).SetBlockState();
	}
	else if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlock.SetBlockState(x, y);
	}
	else if (type == BlockNS::WAIT_BLOCK)
	{
		return m_WaitBlock.SetBlockState(x, y);
	}
	else if (type == BlockNS::WAIT_NEXT_BLOCK)
	{
		return m_WaitNextBlock.SetBlockState(x, y);
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlock.SetBlockState(x, y);;
	}
	else
	{
		return m_Block(x, y).SetBlockState();
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetCheckBlock			:	ブロックがチェック済みどうかを取得	*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*				char					:	落下ブロックのタイプ				*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFiled::GetCheckBlock(long x, long y, char type)
{
	if (type == BlockNS::FILED_BLOCK)
	{
		return m_Block(x, y).GetCheckBlock();
	}
	else if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlock.GetCheckBlock(x, y);
	}
	else if (type == BlockNS::WAIT_BLOCK)
	{
		return m_WaitBlock.GetCheckBlock(x, y);
	}
	else if (type == BlockNS::WAIT_NEXT_BLOCK)
	{
		return m_WaitNextBlock.GetCheckBlock(x, y);
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlock.GetCheckBlock(x, y);
	}
	else
	{
		return 0;
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetCheckBlock			:	ブロックをチェック済みに設定		*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*				char					:	落下ブロックのタイプ				*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CPuyoFiled::SetCheckBlock(long x, long y, char type)
{

	if (type == BlockNS::FILED_BLOCK)
	{
		return m_Block(x, y).SetCheckBlock();
	}
	else if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlock.SetCheckBlock(x, y);
	}
	else if (type == BlockNS::WAIT_BLOCK)
	{
		return m_WaitBlock.SetCheckBlock(x, y);
	}
	else if (type == BlockNS::WAIT_NEXT_BLOCK)
	{
		return m_WaitNextBlock.SetCheckBlock(x, y);
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlock.SetCheckBlock(x, y);;
	}
	else
	{
		return m_Block(x, y).SetCheckBlock();
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetConnectBlock			:	ブロックの連結状態を取得			*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*				char					:	落下ブロックのタイプ				*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFiled::GetConnectBlock(long x, long y, char type)
{
	if (type == BlockNS::FILED_BLOCK)
	{
		return m_Block(x, y).GetConnectBlock();
	}
	else if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlock.GetConnectBlock(x, y);
	}
	else if (type == BlockNS::WAIT_BLOCK)
	{
		return m_WaitBlock.GetConnectBlock(x, y);
	}
	else if (type == BlockNS::WAIT_NEXT_BLOCK)
	{
		return m_WaitNextBlock.GetConnectBlock(x, y);
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlock.GetConnectBlock(x, y);
	}
	else
	{
		return 0;
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetConnectBlock			:	ブロックの連結状態を設定			*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*				char					:	落下ブロックのタイプ				*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short& CPuyoFiled::SetConnectBlock(long x, long y, char type)
{

	if (type == BlockNS::FILED_BLOCK)
	{
		return m_Block(x, y).SetConnectBlock();
	}
	else if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlock.SetConnectBlock(x, y);
	}
	else if (type == BlockNS::WAIT_BLOCK)
	{
		return m_WaitBlock.SetConnectBlock(x, y);
	}
	else if (type == BlockNS::WAIT_NEXT_BLOCK)
	{
		return m_WaitNextBlock.SetConnectBlock(x, y);
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlock.SetConnectBlock(x, y);;
	}
	else
	{
		return m_Block(x, y).SetCheckBlock();
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetBlock				:	ブロックを取得						*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックを取得						*/
/*	[引数]		unsigned short			:	ブロックの位置 ( 横座標 )			*/
/*				unsigned short			:	ブロックの位置 ( 縦座標 )			*/
/*																				*/
/*------------------------------------------------------------------------------*/
CPuyoBlock CPuyoFiled::GetBlock(long x, long y) const
{
	return m_Block(x, y);
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
CPuyoBlock& CPuyoFiled::SetBlock(long x, long y)
{
	return m_Block(x, y);
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetBlockTopPosX			:	落下ブロックの位置情報を取得		*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]		char					:	落下ブロックのタイプ				*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFiled::GetBlockTopPosX(char type) const
{
	if (type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlockTopPosX;
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlockTopPosX;
	}
	else
	{
		return 0;
	}

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetBlockTopPosY			:	落下ブロックの位置情報を取得		*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]		char					:	落下ブロックのタイプ				*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFiled::GetBlockTopPosY(char type) const
{
	if(type == BlockNS::CURRENT_BLOCK)
	{
		return m_CurrentBlockTopPosY;
	}
	else if (type == BlockNS::LANDING_BLOCK)
	{
		return m_LandingBlockTopPosY;
	}
	else
	{
		return 0;
	}

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetFiledSizeX			:	フィールドサイズを取得				*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short&			:	ブロックの状態						*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFiled::GetFiledSizeX() const
{
	return PUYO_FILED_SIZE_X;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetFiledSizeY			:	フィールドサイズを取得				*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned short			:	ブロックの状態						*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned short CPuyoFiled::GetFiledSizeY() const
{
	return PUYO_FILED_SIZE_Y;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetDeleteChainBlock		:	現在のブロック連鎖数を取得			*/
/*	---------------------------------------------------------------------------	*/
/*	[戻り値]	unsigned char			:	現在の連鎖ブロック数				*/
/*	[引数]		char					:	取得する連鎖数のタイプ				*/
/*											 0 -> 現在　1 -> 最大値				*/
/*																				*/
/*------------------------------------------------------------------------------*/
unsigned char CPuyoFiled::GetDeleteChainBlock(char type) const
{
	if (type)
	{
		return m_DeleteChainBlockMaxCount;
	}
	else
	{
		return m_DeleteChainBlockCurrentCount;
	}
}
