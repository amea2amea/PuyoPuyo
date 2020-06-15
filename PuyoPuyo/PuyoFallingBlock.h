#ifndef PuyoFalling_Block_h
#define PuyoFalling_Block_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "PuyoBlock.h"
#include "Array2D.h"

/*--------------*/
/*	クラス		*/
/*--------------*/

/****************************/
/*	落下ブロックのクラス	*/
/****************************/
class CPuyoFalling_Block
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CPuyoFalling_Block();														/* 引数なしコンストラクタ					*/			
	CPuyoFalling_Block(unsigned short, unsigned short);							/* 引数ありコンストラクタ					*/

	/*	デストラクタ	*/
	~CPuyoFalling_Block();

	/*	関数	*/
	void						SetFallingBlockState();							/* 落下ブロックの位置情報を設定				*/
	void						CreateFallingBlock(char, unsigned char);		/* 落下ブロックを作成						*/
	void						Clear();										/* 落下ブロックのメモリ解放					*/
	void						FallingBlockInit();								/* 落下ブロックの初期化						*/
	void						SetSize(unsigned short, unsigned short);		/* 落下ブロックのサイズを設定				*/
	unsigned short				GetFallingBlockLeft() const;					/* 落下ブロックの左端						*/
	unsigned short				GetFallingBlockTop() const;						/* 落下ブロックの上端						*/
	unsigned short				GetFallingBlockRight() const;					/* 落下ブロックの右端						*/
	unsigned short				GetFallingBlockBottom() const;					/* 落下ブロックの下端						*/
	CPuyoBlock					GetBlock(long, long) const;						/* 落下ブロックを取得						*/		
	CPuyoBlock&					SetBlock(long, long);							/* 落下ブロックを設定						*/
	unsigned short				GetBlockColor(long, long);						/* 落下ブロック位置のカラーを取得			*/
	unsigned short&				SetBlockColor(long, long);						/* 落下ブロック位置のカラーを設定			*/
	unsigned short				GetBlockState(long, long);						/* 落下ブロックの状態を取得					*/
	unsigned short&				SetBlockState(long, long);						/* 落下ブロックの状態を設定					*/
	unsigned short				GetCheckBlock(long, long);						/* 落下ブロックのチェック済みかどうかを取得	*/
	unsigned short&				SetCheckBlock(long, long);						/* 落下ブロックをチェック済みに設定			*/
	unsigned short				GetConnectBlock(long, long);					/* 落下ブロックの連結状態を取得				*/
	unsigned short&				SetConnectBlock(long, long);					/* 落下ブロックの連結状態を設定				*/

	/*------------------*/
	/*	メンバ変数		*/
	/*------------------*/
private:
	Array2D< CPuyoBlock >		m_FallingBlock;									/*	落下ブロックの情報						*/
	unsigned short				m_FallingBlockTop;								/*	落下ブロックの上端位置					*/	
	unsigned short				m_FallingBlockLeft;								/*	落下ブロックの左端位置					*/
	unsigned short				m_FallingBlockBottom;							/*	落下ブロックの下端位置					*/
	unsigned short				m_FallingBlockRight;							/*	落下ブロックの右端位置					*/
	unsigned short				m_FallingBlockX;								/*	落下ブロックサイズ (横)					*/
	unsigned short				m_FallingBlockY;								/*	落下ブロックサイズ (縦)					*/

};
#endif
