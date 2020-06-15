/*------------------*/
/* インクルード		*/
/*------------------*/
#include "PuyoBitmap.h"
#include "resource.h"

/*==============================================================*/
/*																*/
/*	[関数]		CPuyoBitmap	:	コンストラクタ ( 引数なし )		*/
/*																*/
/*==============================================================*/
CPuyoBitmap::CPuyoBitmap()
{
}

/*======================================================*/
/*														*/
/*	[関数]		~CPuyoBitmap	:	デストラクタ		*/
/*														*/
/*======================================================*/
CPuyoBitmap::~CPuyoBitmap()
{
}

/*----------------------------------------------------------------------------------*/
/*																					*/
/*	[関数]		GetBitmapHandleBluePuyo	:	指定したビットマップのハンドルを取得	*/
/*											 ( ぷよぷよの青色 )						*/
/*	--------------------------------------------------------------------------------*/
/*	[戻り値]	HBITMAP					:	ビットマップハンドル					*/
/*	[引数]		char					:	ビットマップのタイプ					*/
/*																					*/
/*----------------------------------------------------------------------------------*/
HBITMAP CPuyoBitmap::GetBitmapHandleBluePuyo(BitmapNS::Puyo_Bitmap type)
{
	HBITMAP hbitmap = NULL;

	switch (type)
	{
	case BitmapNS::PUYOPUYO_NORMAL_TYPE:							/*	通常のぷよぷよ								*/
		hbitmap = m_hBluePuyo_n;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TYPE:						/*	結合ぷよぷよ ( 左 )							*/
		hbitmap = m_hBluePuyo_l;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_TYPE:						/*	結合ぷよぷよ ( 上 )							*/
		hbitmap = m_hBluePuyo_t;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_RIGHT_TYPE:						/*	結合ぷよぷよ ( 右 )							*/
		hbitmap = m_hBluePuyo_r;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_BOTTOM_TYPE:					/*	結合ぷよぷよ ( 下 )							*/
		hbitmap = m_hBluePuyo_b;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_TYPE:					/*	結合ぷよぷよ ( 左、上 )						*/
		hbitmap = m_hBluePuyo_lt;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_RIGHT_TYPE:				/*	結合ぷよぷよ ( 左、右 )						*/
		hbitmap = m_hBluePuyo_lr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 左、下 )						*/
		hbitmap = m_hBluePuyo_lb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_RIGHT_TYPE:					/*	結合ぷよぷよ ( 上、右 )						*/
		hbitmap = m_hBluePuyo_tr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 上、下 )						*/
		hbitmap = m_hBluePuyo_tb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_RIGHT_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 右、下 )						*/
		hbitmap = m_hBluePuyo_rb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_RIGHT_TYPE:			/*	結合ぷよぷよ ( 左、上、右 )					*/
		hbitmap = m_hBluePuyo_ltr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 左、上、下 )					*/
		hbitmap = m_hBluePuyo_ltb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 左、右、下 )					*/
		hbitmap = m_hBluePuyo_lrb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 上、右、下 )					*/
		hbitmap = m_hBluePuyo_trb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_ALL_TYPE:						/*	結合ぷよぷよ ( 左、上、右、下 )				*/
		hbitmap = m_hBluePuyo_ltrb;
		break;

	default:
		break;
	}

	return hbitmap;
}

