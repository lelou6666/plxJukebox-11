#pragma once


#include "File.h"

namespace XFILE
{
class CFileSpecialProtocol : public IFile
{
public:
  CFileSpecialProtocol(void);
  virtual ~CFileSpecialProtocol(void);
  virtual bool Open(const CURL& url);
  virtual bool Exists(const CURL& url);
  virtual int Stat(const CURL& url, struct __stat64* buffer);
  virtual int Stat(struct __stat64* buffer);
  virtual bool OpenForWrite(const CURL& url, bool bOverWrite = false);
  virtual bool Delete(const CURL& url);
  virtual bool Rename(const CURL& url, const CURL& urlnew);

  virtual unsigned int Read(void* lpBuf, int64_t uiBufSize);
  virtual int Write(const void* lpBuf, int64_t uiBufSize);
  virtual int64_t Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
  virtual void Close();
  virtual int64_t GetPosition();
  virtual int64_t GetLength();

protected:
  CFile m_file;
};
}
