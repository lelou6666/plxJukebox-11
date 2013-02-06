/*!
\file GUIInfoTypes.h
\brief
*/

#ifndef GUILIB_GUIINFOTYPES_H
#define GUILIB_GUIINFOTYPES_H

#pragma once



#include "utils/StdString.h"

class CGUIListItem;

class CGUIInfoBool
{
public:
  CGUIInfoBool(bool value = false);
  virtual ~CGUIInfoBool();

  operator bool() const { return m_value; };

  void Update(const CGUIListItem *item = NULL);
  void Parse(const CStdString &expression, int context);
private:
  unsigned int m_info;
  bool m_value;
};

typedef uint32_t color_t;

class CGUIInfoColor
{
public:
  CGUIInfoColor(color_t color = 0);

  const CGUIInfoColor &operator=(const CGUIInfoColor &color);
  const CGUIInfoColor &operator=(color_t color);
  operator color_t() const { return m_color; };

  bool Update();
  void Parse(const CStdString &label, int context);

private:
  color_t GetColor() const;
  int     m_info;
  color_t m_color;
};

class CGUIInfoLabel
{
public:
  CGUIInfoLabel();
  CGUIInfoLabel(const CStdString &label, const CStdString &fallback = "", int context = 0);

  void SetLabel(const CStdString &label, const CStdString &fallback, int context = 0);
  CStdString GetLabel(int contextWindow, bool preferImage = false) const;
  CStdString GetItemLabel(const CGUIListItem *item, bool preferImage = false) const;
  bool IsConstant() const;
  bool IsEmpty() const;

  const CStdString GetFallback() const { return m_fallback; };

  static CStdString GetLabel(const CStdString &label, int contextWindow = 0, bool preferImage = false);

  /*!
   \brief Replaces instances of $LOCALIZE[number] with the appropriate localized string
   \param label text to replace
   \return text with any localized strings filled in.
   */
  static CStdString ReplaceLocalize(const CStdString &label);

  /*!
   \brief Replaces instances of $ADDON[id number] with the appropriate localized addon string
   \param label text to replace
   \return text with any localized strings filled in.
   */
  static CStdString ReplaceAddonStrings(const CStdString &label);

private:
  void Parse(const CStdString &label, int context);

  class CInfoPortion
  {
  public:
    CInfoPortion(int info, const CStdString &prefix, const CStdString &postfix, bool escaped = false);
    CStdString GetLabel(const CStdString &info) const;
    int m_info;
    CStdString m_prefix;
    CStdString m_postfix;
  private:
    bool m_escaped;
  };

  CStdString m_fallback;
  std::vector<CInfoPortion> m_info;
};

#endif
