#ifndef PuyoManger_h
#define PuyoManger_h

/*------------------*/
/* インクルード		*/
/*------------------*/
#include "global.h"
#include "PuyoFiled.h"
#include "Array2D.h"

/*--------------------------------------*/
/*	マネジャークラス ( シングルトン )	*/ 
/*--------------------------------------*/
class CPuyoManger
{

	/*--------------*/
	/*	メンバ変数	*/
	/*--------------*/
private:
	/*	コンストラクタ	*/
	CPuyoManger();
	CPuyoManger(const CPuyoManger&);
	
	/*	コピーコンストラクタ	*/
	void operator=(const CPuyoManger&) {};				/* クラスの代入操作( = 操作)は禁止			*/

public:
	/*	デストラクタ	*/
	virtual	~CPuyoManger();
	
	/*	関数	*/
	CPuyoFiled&					GetPuyoFiled();
	static CPuyoManger*			Instance();
	DWORD						GetPuyoPoint() const;
	DWORD&						SetPuyoPoint();
	DWORD						GetPuyoFallingTime() const;
	DWORD&						SetPuyoFallingTime();
	DWORD						GetPuyoNextBlockWaitTime() const;
	DWORD&						SetPuyoNextBlockWaitTime();

	/*------------------*/
	/*	メンバ変数		*/
	/*------------------*/
private:
	CPuyoFiled					m_PuyoFiled;				/*	テトリスの情報							*/
	DWORD		 				m_PuyoPoints;				/*	点数									*/
	DWORD		 				m_FallingTime;				/*	落下時間								*/
	DWORD		 				m_NextBlockWaitTime;		/*	次のブロックの待ち時間					*/


};
#endif