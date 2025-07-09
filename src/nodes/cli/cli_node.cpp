#include "cli_node.h"
#include "cli.h"

#include <thread>
#include <chrono>
#include <toml.hpp>
#include <spdlog/spdlog.h>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/qos/DomainParticipantQos.hpp>

#include "string_message/string_messagePubSubTypes.hpp"


CLIPublisher::CLIPublisher(toml::basic_value<toml::type_config> config)
	: participant_(nullptr)
	, publisher_(nullptr)
	, command_topic_(nullptr)
	, command_writer_(nullptr)
	, command_type_(new StringMessagePubSubType())
	, config_(config)
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
	participantQos.name(PROJECT_NAME_STRING);
	participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

	if (participant_ == nullptr)
	{
		return false;
	}

	command_type_.register_type(participant_);

	auto command_topic_string = toml::find<std::string>(config_, "topics", "publish");

	spdlog::info("Broadcasting commands on {}", command_topic_string);

	command_topic_ = participant_->create_topic(command_topic_string, "StringMessage", TOPIC_QOS_DEFAULT);

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
		while (command_listener_.matched_ == 0)
		{
			std::this_thread::sleep_for(std::chrono::seconds(1));
			spdlog::info("No one is listening, waiting...");
		}

		std::string user_message = skyframe::cli::get_user_input();

		if (command_listener_.matched_ > 0)
		{
			StringMessage my_command;
			my_command.message(user_message);
			command_writer_->write(&my_command);
		}
	}
}