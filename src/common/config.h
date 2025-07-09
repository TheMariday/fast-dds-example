#include <toml.hpp>


namespace skyframe {
	typedef toml::basic_value<toml::type_config> config;

	config get_config(int argc, char** argv);
}