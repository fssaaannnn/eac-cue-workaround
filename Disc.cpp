#include "Disc.h"

Disc::Disc(const std::string& title, const std::string& artist,
           std::vector<Track> tracks)
    : m_title(title), m_artist(artist), m_tracks(tracks) {}

Disc::~Disc() {}

const std::string& Disc::title() { return m_title; }

const std::string& Disc::artist() { return m_artist; }

const Track& Disc::track(size_t index) { return m_tracks.at(index); }
