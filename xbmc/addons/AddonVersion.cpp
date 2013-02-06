

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "AddonVersion.h"
#include "guilib/LocalizeStrings.h"

namespace ADDON
{
  AddonVersion::AddonVersion(const CStdString& version)
  {
    m_originalVersion = version;
    if (m_originalVersion.IsEmpty())
      m_originalVersion = "0.0.0";
    const char *epoch_end = strchr(m_originalVersion.c_str(), ':');
    if (epoch_end != NULL)
      mEpoch = atoi(m_originalVersion.c_str());
    else
      mEpoch = 0;

    const char *upstream_start;
    if (epoch_end)
      upstream_start = epoch_end + 1;
    else
      upstream_start = m_originalVersion.c_str();

    const char *upstream_end = strrchr(upstream_start, '-');
    size_t upstream_size;
    if (upstream_end == NULL)
      upstream_size = strlen(upstream_start);
    else
      upstream_size = upstream_end - upstream_start;

    mUpstream = (char*) malloc(upstream_size + 1);
    strncpy(mUpstream, upstream_start, upstream_size);
    mUpstream[upstream_size] = '\0';

    if (upstream_end == NULL)
      mRevision = strdup("0");
    else
      mRevision = strdup(upstream_end + 1);
  }

  /**Compare two components of a Debian-style version.  Return -1, 0, or 1
   * if a is less than, equal to, or greater than b, respectively.
   */
  int AddonVersion::CompareComponent(const char *a, const char *b)
  {
    while (*a && *b)
    {
      while (*a && *b && !isdigit(*a) && !isdigit(*b))
      {
        if (*a != *b)
        {
          if (*a == '~') return -1;
          if (*b == '~') return 1;
          return *a < *b ? -1 : 1;
        }
        a++;
        b++;
      }
      if (*a && *b && (!isdigit(*a) || !isdigit(*b)))
      {
        if (*a == '~') return -1;
        if (*b == '~') return 1;
        return isdigit(*a) ? -1 : 1;
      }

      char *next_a, *next_b;
      long int num_a = strtol(a, &next_a, 10);
      long int num_b = strtol(b, &next_b, 10);
      if (num_a != num_b)
        return num_a < num_b ? -1 : 1;

      a = next_a;
      b = next_b;
    }
    if (!*a && !*b)
      return 0;
    if (*a)
      return *a == '~' ? -1 : 1;
    else
      return *b == '~' ? 1 : -1;
  }

  bool AddonVersion::operator<(const AddonVersion& other) const
  {
    if (Epoch() != other.Epoch())
      return Epoch() < other.Epoch();

    int result = CompareComponent(Upstream(), other.Upstream());
    if (result)
      return (-1 == result);

    return (-1 == CompareComponent(Revision(), other.Revision()));
  }

  CStdString AddonVersion::Print() const
  {
    CStdString out;
    out.Format("%s %s", g_localizeStrings.Get(24051), m_originalVersion); // "Version <str>"
    return CStdString(out);
  }

  bool AddonVersion::SplitFileName(CStdString& ID, CStdString& version,
                                   const CStdString& filename)
  {
    int dpos = filename.rfind("-");
    if (dpos < 0)
      return false;
    ID = filename.Mid(0,dpos);
    version = filename.Mid(dpos+1);
    version = version.Mid(0,version.size()-4);

    return true;
  }
}
