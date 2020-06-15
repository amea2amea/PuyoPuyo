#ifndef _GRAPHICS_H
#define _GRAPHICS_H 

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"
#include "Array1D.h"
#include "Array2D.h"

/*--------------*/
/*	名前空間	*/
/*--------------*/
namespace ImageNS
{
	enum Image_Type									/*	画像タイプ									*/
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

	enum Image_Trans_Mode							/*	画像転送のタイプ							*/
	{
		NORMAL_MODE,								/*	通常の転送									*/
		STRETCH_MODE,								/*	画像サイズに合わせて伸縮して転送			*/
		TRANSPARENT_MODE							/*	透明部分を設定して転送						*/
	};
}

/*--------------*/
/*	構造体		*/
/*--------------*/
struct GeometryDraw
{
	UINT		left;
	UINT		top;
	UINT		right;
	UINT		bottom;
	UINT		style;
	UINT		line_width;
	COLORREF	pen_color;
	COLORREF	brush_color;
};

struct BitmapDraw
{
	UINT			left;
	UINT			top;
	UINT			right;
	UINT			bottom;
	UINT			mode;
	HBITMAP			hbitmap;
	COLORREF		transparent_color;
};

struct TextOutDraw
{
	UINT		x_start;
	UINT		y_start;
	std::string string;
	UINT		textpitch;
	COLORREF	color;
};

struct TextRectDraw
{
	UINT		left;
	UINT		top;
	UINT		right;
	UINT		bottom;
	std::string	string;
	UINT		textpitch;
	UINT		format;
	COLORREF	color;
};

/*--------------*/
/*	名前空間	*/
/*--------------*/
namespace GraphicsDrawNS
{
	enum Draw_Flag								/*	描画の種類						*/
	{
		None		= 0,						/*	なし							*/
		Rectangle	= BIT0,						/*	長方形							*/
		Text_Rect	= BIT1,						/*	矩形に囲まれたテキスト			*/
		Text		= BIT2,						/*	テキスト						*/
		Arc			= BIT3,						/*	円								*/
		Bitmap		= BIT4,						/*	ビットマップを設定				*/
	};

}

/*------------------*/
/*	描画クラス		*/
/*------------------*/
class CGraphics
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CGraphics();

	/*	デストラクタ	*/
	virtual	~CGraphics();

	/*	純仮想関数	*/
	virtual void			Draw() = 0;
	virtual void			LoadBitmapPuyo(HINSTANCE) = 0;

	/*	関数	*/
	bool					Create();
	void					DrawMain();
	void					SetWindowHandle(HWND);
	void					SetWindowHFont(HFONT);
	HWND					GetWindowHandle() const;
	HDC						GetDeviceContext() const;
	void					SetRectAngle(UINT, UINT, UINT, UINT, UINT, UINT, COLORREF, COLORREF);
	void					SetArc(UINT, UINT, UINT, UINT, UINT, UINT, COLORREF, COLORREF);
	void					SetBitmap(UINT, UINT, UINT, UINT, UINT, HBITMAP, COLORREF);
	void					SetTextRect(UINT, UINT, UINT, UINT, std::string, UINT, UINT, COLORREF);
	void					SetTextOut(UINT, UINT, std::string, UINT, COLORREF);

private:
	void					DrawRectAngle(HDC);
	void					DrawArc(HDC);
	void					DrawBitmap(HDC);
	void					DrawTextRect(HDC);
	void					DrawTextOut(HDC);
	void					DrawClear(HDC);
	void					MemoryClear();

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	/*	定義用変数 ( const )	*/
	static const short			TEXT_MAX_BYTE = 1024;	/*	テキストの最大バイト数				*/

protected:
	HINSTANCE					m_hInstance;

private:
	HWND						m_hWnd;
	HDC							m_hdc;
	HFONT						m_hFont;
	HDC							m_Memoryhdc;
	HBITMAP						m_hBitmap;
	TEXTMETRIC					m_textmetric;
	std::vector<GeometryDraw>	m_GeometryRectAngle;	/*	描画用の長方形の情報				*/
	std::vector<GeometryDraw>	m_GeometryArc;			/*	描画用の円の情報					*/
	std::vector<BitmapDraw>		m_BitmapDraw;			/*	描画用のBitmapの設定情報			*/
	std::vector<TextRectDraw>	m_TextRectDraw;			/*	描画用のテキスト(長方形)の設定情報	*/
	std::vector<TextOutDraw>	m_TextOutDraw;			/*	描画用のテキストの設定情報			*/
	short						m_DrawFlag;				/*	描画するためのビットフラグ			*/
														/*	bit0:	四角形の描画				*/
														/*	bit1:	テキスト(四角形)の描画		*/
														/*	bit2:	テキストの描画				*/
														/*	bit3:	円の描画					*/
														/*	bit4:	Bitmapの描画				*/

};
#endif