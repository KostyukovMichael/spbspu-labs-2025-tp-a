#include "commandProcessor.hpp"

#include <iostream>
#include <limits>
#include <stdexcept>

#include "freqDict.hpp"

kostyukov::CommandProcessor::CommandProcessor(std::istream& in, std::ostream& out):
  in_(in),
  out_(out)
{
  add("getfreq", getFreq);
  add("top", top);
  add("bottom", bottom);
  add("listdicts", listDicts);
  add("finduniq", findUniq);
  add("findsame", findSame);
  add("rangefreq", rangeFreq);
  add("outrangefreq", outRangeFreq);
  add("help", printHelp);

  add("create", createDict);
  add("load", loadDict);
  add("delete", deleteDict);
  add("merge", merge);
  add("intersect", intersect);
  add("clear", clear);
  add("removebatch", removeBatch);
}

void kostyukov::CommandProcessor::add(const std::string& commandName, ModifyingCommand func)
{
  commands_[commandName] = std::bind(func, std::ref(in_), std::ref(out_), std::ref(dictManager_));
  return;
}

void kostyukov::CommandProcessor::add(const std::string& commandName, ConstCommand func)
{
  commands_[commandName] = std::bind(func, std::ref(in_), std::ref(out_), std::cref(dictManager_));
  return;
}

void kostyukov::CommandProcessor::add(const std::string& commandName, void (*func)(std::ostream&, const FreqDictManager&))
{
  commands_[commandName] = std::bind(func, std::ref(out_), std::cref(dictManager_));
  return;
}

void kostyukov::CommandProcessor::add(const std::string& commandName, void (*func)(std::ostream&))
{
    commands_[commandName] = std::bind(func, std::ref(out_));
    return;
}

void kostyukov::CommandProcessor::process()
{
  out_ << "Write help if you don't know what to do\n";
  std::string command;
  while (!(in_ >> command).eof())
  {
    try
    {
      commands_.at(command)();
      out_ << '\n';
    }
    catch (const std::out_of_range&)
    {
      out_ << "<INVALID COMMAND>\n";
    }
    catch (const std::exception& error)
    {
      out_ << "<ERROR: " << error.what() << ">\n";
    }
    if (in_.fail())
    {
      in_.clear(in_.rdstate() ^ std::ios::failbit);
      in_.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
    }
  }
}
