/*!
\file GUIListItem.h
\brief
*/

#ifndef GUILIB_GUILISTITEM_H
#define GUILIB_GUILISTITEM_H

#pragma once



#include "utils/StdString.h"

#include <map>
#include <string>

//  Forward
class CGUIListItemLayout;
class CArchive;
class CVariant;

/*!
 \ingroup controls
 \brief
 */
class CGUIListItem
{
public:
  enum GUIIconOverlay { ICON_OVERLAY_NONE = 0,
                        ICON_OVERLAY_RAR,
                        ICON_OVERLAY_ZIP,
                        ICON_OVERLAY_LOCKED,
                        ICON_OVERLAY_HAS_TRAINER,
                        ICON_OVERLAY_TRAINED,
                        ICON_OVERLAY_UNWATCHED,
                        ICON_OVERLAY_WATCHED,
                        ICON_OVERLAY_HD,
                        ICON_OVERLAY_AUDIO, // Laureon: Added
                        ICON_OVERLAY_VIDEO, // Laureon: Added
                        ICON_OVERLAY_MUSICVIDEO, // Laureon: Added
                        ICON_OVERLAY_IMAGE}; // Laureon: Added


  CGUIListItem(void);
  CGUIListItem(const CGUIListItem& item);
  CGUIListItem(const CStdString& strLabel);
  virtual ~CGUIListItem(void);
  virtual CGUIListItem *Clone() const { return new CGUIListItem(*this); };

  const CGUIListItem& operator =(const CGUIListItem& item);

  virtual void SetLabel(const CStdString& strLabel);
  const CStdString& GetLabel() const;

  void SetLabel2(const CStdString& strLabel);
  const CStdString& GetLabel2() const;

  void SetIconImage(const CStdString& strIcon);
  const CStdString& GetIconImage() const;

  void SetThumbnailImage(const CStdString& strThumbnail);
  const CStdString& GetThumbnailImage() const;

  void SetOverlayImage(GUIIconOverlay icon, bool bOnOff=false);
  CStdString GetOverlayImage() const;

  void SetSortLabel(const CStdString &label);
  const CStdStringW &GetSortLabel() const;

  void Select(bool bOnOff);
  bool IsSelected() const;

  bool HasIcon() const;
  bool HasThumbnail() const;
  bool HasOverlay() const;
  virtual bool IsFileItem() const { return false; };

  void SetLayout(CGUIListItemLayout *layout);
  CGUIListItemLayout *GetLayout();

  void SetFocusedLayout(CGUIListItemLayout *layout);
  CGUIListItemLayout *GetFocusedLayout();

  void FreeIcons();
  void FreeMemory(bool immediately = false);
  void SetInvalid();

  bool m_bIsFolder;     ///< is item a folder or a file

  void SetProperty(const CStdString &strKey, const CVariant &value);

  void IncrementProperty(const CStdString &strKey, int nVal);
  void IncrementProperty(const CStdString &strKey, double dVal);

  void ClearProperties();

  /*! \brief Append the properties of one CGUIListItem to another.
   Any existing properties in the current item will be overridden if they
   are set in the passed in item.
   \param item the item containing the properties to append.
   */
  void AppendProperties(const CGUIListItem &item);

  void Archive(CArchive& ar);
  void Serialize(CVariant& value);

  bool       HasProperty(const CStdString &strKey) const;
  bool       HasProperties() const { return m_mapProperties.size() > 0; };
  void       ClearProperty(const CStdString &strKey);

  CVariant   GetProperty(const CStdString &strKey) const;

protected:
  CStdString m_strLabel2;     // text of column2
  CStdString m_strThumbnailImage; // filename of thumbnail
  CStdString m_strIcon;      // filename of icon
  GUIIconOverlay m_overlayIcon; // type of overlay icon

  CGUIListItemLayout *m_layout;
  CGUIListItemLayout *m_focusedLayout;
  bool m_bSelected;     // item is selected or not

  struct icompare
  {
    bool operator()(const CStdString &s1, const CStdString &s2) const
    {
      return s1.CompareNoCase(s2) < 0;
    }
  };

  typedef std::map<CStdString, CVariant, icompare> PropertyMap;
  PropertyMap m_mapProperties;
private:
  CStdStringW m_sortLabel;    // text for sorting. Need to be UTF16 for proper sorting
  CStdString m_strLabel;      // text of column1
};
#endif

