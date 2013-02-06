#pragma once


#include "IDirtyRegionSolver.h"
#include "DirtyRegionSolvers.h"

#if defined(TARGET_DARWIN_IOS)
#define DEFAULT_BUFFERING 4
#else
#define DEFAULT_BUFFERING 3
#endif

class CDirtyRegionTracker
{
public:
  CDirtyRegionTracker(int buffering = DEFAULT_BUFFERING);
  ~CDirtyRegionTracker();
  void SelectAlgorithm();
  void MarkDirtyRegion(const CDirtyRegion &region);

  const CDirtyRegionList &GetMarkedRegions() const;
  CDirtyRegionList GetDirtyRegions();
  void CleanMarkedRegions();

private:
  CDirtyRegionList m_markedRegions;
  int m_buffering;
  IDirtyRegionSolver *m_solver;
};
