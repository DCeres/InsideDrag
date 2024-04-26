#include "stdafx.h"
#include "DragDoc.h"
#include <atltime.h>
#include "DataFile.h"


CDragDoc::CDragDoc(CWindow& pMain): m_pMain(pMain)
{

	HRESULT hr = S_OK;
	hr = m_opcFactory.CoCreateInstance(CLSID_OpcFactory);
	_ASSERTE(SUCCEEDED(hr));
}


CDragDoc::~CDragDoc()
{
}

void CDragDoc::New()
{
	HRESULT hr = m_opcFactory->CreatePackage(&m_opcPackage);
	m_opcPackage->GetPartSet(&m_opcPartSet);
}

void CDragDoc::NewItem()
{
	DataInfo data;
	data.Name.Format(L"Drop_%d", m_Data.size() + 1);
	_time64(&data.time);
	m_Data.push_back(data);
	m_nCurentIndex = m_Data.size() - 1;
}

bool CDragDoc::AddDrop(FORMATETC* pFmtEtc, STGMEDIUM& medium)
{
	FormatInfo info = {0};
	info.fmtEtc = *pFmtEtc;
	::CopyStgMedium(&medium, &info.medium);

	auto& date = m_Data.back();
	date.vecFormat.push_back(info);


	HRESULT hr = S_OK;
	CComPtr<IOpcPartUri> pPartUri;
	hr = m_opcFactory->CreatePartUri(L"", &pPartUri);

	if (!m_opcPartSet)
		return false;

	hr = m_opcPartSet->CreatePart(pPartUri, L"", OPC_COMPRESSION_NORMAL, &m_opcPart);
	if (!m_opcPart)
		return false;

	CComPtr<IStream> pFile;
	hr = m_opcPart->GetContentStream(&pFile);
	//pFile->Write();

	return false;
}

void CDragDoc::ClearView()
{
	std::unique_ptr<CDataFileBase> pFile = std::make_unique<CMemoryFile>(nullptr, 0);
	m_pMain.SendMessageW(WM_VIEWHEX, 0, (LPARAM)pFile.get());
	m_pFile.swap(pFile);
}

void CDragDoc::SetView(long nIndex)
{
	auto& date = m_Data.at(m_nCurentIndex);
	if (date.vecFormat.empty())
		return;

	auto format = date.vecFormat.at(nIndex);
	switch (format.medium.tymed)
	{
	case TYMED_HGLOBAL:
		{
			std::unique_ptr<CDataFileBase> pFile = std::make_unique<CMemoryFile>(format.medium.hGlobal);
			m_pMain.SendMessageW(WM_VIEWHEX, 0, (LPARAM)pFile.get());
			m_pFile.swap(pFile);
		}
		break;
	default:
		break;
	}
}
