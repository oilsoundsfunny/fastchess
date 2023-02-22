#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "engine_config.h"

namespace CMD
{

struct Parameter
{
    std::string longName;
    std::string shortName;
    std::string defaultValue;
    std::string minLimit;
    std::string maxLimit;
};
struct OpeningOptions
{
    std::string file;
    // TODO use enums for this
    std::string format;
    std::string order;
    int plies;
};

struct PgnOptions
{
    std::string file;
};

struct GameManagerOptions
{
    int games = 1;
    int rounds = 1;
    bool recover = false;
    bool repeat = false;
    int concurrency = 1;
    std::string eventName;
    OpeningOptions opening;
    PgnOptions pgn;
};

inline std::ostream &operator<<(std::ostream &os, const Parameter param)
{
    os << "longName" << param.longName << "shortName" << param.shortName << "default" << param.defaultValue << "min"
       << param.minLimit << "max" << param.maxLimit;

    return os;
}

class Options
{
  public:
    Options(int argc, char const *argv[]);

    std::vector<EngineConfiguration> getEngineConfig() const;

    GameManagerOptions getGameOptions() const;

  private:
    // Holds all the relevant settings for the handling of the games
    GameManagerOptions gameOptions;

    // Holds all the engines with their options
    std::vector<EngineConfiguration> configs;

    bool isEngineSettableOption(std::string stringFormat) const;

    TimeControl parseTc(const std::string tcString);

    // Generic function to parse option
    template <typename T> void parseOption(int &i, int argc, const char *argv[], T &optionValue);

    void parseOpeningOptions(int &i, int argc, char const *argv[]);

    void parseEngineParams(int &i, int argc, char const *argv[], EngineConfiguration &engine_params);
};

} // namespace CMD