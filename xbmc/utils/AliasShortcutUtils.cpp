

#if defined(__APPLE__) && !defined(__arm__)
#include <CoreServices/CoreServices.h>
#include "utils/URIUtils.h"
#elif defined(_LINUX)
#else
#endif

#include "Util.h"
#include "AliasShortcutUtils.h"

bool IsAliasShortcut(CStdString &path)
{
  bool  rtn = false;

#if defined(__APPLE__) && !defined(__arm__)
  // Note: regular files that have an .alias extension can be
  //   reported as an alias when clearly, they are not. Trap them out.
  if (URIUtils::GetExtension(path) != ".alias")
  {
    FSRef fileRef;
    Boolean targetIsFolder, wasAliased;

    // It is better to call FSPathMakeRefWithOptions and pass kFSPathMakeRefDefaultOptions
    //   since it will succeed for paths such as "/Volumes" unlike FSPathMakeRef.
    if (noErr == FSPathMakeRefWithOptions((UInt8*)path.c_str(), kFSPathMakeRefDefaultOptions, &fileRef, NULL))
    {
      if (noErr == FSIsAliasFile(&fileRef, &wasAliased, &targetIsFolder))
      {
        if (wasAliased)
        {
          rtn = true;
        }
      }
    }
  }
#elif defined(_LINUX)
  // Linux does not use alias or shortcut methods
#elif defined(WIN32)
/* Needs testing under Windows platform so ignore shortcuts for now
    if (CUtil::GetExtension(path) == ".lnk")
    {
      rtn = true;
    }
*/
#endif
  return(rtn);
}

void TranslateAliasShortcut(CStdString &path)
{
#if defined(__APPLE__) && !defined(__arm__)
  FSRef fileRef;
  Boolean targetIsFolder, wasAliased;

  if (noErr == FSPathMakeRefWithOptions((UInt8*)path.c_str(), kFSPathMakeRefDefaultOptions, &fileRef, NULL))
  {
    if (noErr == FSResolveAliasFileWithMountFlags(&fileRef, TRUE, &targetIsFolder, &wasAliased, kResolveAliasFileNoUI))
    {
      if (wasAliased)
      {
        char real_path[PATH_MAX];
        if (noErr == FSRefMakePath(&fileRef, (UInt8*)real_path, PATH_MAX))
        {
          path = real_path;
        }
      }
    }
  }
#elif defined(_LINUX)
  // Linux does not use alias or shortcut methods

#elif defined(WIN32)
/* Needs testing under Windows platform so ignore shortcuts for now
  CComPtr<IShellLink> ipShellLink;

  // Get a pointer to the IShellLink interface
  if (NOERROR == CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&ipShellLink))
    WCHAR wszTemp[MAX_PATH];

    // Get a pointer to the IPersistFile interface
    CComQIPtr<IPersistFile> ipPersistFile(ipShellLink);

    // IPersistFile is using LPCOLESTR so make sure that the string is Unicode
#if !defined _UNICODE
    MultiByteToWideChar(CP_ACP, 0, lpszShortcutPath, -1, wszTemp, MAX_PATH);
#else
    wcsncpy(wszTemp, lpszShortcutPath, MAX_PATH);
#endif

    // Open the shortcut file and initialize it from its contents
    if (NOERROR == ipPersistFile->Load(wszTemp, STGM_READ))
    {
      // Try to find the target of a shortcut even if it has been moved or renamed
      if (NOERROR == ipShellLink->Resolve(NULL, SLR_UPDATE))
      {
        WIN32_FIND_DATA wfd;
        TCHAR real_path[PATH_MAX];
        // Get the path to the shortcut target
        if (NOERROR == ipShellLink->GetPath(real_path, MAX_PATH, &wfd, SLGP_RAWPATH))
        {
          // Get the description of the target
          TCHAR szDesc[MAX_PATH];
          if (NOERROR == ipShellLink->GetDescription(szDesc, MAX_PATH))
          {
            path = real_path;
          }
        }
      }
    }
  }
*/
#endif
}
