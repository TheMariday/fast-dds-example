#pragma once
#include "string_message/string_messagePubSubTypes.hpp"
#include <chrono>
#include <thread>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#include "config.hpp"

using namespace eprosima::fastdds::dds;


class SubListener : public DataReaderListener
{
public:

	SubListener();

	~SubListener() override;

	void on_subscription_matched(DataReader*, const SubscriptionMatchedStatus& info) override;

	void on_data_available(DataReader* reader) override;
};

class UISubscriber
{

public:

	UISubscriber(skyframe::config config);

	virtual ~UISubscriber();

	bool init();

	void run();

private:

	DomainParticipant* participant_;

	Subscriber* subscriber_;

	DataReader* reader_;

	Topic* topic_;

	TypeSupport type_;

	SubListener listener_;
	
	skyframe::config config_;
};