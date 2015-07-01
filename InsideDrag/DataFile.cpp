#include "stdafx.h"
#include "DataFile.h"


CDataFileBase::CDataFileBase()
{

}

CDataFileBase::~CDataFileBase()
{

}

BOOL CDataFileBase::IsOpen() const
{
	return false;
}

LPBYTE CDataFileBase::GetData() const
{
	return (LPBYTE)nullptr;
}

DWORD CDataFileBase::GetSize() const
{
	return 0;
}

CMapFile::CMapFile() : m_hMapFile(NULL), m_p(NULL), m_dwSize(0UL)
{

}

CMapFile::~CMapFile()
{
	Close();
}

bool CMapFile::Open(LPCTSTR pstrFilename)
{
	Close();
	if (FAILED(f.Create(pstrFilename, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, OPEN_ALWAYS)))
		return false;
	f.GetSize(m_dwSize);
	m_hMapFile = ::CreateFileMapping(f, NULL, PAGE_READWRITE, 0, 0, NULL);
	if (m_hMapFile == NULL) return false;
	m_p = (LPBYTE) ::MapViewOfFile(m_hMapFile, SECTION_ALL_ACCESS, 0, 0, 0);
	if (m_p == NULL) return false;
	return true;
}

void CMapFile::Close()
{
	if (m_p) ::UnmapViewOfFile(m_p);
	m_p = NULL;
	m_dwSize = 0;
	if (m_hMapFile) ::CloseHandle(m_hMapFile);
	m_hMapFile = NULL;
	f.Close();
}

BOOL CMapFile::IsOpen() const
{
	return m_hMapFile != NULL;
}

LPBYTE CMapFile::GetData() const
{
	return (LPBYTE)m_p;
}

DWORD CMapFile::GetSize() const
{
	return (DWORD)m_dwSize;
}
