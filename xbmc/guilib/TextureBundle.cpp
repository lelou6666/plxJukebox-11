

#include "system.h"
#include "TextureBundle.h"

CTextureBundle::CTextureBundle(void)
{
  m_useXPR = false;
  m_useXBT = false;
}

CTextureBundle::~CTextureBundle(void)
{
}

bool CTextureBundle::HasFile(const CStdString& Filename)
{
  if (m_useXBT)
  {
    return m_tbXBT.HasFile(Filename);
  }
  else if (m_useXPR)
  {
    return m_tbXPR.HasFile(Filename);
  }
  else if (m_tbXBT.HasFile(Filename))
  {
    m_useXBT = true;
    return true;
  }
  else if (m_tbXPR.HasFile(Filename))
  {
    m_useXPR = true;
    return true;
  }
  else
  {
    return false;
  }
}

void CTextureBundle::GetTexturesFromPath(const CStdString &path, std::vector<CStdString> &textures)
{
  if (m_useXBT)
  {
    m_tbXBT.GetTexturesFromPath(path, textures);
  }
  else if (m_useXPR)
  {
    m_tbXPR.GetTexturesFromPath(path, textures);
  }
}

bool CTextureBundle::LoadTexture(const CStdString& Filename, CBaseTexture** ppTexture,
                                     int &width, int &height)
{
  if (m_useXBT)
  {
    return m_tbXBT.LoadTexture(Filename, ppTexture, width, height);
  }
  else if (m_useXPR)
  {
    return m_tbXPR.LoadTexture(Filename, ppTexture, width, height);
  }
  else
  {
    return false;
  }
}

int CTextureBundle::LoadAnim(const CStdString& Filename, CBaseTexture*** ppTextures,
                              int &width, int &height, int& nLoops, int** ppDelays)
{
  if (m_useXBT)
  {
    return m_tbXBT.LoadAnim(Filename, ppTextures, width, height, nLoops, ppDelays);
  }
  else if (m_useXPR)
  {
    return m_tbXPR.LoadAnim(Filename, ppTextures, width, height, nLoops, ppDelays);
  }
  else
  {
    return 0;
  }
}

void CTextureBundle::Cleanup()
{
  m_tbXBT.Cleanup();
  m_tbXPR.Cleanup();
  m_useXPR = m_useXBT = false;
}

void CTextureBundle::SetThemeBundle(bool themeBundle)
{
  m_tbXPR.SetThemeBundle(themeBundle);
  m_tbXBT.SetThemeBundle(themeBundle);
}

CStdString CTextureBundle::Normalize(const CStdString &name)
{
  return CTextureBundleXBT::Normalize(name);
}
