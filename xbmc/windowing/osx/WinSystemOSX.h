

#if !defined(__arm__)
#ifndef WINDOW_SYSTEM_OSX_H
#define WINDOW_SYSTEM_OSX_H

#include "windowing/WinSystem.h"
#include "threads/CriticalSection.h"
#include <SDL/SDL_video.h>

typedef struct _CGDirectDisplayID *CGDirectDisplayID;
typedef u_int32_t CGDisplayChangeSummaryFlags;

class IDispResource;

class CWinEventsOSX;
class CWinSystemOSX : public CWinSystemBase
{
public:
  CWinSystemOSX();
  virtual ~CWinSystemOSX();

  // CWinSystemBase
  virtual bool InitWindowSystem();
  virtual bool DestroyWindowSystem();
  virtual bool CreateNewWindow(const CStdString& name, bool fullScreen, RESOLUTION_INFO& res, PHANDLE_EVENT_FUNC userFunction);
  virtual bool DestroyWindow();
  virtual bool ResizeWindow(int newWidth, int newHeight, int newLeft, int newTop);
  virtual bool SetFullScreen(bool fullScreen, RESOLUTION_INFO& res, bool blankOtherDisplays);
  virtual void UpdateResolutions();
  virtual void NotifyAppFocusChange(bool bGaining);
  virtual void ShowOSMouse(bool show);
  virtual bool Minimize();
  virtual bool Restore();
  virtual bool Hide();
  virtual bool Show(bool raise = true);
  virtual void OnMove(int x, int y);

  virtual void Register(IDispResource *resource);
  virtual void Unregister(IDispResource *resource);

  virtual void EnableSystemScreenSaver(bool bEnable);
  virtual bool IsSystemScreenSaverEnabled();
  
  virtual int GetNumScreens();

  void CheckDisplayChanging(u_int32_t flags);
protected:
  void* CreateWindowedContext(void* shareCtx);
  void* CreateFullScreenContext(int screen_index, void* shareCtx);
  void  GetScreenResolution(int* w, int* h, double* fps, int screenIdx);
  void  EnableVSync(bool enable); 
  bool  SwitchToVideoMode(int width, int height, double refreshrate, int screenIdx);
  void  FillInVideoModes();
  bool  FlushBuffer(void);

  static void DisplayReconfigured(CGDirectDisplayID display, 
    CGDisplayChangeSummaryFlags flags, void *userData);
  
  void* m_glContext;
  static void* m_lastOwnedContext;
  SDL_Surface* m_SDLSurface;
  CWinEventsOSX *m_osx_events;
  bool                         m_can_display_switch;
  void                        *m_windowDidMove;
  void                        *m_windowDidReSize;

  CCriticalSection             m_resourceSection;
  std::vector<IDispResource*>  m_resources;
};

#endif // WINDOW_SYSTEM_H
#endif
