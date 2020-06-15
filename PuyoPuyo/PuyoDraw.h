#ifndef _PuyoDRAW_H
#define _PuyoDRAW_H

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "Graphics.h"
#include "PuyoLogic.h"
#include "PuyoBitmap.h"

/*--------------*/
/*	名前空間	*/
/*--------------*/
namespace PuyoDrawNS
{
	enum TITLE_POS								/*	タイトルの表示位置				*/
	{
		SCORE_TITLE				= 2,			/*	スコアのタイトル				*/
		FALL_TIME_TITLE			= 4,			/*	落下時間のタイトル				*/
		NEXT_BLOCK_TITLE		= 6,			/*	次のブロックのタイトル			*/
		NEXT_WAIT_BLOCK_TITLE	= 9				/*	次の待機ブロックのタイトル		*/
	};

	enum CONTENT_POS							/*	内容の表示位置					*/
	{
		SCORE				= 3,				/*	スコア							*/
		FALL_TIME			= 5,				/*	落下時間						*/
		NEXT_BLOCK			= 9,				/*	次のブロック					*/
		NEXT_WAIT_BLOCK		= 13				/*	次の待機ブロック				*/
	};
}

/*--------------*/
/*	構造体		*/
/*--------------*/
struct Block_Rect
{
	/*----------------------*/
	/*	座標位置			*/
	/*----------------------*/
	long	left;												/*	座標位置 ( 左端 )							*/
	long	top;												/*	座標位置 ( 上端 )							*/
	long	right;												/*	座標位置 ( 右端 )							*/
	long	bottom;												/*	座標位置 ( 下端 )							*/

	/*----------------------*/
	/*	コンストラクタ		*/
	/*----------------------*/
	Block_Rect()												/*	引数なしコンストラクタ						*/
	{
		Block_Rect(0, 0, 0, 0);
	}

	Block_Rect(long left, long top, long right, long bottom)	/*	引数ありコンストラクタ						*/
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}

	/*------------------------------*/
	/*	opeart						*/
	/*		演算子オーバーロード	*/
	/*------------------------------*/

	const Block_Rect& operator()(long left, long top, long right, long bottom) const	/*	位置を指定したときの操作　( 代入用 )		*/
	{
		return Block_Rect(left, top, right, bottom);
	}

	Block_Rect& operator()(long left, long top, long right, long bottom)				/*	位置を指定したときの操作　( 操作用 )		*/
	{
		return Block_Rect(left, top, right, bottom);
	}
};

/*----------------------------------*/
/*	テトリスの描画クラス			*/
/*----------------------------------*/
class CPuyoDraw : public CGraphics
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CPuyoDraw();

	/*	デストラクタ	*/
	virtual	~CPuyoDraw();

	/*	関数	*/

protected:
	/*	仮想関数	*/
	virtual void	Draw();
	virtual void	LoadBitmapPuyo(HINSTANCE);

private:
	void					SetPuyoColor();
	void					SetPuyoText();
	COLORREF				GetColor(long, long, char);
	HBITMAP					GetBitmapHandle(long, long, char);
	BitmapNS::Puyo_Bitmap	GetConnectType(long, long, char);
	Block_Rect				GetBlockRect(long x_index, long y_index);
	void					SetBlockRect(long x_index, long y_index, Block_Rect);
	void					InitBlockRect();

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	/*	定義用変数 ( const )	*/
	static const short				PUYO_BLOCK_PIXEL_SIZE_X		= 30;			/*	テトリスブロックのピクセルサイズ (横)		*/
	static const short				PUYO_BLOCK_PIXEL_SIZE_Y		= 30;			/*	テトリスブロックのピクセルサイズ (縦)		*/
	static const short				PUYO_BLOCK_PIXEL_START_X	= 5;			/*	テトリスブロックのピクセルの開始位置 (横)	*/
	static const short				PUYO_BLOCK_PIXEL_START_Y	= 5;			/*	テトリスブロックのピクセルの開始位置 (縦)	*/
	static const short				PUYO_BLOCK_PIXEL_END_X		= 25;			/*	テトリスブロックのピクセルの終了位置 (横)	*/
	static const short				PUYO_BLOCK_PIXEL_END_Y		= 25;			/*	テトリスブロックのピクセルの終了位置 (縦)	*/
	static const short				PUYO_BLOCK_MARGIN_LEFT		= 2;			/*	テトリスブロックのピクセルのマージン (左)	*/
	static const short				PUYO_BLOCK_MARGIN_TOP		= 2;			/*	テトリスブロックのピクセルのマージン (上)	*/
	static const short				PUYO_BLOCK_MARGIN_RIGHT		= 2;			/*	テトリスブロックのピクセルのマージン (右)	*/
	static const short				PUYO_BLOCK_MARGIN_BOTTOM	= 2;			/*	テトリスブロックのピクセルのマージン (下)	*/

private:
	CPuyoFiled&						m_PuyoFiled;								/*	テトリスのブロック情報						*/
	Array2D< Block_Rect >			m_BlockRect;								/*	ブロックの情報								*/
	Array2D< Block_Rect >			m_WaitBlockRect;							/*	待機ブロックの情報							*/
	Array2D< Block_Rect >			m_WaitNextBlockRect;						/*	次の待機ブロックの情報						*/
	Array2D< Block_Rect >			m_LandingBlockRect;							/*	着地表示ブロックの情報						*/
	CPuyoBitmap						m_PuyoBitmapInfo;							/*	ビットマップ情報							*/
};
#endif
