/*------------------*/
/* �C���N���[�h		*/
/*------------------*/
#include "Graphics.h"

/*------------------*/
/* extern�錾		*/
/*------------------*/
extern HINSTANCE			g_hInstance;				/*	�C���X�^���X�n���h��								*/

/*==============================================================*/
/*																*/
/*	[�֐�]		CGraphics	:	�R���X�g���N�^ ( �����Ȃ� )		*/
/*																*/
/*==============================================================*/
CGraphics::CGraphics()
{
	m_hWnd		= NULL;
	m_hdc		= NULL;
	m_hFont		= NULL;
	m_Memoryhdc = NULL;
	m_hBitmap	= NULL;
	m_DrawFlag	= GraphicsDrawNS::None;		/*	�s�N�Z�����Ƃ̕`��t���O�𖳌�				*/
	m_GeometryRectAngle.resize(0);			/*	�`��p�̒����`�̏���������				*/
	m_GeometryArc.resize(0);				/*	�`��p�̉~�̏���������					*/
	m_BitmapDraw.resize(0);					/*	�`��p�̃r�b�g�}�b�v�̏���������			*/
	m_TextRectDraw.resize(0);				/*	�`��p�̃e�L�X�g(�����`)�̐ݒ����������	*/
	m_TextOutDraw.resize(0);				/*	�`��p�̃e�L�X�g�̐ݒ����������			*/
}

