#ifndef COMMAND_PROCESSOR_HPP
#define COMMAND_PROCESSOR_HPP

#include <functional>
#include <iosfwd>
#include <map>
#include <string>

#include "freqDict.hpp"

namespace kostyukov
{
  class CommandProcessor
  {
    public:
      CommandProcessor(std::istream& in, std::ostream& out);
      void process();
    private:
      using ModifyingCommand = void (*)(std::istream&, std::ostream&, FreqDictManager&);
      using ConstCommand = void (*)(std::istream&, std::ostream&, const FreqDictManager&);
      void add(const std::string& commandName, ModifyingCommand func);
      void add(const std::string& commandName, ConstCommand func);
      void add(const std::string& commandName, void (*)(std::ostream&));
      void add(const std::string& commandName, void (*)(std::ostream&, const FreqDictManager&));
      std::map< std::string, std::function< void() > > commands_;
      FreqDictManager dictManager_;
      std::istream& in_;
      std::ostream& out_;
  };
}
#endif
