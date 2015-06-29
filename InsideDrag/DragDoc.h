#pragma once
class CDragDoc
{
public:
	CDragDoc();
	~CDragDoc();
	void New();
	void NewItem();
	bool AddDrop(FORMATETC* pFmtEtc, STGMEDIUM& medium);
	void ClearView();
	void SetView(long nIndex);
};