/*--------------------------------------------------------------------------------------*/
/*																						*/
/*	[関数]		GetBitmapHandleGreenPuyo	:	指定したビットマップのハンドルを取得	*/
/*												( ぷよぷよの緑色 )						*/
/*	------------------------------------------------------------------------------------*/
/*	[戻り値]	HBITMAP						:	ビットマップハンドル					*/
/*	[引数]		char						:	ビットマップのタイプ					*/
/*																						*/
/*--------------------------------------------------------------------------------------*/
HBITMAP CPuyoBitmap::GetBitmapHandleGreenPuyo(BitmapNS::Puyo_Bitmap type)
{
	HBITMAP hbitmap = NULL;

	switch (type)
	{
	case BitmapNS::PUYOPUYO_NORMAL_TYPE:							/*	通常のぷよぷよ								*/
		hbitmap = m_hGreenPuyo_n;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TYPE:						/*	結合ぷよぷよ ( 左 )							*/
		hbitmap = m_hGreenPuyo_l;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_TYPE:						/*	結合ぷよぷよ ( 上 )							*/
		hbitmap = m_hGreenPuyo_t;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_RIGHT_TYPE:						/*	結合ぷよぷよ ( 右 )							*/
		hbitmap = m_hGreenPuyo_r;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_BOTTOM_TYPE:					/*	結合ぷよぷよ ( 下 )							*/
		hbitmap = m_hGreenPuyo_b;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_TYPE:					/*	結合ぷよぷよ ( 左、上 )						*/
		hbitmap = m_hGreenPuyo_lt;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_RIGHT_TYPE:				/*	結合ぷよぷよ ( 左、右 )						*/
		hbitmap = m_hGreenPuyo_lr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 左、下 )						*/
		hbitmap = m_hGreenPuyo_lb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_RIGHT_TYPE:					/*	結合ぷよぷよ ( 上、右 )						*/
		hbitmap = m_hGreenPuyo_tr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 上、下 )						*/
		hbitmap = m_hGreenPuyo_tb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_RIGHT_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 右、下 )						*/
		hbitmap = m_hGreenPuyo_rb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_RIGHT_TYPE:			/*	結合ぷよぷよ ( 左、上、右 )					*/
		hbitmap = m_hGreenPuyo_ltr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 左、上、下 )					*/
		hbitmap = m_hGreenPuyo_ltb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 左、右、下 )					*/
		hbitmap = m_hGreenPuyo_lrb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 上、右、下 )					*/
		hbitmap = m_hGreenPuyo_trb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_ALL_TYPE:						/*	結合ぷよぷよ ( 左、上、右、下 )				*/
		hbitmap = m_hGreenPuyo_ltrb;
		break;

	default:
		break;
	}

	return hbitmap;
}

/*--------------------------------------------------------------------------------------*/
/*																						*/
/*	[関数]		GetBitmapHandlePurplePuyo	:	指定したビットマップのハンドルを取得	*/
/*												( ぷよぷよの紫色 )						*/
/*	------------------------------------------------------------------------------------*/
/*	[戻り値]	HBITMAP						:	ビットマップハンドル					*/
/*	[引数]		char						:	ビットマップのタイプ					*/
/*																						*/
/*--------------------------------------------------------------------------------------*/
HBITMAP CPuyoBitmap::GetBitmapHandlePurplePuyo(BitmapNS::Puyo_Bitmap type)
{
	HBITMAP hbitmap = NULL;

	switch (type)
	{
	case BitmapNS::PUYOPUYO_NORMAL_TYPE:							/*	通常のぷよぷよ								*/
		hbitmap = m_hPurplePuyo_n;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TYPE:						/*	結合ぷよぷよ ( 左 )							*/
		hbitmap = m_hPurplePuyo_l;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_TYPE:						/*	結合ぷよぷよ ( 上 )							*/
		hbitmap = m_hPurplePuyo_t;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_RIGHT_TYPE:						/*	結合ぷよぷよ ( 右 )							*/
		hbitmap = m_hPurplePuyo_r;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_BOTTOM_TYPE:					/*	結合ぷよぷよ ( 下 )							*/
		hbitmap = m_hPurplePuyo_b;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_TYPE:					/*	結合ぷよぷよ ( 左、上 )						*/
		hbitmap = m_hPurplePuyo_lt;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_RIGHT_TYPE:				/*	結合ぷよぷよ ( 左、右 )						*/
		hbitmap = m_hPurplePuyo_lr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 左、下 )						*/
		hbitmap = m_hPurplePuyo_lb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_RIGHT_TYPE:					/*	結合ぷよぷよ ( 上、右 )						*/
		hbitmap = m_hPurplePuyo_tr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 上、下 )						*/
		hbitmap = m_hPurplePuyo_tb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_RIGHT_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 右、下 )						*/
		hbitmap = m_hPurplePuyo_rb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_RIGHT_TYPE:			/*	結合ぷよぷよ ( 左、上、右 )					*/
		hbitmap = m_hPurplePuyo_ltr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 左、上、下 )					*/
		hbitmap = m_hPurplePuyo_ltb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 左、右、下 )					*/
		hbitmap = m_hPurplePuyo_lrb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 上、右、下 )					*/
		hbitmap = m_hPurplePuyo_trb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_ALL_TYPE:						/*	結合ぷよぷよ ( 左、上、右、下 )				*/
		hbitmap = m_hPurplePuyo_ltrb;
		break;

	default:
		break;
	}

	return hbitmap;
}

