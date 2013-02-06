

#ifndef _MD5_H_
#define _MD5_H_ 1

#include "StdString.h"

struct MD5Context {
	uint32_t buf[4];
	uint32_t bytes[2];
	uint32_t in[16];
};

namespace XBMC
{
  class XBMC_MD5
  {
  public:
    XBMC_MD5(void);
    ~XBMC_MD5(void);
    void append(const void *inBuf, size_t inLen);
    void append(const CStdString& str);
    void getDigest(unsigned char digest[16]);
    void getDigest(CStdString& digest);
    
    /*! \brief Get the MD5 digest of the given text
     \param text text to compute the MD5 for
     \return MD5 digest
     */
    static CStdString GetMD5(const CStdString &text);
private:
    MD5Context m_ctx;
  };
}

#endif
