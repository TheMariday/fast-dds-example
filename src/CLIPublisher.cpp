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
	, topic_(nullptr)
	, writer_(nullptr)
	, type_(new StringMessagePubSubType())
{
}

CLIPublisher::~CLIPublisher()
{
	if (writer_ != nullptr)
	{
		publisher_->delete_datawriter(writer_);
	}
	if (publisher_ != nullptr)
	{
		participant_->delete_publisher(publisher_);
	}
	if (topic_ != nullptr)
	{
		participant_->delete_topic(topic_);
	}
	DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool CLIPublisher::init()
{

	DomainParticipantQos participantQos;
	participantQos.name("Participant_publisher");
	participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

	if (participant_ == nullptr)
	{
		return false;
	}

	type_.register_type(participant_);

	topic_ = participant_->create_topic("command", "StringMessage", TOPIC_QOS_DEFAULT);

	if (topic_ == nullptr)
	{
		return false;
	}

	publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);

	if (publisher_ == nullptr)
	{
		return false;
	}

	writer_ = publisher_->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT, &listener_);

	if (writer_ == nullptr)
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
		if (listener_.matched_ > 0)
		{
			StringMessage my_command;
			my_command.message(user_message);
			writer_->write(&my_command);
		}
	}
}

int main(
	int argc,
	char** argv)
{
	std::cout << "Starting publisher." << std::endl;

	auto cli_publisher = std::make_unique<CLIPublisher>();

	if (cli_publisher->init())
	{
		cli_publisher->run();
	}

	return 0;
}