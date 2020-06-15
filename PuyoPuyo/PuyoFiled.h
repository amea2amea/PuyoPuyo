#ifndef PuyoFiled_h
#define PuyoFiled_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "PuyoBlock.h"
#include "PuyoFallingBlock.h"
#include "Array2D.h"

/*--------------*/
/*	構造体		*/
/*--------------*/
struct Block_Point												/*	ボート位置の構造体							*/
{
	/*----------------------*/
	/*	座標位置			*/
	/*----------------------*/
	unsigned int x;												/*	座標位置 ( 横 )								*/
	unsigned int y;												/*	座標位置 ( 縦 )								*/

	/*----------------------*/
	/*	コンストラクタ		*/
	/*----------------------*/
	Block_Point()												/*	引数なしコンストラクタ						*/
	{
		Block_Point(0, 0);
	}

	Block_Point(int x, int y)									/*	引数ありコンストラクタ						*/
	{
		this->x = x;
		this->y = y;
	}

	/*------------------------------*/
	/*	opeart						*/
	/*		演算子オーバーロード	*/
	/*------------------------------*/

	const Block_Point& operator()(int x, int y) const			/*	位置を指定したときの操作　( 代入用 )		*/
	{
		return Block_Point(x, y);
	}

	Block_Point& operator()(int x, int y)						/*	位置を指定したときの操作　( 操作用 )		*/
	{
		return Block_Point(x, y);
	}
};

/*--------------*/
/*	クラス		*/
/*--------------*/

/************************/
/*	ボードのクラス		*/
/************************/
class CPuyoFiled 
{
	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CPuyoFiled();										/* 引数なしコンストラクタ				*/

	/*	デストラクタ	*/
	~CPuyoFiled();

	/*	関数	*/
	void					Init();
	bool					isGameOver();
	void					CurrentBlockToBoard(char);
	void					SetCurrentBlockState();
	void					NextWaitBlockInit();
	void					NextCurrentBlock();
	void					NextWaitBlock();
	void					LandingBlockPos();
	void					LandingBlockClear();
	bool					CurrentMoveBlock(char);
	bool					CheckBlockState();
	unsigned char			GetBlockDeleteInfo() const;
	CPuyoBlock				GetBlock(long, long) const;
	CPuyoBlock&				SetBlock(long, long);
	unsigned short			GetBlockColor(long,long, char);														/* ブロック位置のカラーを取得						*/
	unsigned short&			SetBlockColor(long, long, char);													/* ブロック位置のカラーをを設定						*/
	unsigned short			GetBlockState(long, long, char);													/* ブロックの状態を取得								*/
	unsigned short&			SetBlockState(long, long, char);													/* ブロックの状態を設定								*/
	unsigned short			GetCheckBlock(long, long, char);													/* ブロックがチェック済みどうかを取得				*/
	unsigned short&			SetCheckBlock(long, long, char);													/* ブロックをチェック済みに設定						*/
	unsigned short			GetConnectBlock(long, long, char);													/* ブロックの連結状態を取得							*/
	unsigned short&			SetConnectBlock(long, long, char);													/* ブロックの連結状態を設定							*/
	unsigned short			GetBlockTopPosX(char) const;
	unsigned short			GetBlockTopPosY(char) const;
	unsigned short			GetFiledSizeX() const;
	unsigned short			GetFiledSizeY() const;
	unsigned char			GetDeleteChainBlock(char) const;

private:
	/*	関数	*/
	void					CreateCurrentBlock(char, unsigned char);
	void					FallingBlockToBoard(CPuyoFalling_Block&, char, unsigned short, unsigned short);
	void					MoveBlockUpdate(CPuyoFalling_Block&, char);
	bool					MoveBlock(CPuyoFalling_Block&, char);
	bool					MoveBlockLeft(CPuyoFalling_Block&, unsigned short, unsigned short);
	bool					MoveBlockRight(CPuyoFalling_Block&, unsigned short, unsigned short);
	bool					MoveBlockDown(CPuyoFalling_Block&, unsigned short, unsigned short);
	void					MoveBlockFallMode(CPuyoFalling_Block&);
	bool					RotateBlock(CPuyoFalling_Block&, char);
	bool					CheckDropBlock();
	bool					CheckConnectingBlock();
	unsigned short			CheckSameColorBlock(unsigned short, unsigned short, unsigned short*);
	void					DeleteBlock(unsigned short);
	void					UnCheckedBlock();

