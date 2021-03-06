#pragma once



#include "guilib/GUIDialog.h"

class CFileItemList;

class CGUIDialogPictureInfo :
      public CGUIDialog
{
public:
  CGUIDialogPictureInfo(void);
  virtual ~CGUIDialogPictureInfo(void);
  void SetPicture(CFileItem *item);
  virtual void FrameMove();

protected:
  virtual void OnInitWindow();
  virtual void OnDeinitWindow(int nextWindowID);
  virtual bool OnAction(const CAction& action);
  void UpdatePictureInfo();

  CFileItemList* m_pictureInfo;
  CStdString    m_currentPicture;
};
