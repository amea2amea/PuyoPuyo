#ifndef PuyoFiled_h
#define PuyoFiled_h

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "PuyoBlock.h"
#include "PuyoFallingBlock.h"
#include "Array2D.h"

/*--------------*/
/*	�\����		*/
/*--------------*/
struct Block_Point												/*	�{�[�g�ʒu�̍\����							*/
{
	/*----------------------*/
	/*	���W�ʒu			*/
	/*----------------------*/
	unsigned int x;												/*	���W�ʒu ( �� )								*/
	unsigned int y;												/*	���W�ʒu ( �c )								*/

	/*----------------------*/
	/*	�R���X�g���N�^		*/
	/*----------------------*/
	Block_Point()												/*	�����Ȃ��R���X�g���N�^						*/
	{
		Block_Point(0, 0);
	}

	Block_Point(int x, int y)									/*	��������R���X�g���N�^						*/
	{
		this->x = x;
		this->y = y;
	}

	/*------------------------------*/
	/*	opeart						*/
	/*		���Z�q�I�[�o�[���[�h	*/
	/*------------------------------*/

	const Block_Point& operator()(int x, int y) const			/*	�ʒu���w�肵���Ƃ��̑���@( ����p )		*/
	{
		return Block_Point(x, y);
	}

	Block_Point& operator()(int x, int y)						/*	�ʒu���w�肵���Ƃ��̑���@( ����p )		*/
	{
		return Block_Point(x, y);
	}
};

/*--------------*/
/*	�N���X		*/
/*--------------*/

/************************/
/*	�{�[�h�̃N���X		*/
/************************/
class CPuyoFiled 
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CPuyoFiled();										/* �����Ȃ��R���X�g���N�^				*/

	/*	�f�X�g���N�^	*/
	~CPuyoFiled();

	/*	�֐�	*/
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
	unsigned short			GetBlockColor(long,long, char);														/* �u���b�N�ʒu�̃J���[���擾						*/
	unsigned short&			SetBlockColor(long, long, char);													/* �u���b�N�ʒu�̃J���[����ݒ�						*/
	unsigned short			GetBlockState(long, long, char);													/* �u���b�N�̏�Ԃ��擾								*/
	unsigned short&			SetBlockState(long, long, char);													/* �u���b�N�̏�Ԃ�ݒ�								*/
	unsigned short			GetCheckBlock(long, long, char);													/* �u���b�N���`�F�b�N�ς݂ǂ������擾				*/
	unsigned short&			SetCheckBlock(long, long, char);													/* �u���b�N���`�F�b�N�ς݂ɐݒ�						*/
	unsigned short			GetConnectBlock(long, long, char);													/* �u���b�N�̘A����Ԃ��擾							*/
	unsigned short&			SetConnectBlock(long, long, char);													/* �u���b�N�̘A����Ԃ�ݒ�							*/
	unsigned short			GetBlockTopPosX(char) const;
	unsigned short			GetBlockTopPosY(char) const;
	unsigned short			GetFiledSizeX() const;
	unsigned short			GetFiledSizeY() const;
	unsigned char			GetDeleteChainBlock(char) const;

private:
	/*	�֐�	*/
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
	/*	�����o�ϐ�		*/
	/*------------------*/
public:
	/*	��`�p�ϐ� ( const )	*/
	static const short						PUYO_FILED_SIZE_X = 6;												/*	�Ղ�Ղ�̉��T�C�Y								*/
	static const short						PUYO_FILED_SIZE_Y = 13;												/*	�Ղ�Ղ�̏c�T�C�Y								*/
	static const short						PUYO_FILED_SIZE = PUYO_FILED_SIZE_X * PUYO_FILED_SIZE_Y;			/*	�Ղ�Ղ�̃t�B�[���h�T�C�Y						*/
	static const short						PUYO_FILED_START_X = 2;												/*	�Ղ�Ղ�̊J�n�ʒu (��)							*/
	static const short						PUYO_FILED_START_Y = 3;												/*	�Ղ�Ղ�̊J�n�ʒu (�c)							*/
	static const short						PUYO_COLOR_NUM = 5;													/*	�F�̎��										*/
	static const short						PUYO_DELETE_NUM = 4;												/*	�Ղ�Ղ�̏�����								*/
	static const short						CURRENT_BLOCK_X = 3;												/*	�����u���b�N�T�C�Y (��)							*/
	static const short						CURRENT_BLOCK_Y = 3;												/*	�����u���b�N�T�C�Y (�c)							*/
	static const short						CURRENT_BLOCK_START_X = 1;											/*	�����u���b�N�̊J�n�ʒu (��)						*/
	static const short						CURRENT_BLOCK_START_Y = 0;											/*	�����u���b�N�̊J�n�ʒu (�c)						*/

protected:	
	Array2D< CPuyoBlock >					m_Block;															/*	�u���b�N�̏��									*/
	CPuyoFalling_Block						m_CurrentBlock;														/*	�����u���b�N�̏�� ( �����u���b�N )				*/
	CPuyoFalling_Block						m_WaitBlock;														/*	�ҋ@�̃u���b�N�̏�� ( ���̗����u���b�N )		*/
	CPuyoFalling_Block						m_WaitNextBlock;													/*	�ҋ@�̎��̃u���b�N�̏�� ( ���̑ҋ@�u���b�N )	*/
	CPuyoFalling_Block						m_LandingBlock;														/*	�����u���b�N�̒��n�ʒu�\���u���b�N				*/
	unsigned short							m_CurrentBlockTopPosX;												/*	�����u���b�N�̃t�B�[���h�ʒu ( �� )				*/
	unsigned short							m_CurrentBlockTopPosY;												/*	�����u���b�N�̃t�B�[���h�ʒu ( �c )				*/
	unsigned short							m_LandingBlockTopPosX;												/*	�����u���b�N�̒��n�ʒu  ( �� )					*/
	unsigned short							m_LandingBlockTopPosY;												/*	�����u���b�N�̒��n�ʒu ( �c )					*/
	short									m_CurrentBlockRotatinAngle;											/*	�����u���b�N��]�p�x							*/
	unsigned char							m_BlockColorNum;													/*	�����u���b�N�̐F�̎��							*/
	unsigned char							m_BlockDeleteInfo;													/*	�u���b�N�̏������								*/	
																												/*	Bit0 : 1�i����									*/
																												/*	Bit1 : 2�i����									*/
																												/*	Bit2 : 3�i����									*/
																												/*	Bit3 : 4�i����									*/
																												/*	Bit4 : 1�i���� ( 2�� )						*/
	unsigned char							m_DeleteChainBlockCount;											/*	�A���u���b�N�����J�E���g						*/
	unsigned char							m_DeleteChainBlockCurrentCount;										/*	�A���u���b�N�����J�E���g ( ���ݗp )				*/
	unsigned char							m_DeleteChainBlockMaxCount;											/*	�A���u���b�N�����J�E���g ( �ő�l )				*/
};
#endif