/*======================================================*/
/*														*/
/*	[�֐�]		~CGraphics	:	�f�X�g���N�^			*/
/*														*/
/*======================================================*/
CGraphics::~CGraphics()
{
	/************************/
	/*	�������̉��		*/
	/************************/
	MemoryClear();

	/************************/
	/*	�I�u�W�F�N�g�̉��	*/
	/************************/
	DeleteDC(m_hdc);
	DeleteDC(m_Memoryhdc);
	DeleteObject(m_hFont);
	DeleteObject(m_hBitmap);

	/****************************/
	/*	�I�u�W�F�N�g�̏�����	*/
	/****************************/
	m_hWnd			= NULL;
	m_hdc			= NULL;
	m_hFont			= NULL;
	m_Memoryhdc		= NULL;
	m_hBitmap		= NULL;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		MemoryClear			:	�������N���A							*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]		void				:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CGraphics::MemoryClear()
{
	m_GeometryRectAngle.clear();			/*	�`��p�̐}�`����������				*/
	m_GeometryArc.clear();					/*	�`��p�̐}�`����������				*/
	m_BitmapDraw.clear();					/*	�`��p�̐}�`����������				*/
	m_TextRectDraw.clear();					/*	�`��p�̐}�`����������				*/
	m_TextOutDraw.clear();					/*	�`��p�̐}�`����������				*/
}
/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		DrawMain			:	�`�揈��								*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void				:	�Ȃ�									*/
/*	[����]		void				:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CGraphics::DrawMain()
{
	PAINTSTRUCT		ps;												/*	�`����									*/
	RECT			rect;											/*	�E�B���h�E�T�C�Y�̎擾�p					*/

	GetClientRect(m_hWnd, &rect);									/*	�E�B���h�E�T�C�Y�̎擾						*/
	InvalidateRect(m_hWnd, &rect, NULL);

	m_hdc = BeginPaint(m_hWnd, &ps);								/*	�f�o�C�X�R���e�L�X�g�̃n���h�����擾		*/

	if (	(m_hdc != NULL)											/*	�f�o�C�X�R���e�L�X�g���擾�ł��Ă���Ȃ��	*/
		&&	(m_Memoryhdc != NULL))									/*	�E�B���h�E�n���h�����擾�ł��Ă���Ȃ��	*/
	{
		/************************/
		/*	�`�����ݒ�		*/
		/************************/
		DrawClear(m_Memoryhdc);

		/************************/
		/*	�`�����ݒ�		*/
		/************************/
		Draw();

		/****************/
		/*	�`�揈��	*/
		/****************/
		SetMapMode(m_Memoryhdc, MM_TEXT);							/*	�`�惂�[�h���s�N�Z���P�ʂ̐ݒ�				*/

		if (m_DrawFlag &  GraphicsDrawNS::Rectangle)				/*	�����`�̕`��t���O��L���Ȃ��				*/
			DrawRectAngle(m_Memoryhdc);								/*	�����`�̕`��								*/

		if (m_DrawFlag & GraphicsDrawNS::Arc)						/*	�~�̕`��t���O��L���Ȃ��					*/
			DrawArc(m_Memoryhdc);									/*	�~�̕`��									*/

		if (m_DrawFlag & GraphicsDrawNS::Bitmap)					/*	�r�b�g�}�b�v�̕`��t���O��L���Ȃ��		*/
			DrawBitmap(m_Memoryhdc);								/*	�r�b�g�}�b�v�̕`��							*/

		if (m_DrawFlag & GraphicsDrawNS::Text_Rect)					/*	�e�L�X�g(�����`)�̕`��t���O��L���Ȃ��	*/
			DrawTextRect(m_Memoryhdc);								/*	�e�L�X�g(�����`�w��)�̕`��					*/

		if (m_DrawFlag & GraphicsDrawNS::Text)						/*	�e�L�X�g�̕`��t���O��L���Ȃ��			*/
			DrawTextOut(m_Memoryhdc);								/*	�e�L�X�g�̕`��								*/


		/****************************/
		/*	�r�b�g�}�b�v��]��		*/
		/****************************/								/*	�r�b�g�}�b�v��VRAM�ɓ]��					*/
		BitBlt(m_hdc												/*	�R�s�[��̃f�o�C�X�R���e�L�X�g�̃n���h��	*/
			, rect.left												/*	�R�s�[��̃E�B���h�E�̍���[ ( X���W )		*/
			, rect.top												/*	�R�s�[��̃E�B���h�E�̍���[ ( Y���W )		*/
			, rect.right											/*	�R�s�[��̃E�B���h�E�̉E���[ ( X���W )		*/
			, rect.bottom											/*	�R�s�[��̃E�B���h�E�̉E���[ ( Y���W )		*/
			, m_Memoryhdc											/*	�R�s�[���̃f�o�C�X�R���e�L�X�g�̃n���h��	*/
			, rect.left												/*	�R�s�[���̃E�B���h�E�̍���[ ( X���W )		*/
			, rect.top												/*	�R�s�[���̃E�B���h�E�̍���[ ( Y���W )		*/
			, SRCCOPY												/*	�R�s�[������R�s�[��֒����`���R�s�[		*/
			);
	}

	EndPaint(m_hWnd, &ps);											/*	�f�o�C�X�R���e�L�X�g�̃n���h����ԋp		*/
	m_DrawFlag	= GraphicsDrawNS::None;								/*	�s�N�Z�����Ƃ̕`��t���O�𖳌�				*/
	m_GeometryRectAngle.resize(0);									/*	�`��p�̒����`�̏���������				*/
	m_GeometryArc.resize(0);										/*	�`��p�̉~�̏���������					*/
	m_BitmapDraw.resize(0);											/*	�`��p�̃r�b�g�}�b�v�̏���������			*/
	m_TextRectDraw.resize(0);										/*	�`��p�̃e�L�X�g(�����`)�̐ݒ����������	*/
	m_TextOutDraw.resize(0);										/*	�`��p�̃e�L�X�g�̐ݒ����������			*/

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[�֐�]		Init				:	������									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	bool				:	�Ȃ�									*/
/*	[����]							:	�Ȃ�									*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CGraphics::Create()
{
	HDC		hdc		= NULL;
	RECT	rect;

	/****************************************/
	/*	�_�u���o�b�t�@�̃r�b�g�}�b�v���쐬	*/
	/****************************************/
	hdc = GetDC(m_hWnd);                      							/*	�f�o�C�X�R���e�L�X�g�̃n���h�����擾	*/
	GetClientRect(m_hWnd, &rect);  										/*	�E�B���h�E�T�C�Y���擾					*/
	m_hBitmap = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);	/*	�E�B���h�E�T�C�Y�̃r�b�g�}�b�v���쐬	*/
	m_Memoryhdc = CreateCompatibleDC(hdc);								/*	�������f�o�C�X�R���e�L�X�g���쐬		*/
	SelectObject(m_Memoryhdc, m_hBitmap);								/*	�������f�o�C�X�R���e�L�X�g�ɕR�t��		*/

	/****************************/
	/*	�t�H���g�̏����擾	*/
	/****************************/
	if (m_hFont != NULL)
	{
		SelectObject(hdc, m_hFont);
		GetTextMetrics(hdc, &m_textmetric);
	}

	/********************************/
	/*	�r�b�g�}�b�v����ǂݍ���	*/
	/********************************/
	LoadBitmapPuyo(g_hInstance);

	ReleaseDC(m_hWnd, hdc);

	return TRUE;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetWindowHandle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	HWND						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetWindowHandle(HWND hwnd)
{
	m_hWnd = hwnd;
	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetWindowHFont				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	HWND						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetWindowHFont(HFONT hFont)
{
	m_hFont = hFont;
	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetWindowHandle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	HWND						:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
HWND CGraphics::GetWindowHandle() const
{
	return m_hWnd;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		GetDeviceContex				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	HINSTANCE					:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
HDC CGraphics::GetDeviceContext() const
{
	return m_hdc;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetRectAngle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void						:									*/
/*	[����]		UINT 						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				COLORREF					:									*/
/*				COLORREF					:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetRectAngle(UINT left, UINT top, UINT right, UINT bottom, UINT style, UINT line_width, COLORREF pen_color, COLORREF brush_color)
{
	/****************************/
	/*	�`��p�̐ݒ�			*/
	/****************************/
	m_DrawFlag	|= GraphicsDrawNS::Rectangle;					/*	�`��t���O�̐ݒ�				*/

	/****************************/
	/*	�`�����ݒ�			*/
	/****************************/
	GeometryDraw gemetrydraw;
	gemetrydraw.left		= left;
	gemetrydraw.top			= top;
	gemetrydraw.right		= right;
	gemetrydraw.left		= left;
	gemetrydraw.bottom		= bottom;
	gemetrydraw.style		= style;
	gemetrydraw.line_width	= line_width;
	gemetrydraw.pen_color	= pen_color;
	gemetrydraw.brush_color = brush_color;
	m_GeometryRectAngle.push_back(gemetrydraw);

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetArc						:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void						:									*/
/*	[����]		UINT 						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				COLORREF					:									*/
/*				COLORREF					:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetArc(UINT left, UINT top, UINT right, UINT bottom, UINT style, UINT line_width, COLORREF pen_color, COLORREF brush_color)
{
	/****************************/
	/*	�`��p�̐ݒ�			*/
	/****************************/
	m_DrawFlag |= GraphicsDrawNS::Arc;					/*	�`��t���O�̐ݒ�				*/

	/****************************/
	/*	�`�����ݒ�			*/
	/****************************/
	GeometryDraw gemetrydraw;	
	gemetrydraw.left = left;
	gemetrydraw.top = top;
	gemetrydraw.right = right;
	gemetrydraw.left = left;
	gemetrydraw.bottom = bottom;
	gemetrydraw.style = style;
	gemetrydraw.line_width = line_width;
	gemetrydraw.pen_color = pen_color;
	gemetrydraw.brush_color = brush_color;
	m_GeometryArc.push_back(gemetrydraw);

	return;

}


/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetBitmap					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void						:									*/
/*	[����]		UINT 						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*				UINT						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetBitmap(UINT left, UINT top, UINT right, UINT bottom, UINT mode, HBITMAP hbitmap, COLORREF transparent_color)
{
	/****************************/
	/*	�`��p�̐ݒ�			*/
	/****************************/
	m_DrawFlag |= GraphicsDrawNS::Bitmap;					/*	�`��t���O�̐ݒ�				*/

	/****************************/
	/*	�`�����ݒ�			*/
	/****************************/
	BitmapDraw bitmapdraw;
	bitmapdraw.left		= left;
	bitmapdraw.top		= top;
	bitmapdraw.right	= right;
	bitmapdraw.left		= left;
	bitmapdraw.bottom	= bottom;
	bitmapdraw.hbitmap	= hbitmap;
	bitmapdraw.mode		= mode;
	bitmapdraw.transparent_color = transparent_color;
	m_BitmapDraw.push_back(bitmapdraw);

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetTextRect					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void						:									*/
/*	[����]		UINT 						:									*/
/*				UINT						:									*/
/*				LPCTSTR						:									*/
/*				UINT						:									*/
/*				LPRECT						:									*/
/*				UINT						:									*/
/*				COLORREF					:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetTextRect(UINT left, UINT top, UINT right, UINT bottom, std::string str, UINT textpitch, UINT format, COLORREF color)
{
	/****************************/
	/*	�`��p�̐ݒ�			*/
	/****************************/
	m_DrawFlag |= GraphicsDrawNS::Text_Rect;						/*	�`��t���O�̐ݒ�							*/

	/****************************/
	/*	�`�����ݒ�			*/
	/****************************/
	TextRectDraw textrectdraw;
	textrectdraw.left		= left;
	textrectdraw.top		= top;
	textrectdraw.right		= right;
	textrectdraw.bottom		= bottom;
	textrectdraw.string		= str;
	textrectdraw.format		= format;
	textrectdraw.textpitch	= textpitch;
	textrectdraw.color		= color;
	m_TextRectDraw.push_back(textrectdraw);

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		SetTextOut					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	void						:									*/
/*	[����]		UINT 						:									*/
/*				UINT						:									*/
/*				LPCTSTR						:									*/
/*				UINT						:									*/
/*				COLORREF					:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::SetTextOut(UINT x_start, UINT y_start, std::string str, UINT textpitch, COLORREF color)
{
	/****************************/
	/*	�`��p�̐ݒ�			*/
	/****************************/
	m_DrawFlag |= GraphicsDrawNS::Text;						/*	�`��t���O�̐ݒ�							*/

	/****************************/
	/*	�`�����ݒ�			*/
	/****************************/
	TextOutDraw textoutdraw;
	textoutdraw.x_start		= x_start;
	textoutdraw.y_start		= y_start;
	textoutdraw.string		= str;
	textoutdraw.textpitch	= textpitch;
	textoutdraw.color		= color;
	m_TextOutDraw.push_back(textoutdraw);

	return;

}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		DrawRectAngle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned					:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::DrawRectAngle(HDC hdc)
{
	for (unsigned int count = 0; count < m_GeometryRectAngle.size(); count++)
	{
		HPEN		hpen		= NULL;
		HBRUSH		hbrush		= NULL;
		HPEN		oldhpen		= NULL;
		HBRUSH		oldhbrush	= NULL;
		long		left		= m_GeometryRectAngle[count].left;
		long		top			= m_GeometryRectAngle[count].top;
		long		right		= m_GeometryRectAngle[count].right;
		long		bottom		= m_GeometryRectAngle[count].bottom;
		long		style		= m_GeometryRectAngle[count].style;
		long		line_width	= m_GeometryRectAngle[count].line_width;
		COLORREF	pen_color	= m_GeometryRectAngle[count].pen_color;
		COLORREF	brush_color = m_GeometryRectAngle[count].brush_color;

		if ((style < 0) || (style > PS_DASHDOTDOT))
		{
			style = PS_SOLID;
		}

		/****************************/
		/*	�����`�̕`��			*/
		/****************************/
		if (line_width == 0)
		{
			oldhpen = (HPEN)SelectObject(hdc, GetStockObject(NULL_PEN));					/*	�y���̐ݒ� ( �u���V�Ȃ� )		*/
		}
		else
		{
			hpen = CreatePen(style, line_width, pen_color);									/*	�y���̍쐬						*/
			oldhpen = (HPEN)SelectObject(hdc, hpen);										/*	�y���̐ݒ�						*/
		}

		hbrush = CreateSolidBrush(brush_color);												/*	�u���V�̍쐬					*/
		oldhbrush = (HBRUSH)SelectObject(hdc, hbrush);										/*	�u���V�̐ݒ� 					*/
		SetBkMode(hdc, OPAQUE);																/*	�w�i��h��Ԃ��ɐݒ�			*/
		Rectangle(hdc, left, top, right, bottom);											/*	�����`��ݒ�					*/

		/****************************/
		/*	�I�u�W�F�N�g�̏���		*/
		/****************************/
		SetBkMode(hdc, TRANSPARENT);														/*	�w�i�𓧖��ɐݒ肵�Ă���		*/
		SelectObject(hdc, oldhpen);															/*	�y���̐ݒ�����ɖ߂�			*/
		SelectObject(hdc, oldhbrush);														/*	�u���V�̐ݒ�����ɖ߂�			*/
		
		if(hpen != NULL)
			DeleteObject(hpen);																/*	�쐬�����y�����폜				*/
		
		if(hbrush != NULL)
			DeleteObject(hbrush);															/*	�쐬�����u���V���폜			*/
		
		if (oldhpen != NULL)
			DeleteObject(oldhpen);															/*	�쐬�����y�����폜				*/
		
		if (oldhbrush != NULL)
			DeleteObject(oldhbrush);														/*	�쐬�����u���V���폜			*/
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		DrawArc						:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned					:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::DrawArc(HDC hdc)
{
	for (unsigned int  count = 0; count < m_GeometryArc.size(); count++)
	{
		HPEN		hpen		= NULL;
		HBRUSH		hbrush		= NULL;
		HPEN		oldhpen		= NULL;
		HBRUSH		oldhbrush	= NULL;
		long		left		= m_GeometryArc[count].left;
		long		top			= m_GeometryArc[count].top;
		long		right		= m_GeometryArc[count].right;
		long		bottom		= m_GeometryArc[count].bottom;
		long		style		= m_GeometryArc[count].style;
		long		line_width	= m_GeometryArc[count].line_width;
		COLORREF	pen_color	= m_GeometryArc[count].pen_color;
		COLORREF	brush_color = m_GeometryArc[count].brush_color;

		if ((style < 0) || (style > PS_DASHDOTDOT))
		{
			style = PS_SOLID;
		}

		/****************************/
		/*	�����`�̕`��			*/
		/****************************/
		if (line_width == 0)
		{
			oldhpen = (HPEN)SelectObject(hdc, GetStockObject(NULL_PEN));					/*	�y���̐ݒ� ( �u���V�Ȃ� )		*/
		}
		else
		{
			hpen = CreatePen(style, line_width, pen_color);									/*	�y���̍쐬						*/
			oldhpen = (HPEN)SelectObject(hdc, hpen);										/*	�y���̐ݒ�						*/
		}

		
		hbrush = CreateSolidBrush(brush_color);												/*	�u���V�̍쐬					*/
		oldhbrush = (HBRUSH)SelectObject(hdc, hbrush);										/*	�u���V�̐ݒ� 					*/
		SetBkMode(hdc, OPAQUE);																/*	�w�i��h��Ԃ��ɐݒ�			*/
		Ellipse(hdc, left, top, right, bottom);												/*	�~��ݒ�						*/

		/****************************/
		/*	�I�u�W�F�N�g�̏���		*/
		/****************************/
		SetBkMode(hdc, TRANSPARENT);														/*	�w�i�𓧖��ɐݒ肵�Ă���		*/
		SelectObject(hdc, oldhpen);															/*	�y���̐ݒ�����ɖ߂�			*/
		SelectObject(hdc, oldhbrush);														/*	�u���V�̐ݒ�����ɖ߂�			*/
		if (hpen != NULL)
			DeleteObject(hpen);																/*	�쐬�����y�����폜				*/

		if (hbrush != NULL)
			DeleteObject(hbrush);															/*	�쐬�����u���V���폜			*/

		if (oldhpen != NULL)
			DeleteObject(oldhpen);															/*	�쐬�����y�����폜				*/

		if (oldhbrush != NULL)
			DeleteObject(oldhbrush);														/*	�쐬�����u���V���폜			*/
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		DrawBitmap					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned					:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::DrawBitmap(HDC hdc)
{
	/************************************/
	/*	���������VRAM�]���p�̃}�b�v	*/
	/************************************/
	long		left				= 0;
	long		top					= 0;
	long		right				= 0;
	long		bottom				= 0;
	long		mode				= 0;
	HDC			hmemDC				= CreateCompatibleDC(hdc);
	BITMAP		bitmap;
	HBITMAP		hBitmap;
	COLORREF	transparent_color	= 0;

	for (unsigned int  count = 0; count < m_BitmapDraw.size(); count++)
	{
		left				= m_BitmapDraw[count].left;
		top					= m_BitmapDraw[count].top;
		right				= m_BitmapDraw[count].right;
		bottom				= m_BitmapDraw[count].bottom;
		mode				= m_BitmapDraw[count].mode;
		hBitmap				= m_BitmapDraw[count].hbitmap;
		transparent_color	= m_BitmapDraw[count].transparent_color;

		if (hBitmap == NULL)
			break;

		/********************************/
		/*	�e���Bitmap��ݒ�			*/
		/********************************/
		GetObject(hBitmap, sizeof(bitmap), &bitmap);					/*	�r�b�g�}�b�v�̏����擾										*/
		SelectObject(hmemDC, hBitmap);									/*	�r�b�g�}�b�v�̃I�u�W�F�N�g��ݒ�								*/

		/****************/
		/*	�`�惂�[�h	*/
		/****************/
		SetMapMode(hdc, MM_TEXT);										/*	�`�惂�[�h���s�N�Z���P�ʂ̐ݒ�									*/

		/****************************/
		/*	�r�b�g�}�b�v��]��		*/
		/****************************/									/*	�r�b�g�}�b�v��VRAM�ɓ]��										*/
		if (mode == ImageNS::NORMAL_MODE)
		{
			BitBlt(hdc													/*	�R�s�[��̃f�o�C�X�R���e�L�X�g�̃n���h��						*/
				, left													/*	�R�s�[��̃r�b�g�}�b�v�̍���[ ( X���W )						*/
				, top													/*	�R�s�[��̃r�b�g�}�b�v�̍���[ ( Y���W )						*/
				, right - left											/*	�R�s�[��̃r�b�g�}�b�v�̕� 										*/
				, bottom - top											/*	�R�s�[��̃r�b�g�}�b�v�̍���									*/
				, hmemDC												/*	�r�b�g�}�b�v���쐬�����f�o�C�X�R���e�L�X�g�̃n���h��			*/
				, 0														/*	��������ɍ쐬�����r�b�g�}�b�v�̍�����W ( X���W )				*/
				, 0														/*	��������ɍ쐬�����r�b�g�}�b�v�̍�����W ( Y���W )				*/
				, SRCCOPY												/*	��������ɍ쐬�����r�b�g�}�b�v����R�s�[��֒����`���R�s�[		*/
			);

		}
		else if (mode == ImageNS::STRETCH_MODE)
		{
			SetStretchBltMode(hdc, BLACKONWHITE);
			StretchBlt(hdc												/*	�R�s�[��̃f�o�C�X�R���e�L�X�g�̃n���h��						*/
				, left													/*	�R�s�[��̃r�b�g�}�b�v�̍���[ ( X���W )						*/
				, top													/*	�R�s�[��̃r�b�g�}�b�v�̍���[ ( Y���W )						*/
				, right	- left											/*	�R�s�[��̃r�b�g�}�b�v�̕� 										*/
				, bottom - top											/*	�R�s�[��̃r�b�g�}�b�v�̍���									*/
				, hmemDC												/*	�r�b�g�}�b�v���쐬�����f�o�C�X�R���e�L�X�g�̃n���h��			*/
				, 0														/*	��������ɍ쐬�����r�b�g�}�b�v�̍�����W ( X���W )				*/
				, 0														/*	��������ɍ쐬�����r�b�g�}�b�v�̍�����W ( Y���W )				*/
				, bitmap.bmWidth										/*	��������ɍ쐬�����r�b�g�}�b�v�̕�								*/
				, bitmap.bmHeight										/*	��������ɍ쐬�����r�b�g�}�b�v�̍���							*/
				, SRCCOPY												/*	��������ɍ쐬�����r�b�g�}�b�v����R�s�[��֒����`���R�s�[		*/
			);
		}
		else if (mode == ImageNS::TRANSPARENT_MODE)
		{
			TransparentBlt(hdc											/*	�R�s�[��̃f�o�C�X�R���e�L�X�g�̃n���h��						*/
				, left													/*	�R�s�[��̃r�b�g�}�b�v�̍���[ ( X���W )						*/
				, top													/*	�R�s�[��̃r�b�g�}�b�v�̍���[ ( Y���W )						*/
				, right - left											/*	�R�s�[��̃r�b�g�}�b�v�̕� 										*/
				, bottom - top											/*	�R�s�[��̃r�b�g�}�b�v�̍���									*/
				, hmemDC												/*	�r�b�g�}�b�v���쐬�����f�o�C�X�R���e�L�X�g�̃n���h��			*/
				, 0														/*	��������ɍ쐬�����r�b�g�}�b�v�̍�����W ( X���W )				*/
				, 0														/*	��������ɍ쐬�����r�b�g�}�b�v�̍�����W ( Y���W )				*/
				, bitmap.bmWidth										/*	��������ɍ쐬�����r�b�g�}�b�v�̕�								*/
				, bitmap.bmHeight										/*	��������ɍ쐬�����r�b�g�}�b�v�̍���							*/
				, transparent_color										/*	��������ɍ쐬�����r�b�g�}�b�v����R�s�[��֒����`���R�s�[		*/
			);
		}

	}

	DeleteDC(hmemDC);

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		DrawTextRect				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned					:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::DrawTextRect(HDC hdc)
{
	for (unsigned int  count = 0; count < m_TextRectDraw.size(); count++)
	{
		RECT		rect;
		COLORREF	old_color;
		const char*	cs							= m_TextRectDraw[count].string.c_str();
		UINT		format						= m_TextRectDraw[count].format;
		UINT		textpitch					= m_TextRectDraw[count].textpitch;
		COLORREF	color						= m_TextRectDraw[count].color;
		TCHAR		strBuffer[TEXT_MAX_BYTE]	= {};
		size_t		size;

		rect.left	= m_TextRectDraw[count].left;
		rect.top	= m_TextRectDraw[count].top;
		rect.right	= m_TextRectDraw[count].right;
		rect.bottom = m_TextRectDraw[count].bottom;



#ifdef UNICODE
		mbstowcs_s(&size, strBuffer, TEXT_MAX_BYTE, cs, _TRUNCATE);
#else
		strcpy(strBuffer, cs);
#endif

		if (format == 0)
		{
			format = DT_WORDBREAK | DT_CENTER;
		}

		/********************/
		/*	�����̕`��		*/
		/********************/
		SetBkMode(hdc, TRANSPARENT);
		old_color = SetTextColor(hdc, color);

		if (textpitch != NULL)
			SetTextCharacterExtra(hdc, textpitch);
			
		DrawText(	hdc
				,	strBuffer
				,	lstrlen(strBuffer)
				,	&rect
				,	format
			);

		SetTextColor(hdc, old_color);
	
	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		DrawTextOut					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned					:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::DrawTextOut(HDC hdc)
{
	for (unsigned int  count = 0; count < m_TextOutDraw.size(); count++)
	{
		COLORREF	old_color;
		UINT		x_start						= m_TextOutDraw[count].x_start;
		UINT		y_start						= m_TextOutDraw[count].y_start;
		const char*	cs							= m_TextOutDraw[count].string.c_str();
		UINT		textpitch					= m_TextOutDraw[count].textpitch;
		COLORREF	color						= m_TextOutDraw[count].color;
		TCHAR		strBuffer[TEXT_MAX_BYTE]	= {};
		size_t		size;

#ifdef UNICODE
		mbstowcs_s(&size, strBuffer, TEXT_MAX_BYTE, cs, _TRUNCATE);
#else
		strcpy(strBuffer, cs);
#endif

		/********************/
		/*	�����̕`��		*/
		/********************/
		SetBkMode(hdc, TRANSPARENT);
		old_color = SetTextColor(hdc, color);

		if (textpitch != NULL)
			SetTextCharacterExtra(hdc, textpitch);
		
		TextOut(	hdc
				,	x_start
				,	y_start * m_textmetric.tmHeight
				,	strBuffer
				,	lstrlen(strBuffer)
			);

		SetTextColor(hdc, old_color);

	}

	return;
}

/*==============================================================================*/
/*																				*/
/*	[�֐�]		DrawClear					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[�߂�l]	unsigned					:									*/
/*	[����]		void						:									*/
/*																				*/
/*==============================================================================*/
void CGraphics::DrawClear(HDC hdc)
{
	HPEN		hpen		= NULL;
	HPEN		oldhpen		= NULL;
	HBRUSH		oldhbrush	= NULL;
	RECT		rect;																	/*	�E�B���h�E�T�C�Y�̎擾�p		*/

	GetClientRect(m_hWnd, &rect);  														/*	�E�B���h�E�T�C�Y���擾			*/

	/****************************/
	/*	�w�i�̃N���A			*/
	/****************************/
	oldhpen = (HPEN)SelectObject(hdc, GetStockObject(NULL_PEN));						/*	�y���̐ݒ�						*/
	oldhbrush = (HBRUSH)SelectObject(hdc, GetStockObject(BLACK_BRUSH));					/*	�u���V�̐ݒ� ( �u���V�Ȃ� )		*/
	SetBkMode(hdc, OPAQUE);																/*	�w�i�͓h��Ԃ�				*/
	Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);						/*	�����`��ݒ�					*/

	/****************************/
	/*	�I�u�W�F�N�g�̏���		*/
	/****************************/
	SetBkMode(hdc, TRANSPARENT);														/*	�w�i�𓧖��ɐݒ肵�Ă���		*/
	SelectObject(hdc, oldhpen);															/*	�y���̐ݒ�����ɖ߂�			*/
	SelectObject(hdc, oldhbrush);														/*	�u���V�̐ݒ�����ɖ߂�			*/

	if (hpen != NULL)
		DeleteObject(hpen);																/*	�쐬�����y�����폜				*/

	if (oldhpen != NULL)
		DeleteObject(oldhpen);															/*	�쐬�����y�����폜				*/

	if (oldhbrush != NULL)
		DeleteObject(oldhbrush);														/*	�쐬�����u���V���폜			*/

	return;
}