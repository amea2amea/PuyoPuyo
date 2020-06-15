/*------------------*/
/* インクルード		*/
/*------------------*/
#include "PuyoManger.h"
#include "PuyoLogic.h"

/*==============================================================================*/
/*																				*/
/*	[関数]		CPuyoLogic		:	コンストラクタ ( 引数なし )					*/
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
/*	[関数]		~CPuyoLogic		:	デストラクタ								*/
/*																				*/
/*==============================================================================*/
CPuyoLogic::~CPuyoLogic()
{
}

/*==============================================================================*/
/*																				*/
/*	[関数]		Logic				:	ロジック								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
void CPuyoLogic::Logic(CInput* input)
{
	/************************/
	/*	終了処理			*/
	/************************/
	if (m_bFinish == true)
		return;
	
	/************************/
	/*	初期化処理			*/
	/************************/
	if (m_bInit == false)
	{
		Init();					/*	初期化処理			*/
	}

	/************************/
	/*	キー処理			*/
	/************************/
	if (Keydown(input))
	{
		UpdateBlock();
	}

	/************************/
	/*	更新処理			*/
	/************************/
	Update();

	return;

}
/*==============================================================================*/
/*																				*/
/*	[関数]		Init				:	初期設定								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
void CPuyoLogic::Init()
{
	/********************/
	/*	ぷよぷよを作成	*/
	/********************/
	m_PuyoFiled.Init();

	/****************************/
	/*	次のブロックの初期設定	*/
	/****************************/
	m_PuyoFiled.NextWaitBlockInit();

	/********************************/
	/*	現在のブロック状態を設定	*/
	/********************************/
	m_PuyoFiled.SetCurrentBlockState();

	/************************************/
	/*	ブロックをフィールドにコピー	*/
	/************************************/
	m_PuyoFiled.CurrentBlockToBoard(2);

	/************************/
	/*	待機ブロックを作成	*/
	/************************/
	m_PuyoFiled.NextWaitBlock();

	/****************/
	/*	初期化完了	*/
	/****************/
	m_bInit = true;

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		Keydown				:	キーダウン処理							*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
bool CPuyoLogic::Keydown(CInput* input)
{
	char keycord		= input->GetKeyPressed();
	char ctrl_keydown	= input->isKeyDown(VK_CONTROL);
	bool block_move = false;

	/****************************************/
	/*	着地後の落下中はキー処理させない	*/
	/****************************************/
	if (m_bDroppingBlock == true)
		return block_move;

	/********************************/
	/*	落下モードの状態チェック	*/
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
/*	[関数]		Update				:	更新処理								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
void CPuyoLogic::Update()
{
	/************************/
	/*	更新タイマー処理	*/
	/************************/
	if (!UpdateTimer())
		return;

	/****************************/
	/*	着地後の落下中の判定	*/
	/****************************/
	if (m_bDroppingBlock == false)														/*	ブロックチェック処理中ではないならば	*/
	{
		/************************/
		/*	ブロック更新処理	*/
		/************************/
		if (m_PuyoFiled.CurrentMoveBlock(BlockNS::BLOCK_MOVE_DOWN))
		{
			UpdateBlock();

		}
		else
		{
			/****************************/
			/*	ゲーム終了の判定		*/
			/****************************/
			if (m_PuyoFiled.isGameOver())
			{
				m_bFinish = true;
			}
			else																			/*	次のブロックへ進むならば				*/
			{
				/****************************/
				/*	ブロックチェック処理	*/
				/*	(着地後の１回目の処理 )	*/
				/****************************/
				CheckBlock();
			}
		}
	}
	else																				/*	ブロックチェック処理中ならば			*/
	{
		/****************************/
		/*	ブロックチェック処理	*/
		/*	(落下中の処理 )			*/
		/****************************/
		CheckBlock();
	}

	/********************/
	/*	時間の更新		*/
	/********************/
	m_TimeStart = m_TimeEnd;

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		UpdateBlock			:	ブロック更新処理						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
void CPuyoLogic::UpdateBlock()
{
	/********************************/
	/*	現在のブロック状態を設定	*/
	/********************************/
	m_PuyoFiled.SetCurrentBlockState();

	/************************************/
	/*	ブロックをフィールドにコピー	*/
	/************************************/
	m_PuyoFiled.CurrentBlockToBoard(0);

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		CheckBlock			:	ブロックチェック処理					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
void CPuyoLogic::CheckBlock()
{
	/********************************/
	/*	ブロックのチェック処理		*/
	/********************************/
	if (m_PuyoFiled.CheckBlockState() == true)						/*	ブロックチェック処理が完了済ならば		*/
	{
		/************************/
		/*	得点の更新処理		*/
		/************************/
		UpdatePoint();

		/****************************/
		/*	次のブロックを作成		*/
		/****************************/
		m_PuyoFiled.NextCurrentBlock();
		m_PuyoFiled.NextWaitBlock();

		/****************************************/
		/*	次のブロックをフィールドにコピー	*/
		/****************************************/
		m_PuyoFiled.CurrentBlockToBoard(2);

		/****************************/
		/*	次のブロックの待ち時間	*/
		/****************************/
		m_bDroppingBlock = false;
		Sleep(CPuyoManger::Instance()->GetPuyoNextBlockWaitTime());
	}
	else																/*	ブロックチェック処理が未完了ならば		*/
	{
		m_bDroppingBlock = true;
	}

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		UpdatePoint			:	得点の更新処理							*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
void CPuyoLogic::UpdatePoint()
{
	unsigned char block_delete = m_PuyoFiled.GetBlockDeleteInfo();

	/************************/
	/*	得点処理 ( 連段 )	*/
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
	/*	シングル ( 複数 )	*/
	/************************/
	if (block_delete & BIT4)
	{
		CPuyoManger::Instance()->SetPuyoPoint() += PUYO_SINGLE_POINTS * 2;
	}

	return;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		UpdateTimer			:	更新タイマー処理						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool				:	なし									*/
/*	[引数]							:	なし									*/
/*																				*/
/*==============================================================================*/
bool CPuyoLogic::UpdateTimer()
{
	/************************************/
	/*	更新タイマーのスピードアップ	*/
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
	/*	更新タイマー処理	*/
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

