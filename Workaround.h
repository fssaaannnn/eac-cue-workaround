#ifndef _WORKAROUND_H_
#define _WORKAROUND_H_

#include <string>

class Workaround {
   private:
    std::string m_cuePath;
    std::string m_clipboardPath;

   public:
    Workaround(const std::string& cuePath, const std::string& clipboardPath);
    ~Workaround();

    void fillSheetFromClipboard(bool removeComposer);
};

#endif