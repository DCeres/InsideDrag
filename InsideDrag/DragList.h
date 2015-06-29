#pragma once

class CDragDoc;
class CDragList : public CSortListViewCtrlImpl<CDragList, CListViewCtrl>, public CTheme
{
	typedef CSortListViewCtrlImpl<CDragList, CListViewCtrl> baseClass;
public:
	DECLARE_WND_SUPERCLASS(_T("CDragList"), CListViewCtrl::GetWndClassName())

	CDragList();
	~CDragList();

	BOOL PreTranslateMessage(MSG* pMsg);
	
	CDragDoc* m_pDoc;
public:
	BEGIN_MSG_MAP(CDragList)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		CHAIN_MSG_MAP(baseClass)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()

	// Handler prototypes (uncomment arguments if needed):
	//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)
	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	void Init(CDragDoc* pDoc);
};

