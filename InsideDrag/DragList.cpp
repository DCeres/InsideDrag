#include "stdafx.h"
#include "DragList.h"


CDragList::CDragList()
{
}


CDragList::~CDragList()
{
}

BOOL CDragList::PreTranslateMessage(MSG* pMsg)
{
	pMsg;
	return FALSE;
}

LRESULT CDragList::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	return S_OK;
}

void CDragList::Init(CDragDoc* pDoc)
{
	m_pDoc = pDoc;
	if (IsThemingSupported())
		SetWindowTheme(m_hWnd, L"Explorer", NULL);

	SetExtendedListViewStyle(LVS_EX_REGIONAL, LVS_EX_REGIONAL);
	SetExtendedListViewStyle(LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);
	SetExtendedListViewStyle(LVS_EX_DOUBLEBUFFER, LVS_EX_DOUBLEBUFFER);
	SetExtendedListViewStyle(LVS_EX_INFOTIP, LVS_EX_INFOTIP);
	SetViewType(LV_VIEW_DETAILS);
	SetUnicodeFormat();

	InsertColumn(1, L"Name", LVCFMT_LEFT, 180);
	InsertColumn(2, L"Added On", LVCFMT_LEFT, 80);
	InsertColumn(3, L"File Size", LVCFMT_RIGHT, 80);
}
