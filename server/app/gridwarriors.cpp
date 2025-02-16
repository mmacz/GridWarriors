#include "gridwarriors.h"
#include "logger.h"
#include "connection_manager.h"

int main(int argc, char **argv) {
  Modules::Logger logger{};
  Modules::Config cmCfg { 8880, Modules::DEFAULT_BUFFER_SIZE, &logger };
  Modules::ConnectionManager cm{cmCfg};
  cm.run();
  return 0;
}

