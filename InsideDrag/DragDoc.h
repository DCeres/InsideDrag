#pragma once
#include <vector>
#include <memory>

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
class CDataFileBase;
class CDragDoc
{
private:
	CComPtr<IOpcFactory> m_opcFactory;
	CComPtr<IOpcPackage> m_opcPackage;
	CComPtr<IOpcPartSet> m_opcPartSet;
	CComPtr<IOpcPart> m_opcPart;

	std::unique_ptr<CDataFileBase> m_pFile;
	vecData m_Data;
	long m_nCurentIndex = 0;
	CWindow& m_pMain;
public:
	CDragDoc(CWindow& pMain);
	~CDragDoc();
	void New();
	void NewItem();
	bool AddDrop(FORMATETC* pFmtEtc, STGMEDIUM& medium);
	void ClearView();
	void SetView(long nIndex);
};

