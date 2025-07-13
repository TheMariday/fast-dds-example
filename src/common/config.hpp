#include <toml.hpp>

namespace skyframe {
	typedef toml::basic_value<toml::type_config> config;

	config get_config(int argc, char** argv) {

		std::string config_name = "";
		if (argc >= 2) {
			config_name = argv[1];
		}

		if (config_name.empty()) {
			auto config_path = std::filesystem::path{ CONFIG_ROOT } / PROJECT_NAME_STRING / "default.toml";
			//spdlog::info("config path set to {}", config_path.c_str());
			return toml::parse(config_path, toml::spec::v(1, 1, 0));
		}

		try {
			auto config_path = std::filesystem::path{ config_name };
			return toml::parse(config_path, toml::spec::v(1, 1, 0));
		}
		catch (toml::file_io_error e) {
			auto config_path = std::filesystem::path{ CONFIG_ROOT } / PROJECT_NAME_STRING / (config_name + ".toml");
			return toml::parse(config_path, toml::spec::v(1, 1, 0));
		}

		throw std::runtime_error("Failed to get config");
	}
}