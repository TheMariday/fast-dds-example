#include "cli_node.h"
#include "config.hpp"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <iostream>
#include <memory>
#include <toml.hpp>

int main(int argc, char **argv) {
  spdlog::info("Starting publisher");

  toml::basic_value<toml::type_config> config =
      skyframe::get_config(argc, argv);

  auto cli_publisher = std::make_unique<CLIPublisher>(config);

  if (cli_publisher->init()) {
    cli_publisher->run();
  }

  return 0;
}