#ifndef _TRACK_H_
#define _TRACK_H_

#include <string>

class Track {
   private:
    uint32_t m_number;
    std::string m_title;
    std::string m_artist;

   public:
    Track(uint32_t number, const std::string& title, const std::string& artist);
    ~Track();

    uint32_t number() const;
    const std::string& title() const;
    const std::string& artist() const;
};

#endif