# DDS tutorial, the Mariday way:

## Installation:

Firstly on windows, this only works in visual studio, bear that in mind. Otherwise it will fallover when it comes to finding openssl

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



## Oh oh bloody fastddsgen

- Install specifically v19 of the Java SDK from [here](https://www.oracle.com/java/technologies/javase/jdk19-archive-downloads.html) < Very important
- `git clone --recursive https://github.com/eProsima/Fast-DDS-Gen.git fastddsgen`
- Run `gradlew.bat assemble`
- Run `./fastddsgen path/to/my/interface.idl`

## install fast-dds monitor

- Download from [here](https://www.eprosima.com/product-download) (only 3.1 has a windows installer btw)
- Okay that was straightforward
- I spoke too soon, this is basically useless unless you re-compile Fast-DDS with `STATISTICS=ON` as otherwise you can't see any graphable info, just who's publishing and who's subscribing