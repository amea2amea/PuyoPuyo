/*------------------*/
/* インクルード		*/
/*------------------*/
#include "input.h"

/*==============================================================================*/
/*																				*/
/*	[関数]		CInput			:	コンストラクタ								*/
/*																				*/
/*==============================================================================*/
CInput::CInput()
{
	/********************************/
	/*	初期化 ( キー情報 )			*/
	/********************************/
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		m_KeysDown[i] = false;
	}

	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		m_KeysPressed[i] = false;
	}

	/********************************/
	/*	初期化	( 文字情報 )		*/
	/********************************/
	m_NewLine = true;
	m_TextIn = "";
	m_CharIn = 0;

	/********************************/
	/*	初期化	( マウス情報 )		*/
	/********************************/
    m_MouseX		= 0;
	m_MouseY		= 0;
	m_MouseRawX		= 0;
	m_MouseRawY		= 0;
	m_MouseLButton	= false;
	m_MouseMButton	= false;
	m_MouseRButton	= false;
	m_MouseX1Button = false;
	m_MouseX2Button = false;

}

/*==============================================================================*/
/*																				*/
/*	[関数]		~Input			:	デストラクタ								*/
/*																				*/
/*==============================================================================*/
CInput::~CInput()
{
	if (m_MouseCaptured)				/*	マウスがキャプチャされているならば		*/
	{
		ReleaseCapture();				/*	キャプチャー情報のリソースを解放		*/
	}
}

