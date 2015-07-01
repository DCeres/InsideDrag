// InsideDragView.h : interface of the CInsideDragView class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "DragDropImpl.h"

class CDragDoc;
class CInsideDragView : public CSortListViewCtrlImpl<CInsideDragView, CListViewCtrl>, public CTheme, public CIDropTarget
{
	typedef CSortListViewCtrlImpl<CInsideDragView, CListViewCtrl> baseClass;
public:
	DECLARE_WND_SUPERCLASS(_T("CInsideDragView"), CListViewCtrl::GetWndClassName())

	CInsideDragView();
	~CInsideDragView();

	BOOL PreTranslateMessage(MSG* pMsg);

public:
	//CIDropTarget
	virtual HRESULT STDMETHODCALLTYPE DragEnter(IDataObject __RPC_FAR *pDataObj, DWORD grfKeyState, POINTL pt, DWORD __RPC_FAR *pdwEffect) override;
	virtual bool OnDrop(FORMATETC* pFmtEtc, STGMEDIUM& medium, DWORD *pdwEffect) override;
	//virtual HRESULT STDMETHODCALLTYPE Drop(IDataObject __RPC_FAR *pDataObj, DWORD grfKeyState, /* [in] */ POINTL pt, DWORD __RPC_FAR *pdwEffect) override;
	virtual HRESULT STDMETHODCALLTYPE DragOver(DWORD grfKeyState, POINTL pt, DWORD __RPC_FAR *pdwEffect) override;
	virtual HRESULT STDMETHODCALLTYPE DragLeave(void) override;

public:
	bool InitDragDrop(CDragDoc* pDoc);
	CDragDoc*	m_pDoc;
public:
	BEGIN_MSG_MAP(CInsideDragView)
		MESSAGE_HANDLER(WM_CREATE, OnCreate)
		CHAIN_MSG_MAP(baseClass)
		REFLECTED_NOTIFY_CODE_HANDLER(LVN_ITEMCHANGED, OnSelChanged)
		DEFAULT_REFLECTION_HANDLER()
	END_MSG_MAP()


// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnSelChanged(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);
};
