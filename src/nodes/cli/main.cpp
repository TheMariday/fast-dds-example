#include "cli_node.h"
#include <toml.hpp>
#include <filesystem>
#include <iostream>
#include "spdlog/spdlog.h"
#include "../../common/config.h"

std::string getOsName()
{
#ifdef _WIN64
	return "Windows 64-bit";
#elif _WIN32
	return "Windows 32-bit";
#elif __APPLE__ || __MACH__
	return "Mac OSX";
#elif __linux__
	return "Linux";
#elif __FreeBSD__
	return "FreeBSD";
#elif __unix || __unix__
	return "Unix";
#else
	return "Other";
#endif
}


int main(
	int argc,
	char** argv)
{
	spdlog::info("Starting publisher on {}", getOsName());

	toml::basic_value<toml::type_config> config = skyframe::get_config(argc, argv);

	CLIPublisher* cli_publisher = new CLIPublisher(config);

	if (cli_publisher->init())
	{
		cli_publisher->run();
	}
	delete cli_publisher;

	return 0;
}