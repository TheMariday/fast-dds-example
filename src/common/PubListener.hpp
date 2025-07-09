#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/core/status/PublicationMatchedStatus.hpp>
#include <spdlog/spdlog.h>


#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/core/status/PublicationMatchedStatus.hpp>
#include <atomic>

using namespace eprosima::fastdds::dds;

class PubListener : public DataWriterListener
{
public:

	PubListener() : matched_(0)
	{
	};

	~PubListener() override 
	{
	};

	void on_publication_matched(DataWriter*, const PublicationMatchedStatus& info) override
	{
		if (info.current_count_change == 1)
		{
			matched_ = info.total_count;
			spdlog::info("Publisher matched.");
		}
		else if (info.current_count_change == -1)
		{
			matched_ = info.total_count;
			spdlog::info("Publisher unmatched.");
		}
		else
		{
			spdlog::error("{} is not a valid value for PublicationMatchedStatus current count change.", info.current_count_change);
		}
	}

	std::atomic_int matched_;

};