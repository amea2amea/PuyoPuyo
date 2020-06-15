/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"
#include "ControlProcess.h"

/*----------------------*/
/* グローバル変数宣言	*/
/*----------------------*/
CControlProcess*		g_pAppWndProc	= NULL;											/*	ウィンドウをコントロールするクラスのポインタ		*/
HINSTANCE				g_hInstance		= NULL;											/*	インスタンスハンドル								*/