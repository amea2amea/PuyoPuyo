#ifndef _GRAPHICS_H
#define _GRAPHICS_H 

/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "global.h"
#include "Array1D.h"
#include "Array2D.h"

/*--------------*/
/*	���O���	*/
/*--------------*/
namespace ImageNS
{
	enum Image_Type									/*	�摜�^�C�v									*/
	{
		PUYOPUYO_NORMAL_TYPE,						/*	�ʏ�̂Ղ�Ղ�								*/
		PUYOPUYO_CONNECT_LEFT_TYPE,					/*	�����Ղ�Ղ� ( �� )							*/
		PUYOPUYO_CONNECT_TOP_TYPE,					/*	�����Ղ�Ղ� ( �� )							*/
		PUYOPUYO_CONNECT_RIGHT_TYPE,				/*	�����Ղ�Ղ� ( �E )							*/
		PUYOPUYO_CONNECT_BOTTOM_TYPE,				/*	�����Ղ�Ղ� ( �� )							*/
		PUYOPUYO_CONNECT_LEFT_TOP_TYPE,				/*	�����Ղ�Ղ� ( ���A�� )						*/
		PUYOPUYO_CONNECT_LEFT_RIGHT_TYPE,			/*	�����Ղ�Ղ� ( ���A�E )						*/
		PUYOPUYO_CONNECT_LEFT_BOTTOM_TYPE,			/*	�����Ղ�Ղ� ( ���A�� )						*/
		PUYOPUYO_CONNECT_TOP_RIGHT_TYPE,			/*	�����Ղ�Ղ� ( ��A�E )						*/
		PUYOPUYO_CONNECT_TOP_BOTTOM_TYPE,			/*	�����Ղ�Ղ� ( ��A�� )						*/
		PUYOPUYO_CONNECT_RIGHT_BOTTOM_TYPE,			/*	�����Ղ�Ղ� ( �E�A�� )						*/
		PUYOPUYO_CONNECT_LEFT_TOP_RIGHT_TYPE,		/*	�����Ղ�Ղ� ( ���A��A�E )					*/
		PUYOPUYO_CONNECT_LEFT_TOP_BOTTOM_TYPE,		/*	�����Ղ�Ղ� ( ���A��A�� )					*/
		PUYOPUYO_CONNECT_LEFT_RIGHT_BOTTOM_TYPE,	/*	�����Ղ�Ղ� ( ���A�E�A�� )					*/
		PUYOPUYO_CONNECT_TOP_RIGHT_BOTTOM_TYPE,		/*	�����Ղ�Ղ� ( ��A�E�A�� )					*/
		PUYOPUYO_CONNECT_ALL_TYPE,					/*	�����Ղ�Ղ� ( ���A��A�E�A�� )				*/
	};

	enum Image_Trans_Mode							/*	�摜�]���̃^�C�v							*/
	{
		NORMAL_MODE,								/*	�ʏ�̓]��									*/
		STRETCH_MODE,								/*	�摜�T�C�Y�ɍ��킹�ĐL�k���ē]��			*/
		TRANSPARENT_MODE							/*	����������ݒ肵�ē]��						*/
	};
}

/*--------------*/
/*	�\����		*/
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
/*	���O���	*/
/*--------------*/
namespace GraphicsDrawNS
{
	enum Draw_Flag								/*	�`��̎��						*/
	{
		None		= 0,						/*	�Ȃ�							*/
		Rectangle	= BIT0,						/*	�����`							*/
		Text_Rect	= BIT1,						/*	��`�Ɉ͂܂ꂽ�e�L�X�g			*/
		Text		= BIT2,						/*	�e�L�X�g						*/
		Arc			= BIT3,						/*	�~								*/
		Bitmap		= BIT4,						/*	�r�b�g�}�b�v��ݒ�				*/
	};

}

/*------------------*/
/*	�`��N���X		*/
/*------------------*/
class CGraphics
{
	/*--------------*/
	/*	�����o�֐�	*/
	/*--------------*/
public:
	/*	�R���X�g���N�^	*/
	CGraphics();

	/*	�f�X�g���N�^	*/
	virtual	~CGraphics();

	/*	�����z�֐�	*/
	virtual void			Draw() = 0;
	virtual void			LoadBitmapPuyo(HINSTANCE) = 0;

	/*	�֐�	*/
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
	/*	�����o�ϐ�	*/
	/*--------------*/
private:
	/*	��`�p�ϐ� ( const )	*/
	static const short			TEXT_MAX_BYTE = 1024;	/*	�e�L�X�g�̍ő�o�C�g��				*/

protected:
	HINSTANCE					m_hInstance;

private:
	HWND						m_hWnd;
	HDC							m_hdc;
	HFONT						m_hFont;
	HDC							m_Memoryhdc;
	HBITMAP						m_hBitmap;
	TEXTMETRIC					m_textmetric;
	std::vector<GeometryDraw>	m_GeometryRectAngle;	/*	�`��p�̒����`�̏��				*/
	std::vector<GeometryDraw>	m_GeometryArc;			/*	�`��p�̉~�̏��					*/
	std::vector<BitmapDraw>		m_BitmapDraw;			/*	�`��p��Bitmap�̐ݒ���			*/
	std::vector<TextRectDraw>	m_TextRectDraw;			/*	�`��p�̃e�L�X�g(�����`)�̐ݒ���	*/
	std::vector<TextOutDraw>	m_TextOutDraw;			/*	�`��p�̃e�L�X�g�̐ݒ���			*/
	short						m_DrawFlag;				/*	�`�悷�邽�߂̃r�b�g�t���O			*/
														/*	bit0:	�l�p�`�̕`��				*/
														/*	bit1:	�e�L�X�g(�l�p�`)�̕`��		*/
														/*	bit2:	�e�L�X�g�̕`��				*/
														/*	bit3:	�~�̕`��					*/
														/*	bit4:	Bitmap�̕`��				*/

};
#endif