#include "ui.h"
#include "config.hpp"
#include "spdlog/spdlog.h"
#include <filesystem>
#include <iostream>
#include <memory>

int main(
	int argc,
	char** argv)
{

	printf("something!!!");
	std::cout << "Starting subscriber" << std::endl;
	printf("something else!!!");

	skyframe::config config =
		skyframe::get_config(argc, argv);

	auto ui_subscriber = std::make_unique<UISubscriber>(config);

	if (ui_subscriber->init())
	{
		ui_subscriber->run();
	}

	return 0;
}