/*==============================================================================*/
/*																				*/
/*	[関数]		Initialize		:	初期化										*/
/*																				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]					:	なし										*/
/*	[引数]		HWND			:	ウィンドウハンドル							*/
/*				bool			:	マウスがキャプチャされているかどうか		*/
/*									( true : 有効　false : 無効 )				*/
/*																				*/
/*==============================================================================*/
void CInput::Initialize(HWND hwnd, bool capture)
{
  
	/********************************/
	/*	初期設定					*/
	/********************************/
	m_MouseCaptured = capture;

	/********************************************************************/
	/*	複数のマウスやキーボードの情報を検出							*/
	/*	 ( 高精細マウス用の読み取り。WM_MOUSEMOVEでは取得できないので	*/
	/*		WM_INPUTに来るようにRegisterRawInputDevicesで設定しておく )	*/
	/*		● 標準マウス -> 400dpi										*/
	/*		● 標準マウス -> 800dpi以上									*/
	/********************************************************************/
	m_Rid[0].usUsagePage	= HID_USAGE_PAGE_GENERIC; 
	m_Rid[0].usUsage		= HID_USAGE_GENERIC_MOUSE;
	m_Rid[0].dwFlags		= RIDEV_INPUTSINK;
	m_Rid[0].hwndTarget		= hwnd;
    RegisterRawInputDevices(m_Rid, 1, sizeof(m_Rid[0]));

	/********************************/
	/*	マウスキャプチャー処理		*/
	/********************************/
	if (m_MouseCaptured)
	{
		SetCapture(hwnd);
	}

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		KeyDown			:	キーの押し下げ処理							*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]		WPARAM			:	仮想キーコード( 0 〜 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::KeyDown(WPARAM wParam)
{
	/********************************/
	/*	キーコード処理				*/
	/********************************/
    if (wParam < inputNS::KEYS_ARRAY_LEN)
    {
        m_KeysDown[wParam]		= true;					/*	指定のキーが押されている状態 　( 現在の状態 ) 			*/
        m_KeysPressed[wParam]	= true;					/*	指定のキーが押された  									*/
    }

	return;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		KeyUp			:	キーの押し上げ処理							*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]		WPARAM			:	仮想キーコード( 0 〜 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::KeyUp(WPARAM wParam)
{
	/********************************/
	/*	キーコード処理				*/
	/********************************/
	if (wParam < inputNS::KEYS_ARRAY_LEN)
	{
		m_KeysDown[wParam] = false;						/*	指定のキーが押されていない状態 　( 現在の状態 ) 			*/
	}

	return;
}


/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		isKeyDown		:	指定されたキーが押されているかどうか確認	*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool 			:	仮想キーが押されているかどうか				*/
/*									　( true : 有効　false : 無効 )				*/
/*	[引数]		UCHAR			:	仮想キーコード( 0 〜 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::isKeyDown(UCHAR vkey) const
{

	if (vkey < inputNS::KEYS_ARRAY_LEN)
	{
		return m_KeysDown[vkey];
	}
	else
	{
		return false;
	}

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		wasKeyPressed	:	指定されたキーが押されたかどうか確認		*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool 			:	仮想キーが押されたかどうか					*/
/*									　( true : 仮想キーコード　false : 無効 ) 	*/
/*	[引数]		UCHAR			:	仮想キーコード( 0 〜 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::wasKeyPressed(UCHAR vkey) const
{

	if (vkey < inputNS::KEYS_ARRAY_LEN)
	{
		return m_KeysPressed[vkey];
	}
	else
	{
		return false;
	}

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		wasKeyPressed	:	何らかのキーが押されたかどうか確認			*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool 			:	仮想キーが複数押されたかどうか				*/
/*									　( true : 有効　false : 無効 )				*/
/*	[引数]		UCHAR			:	仮想キーコード( 0 〜 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::anyKeyPressed() const
{
	for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		if (m_KeysPressed[i] == true)
			return true;
	}


    return false;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetKeyPressed	:	現在押された仮想キーを取得					*/
/*									( 複数のキーの場合、若い仮想コード )		*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool 			:	仮想キー									*/
/*									　( 0 ~ 255の仮想キーコード )				*/
/*	[引数]		void			:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
char CInput::GetKeyPressed() const
{
	for (int i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
	{
		if (m_KeysPressed[i] == true)
			return static_cast<char>(i);
	}


	return 0x00;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		ClearKeyPress	:	指定されたキーの押し下げを解除				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]		UCHAR			:	仮想キーコード( 0 〜 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::ClearKeyPress(UCHAR vkey)
{
	if (vkey < inputNS::KEYS_ARRAY_LEN)
	{
		m_KeysPressed[vkey] = false;
	}
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		TextIn			:	文字入力処理								*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]		WPARAM			:	仮想キーコード( 0 〜 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::TextIn(WPARAM wParam)
{
	if (m_NewLine)											/*	新しい行を選択したならば							*/
	{
		m_TextIn.clear();									/*	キー情報をクリア									*/
		m_NewLine = false;									/*	新しい行の選択をオフ								*/
	}

	if (wParam == '\b')										/*	バックスペースならば								*/
	{
		if (m_TextIn.length() > 0)							/*	文字が設定済みならば								*/
		{
			m_TextIn.erase(m_TextIn.size() - 1);			/*	最後の文字を消去									*/
		}
	}
	else													/*	バックスペース以外ならば							*/
	{
		m_TextIn += static_cast<char>(wParam);				/*	文字を追加していく									*/
		m_CharIn = static_cast<char>(wParam);				/*	最後の文字に設定									*/
	}

	if (static_cast<char>(wParam) == '\r')					/*	改行コードが設定されたら ( キャリッジリターン )		*/
	{
		m_NewLine = true;									 /*	新しい行を選択										*/
	}

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetTextIn		:	文字を取得									*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]						:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
std::string CInput::GetTextIn() const
{
	return m_TextIn;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetTextIn		:	最後の文字を取得							*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]						:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
char CInput::GetCharIn() const
{
	return m_CharIn;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		ClearTextIn		:	文字バッファのクリア						*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]						:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::ClearTextIn()
{
	m_TextIn.clear();
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		Clear			:	指定された入力バッファをクリア				*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]		UCHAR			:	仮想キーコード( 0 〜 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::Clear(UCHAR what)
{
	/****************************/
	/*	キーの押し下げ			*/
	/****************************/
	if(what & inputNS::KEYS_DOWN)
    {
        for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
            m_KeysDown[i] = false;
    }

	/****************************/
	/*	キーの押し上げ			*/
	/****************************/
    if(what & inputNS::KEYS_PRESSED)
    {
        for (size_t i = 0; i < inputNS::KEYS_ARRAY_LEN; i++)
            m_KeysPressed[i] = false;
    }

	/****************************/
	/*	マウス					*/
	/****************************/
    if(what & inputNS::MOUSE)
    {
        m_MouseX	= 0;
        m_MouseY	= 0;
        m_MouseRawX = 0;
        m_MouseRawY = 0;
    }

	/****************************/
	/*	文字が入力された		*/
	/****************************/
	if (what & inputNS::TEXT_IN)
	{
		ClearTextIn();
	}

	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		ClearAll		:												*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]						:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::ClearAll()
{
	Clear(inputNS::KEYS_MOUSE_TEXT);
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		MouseIn			:	マウス入力処理								*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]		WPARAM			:	仮想キーコード( 0 〜 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::MouseIn(LPARAM lParam)
{
    m_MouseX = GET_X_LPARAM(lParam); 
    m_MouseY = GET_Y_LPARAM(lParam);
	return;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		MouseIn			:	高精細マウス入力処理						*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]		WPARAM			:	仮想キーコード( 0 〜 255 )					*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::MouseRawIn(LPARAM lParam)
{
    UINT dwSize = 40;
    static BYTE lpb[40];
    
	/****************************/
	/*	高精細マウスの読み取り	*/
	/****************************/
    GetRawInputData((HRAWINPUT)lParam, RID_INPUT, 
                    lpb, &dwSize, sizeof(RAWINPUTHEADER));
    
    RAWINPUT* raw = (RAWINPUT*)lpb;
    
    if (raw->header.dwType == RIM_TYPEMOUSE)			/*	マウスから入力された						*/
    {
        m_MouseRawX = raw->data.mouse.lLastX;
        m_MouseRawY = raw->data.mouse.lLastY;
    } 

	return;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetMouseLButton	:	マウスの左クリック入力						*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]		bool			:	左クリックの状態							*/
/*									( true : あり　false : なし )				*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::SetMouseLButton(bool LButtonOn)
{
	m_MouseLButton = LButtonOn;
	return;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetMouseMButton	:	マウスの中央ボタン入力						*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]		bool			:	中央ボタンの状態							*/
/*									( true : あり　false : なし )				*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::SetMouseMButton(bool MButtoOn)
{
	m_MouseMButton = MButtoOn;
	return;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetMouseLButton	:	マウスの右クリック入力						*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]		bool			:	右クリックの状態							*/
/*									( true : あり　false : なし )				*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::SetMouseRButton(bool RButtonOn)
{
	m_MouseRButton = RButtonOn;
	return;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		SetMouseXButton	:	マウスのXボタン入力							*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	なし										*/
/*	[引数]		bool			:	Xボタンの状態								*/
/*									( true : あり　false : なし )				*/
/*																				*/
/*------------------------------------------------------------------------------*/
void CInput::SetMouseXButton(WPARAM wParam)
{
	m_MouseX1Button = (wParam & MK_XBUTTON1) ? true : false;
	m_MouseX2Button = (wParam & MK_XBUTTON2) ? true : false;
	return;

}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetMouseX		:	マウスの座標位置 ( 横座標 )	を取得			*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	int 			:	座標位置 ( 横座標 )							*/
/*	[引数]						:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
int CInput::GetMouseX() const
{
	return m_MouseX;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GettMouseY		:	マウスの座標位置 ( 縦座標 )	を取得			*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	int 			:	座標位置 ( 縦座標 )							*/
/*	[引数]						:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
int CInput::GetMouseY() const
{
	return m_MouseY;
}


/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetMouseRawX	:	高精細マウスの座標位置 ( 横座標 ) を取得	*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	int 			:	座標位置 ( 横座標 )							*/
/*	[引数]						:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
int CInput::GetMouseRawX() const
{
	return m_MouseRawX;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetMouseRawY	:	高精細マウスの座標位置 ( 縦座標 ) を取得	*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	void 			:	座標位置 ( 縦座標 )							*/
/*	[引数]						:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
int CInput::GetMouseRawY() const
{
	return m_MouseRawY;
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetMouseLButton	:	マウスの左クリックの有効状態を取得			*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool 			:	左クリックの状態							*/
/*									( true : あり　false : なし )				*/
/*	[引数]						:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::GetMouseLButton() const 
{ 
	return m_MouseLButton; 
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetMouseLButton	:	マウスの中央ボタンの有効状態を取得			*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool 			:	中央ボタンの状態							*/
/*									( true : 有効　false : 無効 )				*/
/*	[引数]						:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::GetMouseMButton() const
{ 
	return m_MouseMButton; 
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetMouseLButton	:	マウスの右クリックの有効状態を取得			*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool 			:	右クリックの状態							*/
/*									( true : あり　false : なし )				*/
/*	[引数]						:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::GetMouseRButton() const
{ 
	return m_MouseRButton; 
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetMouseLButton	:	マウスのX1ボタンの有効状態を取得			*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool 			:	X1ボタンの状態								*/
/*									( true : 有効　false : 無効 )				*/
/*	[引数]						:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::GetMouseX1Button() const
{ 
	return m_MouseX1Button; 
}

/*------------------------------------------------------------------------------*/
/*																				*/
/*	[関数]		GetMouseLButton	:	マウスのX1ボタンの有効状態を取得			*/
/*	----------------------------------------------------------------------------*/
/*	[戻り値]	bool 			:	X1ボタンの状態								*/
/*									( true : 有効　false : 無効 )				*/
/*	[引数]						:	なし										*/
/*																				*/
/*------------------------------------------------------------------------------*/
bool CInput::GetMouseX2Button() const
{ 
	return m_MouseX2Button; 
}
