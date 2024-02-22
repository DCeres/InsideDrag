// InsideDragView.cpp : implementation of the CInsideDragView class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Ribbon.h"
#include "resource.h"

#include "InsideDragView.h"
#include "DragDoc.h"

static CString predefined_name(int cfFormat)
{
	CString buff;
	if (cfFormat >= CF_GDIOBJFIRST && cfFormat <= CF_GDIOBJLAST) 
	{
		buff.Format(L"CF_GDIOBJ%d", cfFormat);
		return buff;
	}
	else if (cfFormat >= CF_PRIVATEFIRST && cfFormat <= CF_PRIVATELAST) 
	{
		buff.Format(L"CF_PRIVATE%d", cfFormat);
		return buff;
	}
	switch (cfFormat) 
	{
	case CF_BITMAP:			 return L"CF_BITMAP";
	case CF_DIB:			 return L"CF_DIB";
	case CF_DIBV5:			 return L"CF_DIBV5";
	case CF_DIF:			 return L"CF_DIF";
	case CF_DSPBITMAP:		 return L"CF_DSPBITMAP";
	case CF_DSPENHMETAFILE:	 return L"CF_DSPENHMETAFILE";
	case CF_DSPMETAFILEPICT: return L"CF_DSPMETAFILEPICT";
	case CF_DSPTEXT:		 return L"CF_DSPTEXT";
	case CF_ENHMETAFILE:	 return L"CF_ENHMETAFILE";
	case CF_HDROP:			 return L"CF_HDROP";
	case CF_LOCALE:			 return L"CF_LOCALE";
	case CF_METAFILEPICT:	 return L"CF_METAFILEPICT";
	case CF_OEMTEXT:		 return L"CF_OEMTEXT";
	case CF_OWNERDISPLAY:	 return L"CF_OWNERDISPLAY";
	case CF_PALETTE:		 return L"CF_PALETTE";
	case CF_PENDATA:		 return L"CF_PENDATA";
	case CF_RIFF:			 return L"CF_RIFF";
	case CF_SYLK:			 return L"CF_SYLK";
	case CF_TEXT:			 return L"CF_TEXT";
	case CF_WAVE:			 return L"CF_WAVE";
	case CF_TIFF:			 return L"CF_TIFF";
	case CF_UNICODETEXT:	 return L"CF_UNICODETEXT";
	}

	const int nMaxCount = 250 * 4;
	const int nLen = GetClipboardFormatName(cfFormat, buff.GetBuffer(nMaxCount), nMaxCount);
	buff.ReleaseBuffer();
	if (nLen <= 0)
	{
		buff.Format(L"(unknown %d)", cfFormat);
	}
	return buff;
}

static CString GetTYMED_Name(TYMED nID)
{
	switch (nID)
	{
	case TYMED_HGLOBAL:		return L"Memory";
	case TYMED_FILE:		return L"File";
	case TYMED_ISTREAM:		return L"IStream";
	case TYMED_ISTORAGE:	return L"IStorage";
	case TYMED_GDI:			return L"GDI";
	case TYMED_MFPICT:		return L"MFPICT";
	case TYMED_ENHMF:		return L"ENHMF";
	case TYMED_NULL:		return L"NULL";
	default:
		break;
	}
	CString buff;
	buff.Format(L"(unknown %d)", nID);
	return buff;
}


static CString GetDVASPECT_Name(DWORD nID)
{
	switch (nID)
	{
	//case DVASPECT_SHORTNAME:	return L"SHORTNAME";
	case DVASPECT_COPY:			return L"COPY";
	//case DVASPECT_LINK:			return L"LINK";
	case DVASPECT_CONTENT:		return L"Content";
	case DVASPECT_THUMBNAIL:	return L"Thumbnail";
	case DVASPECT_ICON:			return L"Icon";
	case DVASPECT_DOCPRINT:		return L"DocPrint";
	default:
		break;
	}
	CString buff;
	buff.Format(L"(unknown %d)", nID);
	return buff;
}


CInsideDragView::CInsideDragView() : CIDropTarget(m_hWnd)
{

}

CInsideDragView::~CInsideDragView()
{

}

BOOL CInsideDragView::PreTranslateMessage(MSG* pMsg)
{
	pMsg;
	return FALSE;
}

