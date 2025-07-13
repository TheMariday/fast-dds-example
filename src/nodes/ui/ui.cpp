#include "ui.h"
#include <memory>
#include "string_message/string_messagePubSubTypes.hpp"

using namespace eprosima::fastdds::dds;


SubListener::SubListener()
{
}

SubListener::~SubListener()
{
}

void SubListener::on_subscription_matched(DataReader*, const SubscriptionMatchedStatus& info)
{
	if (info.current_count_change == 1)
	{
		std::cout << "Subscriber matched." << std::endl;
	}
	else if (info.current_count_change == -1)
	{
		std::cout << "Subscriber unmatched." << std::endl;
	}
	else
	{
		std::cout << info.current_count_change
			<< " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
	}
}

void SubListener::on_data_available(DataReader* reader)
{
	SampleInfo info;
	StringMessage command;
	if (reader->take_next_sample(&command, &info) == eprosima::fastdds::dds::RETCODE_OK)
	{
		if (info.valid_data)
		{
			std::cout << "Message: " << command.message() << std::endl;
		}
	}
}

UISubscriber::UISubscriber(skyframe::config config)
	: participant_(nullptr)
	, subscriber_(nullptr)
	, topic_(nullptr)
	, reader_(nullptr)
	, type_(new StringMessagePubSubType())
	, config_(config)
{
}

UISubscriber::~UISubscriber()
{
	if (reader_ != nullptr)
	{
		subscriber_->delete_datareader(reader_);
	}
	if (topic_ != nullptr)
	{
		participant_->delete_topic(topic_);
	}
	if (subscriber_ != nullptr)
	{
		participant_->delete_subscriber(subscriber_);
	}
	DomainParticipantFactory::get_instance()->delete_participant(participant_);
}


bool UISubscriber::init()
{
	DomainParticipantQos participantQos;
	participantQos.name(PROJECT_NAME_STRING);
	participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

	if (participant_ == nullptr)
	{
		return false;
	}


	type_.register_type(participant_);

	auto command_topic_string =
		toml::find<std::string>(config_, "topics", "subscribe");

	topic_ = participant_->create_topic(command_topic_string, "StringMessage", TOPIC_QOS_DEFAULT);

	if (topic_ == nullptr)
	{
		return false;
	}


	subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);

	if (subscriber_ == nullptr)
	{
		return false;
	}


	reader_ = subscriber_->create_datareader(topic_, DATAREADER_QOS_DEFAULT, &listener_);

	if (reader_ == nullptr)
	{
		return false;
	}

	return true;
}


void UISubscriber::run()
{
	while (true)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
}