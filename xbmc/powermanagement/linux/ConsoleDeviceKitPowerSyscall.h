

#ifdef HAS_DBUS
#ifndef _DBUS_POWER_SYSCALL_H_
#define _DBUS_POWER_SYSCALL_H_
#include "powermanagement/IPowerSyscall.h"

class CConsoleDeviceKitPowerSyscall : public CPowerSyscallWithoutEvents
{
public:
  CConsoleDeviceKitPowerSyscall();
  virtual ~CConsoleDeviceKitPowerSyscall() { }

  virtual bool Powerdown();
  virtual bool Suspend();
  virtual bool Hibernate();
  virtual bool Reboot();

  virtual bool CanPowerdown();
  virtual bool CanSuspend();
  virtual bool CanHibernate();
  virtual bool CanReboot();
  virtual int  BatteryLevel();

  static bool HasDeviceConsoleKit();
private:
  static bool ConsoleKitMethodCall(const char *method);

  bool m_CanPowerdown;
  bool m_CanSuspend;
  bool m_CanHibernate;
  bool m_CanReboot;
};
#endif
#endif
