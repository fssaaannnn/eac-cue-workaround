#include "Workaround.h"

#include <filesystem>
#include <fstream>
#include <regex>
#include <sstream>

#include "ClipboardReader.h"
#include "Disc.h"

Workaround::Workaround(const std::string& cuePath,
                       const std::string& clipboardPath)
    : m_cuePath(cuePath), m_clipboardPath(clipboardPath) {}

Workaround::~Workaround() {}

void Workaround::fillSheetFromClipboard(bool removeComposer) {
    if (!std::filesystem::exists(m_cuePath)) {
        std::string errorMsg = "cue sheet: " + m_cuePath + " does not exist";
        throw std::runtime_error(errorMsg);
    }
    Disc disc = ClipboardReader().read(m_clipboardPath);

    std::filesystem::path cuePath = std::filesystem::path(m_cuePath);
    std::filesystem::path fixedCuePath =
        cuePath.parent_path() / (std::string(cuePath.filename()) + ".fixed");

    std::ifstream cue(cuePath);
    std::ofstream fixedCue(fixedCuePath);

    bool isParsingTrack = false;
    uint32_t currentTrackNum = 0;

    const std::regex quoted("\"([^\"]*)\"");

    for (std::string line; std::getline(cue, line);) {
        line.push_back('\n');

        if (isParsingTrack) {
            if (line.find("TITLE") != std::string::npos) {
                std::string title =
                    '"' + disc.track(currentTrackNum - 1).title() + '"';
                fixedCue << std::regex_replace(line, quoted, title);
                continue;
            } else if (line.find("PERFORMER") != std::string::npos) {
                std::string artist =
                    '"' + disc.track(currentTrackNum - 1).artist() + '"';
                fixedCue << std::regex_replace(line, quoted, artist);
                continue;
            } else if (line.find("TRACK") != std::string::npos) {
                std::istringstream trackSs(line);
                std::string track;
                trackSs >> track;
                trackSs >> currentTrackNum;
            }
        } else {
            if (line.find("TITLE") != std::string::npos) {
                std::string title = '"' + disc.title() + '"';
                fixedCue << std::regex_replace(line, quoted, title);
                continue;
            } else if (line.find("PERFORMER") != std::string::npos) {
                std::string artist = '"' + disc.artist() + '"';
                fixedCue << std::regex_replace(line, quoted, artist);
                continue;
            } else if (line.find("FILE") != std::string::npos) {
                isParsingTrack = true;
            }
        }

        if (line.find("REM COMPOSER") != std::string::npos && removeComposer) {
            continue;
        }

        fixedCue << line;
    }
}
