#pragma once



#include "guilib/GUIDialog.h"

#include <queue>

#define TOAST_DISPLAY_TIME   5000L  // default 5 seconds
#define TOAST_MESSAGE_TIME   1000L  // minimal message time 1 second

class CGUIDialogKaiToast: public CGUIDialog
{
public:
  CGUIDialogKaiToast(void);
  virtual ~CGUIDialogKaiToast(void);

  struct Notification
  {
    CStdString caption;
    CStdString description;
    CStdString imagefile;
    unsigned int displayTime;
    unsigned int messageTime;
    bool withSound;
  };

  enum eMessageType { Info = 0, Warning, Error };

  static void QueueNotification(eMessageType eType, const CStdString& aCaption, const CStdString& aDescription, unsigned int displayTime = TOAST_DISPLAY_TIME, bool withSound = true, unsigned int messageTime = TOAST_MESSAGE_TIME);
  static void QueueNotification(const CStdString& aCaption, const CStdString& aDescription);
  static void QueueNotification(const CStdString& aImageFile, const CStdString& aCaption, const CStdString& aDescription, unsigned int displayTime = TOAST_DISPLAY_TIME, bool withSound = true, unsigned int messageTime = TOAST_MESSAGE_TIME);
  bool DoWork();

  virtual bool OnMessage(CGUIMessage& message);
  virtual void OnWindowLoaded();
  virtual void FrameMove();
  void ResetTimer();

protected:
  void AddToQueue(eMessageType eType, const CStdString& aCaption, const CStdString& aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);
  void AddToQueue(const CStdString& aImageFile, const CStdString& aCaption, const CStdString& aDescription, unsigned int displayTime, bool withSound, unsigned int messageTime);

  unsigned int m_timer;

  unsigned int m_toastDisplayTime;
  unsigned int m_toastMessageTime;

  CStdString m_defaultIcon;

  typedef std::queue<Notification> TOASTQUEUE;
  TOASTQUEUE m_notifications;
  CCriticalSection m_critical;
};
