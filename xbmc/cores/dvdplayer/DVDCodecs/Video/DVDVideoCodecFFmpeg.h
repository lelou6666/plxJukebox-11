#pragma once



#include "DVDVideoCodec.h"
#include "DVDResource.h"
#include "DllAvCodec.h"
#include "DllAvFormat.h"
#include "DllAvUtil.h"
#include "DllSwScale.h"
#include "DllAvFilter.h"

class CVDPAU;
class CCriticalSection;

class CDVDVideoCodecFFmpeg : public CDVDVideoCodec
{
public:
  class IHardwareDecoder : public IDVDResourceCounted<IHardwareDecoder>
  {
    public:
             IHardwareDecoder() {}
    virtual ~IHardwareDecoder() {};
    virtual bool Open      (AVCodecContext* avctx, const enum PixelFormat, unsigned int surfaces) = 0;
    virtual int  Decode    (AVCodecContext* avctx, AVFrame* frame) = 0;
    virtual bool GetPicture(AVCodecContext* avctx, AVFrame* frame, DVDVideoPicture* picture) = 0;
    virtual int  Check     (AVCodecContext* avctx) = 0;
    virtual void Reset     () {}
    virtual const std::string Name() = 0;
    virtual CCriticalSection* Section() { return NULL; }
  };

  CDVDVideoCodecFFmpeg();
  virtual ~CDVDVideoCodecFFmpeg();
  virtual bool Open(CDVDStreamInfo &hints, CDVDCodecOptions &options);
  virtual void Dispose();
  virtual int Decode(BYTE* pData, int iSize, double dts, double pts);
  virtual void Reset();
  bool GetPictureCommon(DVDVideoPicture* pDvdVideoPicture);
  virtual bool GetPicture(DVDVideoPicture* pDvdVideoPicture);
  virtual void SetDropState(bool bDrop);
  virtual unsigned int SetFilters(unsigned int filters);
  virtual const char* GetName() { return m_name.c_str(); }; // m_name is never changed after open
  virtual unsigned GetConvergeCount();

  bool               IsHardwareAllowed()                     { return !m_bSoftware; }
  IHardwareDecoder * GetHardware()                           { return m_pHardware; };
  void               SetHardware(IHardwareDecoder* hardware) 
  {
    SAFE_RELEASE(m_pHardware);
    m_pHardware = hardware;
    m_name += "-";
    m_name += m_pHardware->Name();
  }

protected:
  static enum PixelFormat GetFormat(struct AVCodecContext * avctx, const PixelFormat * fmt);

  int  FilterOpen(const CStdString& filters);
  void FilterClose();
  int  FilterProcess(AVFrame* frame);

  AVFrame* m_pFrame;
  AVCodecContext* m_pCodecContext;

  AVPicture* m_pConvertFrame;
  CStdString       m_filters;
  CStdString       m_filters_next;
  AVFilterGraph*   m_pFilterGraph;
  AVFilterContext* m_pFilterIn;
  AVFilterContext* m_pFilterOut;
  AVFilterLink*    m_pFilterLink;

  int m_iPictureWidth;
  int m_iPictureHeight;

  int m_iScreenWidth;
  int m_iScreenHeight;

  unsigned int m_uSurfacesCount;

  DllAvCodec m_dllAvCodec;
  DllAvUtil  m_dllAvUtil;
  DllSwScale m_dllSwScale;
  DllAvFilter m_dllAvFilter;

  std::string m_name;
  bool              m_bSoftware;
  IHardwareDecoder *m_pHardware;
  int m_iLastKeyframe;
  double m_dts;
  bool   m_started;
};
