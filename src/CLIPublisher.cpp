#include "CLIPublisher.h"
#include <memory>

#include "types/string_message/string_messagePubSubTypes.hpp"
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>

using namespace eprosima::fastdds::dds;

PubListener::PubListener()
	: matched_(0)
{
};

PubListener::~PubListener()
{
}

void PubListener::on_publication_matched(DataWriter*, const PublicationMatchedStatus& info)
{
	if (info.current_count_change == 1)
	{
		matched_ = info.total_count;
		std::cout << "Publisher matched." << std::endl;
	}
	else if (info.current_count_change == -1)
	{
		matched_ = info.total_count;
		std::cout << "Publisher unmatched." << std::endl;
	}
	else
	{
		std::cout << info.current_count_change
			<< " is not a valid value for PublicationMatchedStatus current count change." << std::endl;
	}
}


CLIPublisher::CLIPublisher()
	: participant_(nullptr)
	, publisher_(nullptr)
	, command_topic_(nullptr)
	, command_writer_(nullptr)
	, command_type_(new StringMessagePubSubType())
{
}

CLIPublisher::~CLIPublisher()
{
	if (command_writer_ != nullptr)
	{
		publisher_->delete_datawriter(command_writer_);
	}
	if (publisher_ != nullptr)
	{
		participant_->delete_publisher(publisher_);
	}
	if (command_topic_ != nullptr)
	{
		participant_->delete_topic(command_topic_);
	}
	DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool CLIPublisher::init()
{

	DomainParticipantQos participantQos;
	participantQos.name("CLI_Publisher");
	participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

	if (participant_ == nullptr)
	{
		return false;
	}

	command_type_.register_type(participant_);

	command_topic_ = participant_->create_topic("command", "StringMessage", TOPIC_QOS_DEFAULT);

	if (command_topic_ == nullptr)
	{
		return false;
	}

	publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);

	if (publisher_ == nullptr)
	{
		return false;
	}

	command_writer_ = publisher_->create_datawriter(command_topic_, DATAWRITER_QOS_DEFAULT, &command_listener_);

	if (command_writer_ == nullptr)
	{
		return false;
	}
	return true;
}

void  CLIPublisher::run()
{
	while (true)
	{
		std::string user_message;
		std::cout << "Message: ";
		std::cin >> user_message;
		if (command_listener_.matched_ > 0)
		{
			StringMessage my_command;
			my_command.message(user_message);
			command_writer_->write(&my_command);
		}
	}
}

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
	std::cout << "Starting publisher on " << getOsName() << std::endl;

	CLIPublisher* cli_publisher = new CLIPublisher();

	if (cli_publisher->init())
	{
		cli_publisher->run();
	}
	delete cli_publisher;

	return 0;
}