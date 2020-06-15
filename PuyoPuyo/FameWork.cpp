/*------------------*/
/* インクルード		*/
/*------------------*/
#include "FrameWork.h"

/*==============================================================================*/
/*																				*/
/*	[関数]		CFameWork	:	コンストラクタ ( 引数なし )						*/
/*																				*/
/*==============================================================================*/
CFameWork::CFameWork()
{
}

/*==============================================================================*/
/*																				*/
/*	[関数]		CFameWork		:	コンストラクタ ( 引数あり )					*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[引数]		HINSTANCE 		:												*/
/*				LPTSTR			:												*/
/*																				*/
/*==============================================================================*/
CFameWork::CFameWork(HINSTANCE hInstance, LPTSTR lpCmdLine) :
			m_CommandLine(lpCmdLine)
		,	m_hWnd(0)
{
}

/*==============================================================================*/
/*																				*/
/*	[関数]		~CFameWork		:	デストラクタ								*/
/*																				*/
/*==============================================================================*/
CFameWork::~CFameWork()
{
	m_pGraphics = 0;
	m_pGameLogic = 0;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		Initialize					:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
bool CFameWork::Initialize()
{
	return true;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		Run							:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
bool CFameWork::Run()
{
	if (Initialize())
	{
		MessageLoop();
		return true;
	}
	return false;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		GetWindowHandle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	HWND						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
HWND CFameWork::GetWindowHandle() const
{
	return m_hWnd;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetWindowHandle				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	HWND						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
void CFameWork::SetWindowHandle(HWND hwnd)
{
	m_hWnd = hwnd;
	return;
}
/*==============================================================================*/
/*																				*/
/*	[関数]		SetGraphicClass				:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
void CFameWork::SetGraphicClass(CGraphics* pGraphics)
{
	m_pGraphics = pGraphics;
	return ;
}

/*==============================================================================*/
/*																				*/
/*	[関数]		SetGameLogicClass			:									*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void						:									*/
/*	[引数]		void						:									*/
/*																				*/
/*==============================================================================*/
void CFameWork::SetGameLogicClass(CGameLogic* pGameLogic)
{
	m_pGameLogic = pGameLogic;
	return ;
}
