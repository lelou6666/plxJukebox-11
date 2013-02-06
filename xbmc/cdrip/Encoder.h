#ifndef _ENCODER_H
#define _ENCODER_H



#include "utils/StdString.h"

#define ENC_ARTIST  11
#define ENC_TITLE   12
#define ENC_ALBUM   13
#define ENC_YEAR    14
#define ENC_COMMENT 15
#define ENC_TRACK   16
#define ENC_GENRE   17

#define WRITEBUFFER_SIZE 131072 // 128k buffer

namespace XFILE { class CFile; }

class CEncoder
{
public:
  CEncoder();
  virtual ~CEncoder();
  virtual bool Init(const char* strFile, int iInChannels, int iInRate, int iInBits) = 0;
  virtual int Encode(int nNumBytesRead, uint8_t* pbtStream) = 0;
  virtual bool Close() = 0;

  void SetComment(const CStdString& str) { m_strComment = str; }
  void SetArtist(const CStdString& str) { m_strArtist = str; }
  void SetTitle(const CStdString& str) { m_strTitle = str; }
  void SetAlbum(const CStdString& str) { m_strAlbum = str; }
  void SetAlbumArtist(const CStdString& str) { m_strAlbumArtist = str; }
  void SetGenre(const CStdString& str) { m_strGenre = str; }
  void SetTrack(const CStdString& str) { m_strTrack = str; }
  void SetTrackLength(int length) { m_iTrackLength = length; }
  void SetYear(const CStdString& str) { m_strYear = str; }

protected:
  bool FileCreate(const char* filename);
  bool FileClose();
  int FileWrite(const void *pBuffer, uint32_t iBytes);

  int WriteStream(const void *pBuffer, uint32_t iBytes);
  int FlushStream();

  // tag info
  CStdString m_strComment;
  CStdString m_strArtist;
  CStdString m_strAlbumArtist;
  CStdString m_strTitle;
  CStdString m_strAlbum;
  CStdString m_strGenre;
  CStdString m_strTrack;
  CStdString m_strYear;
  int m_iTrackLength;

  CStdString m_strFile;

  XFILE::CFile *m_file;
  int m_iInChannels;
  int m_iInSampleRate;
  int m_iInBitsPerSample;

  uint8_t m_btWriteBuffer[WRITEBUFFER_SIZE]; // 128k buffer for writing to disc
  uint32_t m_dwWriteBufferPointer;
};

#endif // _ENCODER_H

