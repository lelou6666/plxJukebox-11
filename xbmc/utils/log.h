#pragma once



#include <stdio.h>
#include <string>

#include "threads/CriticalSection.h"
#include "utils/GlobalsHandling.h"

#define LOG_LEVEL_NONE         -1 // nothing at all is logged
#define LOG_LEVEL_NORMAL        0 // shows notice, error, severe and fatal
#define LOG_LEVEL_DEBUG         1 // shows all
#define LOG_LEVEL_DEBUG_FREEMEM 2 // shows all + shows freemem on screen
#define LOG_LEVEL_DEBUG_SAMBA   3 // shows all + freemem on screen + samba debugging
#define LOG_LEVEL_MAX           LOG_LEVEL_DEBUG_SAMBA

// ones we use in the code
#define LOGDEBUG   0
#define LOGINFO    1
#define LOGNOTICE  2
#define LOGWARNING 3
#define LOGERROR   4
#define LOGSEVERE  5
#define LOGFATAL   6
#define LOGNONE    7

#ifdef __GNUC__
#define ATTRIB_LOG_FORMAT __attribute__((format(printf,2,3)))
#else
#define ATTRIB_LOG_FORMAT
#endif

class CLog
{
public:

  class CLogGlobals
  {
  public:
    CLogGlobals() : m_file(NULL), m_repeatCount(0), m_repeatLogLevel(-1), m_logLevel(LOG_LEVEL_DEBUG) {}
    FILE*       m_file;
    int         m_repeatCount;
    int         m_repeatLogLevel;
    std::string m_repeatLine;
    int         m_logLevel;
    CCriticalSection critSec;
  };

  CLog();
  virtual ~CLog(void);
  static void Close();
  static void Log(int loglevel, const char *format, ... ) ATTRIB_LOG_FORMAT;
  static void MemDump(char *pData, int length);
  static bool Init(const char* path);
  static void SetLogLevel(int level);
  static int  GetLogLevel();
private:
  static void OutputDebugString(const std::string& line);
};

XBMC_GLOBAL_REF(CLog::CLogGlobals,g_log_globals);
