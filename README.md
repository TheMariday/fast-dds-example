# DDS tutorial, the Mariday way:

## Installation:

Firstly on windows, this only works in visual studio, bear that in mind.

Download the installer from [here](https://www.eprosima.com/product-download) and then restart. usual stuff

More than that everything //should// just work!

## Acronym Zone:


- DDS - Data Distrobition Service, top level get shit to places.
- DCPS - Data Centric Publish Subscribe, middle layer stuff.
- RTPS - Real Time Publish Subscribe, how do you want that delivered layer.
- UDP - User Datagram Protocol, send it now, don't care how it arrives.
- TCP - Transport Control Protocol, send it reliably please.
- SHM - Shared Memory, Why send things over the network when you can share a raw memory pointer?
- QOS - Quality of service, how certain do you want to be that the message has been recieved?
- IDL - Interface Description Language, \*gestures to data\* what the hell is this?
- CDR - Common Data Representation, Okay how do we pack this for transport (serialisation)


## Terminology Zone:

- Domain - All things in a domain can see and talk, domains have ID's, i.e. the `0` in `DomainParticipantFactory::get_instance()->create_participant(0, participantQos);`
- 