	/*------------------*/
	/*	メンバ変数		*/
	/*------------------*/
public:
	/*	定義用変数 ( const )	*/
	static const short						PUYO_FILED_SIZE_X = 6;												/*	ぷよぷよの横サイズ								*/
	static const short						PUYO_FILED_SIZE_Y = 13;												/*	ぷよぷよの縦サイズ								*/
	static const short						PUYO_FILED_SIZE = PUYO_FILED_SIZE_X * PUYO_FILED_SIZE_Y;			/*	ぷよぷよのフィールドサイズ						*/
	static const short						PUYO_FILED_START_X = 2;												/*	ぷよぷよの開始位置 (横)							*/
	static const short						PUYO_FILED_START_Y = 3;												/*	ぷよぷよの開始位置 (縦)							*/
	static const short						PUYO_COLOR_NUM = 5;													/*	色の種類										*/
	static const short						PUYO_DELETE_NUM = 4;												/*	ぷよぷよの消去個数								*/
	static const short						CURRENT_BLOCK_X = 3;												/*	落下ブロックサイズ (横)							*/
	static const short						CURRENT_BLOCK_Y = 3;												/*	落下ブロックサイズ (縦)							*/
	static const short						CURRENT_BLOCK_START_X = 1;											/*	落下ブロックの開始位置 (横)						*/
	static const short						CURRENT_BLOCK_START_Y = 0;											/*	落下ブロックの開始位置 (縦)						*/

protected:	
	Array2D< CPuyoBlock >					m_Block;															/*	ブロックの情報									*/
	CPuyoFalling_Block						m_CurrentBlock;														/*	落下ブロックの情報 ( 落下ブロック )				*/
	CPuyoFalling_Block						m_WaitBlock;														/*	待機のブロックの情報 ( 次の落下ブロック )		*/
	CPuyoFalling_Block						m_WaitNextBlock;													/*	待機の次のブロックの情報 ( 次の待機ブロック )	*/
	CPuyoFalling_Block						m_LandingBlock;														/*	落下ブロックの着地位置表示ブロック				*/
	unsigned short							m_CurrentBlockTopPosX;												/*	落下ブロックのフィールド位置 ( 横 )				*/
	unsigned short							m_CurrentBlockTopPosY;												/*	落下ブロックのフィールド位置 ( 縦 )				*/
	unsigned short							m_LandingBlockTopPosX;												/*	落下ブロックの着地位置  ( 横 )					*/
	unsigned short							m_LandingBlockTopPosY;												/*	落下ブロックの着地位置 ( 縦 )					*/
	short									m_CurrentBlockRotatinAngle;											/*	落下ブロック回転角度							*/
	unsigned char							m_BlockColorNum;													/*	落下ブロックの色の種類							*/
	unsigned char							m_BlockDeleteInfo;													/*	ブロックの消去情報								*/	
																												/*	Bit0 : 1段消去									*/
																												/*	Bit1 : 2段消去									*/
																												/*	Bit2 : 3段消去									*/
																												/*	Bit3 : 4段消去									*/
																												/*	Bit4 : 1段消去 ( 2つ目 )						*/
	unsigned char							m_DeleteChainBlockCount;											/*	連鎖ブロック数をカウント						*/
	unsigned char							m_DeleteChainBlockCurrentCount;										/*	連鎖ブロック数をカウント ( 現在用 )				*/
	unsigned char							m_DeleteChainBlockMaxCount;											/*	連鎖ブロック数をカウント ( 最大値 )				*/
};
#endif