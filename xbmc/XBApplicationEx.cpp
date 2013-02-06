

#include "system.h"
#include "XBApplicationEx.h"
#include "utils/log.h"
#ifdef HAS_PERFORMANCE_SAMPLE
#include "utils/PerformanceSample.h"
#else
#define MEASURE_FUNCTION
#endif

CXBApplicationEx::CXBApplicationEx()
{
  // Variables to perform app timing
  m_bStop = false;
  m_AppActive = true;
  m_AppFocused = true;
  m_ExitCode = EXITCODE_QUIT;
}

CXBApplicationEx::~CXBApplicationEx()
{
}

/* Create the app */
bool CXBApplicationEx::Create()
{
  // Variables to perform app timing
  m_bStop = false;
  m_AppActive = true;
  m_AppFocused = true;
  m_ExitCode = EXITCODE_QUIT;

  // Initialize the app's device-dependent objects
  if (!Initialize())
  {
    CLog::Log(LOGERROR, "XBAppEx: Call to Initialize() failed!" );
    return false;
  }

  return true;
}

/* Destroy the app */
VOID CXBApplicationEx::Destroy()
{
  CLog::Log(LOGNOTICE, "destroy");
  // Perform app-specific cleanup
  Cleanup();
}

/* Function that runs the application */
INT CXBApplicationEx::Run()
{
  CLog::Log(LOGNOTICE, "Running the application..." );

  BYTE processExceptionCount = 0;
  BYTE frameMoveExceptionCount = 0;
  BYTE renderExceptionCount = 0;

#ifndef _DEBUG
  const BYTE MAX_EXCEPTION_COUNT = 10;
#endif

  // Run xbmc
  while (!m_bStop)
  {
#ifdef HAS_PERFORMANCE_SAMPLE
    CPerformanceSample sampleLoop("XBApplicationEx-loop");
#endif
    //-----------------------------------------
    // Animate and render a frame
    //-----------------------------------------
#ifndef _DEBUG
    try
    {
#endif
      Process();
      //reset exception count
      processExceptionCount = 0;

#ifndef _DEBUG

    }
    catch (...)
    {
      CLog::Log(LOGERROR, "exception in CApplication::Process()");
      processExceptionCount++;
      //MAX_EXCEPTION_COUNT exceptions in a row? -> bail out
      if (processExceptionCount > MAX_EXCEPTION_COUNT)
      {
        CLog::Log(LOGERROR, "CApplication::Process(), too many exceptions");
        throw;
      }
    }
#endif
    // Frame move the scene
#ifndef _DEBUG
    try
    {
#endif
      if (!m_bStop) FrameMove(true);
      //reset exception count
      frameMoveExceptionCount = 0;

#ifndef _DEBUG

    }
    catch (...)
    {
      CLog::Log(LOGERROR, "exception in CApplication::FrameMove()");
      frameMoveExceptionCount++;
      //MAX_EXCEPTION_COUNT exceptions in a row? -> bail out
      if (frameMoveExceptionCount > MAX_EXCEPTION_COUNT)
      {
        CLog::Log(LOGERROR, "CApplication::FrameMove(), too many exceptions");
        throw;
      }
    }
#endif

    // Render the scene
#ifndef _DEBUG
    try
    {
#endif
      if (!m_bStop) Render();
      //reset exception count
      renderExceptionCount = 0;

#ifndef _DEBUG

    }
    catch (...)
    {
      CLog::Log(LOGERROR, "exception in CApplication::Render()");
      renderExceptionCount++;
      //MAX_EXCEPTION_COUNT exceptions in a row? -> bail out
      if (renderExceptionCount > MAX_EXCEPTION_COUNT)
      {
        CLog::Log(LOGERROR, "CApplication::Render(), too many exceptions");
        throw;
      }
    }
#endif
  } // while (!m_bStop)
  Destroy();

  CLog::Log(LOGNOTICE, "application stopped..." );
  return m_ExitCode;
}
