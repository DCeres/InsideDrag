#pragma once
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
	virtual  BOOL IsOpen() const override;
	virtual  LPBYTE GetData() const override;
	virtual  DWORD GetSize() const override;

public:
	bool Open(LPCTSTR pstrFilename);
	void Close();
};