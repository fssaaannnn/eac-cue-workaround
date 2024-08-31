#ifndef _DISC_H_
#define _DISC_H_

#include <vector>

#include "Track.h"

class Disc {
   private:
    std::string m_title;
    std::string m_artist;
    std::vector<Track> m_tracks;

   public:
    Disc(const std::string& title, const std::string& artist,
         std::vector<Track> tracks);
    ~Disc();

    const std::string& title();
    const std::string& artist();
    const Track& track(size_t index);
};

#endif