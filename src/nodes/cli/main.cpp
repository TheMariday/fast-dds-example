#include "cli_node.h"
#include "config.hpp"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <iostream>
#include <memory>

int main(int argc, char **argv) {
  spdlog::info("Starting publisher...");

  skyframe::config config =
      skyframe::get_config(argc, argv);

  auto cli_publisher = std::make_unique<CLIPublisher>(config);

  if (cli_publisher->init()) {
    cli_publisher->run();
  }

  return 0;
}