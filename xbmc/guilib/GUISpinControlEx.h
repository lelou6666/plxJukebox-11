/*!
\file GUISpinControlEx.h
\brief
*/

#ifndef GUILIB_SPINCONTROLEX_H
#define GUILIB_SPINCONTROLEX_H

#pragma once



#include "GUISpinControl.h"
#include "GUIButtonControl.h"

/*!
 \ingroup controls
 \brief
 */
class CGUISpinControlEx : public CGUISpinControl
{
public:
  CGUISpinControlEx(int parentID, int controlID, float posX, float posY, float width, float height, float spinWidth, float spinHeight, const CLabelInfo& spinInfo, const CTextureInfo &textureFocus, const CTextureInfo &textureNoFocus, const CTextureInfo& textureUp, const CTextureInfo& textureDown, const CTextureInfo& textureUpFocus, const CTextureInfo& textureDownFocus, const CLabelInfo& labelInfo, int iType);
  virtual ~CGUISpinControlEx(void);
  virtual CGUISpinControlEx *Clone() const { return new CGUISpinControlEx(*this); };

  virtual void Process(unsigned int currentTime, CDirtyRegionList &dirtyregions);
  virtual void Render();
  virtual void SetPosition(float posX, float posY);
  virtual float GetWidth() const { return m_buttonControl.GetWidth();};
  virtual void SetWidth(float width);
  virtual float GetHeight() const { return m_buttonControl.GetHeight();};
  virtual void SetHeight(float height);
  virtual void AllocResources();
  virtual void FreeResources(bool immediately = false);
  virtual void DynamicResourceAlloc(bool bOnOff);
  virtual void SetInvalid();
  const CStdString GetCurrentLabel() const;
  void SetText(const std::string & aLabel) {m_buttonControl.SetLabel(aLabel);};
  virtual void SetEnabled(bool bEnable);
  virtual float GetXPosition() const { return m_buttonControl.GetXPosition();};
  virtual float GetYPosition() const { return m_buttonControl.GetYPosition();};
  virtual CStdString GetDescription() const;
  virtual bool HitTest(const CPoint &point) const { return m_buttonControl.HitTest(point); };
  void SetSpinPosition(float spinPosX);

  void SetItemInvalid(bool invalid);
protected:
  virtual void RenderText(float posX, float width);
  virtual bool UpdateColors();
  CGUIButtonControl m_buttonControl;
  float m_spinPosX;
};
#endif
