#ifndef _CLIPBOARDREADER_H_
#define _CLIPBOARDREADER_H_

#include <string>
#include <vector>

#include "Disc.h"

class ClipboardReader {
   private:
   public:
    ClipboardReader();
    ~ClipboardReader();

    Disc read(const std::string& path);
};

#endif