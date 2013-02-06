

#include "PlayListFactory.h"
#include "PlayListM3U.h"
#include "PlayListPLS.h"
#include "PlayListB4S.h"
#include "PlayListWPL.h"
#include "PlayListURL.h"
#include "PlayListXML.h"
#include "utils/URIUtils.h"

using namespace PLAYLIST;

CPlayList* CPlayListFactory::Create(const CStdString& filename)
{
  CFileItem item(filename,false);
  return Create(item);
}

CPlayList* CPlayListFactory::Create(const CFileItem& item)
{
  if(item.IsLastFM()) //lastfm is always a stream, and just silly to check content
    return NULL;

  if( item.IsInternetStream() )
  {
    CStdString strMimeType = item.GetMimeType();
    strMimeType.MakeLower();

    if (strMimeType == "video/x-ms-asf"
    || strMimeType == "video/x-ms-asx"
    || strMimeType == "video/x-ms-wmv"
    || strMimeType == "video/x-ms-wma"
    || strMimeType == "video/x-ms-wfs"
    || strMimeType == "video/x-ms-wvx"
    || strMimeType == "video/x-ms-wax")
      return new CPlayListASX();

    if (strMimeType == "audio/x-pn-realaudio")
      return new CPlayListRAM();

    if (strMimeType == "audio/x-scpls"
    || strMimeType == "playlist"
    || strMimeType == "text/html")
      return new CPlayListPLS();

    if (strMimeType == "audio/x-mpegurl")
      return new CPlayListM3U();

    if (strMimeType == "application/vnd.ms-wpl")
      return new CPlayListWPL();
  }

  CStdString extension = URIUtils::GetExtension(item.GetPath());
  extension.MakeLower();

  if (extension == ".m3u" || extension == ".strm")
    return new CPlayListM3U();

  if (extension == ".pls")
    return new CPlayListPLS();

  if (extension == ".b4s")
    return new CPlayListB4S();

  if (extension == ".wpl")
    return new CPlayListWPL();

  if (extension == ".asx")
    return new CPlayListASX();

  if (extension == ".ram")
    return new CPlayListRAM();

  if (extension == ".url")
    return new CPlayListURL();

  if (extension == ".pxml")
    return new CPlayListXML();

  return NULL;

}

bool CPlayListFactory::IsPlaylist(const CFileItem& item)
{
  CStdString strMimeType = item.GetMimeType();
  strMimeType.ToLower();

/* These are abit uncertain 
  if(strMimeType == "video/x-ms-asf"
  || strMimeType == "video/x-ms-asx"
  || strMimeType == "video/x-ms-wmv"
  || strMimeType == "video/x-ms-wma"
  || strMimeType == "video/x-ms-wfs"
  || strMimeType == "video/x-ms-wvx"
  || strMimeType == "video/x-ms-wax"
  || strMimeType == "video/x-ms-asf")
    return true;
*/

  if(strMimeType == "audio/x-pn-realaudio"
  || strMimeType == "playlist"
  || strMimeType == "audio/x-mpegurl")
    return true;

  return IsPlaylist(item.GetPath());
}

bool CPlayListFactory::IsPlaylist(const CStdString& filename)
{
  CStdString extension = URIUtils::GetExtension(filename);
  extension.ToLower();

  if (extension == ".m3u") return true;
  if (extension == ".b4s") return true;
  if (extension == ".pls") return true;
  if (extension == ".strm") return true;
  if (extension == ".wpl") return true;
  if (extension == ".asx") return true;
  if (extension == ".ram") return true;
  if (extension == ".url") return true;
  if (extension == ".pxml") return true;
  return false;
}

