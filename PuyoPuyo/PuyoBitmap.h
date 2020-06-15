#ifndef _PuyoBitmap_H
#define _PuyoBitmap_H

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"
#include "PuyoBitmap.h"

/*--------------*/
/*	名前空間	*/
/*--------------*/
namespace BitmapNS
{
	enum Puyo_Bitmap								/*	ぷよぷよのビットマップ						*/
	{
		PUYOPUYO_NORMAL_TYPE,						/*	通常のぷよぷよ								*/
		PUYOPUYO_CONNECT_LEFT_TYPE,					/*	結合ぷよぷよ ( 左 )							*/
		PUYOPUYO_CONNECT_TOP_TYPE,					/*	結合ぷよぷよ ( 上 )							*/
		PUYOPUYO_CONNECT_RIGHT_TYPE,				/*	結合ぷよぷよ ( 右 )							*/
		PUYOPUYO_CONNECT_BOTTOM_TYPE,				/*	結合ぷよぷよ ( 下 )							*/
		PUYOPUYO_CONNECT_LEFT_TOP_TYPE,				/*	結合ぷよぷよ ( 左、上 )						*/
		PUYOPUYO_CONNECT_LEFT_RIGHT_TYPE,			/*	結合ぷよぷよ ( 左、右 )						*/
		PUYOPUYO_CONNECT_LEFT_BOTTOM_TYPE,			/*	結合ぷよぷよ ( 左、下 )						*/
		PUYOPUYO_CONNECT_TOP_RIGHT_TYPE,			/*	結合ぷよぷよ ( 上、右 )						*/
		PUYOPUYO_CONNECT_TOP_BOTTOM_TYPE,			/*	結合ぷよぷよ ( 上、下 )						*/
		PUYOPUYO_CONNECT_RIGHT_BOTTOM_TYPE,			/*	結合ぷよぷよ ( 右、下 )						*/
		PUYOPUYO_CONNECT_LEFT_TOP_RIGHT_TYPE,		/*	結合ぷよぷよ ( 左、上、右 )					*/
		PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM_TYPE,		/*	結合ぷよぷよ ( 左、上、下 )					*/
		PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM_TYPE,	/*	結合ぷよぷよ ( 左、右、下 )					*/
		PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM_TYPE,		/*	結合ぷよぷよ ( 上、右、下 )					*/
		PUYOPUYO_CONNECT_ALL_TYPE,					/*	結合ぷよぷよ ( 左、上、右、下 )				*/
	};

}

/*----------------------------------*/
/*	ビットマップクラス				*/
/*----------------------------------*/
class CPuyoBitmap
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CPuyoBitmap();

	/*	デストラクタ	*/
	virtual	~CPuyoBitmap();

	/*	関数	*/
	void		LoadBitmapPuyo(HINSTANCE);
	HBITMAP		GetBitmapHandleBluePuyo(BitmapNS::Puyo_Bitmap);
	HBITMAP		GetBitmapHandleGreenPuyo(BitmapNS::Puyo_Bitmap);
	HBITMAP		GetBitmapHandlePurplePuyo(BitmapNS::Puyo_Bitmap);
	HBITMAP		GetBitmapHandleRedPuyo(BitmapNS::Puyo_Bitmap);
	HBITMAP		GetBitmapHandleYellowPuyo(BitmapNS::Puyo_Bitmap);
	HBITMAP		GetBitmapHandleBlackPuyo(BitmapNS::Puyo_Bitmap);

private:
	void		LoadBitmapBluePuyo(HINSTANCE);
	void		LoadBitmapGreenPuyo(HINSTANCE);
	void		LoadBitmapPurplePuyo(HINSTANCE);
	void		LoadBitmapRedPuyo(HINSTANCE);
	void		LoadBitmapYellowPuyo(HINSTANCE);
	void		LoadBitmapBlackPuyo(HINSTANCE);
	void		DeleteBitmapPuyo();
	void		DeleteBitmapBluePuyo();
	void		DeleteBitmapGreenPuyo();
	void		DeleteBitmapPurplePuyo();
	void		DeleteBitmapRedPuyo();
	void		DeleteBitmapYellowPuyo();
	void		DeleteBitmapBlackPuyo();

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	/*	定義用変数 ( const )	*/


