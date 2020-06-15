#ifndef _PuyoLOGIC_H
#define _PuyoLOGIC_H

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "GameLogic.h"
#include "PuyoFiled.h"

/*----------------------------------*/
/*	プロセスのコントロールクラス	*/
/*----------------------------------*/
class CPuyoLogic : public CGameLogic
{
	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
public:
	/*	コンストラクタ	*/
	CPuyoLogic();

	/*	デストラクタ	*/
	virtual	~CPuyoLogic();

	/*	関数	*/

protected:

	/*	仮想関数	*/
	virtual void	Logic(CInput*);

private:
	void			Init();
	void			Update();
	void			UpdateBlock();
	void			CheckBlock();
	void			UpdatePoint();
	bool			UpdateTimer();
	bool			Keydown(CInput*);

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	/*	定義用変数 ( const )	*/
	static const short				PUYO_FALL_TIME				= 300;		/*	テトリス落下時間の更新時間				*/
	static const short				PUYO_NEXTBLOCK_WAIT_TIME	= 300;		/*	テトリス落下時間の更新時間				*/
	static const short				PUYO_FALL_TIME_SPEED_UP		= 100;		/*	テトリス落下時間の速度更新				*/
	static const short				PUYO_NEXTBLOCK_WAIT_SLOW	= 100;		/*	テトリス落下時間の速度更新				*/
	static const short				PUYO_SINGLE_POINTS			= 40;		/*	テトリス得点 ( シングル )				*/
	static const short				PUYO_DOUBLE_POINTS			= 100;		/*	テトリス得点 ( ダブル )					*/
	static const short				PUYO_TRIPLE_POINTS			= 300;		/*	テトリス得点 ( トリプル )				*/
	static const short				PUYO_POINTS					= 1200;		/*	テトリス得点 ( テトリス )				*/
	static const short				PUYO_KEYDOWN_POINTS			= 1;		/*	テトリス得点 ( キーダウン )				*/

protected:
	CPuyoFiled&						m_PuyoFiled;							/*	テトリスのブロック情報					*/

private:
	DWORD 							m_TimeStart;							/*	更新開始時間							*/
	DWORD		 					m_TimeEnd;								/*	更新終了時間							*/
	bool							m_bInit;									/*	初期化フラグ							*/
																			/*		true	: 初期化済み				*/
																			/*		false	: 初期化してない			*/

	bool							m_bFinish;								/*	終了フラグ								*/
																			/*		true	: 終了済み					*/
																			/*		false	: 終了してない				*/

	bool							m_bDroppingBlock;						/*	ブロック落下中フラグ					*/
																			/*		true	: 落下終了済み				*/
																			/*		false	: 落下中					*/

	bool							m_bCurrentBlockFallTimeMode;			/*	落下高速モード							*/

};
#endif
