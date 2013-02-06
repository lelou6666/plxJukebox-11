

// FileAFP.h: interface for the CFileAFP class.
#ifndef FILEAFP_H_
#define FILEAFP_H_


#ifdef _LINUX

#include "IFile.h"
#include "URL.h"
#include "threads/CriticalSection.h"
#include "DllLibAfp.h"

// libafpclient includes
#ifdef __cplusplus
extern "C" {
#endif
#ifdef __cplusplus
}
#endif

CStdString URLEncode(CStdString str);

class CAfpConnection : public CCriticalSection
{
public:
    enum eAfpConnectError
    {
      AfpOk     = 0,
      AfpFailed = 1,
      AfpAuth   = 2,
    };
    typedef enum eAfpConnectError afpConnnectError;

   CAfpConnection();
  ~CAfpConnection();

  afpConnnectError      Connect(const CURL &url);
  void                  Disconnect(void);
  struct afp_server     *GetServer()    {return m_pAfpServer;}
  struct afp_volume     *GetVolume()    {return m_pAfpVol;};
  struct afp_url        *GetUrl()       {return m_pAfpUrl;};
  CStdString            GetPath(const CURL &url);
  DllLibAfp             *GetImpl()      {return m_pLibAfp;}
  
  const char            *GetConnectedIp() const { if(m_pAfpUrl) return m_pAfpUrl->servername;else return "";}
  
  //special stat which uses its own context
  //needed for getting intervolume symlinks to work
  //it uses the same global server connection
  //but its own volume
  int                   stat(const CURL &url, struct stat *statbuff);
  
  void AddActiveConnection();
  void AddIdleConnection();
  void CheckIfIdle();  
  void Deinit();  

private:
  bool                  initLib(void);
  bool                  connectVolume(const char *volumename, struct afp_volume *&pVolume);
  void                  disconnectVolume(void);
  CStdString            getAuthenticatedPath(const CURL &url);

  int                   m_OpenConnections;
  int                   m_IdleTimeout;
  struct afp_server     *m_pAfpServer;
  struct afp_volume     *m_pAfpVol;
  struct afp_url        *m_pAfpUrl;
  struct libafpclient   *m_pAfpClient;
  DllLibAfp             *m_pLibAfp;
  bool                  m_bDllInited;
};

extern CAfpConnection gAfpConnection;

namespace XFILE
{
class CFileAFP : public IFile
{
public:
  CFileAFP();
  virtual ~CFileAFP();
  virtual void          Close();
  virtual int64_t       Seek(int64_t iFilePosition, int iWhence = SEEK_SET);
  virtual unsigned int  Read(void* lpBuf, int64_t uiBufSize);
  virtual bool          Open(const CURL& url);
  virtual bool          Exists(const CURL& url);
  virtual int           Stat(const CURL& url, struct __stat64* buffer);
  virtual int           Stat(struct __stat64* buffer);
  virtual int64_t       GetLength();
  virtual int64_t       GetPosition();
  virtual int           Write(const void* lpBuf, int64_t uiBufSize);

  virtual bool          OpenForWrite(const CURL& url, bool bOverWrite = false);
  virtual bool          Delete(const CURL& url);
  virtual bool          Rename(const CURL& url, const CURL& urlnew);
  virtual int           GetChunkSize() {return 1;}
  // implement iocontrol for seek_possible for preventing the stat in File class for
  // getting this info ...
  virtual int           IoControl(EIoControl request, void* param)
                        { if (request == IOCTRL_SEEK_POSSIBLE) return 1;
                          return -1;
                        };

protected:
  bool                  IsValidFile(const CStdString& strFileName);

  CURL                  m_url;
  int64_t               m_fileSize;
  off_t                 m_fileOffset; // current SEEK pointer
  struct afp_file_info *m_pFp;
  struct afp_volume    *m_pAfpVol;  
};
}
#endif // _LINUX
#endif // FILEAFP_H_
