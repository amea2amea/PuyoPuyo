/*------------------*/
/* ifdef用の定義	*/
/*------------------*/
#define WIN32_LEAN_AND_MEAN

#ifndef _GROBAL_H
#define _GROBAL_H

/*------------------*/
/* インクルード		*/
/*------------------*/
#include <windows.h>
#include <tchar.h>
#include <basetsd.h>
#include <math.h>
#include <time.h>
#include <crtdbg.h>
#include <mmsystem.h>
#include <Strsafe.h>
#include <String.h>
#include <wingdi.h>

/*--------------*/
/*	定義		*/
/*--------------*/

/*	キーマップ	*/
#define VK_B 0x42
#define VK_C 0x43
#define VK_V 0x56

/*	画像ファイルのURL	*/
#define IMAGE_FILE									_T("..\\Image")
#define BULE_PUYOPUYO_NORMAL						_T("..\\Image\\blue_normal.bmp")
#define BULE_PUYOPUYO_CONNECT_LEFT					_T("..\\Image\\blue_l.bmp")
#define BULE_PUYOPUYO_CONNECT_LEFT_BOTTOM			_T("..\\Image\\blue_lb.bmp")
#define BULE_PUYOPUYO_CONNECT_LEFT_RIGHT			_T("..\\Image\\blue_lr.bmp")
#define BULE_PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM		_T("..\\Image\\blue_lrb.bmp")
#define BULE_PUYOPUYO_CONNECT_LEFT_TOP				_T("..\\Image\\blue_lt.bmp")
#define BULE_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM		_T("..\\Image\\blue_ltb.bmp")
#define BULE_PUYOPUYO_CONNECT_LEFT_TOP_RIGTH		_T("..\\Image\\blue_ltr.bmp")
#define BULE_PUYOPUYO_CONNECT_TOP					_T("..\\Image\\blue_t.bmp")
#define BULE_PUYOPUYO_CONNECT_TOP_RIGHT				_T("..\\Image\\blue_tr.bmp")
#define BULE_PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM		_T("..\\Image\\blue_trb.bmp")
#define BULE_PUYOPUYO_CONNECT_TOP_BOTTOM			_T("..\\Image\\blue_tb.bmp")
#define BULE_PUYOPUYO_CONNECT_RIGHT					_T("..\\Image\\blue_r.bmp")
#define BULE_PUYOPUYO_CONNECT_RIGHT_BOTTOM			_T("..\\Image\\blue_rb.bmp")
#define BULE_PUYOPUYO_CONNECT_BOTTOM				_T("..\\Image\\blue_b.bmp")
#define BULE_PUYOPUYO_CONNECT_ALL					_T("..\\Image\\blue_ltrb.bmp")

#define GREEN_PUYOPUYO_NORMAL						_T("..\\Image\\green_normal.bmp")
#define GREEN_PUYOPUYO_CONNECT_LEFT					_T("..\\Image\\green_l.bmp")
#define GREEN_PUYOPUYO_CONNECT_LEFT_BOTTOM			_T("..\\Image\\green_lb.bmp")
#define GREEN_PUYOPUYO_CONNECT_LEFT_RIGHT			_T("..\\Image\\green_lr.bmp")
#define GREEN_PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM	_T("..\\Image\\green_lrb.bmp")
#define GREEN_PUYOPUYO_CONNECT_LEFT_TOP				_T("..\\Image\\green_lt.bmp")
#define GREEN_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM		_T("..\\Image\\green_ltb.bmp")
#define GREEN_PUYOPUYO_CONNECT_LEFT_TOP_RIGTH		_T("..\\Image\\green_ltr.bmp")
#define GREEN_PUYOPUYO_CONNECT_TOP					_T("..\\Image\\green_t.bmp")
#define GREEN_PUYOPUYO_CONNECT_TOP_RIGHT			_T("..\\Image\\green_tr.bmp")
#define GREEN_PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM		_T("..\\Image\\green_trb.bmp")
#define	GREEN_PUYOPUYO_CONNECT_TOP_BOTTOM			_T("..\\Image\\green_tb.bmp")
#define GREEN_PUYOPUYO_CONNECT_RIGHT				_T("..\\Image\\green_r.bmp")
#define GREEN_PUYOPUYO_CONNECT_RIGHT_BOTTOM			_T("..\\Image\\green_rb.bmp")
#define GREEN_PUYOPUYO_CONNECT_BOTTOM				_T("..\\Image\\green_b.bmp")
#define GREEN_PUYOPUYO_CONNECT_ALL					_T("..\\Image\\green_ltrb.bmp")

#define PURPLE_PUYOPUYO_NORMAL						_T("..\\Image\\purple_normal.bmp")
#define PURPLE_PUYOPUYO_CONNECT_LEFT				_T("..\\Image\\purple_l.bmp")
#define PURPLE_PUYOPUYO_CONNECT_LEFT_BOTTOM			_T("..\\Image\\purple_lb.bmp")
#define PURPLE_PUYOPUYO_CONNECT_LEFT_RIGHT			_T("..\\Image\\purple_lr.bmp")
#define PURPLE_PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM	_T("..\\Image\\purple_lrb.bmp")
#define PURPLE_PUYOPUYO_CONNECT_LEFT_TOP			_T("..\\Image\\purple_lt.bmp")
#define PURPLE_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM		_T("..\\Image\\purple_ltb.bmp")
#define PURPLE_PUYOPUYO_CONNECT_LEFT_TOP_RIGTH		_T("..\\Image\\purple_tr.bmp")
#define PURPLE_PUYOPUYO_CONNECT_TOP					_T("..\\Image\\purple_t.bmp")
#define PURPLE_PUYOPUYO_CONNECT_TOP_RIGHT			_T("..\\Image\\purple_tr.bmp")
#define PURPLE_PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM	_T("..\\Image\\purple_trb.bmp")
#define	PURPLE_PUYOPUYO_CONNECT_TOP_BOTTOM			_T("..\\Image\\purple_tb.bmp")
#define PURPLE_PUYOPUYO_CONNECT_RIGHT				_T("..\\Image\\purple_r.bmp")
#define PURPLE_PUYOPUYO_CONNECT_RIGHT_BOTTOM		_T("..\\Image\\purple_rb.bmp")
#define PURPLE_PUYOPUYO_CONNECT_BOTTOM				_T("..\\Image\\purple_b.bmp")
#define PURPLE_PUYOPUYO_CONNECT_ALL					_T("..\\Image\\purple_ltrb.bmp")

