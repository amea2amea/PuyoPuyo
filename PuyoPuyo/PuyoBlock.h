#ifndef PuyoBlock_h
#define PuyoBlock_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"

namespace BlockNS
{
	enum Block_Color									/*	ブロックカラーの状態						*/
	{
		NON_COLOR,										/*	色が未設定									*/
		RED,											/*	赤											*/
		PURPLE,											/*	紫											*/
		YELLOW,											/*	黄											*/
		PINK,											/*	ピンク										*/
		GREEN,											/*	緑											*/
		BLUE,											/*	青											*/
		CYAN,											/*	シアン										*/
		ORANGE,											/*	オレンジ									*/
		BLACK,											/*	黒											*/
		WHITE,											/*	白											*/
		DIMGRAY,										/*	ディムグレイ ( 暗いグレイ )					*/
		LIGHTGRAY,										/*	ライトグレイ ( 淡いグレイ )					*/
		GRAY											/*	グレイ										*/
	};

	enum Block_State									/*	ブロックの状態								*/
	{
		EXISTENCE	= 1,								/*	ブロックあり								*/
		EMPTY		= 0,								/*	ブロックなし								*/
		WALL		= 2									/*	壁											*/
	};

	enum Block_Move										/*	ブロックの移動方向							*/
	{
		BLOCK_MOVE_LEFT,								/*	ブロックの移動方向が左方向					*/
		BLOCK_MOVE_RIGHT,								/*	ブロックの移動方向が右方向					*/
		BLOCK_MOVE_DOWN,								/*	ブロックの移動方向が下方向					*/
		BLOCK_MOVE_ROTATE_CW,							/*	ブロックの移動方向がCW回転					*/
		BLOCK_MOVE_ROTATE_CCW,							/*	ブロックの移動方向がCCW回転					*/
		BLOCK_MOVE_FALL_MODE,							/*	ブロックの落下モード						*/
		BLOCK_MOVE_LANDING_MODE							/*	ブロックの着地位置表示モード				*/
	};

	enum Block_Rotation									/*	ブロックの回転方向							*/
	{
		BLOCK_CW_ROTATION,								/*	ブロックの回転方向がCW回転					*/
		BLOCK_CCW_ROTATION								/*	ブロックの回転方向がCCW回転					*/
	};

	enum Block_Type										/*	ブロックの種類								*/
	{
		FILED_BLOCK,									/*	フィールド上のブロック						*/
		CURRENT_BLOCK,									/*	現在のブロック								*/
		WAIT_BLOCK,										/*	待機ブロック ( 次のブロック )				*/
		WAIT_NEXT_BLOCK,								/*	待機ブロック ( 次の待機ブロック )			*/
		LANDING_BLOCK									/*	着地点表示ブロック							*/
	};

	enum Block_Check									/*	ブロックのチェック状態						*/
	{
		NON_CHECEKED_BLOCK,								/*	チェックされていないブロック				*/
		CHECEKED_BLOCK,									/*	チェック済みのブロック						*/
	};

	enum Block_Connect									/*	ブロックの連結状態							*/
	{
		BLOCK_CONNECT_NONE		= 0,					/*	連結していないブロック						*/
		BLOCK_CONNECT_LEFT		= BIT0,					/*	連結ブロックあり ( 左 )						*/
		BLOCK_CONNECT_TOP		= BIT1,					/*	連結ブロックあり ( 上 )						*/
		BLOCK_CONNECT_RIGHT		= BIT2,					/*	連結ブロックあり ( 右 )						*/
		BLOCK_CONNECT_BOTTOM	= BIT3,					/*	連結ブロックあり ( 下 )						*/
	};

}

/*--------------*/
/*	クラス		*/
/*--------------*/
class CPuyoBlock										/*	テトリスのブロッククラス			*/
{

	/*--------------*/
	/*	メンバ関数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CPuyoBlock();										/* 引数なしコンストラクタ				*/
	CPuyoBlock( short, unsigned short );				/* 引数ありコンストラクタ				*/

	/*	デストラクタ	*/
	~CPuyoBlock();

	/*	関数	*/
	unsigned short			GetBlockColor() const;		/* ブロック位置のカラーを取得			*/
	unsigned short&			SetBlockColor();			/* ブロック位置のカラーをを設定			*/
	unsigned short			GetBlockState() const;		/* ブロックの状態を取得					*/
	unsigned short&			SetBlockState();			/* ブロックの状態を設定					*/
	unsigned short			GetCheckBlock() const;		/* ブロックがチェック済みどうかを取得	*/
	unsigned short&			SetCheckBlock();			/* ブロックをチェック済みに設定			*/
	unsigned short			GetConnectBlock() const;	/* ブロックの連結状態を取得				*/
	unsigned short&			SetConnectBlock();			/* ブロックの連結状態を設定				*/

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	unsigned short			m_Color;					/* ブロックの色							*/
	unsigned short			m_BlockState;				/* ブロックの状態						*/
	unsigned short			m_Check;					/* チェック済みのブロック				*/
	unsigned short			m_ConnectState;				/* 連結ブロックの状態					*/


};
#endif