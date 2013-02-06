
#ifndef _OSX_INTERFACE_H_
#define _OSX_INTERFACE_H_

#include <string>
#include "utils/StdString.h"
#if !defined(__arm__)
#include <Carbon/Carbon.h>
#endif
#include "AutoPool.h"

#ifdef __cplusplus
extern "C"
{
#endif
  // Power and Screen
  //
  void Cocoa_UpdateSystemActivity(void);
  
  // DisplayLink
  //
  bool Cocoa_CVDisplayLinkCreate(void *displayLinkcallback, void *displayLinkContext);
  void Cocoa_CVDisplayLinkRelease(void);
  void Cocoa_CVDisplayLinkUpdate(void);
  double Cocoa_GetCVDisplayLinkRefreshPeriod(void);

  // AppleScript
  //
  void Cocoa_DoAppleScript(const char* scriptSource);
  void Cocoa_DoAppleScriptFile(const char* filePath);
  
  // Application support
  //
  const char* Cocoa_GetIconFromBundle(const char *_bundlePath, const char *_iconName);
  
  // Devices
  //
  char* Cocoa_MountPoint2DeviceName(char *path);
  bool Cocoa_GetVolumeNameFromMountPoint(const char *mountPoint, CStdString &volumeName);

  // Mouse.
  //
  void Cocoa_HideMouse();
  void Cocoa_ShowMouse();
  void Cocoa_HideDock();

  // Smart folders.
  //
  void Cocoa_GetSmartFolderResults(const char* strFile, void (*)(void* userData, void* userData2, const char* path), void* userData, void* userData2);

  // Version.
  //
  const char* Cocoa_GetAppVersion();
  bool Cocoa_HasVDADecoder();
  bool Cocoa_GPUForDisplayIsNvidiaPureVideo3();
  int Cocoa_GetOSVersion();

  
  void  Cocoa_MakeChildWindow();
  void  Cocoa_DestroyChildWindow();

  const char *Cocoa_Paste() ;  

#if !defined(__arm__)
  // helper from QA 1134
  // http://developer.apple.com/mac/library/qa/qa2001/qa1134.html
  OSStatus SendAppleEventToSystemProcess(AEEventID EventToSend);
#endif

  void Cocoa_ResetAudioDevices();

#ifdef __cplusplus
}
#endif

#endif
