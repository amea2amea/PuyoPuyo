#ifndef PuyoManger_h
#define PuyoManger_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"
#include "PuyoFiled.h"
#include "Array2D.h"

/*--------------------------------------*/
/*	�}�l�W���[�N���X ( �V���O���g�� )	*/ 
/*--------------------------------------*/
class CPuyoManger
{

	/*--------------*/
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
	/*	�R���X�g���N�^	*/
	CPuyoManger();
	CPuyoManger(const CPuyoManger&);
	
	/*	�R�s�[�R���X�g���N�^	*/
	void operator=(const CPuyoManger&) {};				/* �N���X�̑������( = ����)�͋֎~			*/

public:
	/*	�f�X�g���N�^	*/
	virtual	~CPuyoManger();
	
	/*	�֐�	*/
	CPuyoFiled&					GetPuyoFiled();
	static CPuyoManger*			Instance();
	DWORD						GetPuyoPoint() const;
	DWORD&						SetPuyoPoint();
	DWORD						GetPuyoFallingTime() const;
	DWORD&						SetPuyoFallingTime();
	DWORD						GetPuyoNextBlockWaitTime() const;
	DWORD&						SetPuyoNextBlockWaitTime();

	/*------------------*/
	/*	�����o�ϐ�		*/
	/*------------------*/
private:
	CPuyoFiled					m_PuyoFiled;				/*	�e�g���X�̏��							*/
	DWORD		 				m_PuyoPoints;				/*	�_��									*/
	DWORD		 				m_FallingTime;				/*	��������								*/
	DWORD		 				m_NextBlockWaitTime;		/*	���̃u���b�N�̑҂�����					*/


};
#endif