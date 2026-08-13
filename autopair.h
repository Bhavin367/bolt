#include <unordered_map>

static const std::unordered_map<char,char> AUTO_PAIRS = {
  {'(',')'},
  {'{','}'},
  {'[',']'}, 
  {'"', '"'},
  {'\'','\''},
};
