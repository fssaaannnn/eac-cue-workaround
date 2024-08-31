#include "ClipboardReader.h"

#include <cstring>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <stdexcept>

#define CD_ARTIST_TITLE_DELIMITER " - "
#define ARTIST_TITLE_DELIMITER " / "

ClipboardReader::ClipboardReader() {}

ClipboardReader::~ClipboardReader() {}

Disc ClipboardReader::read(const std::string& path) {
    if (!std::filesystem::exists(path)) {
        std::string errorMsg = "clipboard file: " + path + " does not exist";
        throw std::runtime_error(errorMsg);
    }

    std::ifstream clipboard(path);

    std::string firstLine;

    std::string cdArtist;
    std::string cdTitle;

    std::vector<Track> tracks;

    for (std::string line; std::getline(clipboard, line);) {
        line = line.substr(0, line.size() - 1);
        if (line.empty()) {
            continue;
        }

        if (firstLine.empty()) {
            firstLine = line;
            size_t delPos = firstLine.find(CD_ARTIST_TITLE_DELIMITER);
            if (delPos != std::string::npos) {
                cdArtist = firstLine.substr(0, delPos);
                cdTitle = firstLine.substr(
                    delPos + std::strlen(CD_ARTIST_TITLE_DELIMITER));
            }
            continue;
        }

        uint32_t number;
        std::string title;
        std::string artist;

        std::istringstream lineStream(line);
        std::string numberString;
        std::getline(lineStream, numberString, '\t');
        std::istringstream(numberString) >> number;

        std::string artistAndTitle;
        std::getline(lineStream, artistAndTitle, '\t');
        if (!artistAndTitle.empty()) {
            size_t delPos = artistAndTitle.find(ARTIST_TITLE_DELIMITER);
            if (delPos != std::string::npos) {
                artist = artistAndTitle.substr(0, delPos);
                title = artistAndTitle.substr(
                    delPos + std::strlen(ARTIST_TITLE_DELIMITER));
                tracks.emplace_back(Track(number, title, artist));
            }
        }
    }

    return Disc(cdTitle, cdArtist, tracks);
}
