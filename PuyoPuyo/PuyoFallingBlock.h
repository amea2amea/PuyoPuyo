#ifndef PuyoFalling_Block_h
#define PuyoFalling_Block_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "PuyoBlock.h"
#include "Array2D.h"

/*--------------*/
/*	�N���X		*/
/*--------------*/

/****************************/
/*	�����u���b�N�̃N���X	*/
/****************************/
class CPuyoFalling_Block
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CPuyoFalling_Block();														/* �����Ȃ��R���X�g���N�^					*/			
	CPuyoFalling_Block(unsigned short, unsigned short);							/* ��������R���X�g���N�^					*/

	/*	�f�X�g���N�^	*/
	~CPuyoFalling_Block();

	/*	�֐�	*/
	void						SetFallingBlockState();							/* �����u���b�N�̈ʒu����ݒ�				*/
	void						CreateFallingBlock(char, unsigned char);		/* �����u���b�N���쐬						*/
	void						Clear();										/* �����u���b�N�̃��������					*/
	void						FallingBlockInit();								/* �����u���b�N�̏�����						*/
	void						SetSize(unsigned short, unsigned short);		/* �����u���b�N�̃T�C�Y��ݒ�				*/
	unsigned short				GetFallingBlockLeft() const;					/* �����u���b�N�̍��[						*/
	unsigned short				GetFallingBlockTop() const;						/* �����u���b�N�̏�[						*/
	unsigned short				GetFallingBlockRight() const;					/* �����u���b�N�̉E�[						*/
	unsigned short				GetFallingBlockBottom() const;					/* �����u���b�N�̉��[						*/
	CPuyoBlock					GetBlock(long, long) const;						/* �����u���b�N���擾						*/		
	CPuyoBlock&					SetBlock(long, long);							/* �����u���b�N��ݒ�						*/
	unsigned short				GetBlockColor(long, long);						/* �����u���b�N�ʒu�̃J���[���擾			*/
	unsigned short&				SetBlockColor(long, long);						/* �����u���b�N�ʒu�̃J���[��ݒ�			*/
	unsigned short				GetBlockState(long, long);						/* �����u���b�N�̏�Ԃ��擾					*/
	unsigned short&				SetBlockState(long, long);						/* �����u���b�N�̏�Ԃ�ݒ�					*/
	unsigned short				GetCheckBlock(long, long);						/* �����u���b�N�̃`�F�b�N�ς݂��ǂ������擾	*/
	unsigned short&				SetCheckBlock(long, long);						/* �����u���b�N���`�F�b�N�ς݂ɐݒ�			*/
	unsigned short				GetConnectBlock(long, long);					/* �����u���b�N�̘A����Ԃ��擾				*/
	unsigned short&				SetConnectBlock(long, long);					/* �����u���b�N�̘A����Ԃ�ݒ�				*/

	/*------------------*/
	/*	�����o�ϐ�		*/
	/*------------------*/
private:
	Array2D< CPuyoBlock >		m_FallingBlock;									/*	�����u���b�N�̏��						*/
	unsigned short				m_FallingBlockTop;								/*	�����u���b�N�̏�[�ʒu					*/	
	unsigned short				m_FallingBlockLeft;								/*	�����u���b�N�̍��[�ʒu					*/
	unsigned short				m_FallingBlockBottom;							/*	�����u���b�N�̉��[�ʒu					*/
	unsigned short				m_FallingBlockRight;							/*	�����u���b�N�̉E�[�ʒu					*/
	unsigned short				m_FallingBlockX;								/*	�����u���b�N�T�C�Y (��)					*/
	unsigned short				m_FallingBlockY;								/*	�����u���b�N�T�C�Y (�c)					*/

};
#endif
