#include "cli.h"
#include <iostream>

std::string skyframe::cli::get_user_input()
{
	std::string user_message;
	std::cout << "Message: ";
	std::cin >> user_message;
	return user_message;
}
