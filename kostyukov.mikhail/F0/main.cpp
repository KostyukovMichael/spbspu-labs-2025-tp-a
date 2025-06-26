#include <iostream>

#include "commandProcessor.hpp"

int main()
{
  using namespace kostyukov;
  CommandProcessor processor(std::cin, std::cout);
  processor.process();
  return 0;
}
