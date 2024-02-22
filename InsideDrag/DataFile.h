#pragma once
#include <vector>
class CDataFileBase
{
public:
	CDataFileBase();
	~CDataFileBase();

	virtual BOOL IsOpen() const;
	virtual LPBYTE GetData() const;
	virtual DWORD GetSize() const;
};


class CMapFile : public CDataFileBase
{
private:
	CAtlFile f;
	HANDLE m_hMapFile;
	ULONGLONG m_dwSize;
	LPBYTE m_p;
public:
	CMapFile();
	~CMapFile();
public:
	BOOL IsOpen() const override;
	LPBYTE GetData() const override;
	DWORD GetSize() const override;

public:
	bool Open(LPCTSTR pstrFilename);
	void Close();
};

class CMemoryFile : public CDataFileBase
{
public:
	CMemoryFile(LPBYTE pBuf, DWORD dwSize): m_p(pBuf), m_dwSize(dwSize){};
	CMemoryFile(HGLOBAL hGlobal);
	~CMemoryFile() = default;

	BOOL IsOpen() const override;
	LPBYTE GetData() const override;
	DWORD GetSize() const override;
private:
	std::vector<char> bufMemo;
	DWORD m_dwSize = 0;
	LPBYTE m_p = nullptr;
};