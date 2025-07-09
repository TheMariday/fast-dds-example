#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/core/status/PublicationMatchedStatus.hpp>
#include <atomic>

using namespace eprosima::fastdds::dds;

class PubListener : public DataWriterListener
{
public:

	PubListener();

	~PubListener() override;

	void on_publication_matched(DataWriter*, const PublicationMatchedStatus& info) override;

	std::atomic_int matched_;

};