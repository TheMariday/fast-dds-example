#include "PubListener.h"
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/core/status/PublicationMatchedStatus.hpp>
#include <spdlog/spdlog.h>

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