bool CInsideDragView::InitDragDrop(CDragDoc* pDoc)
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

	InsertColumn(0, L"Format ID", LVCFMT_RIGHT, 80);
	InsertColumn(1, L"Format Name", LVCFMT_LEFT, 180);
	InsertColumn(2, L"Handle Type", LVCFMT_LEFT, 180);
	InsertColumn(3, L"Size", LVCFMT_RIGHT, 180);
	InsertColumn(4, L"Index", LVCFMT_RIGHT, 180);
	InsertColumn(5, L"Shell data transfer", LVCFMT_LEFT, 180);

	CIDropTarget::m_hTargetWnd = m_hWnd;
	HRESULT hr = ::RegisterDragDrop(m_hWnd, this);
	if (SUCCEEDED(hr)) //calls addref
		;//this->Release(); //i decided to AddRef explicitly after new
	else
		return false;
	return true;
}

LRESULT CInsideDragView::OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled)
{
	bHandled = FALSE;
	return S_OK;
}

LRESULT CInsideDragView::OnSelChanged(int idCtrl, LPNMHDR pnmh, BOOL& bHandled)
{
	LPNMLISTVIEW pnmv = (LPNMLISTVIEW)pnmh;
	if ((pnmv->uNewState & LVIS_SELECTED) != (pnmv->uOldState & LVIS_SELECTED))
	{
		if (pnmv->uNewState & LVIS_SELECTED)
		{
			CWaitCursor wait(true);
			m_pDoc->SetView(pnmv->iItem);
		}
		else
		{
			m_pDoc->ClearView();
		}
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE CInsideDragView::DragEnter(IDataObject __RPC_FAR *pDataObj, DWORD grfKeyState, POINTL pt, DWORD __RPC_FAR *pdwEffect)
{
	DeleteAllItems();
	m_pDoc->NewItem();
	return CIDropTarget::DragEnter(pDataObj, grfKeyState, pt, pdwEffect);
}

/*
HRESULT STDMETHODCALLTYPE CInsideDragView::Drop(IDataObject __RPC_FAR *pDataObj, DWORD grfKeyState, / * [in] * / POINTL pt, DWORD __RPC_FAR *pdwEffect)
{
	if (pDataObj == NULL)
		return E_INVALIDARG;

	if (QueryDrop(grfKeyState, pdwEffect))
	{
		IEnumFORMATETC* pEnum;
		pDataObj->EnumFormatEtc(DATADIR_GET, &pEnum);
		FORMATETC ftm;
		while (pEnum->Next(1, &ftm, 0) == S_OK)
		{
			STGMEDIUM medium;
			if (pDataObj->GetData(&ftm, &medium) == S_OK)
			{
				if (OnDrop(&ftm, medium, pdwEffect)) //does derive class wants us to free medium?
					ReleaseStgMedium(&medium);
			}
		};
		pEnum->Release();
	}
	*pdwEffect = DROPEFFECT_NONE;
	return S_OK;
}*/

bool CInsideDragView::OnDrop(FORMATETC* pFmtEtc, STGMEDIUM& medium, DWORD *pdwEffect)
{
	m_pDoc->AddDrop(pFmtEtc, medium);

	int nCount = GetItemCount();
	CString str;
	str.Format(L"%d", pFmtEtc->cfFormat);

	int nIndex = InsertItem(nCount, str);
	SetItemText(nIndex, 1, predefined_name(pFmtEtc->cfFormat));
	SetItemText(nIndex, 2, GetTYMED_Name((TYMED)pFmtEtc->tymed));

	SIZE_T nSize = 0;
	switch (medium.tymed)
	{
	case TYMED_HGLOBAL:
		nSize = GlobalSize(medium.hGlobal);
		break;
	default:
		break;
	}
	str.Format(L"%d", nSize);
	SetItemText(nIndex, 3, str);
	str.Format(L"%d", pFmtEtc->lindex);
	SetItemText(nIndex, 4, str);
	SetItemText(nIndex, 5, GetDVASPECT_Name(pFmtEtc->dwAspect));
	//SortItems();
	return true;
}

HRESULT STDMETHODCALLTYPE CInsideDragView::DragOver(DWORD grfKeyState, POINTL pt, DWORD __RPC_FAR *pdwEffect)
{
	return CIDropTarget::DragOver(grfKeyState, pt, pdwEffect);
}

HRESULT STDMETHODCALLTYPE CInsideDragView::DragLeave(void)
{
	return CIDropTarget::DragLeave();
}