private:
	HBITMAP							m_hBluePuyo_n;
	HBITMAP							m_hBluePuyo_l;
	HBITMAP							m_hBluePuyo_t;
	HBITMAP							m_hBluePuyo_r;
	HBITMAP							m_hBluePuyo_b;
	HBITMAP							m_hBluePuyo_lt;
	HBITMAP							m_hBluePuyo_lr;
	HBITMAP							m_hBluePuyo_lb;
	HBITMAP							m_hBluePuyo_tr;
	HBITMAP							m_hBluePuyo_tb;
	HBITMAP							m_hBluePuyo_rb;
	HBITMAP							m_hBluePuyo_ltr;
	HBITMAP							m_hBluePuyo_ltb;
	HBITMAP							m_hBluePuyo_lrb;
	HBITMAP							m_hBluePuyo_trb;
	HBITMAP							m_hBluePuyo_ltrb;

	HBITMAP							m_hGreenPuyo_n;
	HBITMAP							m_hGreenPuyo_l;
	HBITMAP							m_hGreenPuyo_t;
	HBITMAP							m_hGreenPuyo_r;
	HBITMAP							m_hGreenPuyo_b;
	HBITMAP							m_hGreenPuyo_lt;
	HBITMAP							m_hGreenPuyo_lr;
	HBITMAP							m_hGreenPuyo_lb;
	HBITMAP							m_hGreenPuyo_tr;
	HBITMAP							m_hGreenPuyo_tb;
	HBITMAP							m_hGreenPuyo_rb;
	HBITMAP							m_hGreenPuyo_ltr;
	HBITMAP							m_hGreenPuyo_ltb;
	HBITMAP							m_hGreenPuyo_lrb;
	HBITMAP							m_hGreenPuyo_trb;
	HBITMAP							m_hGreenPuyo_ltrb;

	HBITMAP							m_hPurplePuyo_n;
	HBITMAP							m_hPurplePuyo_l;
	HBITMAP							m_hPurplePuyo_t;
	HBITMAP							m_hPurplePuyo_r;
	HBITMAP							m_hPurplePuyo_b;
	HBITMAP							m_hPurplePuyo_lt;
	HBITMAP							m_hPurplePuyo_lr;
	HBITMAP							m_hPurplePuyo_lb;
	HBITMAP							m_hPurplePuyo_tr;
	HBITMAP							m_hPurplePuyo_tb;
	HBITMAP							m_hPurplePuyo_rb;
	HBITMAP							m_hPurplePuyo_ltr;
	HBITMAP							m_hPurplePuyo_ltb;
	HBITMAP							m_hPurplePuyo_lrb;
	HBITMAP							m_hPurplePuyo_trb;
	HBITMAP							m_hPurplePuyo_ltrb;

	HBITMAP							m_hRedPuyo_n;
	HBITMAP							m_hRedPuyo_l;
	HBITMAP							m_hRedPuyo_t;
	HBITMAP							m_hRedPuyo_r;
	HBITMAP							m_hRedPuyo_b;
	HBITMAP							m_hRedPuyo_lt;
	HBITMAP							m_hRedPuyo_lr;
	HBITMAP							m_hRedPuyo_lb;
	HBITMAP							m_hRedPuyo_tr;
	HBITMAP							m_hRedPuyo_tb;
	HBITMAP							m_hRedPuyo_rb;
	HBITMAP							m_hRedPuyo_ltr;
	HBITMAP							m_hRedPuyo_ltb;
	HBITMAP							m_hRedPuyo_lrb;
	HBITMAP							m_hRedPuyo_trb;
	HBITMAP							m_hRedPuyo_ltrb;

	HBITMAP							m_hYellowPuyo_n;
	HBITMAP							m_hYellowPuyo_l;
	HBITMAP							m_hYellowPuyo_t;
	HBITMAP							m_hYellowPuyo_r;
	HBITMAP							m_hYellowPuyo_b;
	HBITMAP							m_hYellowPuyo_lt;
	HBITMAP							m_hYellowPuyo_lr;
	HBITMAP							m_hYellowPuyo_lb;
	HBITMAP							m_hYellowPuyo_tr;
	HBITMAP							m_hYellowPuyo_tb;
	HBITMAP							m_hYellowPuyo_rb;
	HBITMAP							m_hYellowPuyo_ltr;
	HBITMAP							m_hYellowPuyo_ltb;
	HBITMAP							m_hYellowPuyo_lrb;
	HBITMAP							m_hYellowPuyo_trb;
	HBITMAP							m_hYellowPuyo_ltrb;

	HBITMAP							m_hBlackPuyo_n;
};
#endif
