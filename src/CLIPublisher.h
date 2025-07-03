#include "types/string_message/string_message.hpp"

#include <atomic>

#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/core/status/PublicationMatchedStatus.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/topic/Topic.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/PublisherListener.hpp>

using namespace eprosima::fastdds::dds;

class PubListener : public DataWriterListener
{
public:

	PubListener();

	~PubListener() override;

	void on_publication_matched(DataWriter*, const PublicationMatchedStatus& info) override;

	std::atomic_int matched_;

};

class CLIPublisher
{
public:

	CLIPublisher();

	virtual ~CLIPublisher();

	bool init();

	void run();

private:

	DomainParticipant* participant_;

	Publisher* publisher_;

	Topic* topic_;

	DataWriter* writer_;

	TypeSupport type_;

	PubListener listener_;
};