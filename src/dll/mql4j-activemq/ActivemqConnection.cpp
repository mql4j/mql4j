/* ActivemqConnection.cpp */
#include "stdafx.h"
#include "ActivemqConnection.h"

mql4j::amq::ActivemqConnection::ActivemqConnection(const string brokerURI) {
	this->brokerURI = brokerURI;
	this->connection = nullptr;
	this->session = nullptr;
}

mql4j::amq::ActivemqConnection::~ActivemqConnection() {
	try {
		if(session != nullptr) {
			session->close();
		}
		if(connection != nullptr) {
			connection->close();
		}
	} catch(CMSException& e) {
		e.printStackTrace();
	}
}

bool mql4j::amq::ActivemqConnection::connect() {
	if(isConnected()) {
		return false;
	}
	try {
		auto_ptr<ActiveMQConnectionFactory> connectionFactory(new ActiveMQConnectionFactory(brokerURI));
		connection = connectionFactory->createConnection();
		connection->start();
		session = connection->createSession(Session::AUTO_ACKNOWLEDGE);
		return true;
	} catch(CMSException& e) {
		e.printStackTrace();
		connection = nullptr;
		session = nullptr;
		return false;
	}
}

bool mql4j::amq::ActivemqConnection::isConnected() {
	if(connection == nullptr || session == nullptr) {
		return false;
	} else {
		return true;
	}
}

mql4j::amq::ActivemqDestination * mql4j::amq::ActivemqConnection::createDestination(const string name,
        ActivemqDestination::Type type) {
	if(!isConnected()) {
		return nullptr;
	}
	return new ActivemqDestination(name, type, session);
}

Session * mql4j::amq::ActivemqConnection::getSession() {
	return session;
}