/* Activemq.cpp */
#include "stdafx.h"
#include "Activemq.h"

mql4j::amq::Activemq * mql4j::amq::Activemq::_instance = 0;

mql4j::amq::Activemq::Activemq() {
	activemq::library::ActiveMQCPP::initializeLibrary();
}

mql4j::amq::Activemq::~Activemq() {
}

mql4j::amq::Activemq * mql4j::amq::Activemq::instance() {
	if(_instance == 0) {
		_instance = new Activemq();
		log::trace(__FILE__, __LINE__, "Instance created");
	}
	return _instance;
}

void mql4j::amq::Activemq::release() {
	if(_instance != 0) {
		delete _instance;
		_instance = 0;
		log::trace(__FILE__, __LINE__, "Instance released");
	}
}