/*--------------------------------------------------------------------------------------*/
/*																						*/
/*	[関数]		GetBitmapHandleRedPuyo		:	指定したビットマップのハンドルを取得	*/
/*												( ぷよぷよの赤色 )						*/
/*	------------------------------------------------------------------------------------*/
/*	[戻り値]	HBITMAP						:	ビットマップハンドル					*/
/*	[引数]		char						:	ビットマップのタイプ					*/
/*																						*/
/*--------------------------------------------------------------------------------------*/
HBITMAP CPuyoBitmap::GetBitmapHandleRedPuyo(BitmapNS::Puyo_Bitmap type)
{
	HBITMAP hbitmap = NULL;

	switch (type)
	{
	case BitmapNS::PUYOPUYO_NORMAL_TYPE:							/*	通常のぷよぷよ								*/
		hbitmap = m_hRedPuyo_n;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TYPE:						/*	結合ぷよぷよ ( 左 )							*/
		hbitmap = m_hRedPuyo_l;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_TYPE:						/*	結合ぷよぷよ ( 上 )							*/
		hbitmap = m_hRedPuyo_t;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_RIGHT_TYPE:						/*	結合ぷよぷよ ( 右 )							*/
		hbitmap = m_hRedPuyo_r;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_BOTTOM_TYPE:					/*	結合ぷよぷよ ( 下 )							*/
		hbitmap = m_hRedPuyo_b;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_TYPE:					/*	結合ぷよぷよ ( 左、上 )						*/
		hbitmap = m_hRedPuyo_lt;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_RIGHT_TYPE:				/*	結合ぷよぷよ ( 左、右 )						*/
		hbitmap = m_hRedPuyo_lr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 左、下 )						*/
		hbitmap = m_hRedPuyo_lb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_RIGHT_TYPE:					/*	結合ぷよぷよ ( 上、右 )						*/
		hbitmap = m_hRedPuyo_tr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 上、下 )						*/
		hbitmap = m_hRedPuyo_tb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_RIGHT_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 右、下 )						*/
		hbitmap = m_hRedPuyo_rb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_RIGHT_TYPE:			/*	結合ぷよぷよ ( 左、上、右 )					*/
		hbitmap = m_hRedPuyo_ltr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 左、上、下 )					*/
		hbitmap = m_hRedPuyo_ltb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 左、右、下 )					*/
		hbitmap = m_hRedPuyo_lrb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 上、右、下 )					*/
		hbitmap = m_hRedPuyo_trb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_ALL_TYPE:						/*	結合ぷよぷよ ( 左、上、右、下 )				*/
		hbitmap = m_hRedPuyo_ltrb;
		break;

	default:
		break;
	}

	return hbitmap;
}

