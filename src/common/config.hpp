#pragma once

#include <toml.hpp>
#include <spdlog/spdlog.h>

namespace skyframe {
	using config = toml::basic_value<toml::type_config>;

	inline config get_config(int argc, char** argv) {

		std::string config_name = "";
		if (argc >= 2) {
			config_name = argv[1];
		}

		if (config_name.empty()) {
			auto config_path = std::filesystem::path{ CONFIG_ROOT } / PROJECT_NAME_STRING / "default.toml";
			spdlog::info("Config not provided, loading default from {}", config_path.string());
			config c = toml::parse(config_path, toml::spec::v(1, 1, 0));
			spdlog::info("Config successfully loaded");
			return c;
		}

		try {
			auto config_path = std::filesystem::path{ config_name };
			spdlog::info("Config attempting to load {}", config_path.string());
			config c = toml::parse(config_path, toml::spec::v(1, 1, 0));
			spdlog::info("Config successfully loaded");
			return c;
		}
		catch (toml::file_io_error e) {
			auto config_path = std::filesystem::path{ CONFIG_ROOT } / PROJECT_NAME_STRING / (config_name + ".toml");
			spdlog::info("Config attempting to load {}", config_path.string());
			config c = toml::parse(config_path, toml::spec::v(1, 1, 0));
			spdlog::info("Config successfully loaded");
			return c;
		}

		throw std::runtime_error("Failed to get config");
	}
}