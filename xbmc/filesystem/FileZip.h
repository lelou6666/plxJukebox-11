#ifndef FILE_ZIP_H_
#define FILE_ZIP_H_



#include "IFile.h"
#include <zlib.h>
#include "utils/log.h"
#include "File.h"
#include "ZipManager.h"

namespace XFILE
{
  class CFileZip : public IFile
  {
  public:
    CFileZip();
    virtual ~CFileZip();

    virtual int64_t GetPosition();
    virtual int64_t GetLength();
    virtual bool Open(const CURL& url);
    virtual bool Exists(const CURL& url);
    virtual int Stat(struct __stat64* buffer);
    virtual int Stat(const CURL& url, struct __stat64* buffer);
    virtual unsigned int Read(void* lpBuf, int64_t uiBufSize);
    //virtual bool ReadString(char *szLine, int iLineLength);
    virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
    virtual void Close();

    int UnpackFromMemory(std::string& strDest, const std::string& strInput, bool isGZ=false);
  private:
    bool InitDecompress();
    bool FillBuffer();
    void DestroyBuffer(void* lpBuffer, int iBufSize);
    CFile mFile;
    SZipEntry mZipItem;
    int64_t m_iFilePos; // position in _uncompressed_ data read
    int64_t m_iZipFilePos; // position in _compressed_ data
    int m_iAvailBuffer;
    z_stream m_ZStream;
    char m_szBuffer[65535];     // 64k buffer for compressed data
    char* m_szStringBuffer;
    char* m_szStartOfStringBuffer; // never allocated!
    int m_iDataInStringBuffer;
    int m_iRead;
    bool m_bFlush;
    bool m_bCached;
  };
}

#endif