/*--------------------------------------------------------------------------------------*/
/*																						*/
/*	[関数]		GetBitmapHandleYellowPuyo	:	指定したビットマップのハンドルを取得	*/
/*												( ぷよぷよの黄色 )						*/
/*	------------------------------------------------------------------------------------*/
/*	[戻り値]	HBITMAP						:	ビットマップハンドル					*/
/*	[引数]		char						:	ビットマップのタイプ					*/
/*																						*/
/*--------------------------------------------------------------------------------------*/
HBITMAP CPuyoBitmap::GetBitmapHandleYellowPuyo(BitmapNS::Puyo_Bitmap type)
{
	HBITMAP hbitmap = NULL;

	switch (type)
	{
	case BitmapNS::PUYOPUYO_NORMAL_TYPE:							/*	通常のぷよぷよ								*/
		hbitmap = m_hYellowPuyo_n;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TYPE:						/*	結合ぷよぷよ ( 左 )							*/
		hbitmap = m_hYellowPuyo_l;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_TYPE:						/*	結合ぷよぷよ ( 上 )							*/
		hbitmap = m_hYellowPuyo_t;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_RIGHT_TYPE:						/*	結合ぷよぷよ ( 右 )							*/
		hbitmap = m_hYellowPuyo_r;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_BOTTOM_TYPE:					/*	結合ぷよぷよ ( 下 )							*/
		hbitmap = m_hYellowPuyo_b;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_TYPE:					/*	結合ぷよぷよ ( 左、上 )						*/
		hbitmap = m_hYellowPuyo_lt;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_RIGHT_TYPE:				/*	結合ぷよぷよ ( 左、右 )						*/
		hbitmap = m_hYellowPuyo_lr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 左、下 )						*/
		hbitmap = m_hYellowPuyo_lb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_RIGHT_TYPE:					/*	結合ぷよぷよ ( 上、右 )						*/
		hbitmap = m_hYellowPuyo_tr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 上、下 )						*/
		hbitmap = m_hYellowPuyo_tb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_RIGHT_BOTTOM_TYPE:				/*	結合ぷよぷよ ( 右、下 )						*/
		hbitmap = m_hYellowPuyo_rb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_RIGHT_TYPE:			/*	結合ぷよぷよ ( 左、上、右 )					*/
		hbitmap = m_hYellowPuyo_ltr;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 左、上、下 )					*/
		hbitmap = m_hYellowPuyo_ltb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 左、右、下 )					*/
		hbitmap = m_hYellowPuyo_lrb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM_TYPE:			/*	結合ぷよぷよ ( 上、右、下 )					*/
		hbitmap = m_hYellowPuyo_trb;
		break;

	case BitmapNS::PUYOPUYO_CONNECT_ALL_TYPE:						/*	結合ぷよぷよ ( 左、上、右、下 )				*/
		hbitmap = m_hYellowPuyo_ltrb;
		break;

	default:
		break;
	}

	return hbitmap;
}

/*--------------------------------------------------------------------------------------*/
/*																						*/
/*	[関数]		GetBitmapHandleBlackPuyo	:	指定したビットマップのハンドルを取得	*/
/*												( ぷよぷよの黒色 )						*/
/*	------------------------------------------------------------------------------------*/
/*	[戻り値]	HBITMAP						:	ビットマップハンドル					*/
/*	[引数]		char						:	ビットマップのタイプ					*/
/*																						*/
/*--------------------------------------------------------------------------------------*/
HBITMAP CPuyoBitmap::GetBitmapHandleBlackPuyo(BitmapNS::Puyo_Bitmap type)
{
	HBITMAP hbitmap = NULL;

	switch (type)
	{
	case BitmapNS::PUYOPUYO_NORMAL_TYPE:						/*	通常のぷよぷよ								*/
		hbitmap = m_hBlackPuyo_n;
		break;

	default:
		break;
	}

	return hbitmap;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		LoadBitmap			:	ビットマップをロード					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]		void				:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::LoadBitmapPuyo(HINSTANCE hinst)
{
	/************************************/
	/*	各種ビットマップのロード		*/
	/************************************/
	LoadBitmapBluePuyo(hinst);
	LoadBitmapGreenPuyo(hinst);
	LoadBitmapPurplePuyo(hinst);
	LoadBitmapRedPuyo(hinst);
	LoadBitmapYellowPuyo(hinst);
	LoadBitmapBlackPuyo(hinst);
}