#define RED_PUYOPUYO_NORMAL							_T("..\\Image\\red_normal.bmp")
#define	RED_PUYOPUYO_CONNECT_LEFT					_T("..\\Image\\red_l.bmp")
#define RED_PUYOPUYO_CONNECT_LEFT_BOTTOM			_T("..\\Image\\red_lb.bmp")
#define RED_PUYOPUYO_CONNECT_LEFT_RIGHT				_T("..\\Image\\red_lr.bmp")
#define RED_PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM		_T("..\\Image\\red_lrb.bmp")
#define RED_PUYOPUYO_CONNECT_LEFT_TOP				_T("..\\Image\\red_lt.bmp")
#define RED_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM		_T("..\\Image\\red_ltb.bmp")
#define RED_PUYOPUYO_CONNECT_LEFT_TOP_RIGTH			_T("..\\Image\\red_tr.bmp")
#define RED_PUYOPUYO_CONNECT_TOP					_T("..\\Image\\red_t.bmp")
#define RED_PUYOPUYO_CONNECT_TOP_RIGHT				_T("..\\Image\\red_tr.bmp")
#define RED_PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM		_T("..\\Image\\red_trb.bmp")
#define	RED_PUYOPUYO_CONNECT_TOP_BOTTOM				_T("..\\Image\\red_tb.bmp")
#define	RED_PUYOPUYO_CONNECT_RIGHT					_T("..\\Image\\red_r.bmp")
#define RED_PUYOPUYO_CONNECT_RIGHT_BOTTOM			_T("..\\Image\\red_rb.bmp")
#define RED_PUYOPUYO_CONNECT_BOTTOM					_T("..\\Image\\red_b.bmp")
#define RED_PUYOPUYO_CONNECT_ALL					_T("..\\Image\\red_ltrb.bmp")

#define YELLOW_PUYOPUYO_NORMAL						_T("..\\Image\\yellow_normal.bmp")
#define	YELLOW_PUYOPUYO_CONNECT_LEFT				_T("..\\Image\\yellow_l.bmp")
#define YELLOW_PUYOPUYO_CONNECT_LEFT_BOTTOM			_T("..\\Image\\yellow_lb.bmp")
#define YELLOW_PUYOPUYO_CONNECT_LEFT_RIGHT			_T("..\\Image\\yellow_lr.bmp")
#define YELLOW_PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM	_T("..\\Image\\yellow_lrb.bmp")
#define YELLOW_PUYOPUYO_CONNECT_LEFT_TOP			_T("..\\Image\\yellow_lt.bmp")
#define YELLOW_PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM		_T("..\\Image\\yellow_ltb.bmp")
#define YELLOW_PUYOPUYO_CONNECT_LEFT_TOP_RIGTH		_T("..\\Image\\yellow_tr.bmp")
#define YELLOW_PUYOPUYO_CONNECT_TOP					_T("..\\Image\\yellow_t.bmp")
#define YELLOW_PUYOPUYO_CONNECT_TOP_RIGHT			_T("..\\Image\\yellow_tr.bmp")
#define YELLOW_PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM	_T("..\\Image\\yellow_trb.bmp")
#define	YELLOW_PUYOPUYO_CONNECT_TOP_BOTTOM			_T("..\\Image\\yellow_tb.bmp")
#define	YELLOW_PUYOPUYO_CONNECT_RIGHT				_T("..\\Image\\yellow_r.bmp")
#define YELLOW_PUYOPUYO_CONNECT_RIGHT_BOTTOM		_T("..\\Image\\yellow_rb.bmp")
#define YELLOW_PUYOPUYO_CONNECT_BOTTOM				_T("..\\Image\\yellow_b.bmp")
#define YELLOW_PUYOPUYO_CONNECT_ALL					_T("..\\Image\\yellow_ltrb.bmp")

#define BLACK_PUYOPUYO_NORMAL						_T("..\\Image\\black_normal.bmp")

/*--------------*/
/*	列挙体		*/
/*--------------*/

enum WINDOW_MEASSAGE												/*	ウィンドウのメッセージ定義							*/
{
	WINDOW_MEASSAGE_START	= 0,									/*	ウィンドウの開始処理								*/
	WINDOW_MEASSAGE_QUIT	= 1,									/*	ウィンドウの終了処理								*/
};

enum BIT_FLAG														/*	ビットフラグ										*/
{
	BIT0 = 0x01,
	BIT1 = 0x02,
	BIT2 = 0x04,
	BIT3 = 0x08,
	BIT4 = 0x10,
	BIT5 = 0x20,
	BIT6 = 0x40,
	BIT7 = 0x80,
};

/*----------------------*/
/* プロトタイプ宣言		*/
/*----------------------*/
LRESULT WINAPI	AppWndProc(HWND, UINT, WPARAM, LPARAM);

#endif