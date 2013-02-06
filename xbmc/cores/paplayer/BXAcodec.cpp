

#include "system.h"
#include "BXAcodec.h"
#include "utils/EndianSwap.h"

BXACodec::BXACodec()
{
  m_SampleRate = 0;
  m_Channels = 0;
  m_BitsPerSample = 0;
  m_Bitrate = 0;
  m_CodecName = "XBMC PCM";
}

BXACodec::~BXACodec()
{
  DeInit();
}

bool BXACodec::Init(const CStdString &strFile, unsigned int filecache)
{
  if (!m_file.Open(strFile))
    return false;

  // read header
  BXA_FmtHeader bxah;
  m_file.Read(&bxah, sizeof(BXA_FmtHeader));

  // file valid?
  if (strncmp(bxah.fourcc, "BXA ", 4) != 0 || bxah.type != BXA_PACKET_TYPE_FMT)
  {
    return false;
  }

  m_SampleRate = bxah.sampleRate;
  m_Channels = bxah.channels;
  m_BitsPerSample = bxah.bitsPerSample;
  m_TotalTime = bxah.durationMs;
  m_Bitrate = bxah.sampleRate * bxah.channels * bxah.bitsPerSample;

  if (m_SampleRate == 0 || m_Channels == 0 || m_BitsPerSample == 0)
  {
    return false;
  }

  return true;
}

void BXACodec::DeInit()
{
  m_file.Close();
}

__int64 BXACodec::Seek(__int64 iSeekTime)
{
  return iSeekTime;
}

template <class T>
class MiniScopedArray
{
public:
	MiniScopedArray(int size) {m_arr = new T[size];}
	~MiniScopedArray() {delete[] m_arr;}
	T* raw_data() {return m_arr;}
private:
	T* m_arr;
};

int BXACodec::ReadPCM(BYTE *pBuffer, int size, int *actualsize)
{
  *actualsize=0;

  int iAmountRead;
  //unsigned char data[size];
  MiniScopedArray<char> data(size);
  iAmountRead = m_file.Read(data.raw_data(), size);
  if (iAmountRead > 0)
  {
    *actualsize=iAmountRead;
    memcpy(pBuffer, data.raw_data(), iAmountRead <= size ? iAmountRead : size);
    return READ_SUCCESS;
  }

  *actualsize = 0;
  return READ_EOF;
}

bool BXACodec::CanInit()
{
  return true;
}