/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		LoadBitmapBluePuyo	:	ぷよぷよの青色をロード					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]		void				:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::LoadBitmapBluePuyo(HINSTANCE hinst)
{
	// 配布用に別ファイルにするのは大変なので、ビットマップはリソースに登録しておく
	m_hBluePuyo_n		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_NORMAL)						, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_l		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_LEFT)					, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_t		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_TOP)					, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_r		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_TOP_RIGHT)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_b		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_BOTTOM)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_lt		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_LEFT_TOP)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_lr		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_LEFT_RIGHT)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_lb		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_tr		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_TOP_RIGHT)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_tb		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_TOP_BOTTOM)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_rb		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_RIGHT_BOTTOM)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_ltr		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_LEFT_TOP_RIGTH)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_ltb		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_lrb		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM)	, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_trb		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hBluePuyo_ltrb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BULE_PUYOPUYO_CONNECT_ALL)					, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

}


/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		LoadBitmapGreenPuyo	:	ぷよぷよの緑色をロード					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void				:	なし									*/
/*	[引数]		void				:	なし									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::LoadBitmapGreenPuyo(HINSTANCE hinst)
{
	m_hGreenPuyo_n		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_NORMAL)						, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_l		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_LEFT)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_t		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_TOP)					, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_r		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_TOP_RIGHT)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_b		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_BOTTOM)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_lt		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_LEFT_TOP)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_lr		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_LEFT_RIGHT)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_lb		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_tr		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_TOP_RIGHT)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_tb		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_TOP_BOTTOM)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_rb		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_RIGHT_BOTTOM)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_ltr	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_LEFT_TOP_RIGTH)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_ltb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_lrb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM)	, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_trb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM)	, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hGreenPuyo_ltrb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_GREEN_PUYOPUYO_CONNECT_ALL)					, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		LoadBitmapPurplePuyo	:	ぷよぷよの紫色をロード				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::LoadBitmapPurplePuyo(HINSTANCE hinst)
{
	m_hPurplePuyo_n		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_NORMAL)						, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_l		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_LEFT)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_t		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_TOP)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_r		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_TOP_RIGHT)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_b		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_BOTTOM)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_lt	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_LEFT_TOP)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_lr	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_LEFT_RIGHT)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_lb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM)	, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_tr	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_TOP_RIGHT)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_tb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_TOP_BOTTOM)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_rb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_RIGHT_BOTTOM)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_ltr	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_LEFT_TOP_RIGTH)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_ltb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM)	, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_lrb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM)	, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_trb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM)	, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hPurplePuyo_ltrb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_PURPLE_PUYOPUYO_CONNECT_ALL)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

}


/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		LoadBitmapRedPuyo		:	ぷよぷよの赤色をロード				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::LoadBitmapRedPuyo(HINSTANCE hinst)
{
	m_hRedPuyo_n	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_NORMAL)						, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_l	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_LEFT)					, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_t	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_TOP)					, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_r	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_TOP_RIGHT)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_b	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_BOTTOM)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_lt	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_LEFT_TOP)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_lr	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_LEFT_RIGHT)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_lb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_tr	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_TOP_RIGHT)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_tb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_TOP_BOTTOM)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_rb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_RIGHT_BOTTOM)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_ltr	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_LEFT_TOP_RIGTH)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_ltb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_lrb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_trb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hRedPuyo_ltrb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_RED_PUYOPUYO_CONNECT_ALL)					, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		LoadBitmapYellowPuyo	:	ぷよぷよの黄色をロード				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::LoadBitmapYellowPuyo(HINSTANCE hinst)
{
	m_hYellowPuyo_n		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_NORMAL)						, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_l		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_LEFT)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_t		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_TOP)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_r		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_TOP_RIGHT)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_b		= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_BOTTOM)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_lt	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_LEFT_TOP)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_lr	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_LEFT_RIGHT)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_lb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM)	, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_tr	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_TOP_RIGHT)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_tb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_TOP_BOTTOM)			, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_rb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_RIGHT_BOTTOM)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_ltr	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_LEFT_TOP_RIGTH)		, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_ltb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM)	, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_lrb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM)	, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_trb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM)	, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	m_hYellowPuyo_ltrb	= (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_YELLOW_PUYOPUYO_CONNECT_ALL)				, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		LoadBitmapBlackPuyo		:	ぷよぷよの黒色をロード				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::LoadBitmapBlackPuyo(HINSTANCE hinst)
{
	m_hBlackPuyo_n = (HBITMAP)LoadImage(hinst, MAKEINTRESOURCE(IDB_BLACK_PUYOPUYO_NORMAL), IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}


/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		DeleteBitmapPuyo		:	ぷよぷよを削除						*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::DeleteBitmapPuyo()
{
	DeleteBitmapBluePuyo();
	DeleteBitmapGreenPuyo();
	DeleteBitmapPurplePuyo();
	DeleteBitmapRedPuyo();
	DeleteBitmapYellowPuyo();
	DeleteBitmapBlackPuyo();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		DeleteBitmapBluePuyo	:	ぷよぷよの青色を削除				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::DeleteBitmapBluePuyo()
{
	/****************************/
	/*	オブジェクトの削除		*/
	/****************************/
	DeleteObject(m_hBluePuyo_n);
	DeleteObject(m_hBluePuyo_l);
	DeleteObject(m_hBluePuyo_t);
	DeleteObject(m_hBluePuyo_r);
	DeleteObject(m_hBluePuyo_b);
	DeleteObject(m_hBluePuyo_lt);
	DeleteObject(m_hBluePuyo_lr);
	DeleteObject(m_hBluePuyo_lb);
	DeleteObject(m_hBluePuyo_tr);
	DeleteObject(m_hBluePuyo_tb);
	DeleteObject(m_hBluePuyo_rb);
	DeleteObject(m_hBluePuyo_ltr);
	DeleteObject(m_hBluePuyo_ltb);
	DeleteObject(m_hBluePuyo_lrb);
	DeleteObject(m_hBluePuyo_trb);
	DeleteObject(m_hBluePuyo_ltrb);

	/****************************/
	/*	オブジェクトの初期化	*/
	/****************************/
	m_hBluePuyo_n		= NULL;
	m_hBluePuyo_l		= NULL;
	m_hBluePuyo_t		= NULL;
	m_hBluePuyo_r		= NULL;
	m_hBluePuyo_b		= NULL;
	m_hBluePuyo_lt		= NULL;
	m_hBluePuyo_lr		= NULL;
	m_hBluePuyo_lb		= NULL;
	m_hBluePuyo_tr		= NULL;
	m_hBluePuyo_tb		= NULL;
	m_hBluePuyo_rb		= NULL;
	m_hBluePuyo_ltr		= NULL;
	m_hBluePuyo_ltb		= NULL;
	m_hBluePuyo_lrb		= NULL;
	m_hBluePuyo_trb		= NULL;
	m_hBluePuyo_ltrb	= NULL;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		DeleteBitmapGreenPuyo	:	ぷよぷよの緑色を削除				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::DeleteBitmapGreenPuyo()
{
	/****************************/
	/*	オブジェクトの削除		*/
	/****************************/
	DeleteObject(m_hGreenPuyo_n);
	DeleteObject(m_hGreenPuyo_l);
	DeleteObject(m_hGreenPuyo_t);
	DeleteObject(m_hGreenPuyo_r);
	DeleteObject(m_hGreenPuyo_b);
	DeleteObject(m_hGreenPuyo_lt);
	DeleteObject(m_hGreenPuyo_lr);
	DeleteObject(m_hGreenPuyo_lb);
	DeleteObject(m_hGreenPuyo_tr);
	DeleteObject(m_hGreenPuyo_tb);
	DeleteObject(m_hGreenPuyo_rb);
	DeleteObject(m_hGreenPuyo_ltr);
	DeleteObject(m_hGreenPuyo_ltb);
	DeleteObject(m_hGreenPuyo_lrb);
	DeleteObject(m_hGreenPuyo_trb);
	DeleteObject(m_hGreenPuyo_ltrb);

	/****************************/
	/*	オブジェクトの初期化	*/
	/****************************/
	m_hGreenPuyo_n		= NULL;
	m_hGreenPuyo_l		= NULL;
	m_hGreenPuyo_t		= NULL;
	m_hGreenPuyo_r		= NULL;
	m_hGreenPuyo_b		= NULL;
	m_hGreenPuyo_lt		= NULL;
	m_hGreenPuyo_lr		= NULL;
	m_hGreenPuyo_lb		= NULL;
	m_hGreenPuyo_tr		= NULL;
	m_hGreenPuyo_tb		= NULL;
	m_hGreenPuyo_rb		= NULL;
	m_hGreenPuyo_ltr	= NULL;
	m_hGreenPuyo_ltb	= NULL;
	m_hGreenPuyo_lrb	= NULL;
	m_hGreenPuyo_trb	= NULL;
	m_hGreenPuyo_ltrb	= NULL;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		DeleteBitmapPurplePuyo	:	ぷよぷよの紫色を削除				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::DeleteBitmapPurplePuyo()
{
	/****************************/
	/*	オブジェクトの削除		*/
	/****************************/
	DeleteObject(m_hPurplePuyo_n);
	DeleteObject(m_hPurplePuyo_l);
	DeleteObject(m_hPurplePuyo_t);
	DeleteObject(m_hPurplePuyo_r);
	DeleteObject(m_hPurplePuyo_b);
	DeleteObject(m_hPurplePuyo_lt);
	DeleteObject(m_hPurplePuyo_lr);
	DeleteObject(m_hPurplePuyo_lb);
	DeleteObject(m_hPurplePuyo_tr);
	DeleteObject(m_hPurplePuyo_tb);
	DeleteObject(m_hPurplePuyo_rb);
	DeleteObject(m_hPurplePuyo_ltr);
	DeleteObject(m_hPurplePuyo_ltb);
	DeleteObject(m_hPurplePuyo_lrb);
	DeleteObject(m_hPurplePuyo_trb);
	DeleteObject(m_hPurplePuyo_ltrb);

	/****************************/
	/*	オブジェクトの初期化	*/
	/****************************/
	m_hPurplePuyo_n		= NULL;
	m_hPurplePuyo_l		= NULL;
	m_hPurplePuyo_t		= NULL;
	m_hPurplePuyo_r		= NULL;
	m_hPurplePuyo_b		= NULL;
	m_hPurplePuyo_lt	= NULL;
	m_hPurplePuyo_lr	= NULL;
	m_hPurplePuyo_lb	= NULL;
	m_hPurplePuyo_tr	= NULL;
	m_hPurplePuyo_tb	= NULL;
	m_hPurplePuyo_rb	= NULL;
	m_hPurplePuyo_ltr	= NULL;
	m_hPurplePuyo_ltb	= NULL;
	m_hPurplePuyo_lrb	= NULL;
	m_hPurplePuyo_trb	= NULL;
	m_hPurplePuyo_ltrb	= NULL;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		DeleteBitmapRedPuyo		:	ぷよぷよの赤色を削除				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::DeleteBitmapRedPuyo()
{
	/****************************/
	/*	オブジェクトの削除		*/
	/****************************/
	DeleteObject(m_hRedPuyo_n);
	DeleteObject(m_hRedPuyo_l);
	DeleteObject(m_hRedPuyo_t);
	DeleteObject(m_hRedPuyo_r);
	DeleteObject(m_hRedPuyo_b);
	DeleteObject(m_hRedPuyo_lt);
	DeleteObject(m_hRedPuyo_lr);
	DeleteObject(m_hRedPuyo_lb);
	DeleteObject(m_hRedPuyo_tr);
	DeleteObject(m_hRedPuyo_tb);
	DeleteObject(m_hRedPuyo_rb);
	DeleteObject(m_hRedPuyo_ltr);
	DeleteObject(m_hRedPuyo_ltb);
	DeleteObject(m_hRedPuyo_lrb);
	DeleteObject(m_hRedPuyo_trb);
	DeleteObject(m_hRedPuyo_ltrb);

	/****************************/
	/*	オブジェクトの初期化	*/
	/****************************/
	m_hRedPuyo_n	= NULL;
	m_hRedPuyo_l	= NULL;
	m_hRedPuyo_t	= NULL;
	m_hRedPuyo_r	= NULL;
	m_hRedPuyo_b	= NULL;
	m_hRedPuyo_lt	= NULL;
	m_hRedPuyo_lr	= NULL;
	m_hRedPuyo_lb	= NULL;
	m_hRedPuyo_tr	= NULL;
	m_hRedPuyo_tb	= NULL;
	m_hRedPuyo_rb	= NULL;
	m_hRedPuyo_ltr	= NULL;
	m_hRedPuyo_ltb	= NULL;
	m_hRedPuyo_lrb	= NULL;
	m_hRedPuyo_trb	= NULL;
	m_hRedPuyo_ltrb = NULL;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		DeleteBitmapYellowPuyo	:	ぷよぷよの黄色を削除				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::DeleteBitmapYellowPuyo()
{
	/****************************/
	/*	オブジェクトの削除		*/
	/****************************/
	DeleteObject(m_hYellowPuyo_n);
	DeleteObject(m_hYellowPuyo_l);
	DeleteObject(m_hYellowPuyo_t);
	DeleteObject(m_hYellowPuyo_r);
	DeleteObject(m_hYellowPuyo_b);
	DeleteObject(m_hYellowPuyo_lt);
	DeleteObject(m_hYellowPuyo_lr);
	DeleteObject(m_hYellowPuyo_lb);
	DeleteObject(m_hYellowPuyo_tr);
	DeleteObject(m_hYellowPuyo_tb);
	DeleteObject(m_hYellowPuyo_rb);
	DeleteObject(m_hYellowPuyo_ltr);
	DeleteObject(m_hYellowPuyo_ltb);
	DeleteObject(m_hYellowPuyo_lrb);
	DeleteObject(m_hYellowPuyo_trb);
	DeleteObject(m_hYellowPuyo_ltrb);

	/****************************/
	/*	オブジェクトの初期化	*/
	/****************************/
	m_hYellowPuyo_n		= NULL;
	m_hYellowPuyo_l		= NULL;
	m_hYellowPuyo_t		= NULL;
	m_hYellowPuyo_r		= NULL;
	m_hYellowPuyo_b		= NULL;
	m_hYellowPuyo_lt	= NULL;
	m_hYellowPuyo_lr	= NULL;
	m_hYellowPuyo_lb	= NULL;
	m_hYellowPuyo_tr	= NULL;
	m_hYellowPuyo_tb	= NULL;
	m_hYellowPuyo_rb	= NULL;
	m_hYellowPuyo_ltr	= NULL;
	m_hYellowPuyo_ltb	= NULL;
	m_hYellowPuyo_lrb	= NULL;
	m_hYellowPuyo_trb	= NULL;
	m_hYellowPuyo_ltrb	= NULL;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		DeleteBitmapBlackPuyo	:	ぷよぷよの黒色を削除				*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void					:	なし								*/
/*	[引数]		void					:	なし								*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CPuyoBitmap::DeleteBitmapBlackPuyo()
{
	/****************************/
	/*	オブジェクトの削除		*/
	/****************************/
	DeleteObject(m_hBlackPuyo_n);

	/****************************/
	/*	オブジェクトの初期化	*/
	/****************************/
	m_hBlackPuyo_n = NULL;
}