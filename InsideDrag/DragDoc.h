#pragma once
#include <vector>

struct FormatInfo
{
	FORMATETC	fmtEtc;
	STGMEDIUM	medium;
};

typedef std::vector<FormatInfo> vecFormat;

struct DataInfo
{
	CString		Name;
	__time64_t	time;
	vecFormat	vecFormat;	
};

typedef std::vector<DataInfo> vecData;

class CDragDoc
{
private:
	CComPtr<IOpcFactory> m_opcFactory;
	CComPtr<IOpcPackage> m_opcPackage;
	CComPtr<IOpcPartSet> m_opcPartSet;
	CComPtr<IOpcPart> m_opcPart;

	vecData m_Data;
	long m_nCurentIndex = 0;
public:
	CDragDoc();
	~CDragDoc();
	void New();
	void NewItem();
	bool AddDrop(FORMATETC* pFmtEtc, STGMEDIUM& medium);
	void ClearView();
	void SetView(long nIndex);
};

