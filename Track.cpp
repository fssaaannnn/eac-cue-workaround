#include "Track.h"

Track::Track(uint32_t number, const std::string& title,
             const std::string& artist)
    : m_number(number), m_title(title), m_artist(artist) {}

Track::~Track() {}

uint32_t Track::number() const { return m_number; }

const std::string& Track::title() const { return m_title; }

const std::string& Track::artist() const { return m_artist; }
