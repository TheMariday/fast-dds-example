#include "string_message/string_message.hpp"

#include <atomic>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/topic/Topic.hpp>

#include <fastdds/dds/publisher/PublisherListener.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <toml.hpp>

#include "PubListener.hpp"

using namespace eprosima::fastdds::dds;

class CLIPublisher {
public:
  CLIPublisher(toml::basic_value<toml::type_config> config);

  virtual ~CLIPublisher();

  bool init();

  void run();

private:
  DomainParticipant *participant_;

  Publisher *publisher_;

  Topic *command_topic_;

  DataWriter *command_writer_;

  TypeSupport command_type_;

  PubListener command_listener_;

  toml::basic_value<toml::type_config> config_;
};