#include "stdafx.h"
#include "ActivemqDestination.h"

mql4j::amq::ActivemqDestination::ActivemqDestination(const string name, const Type type, Session * session) {
	this->session = session;
	try {
		string log = "Select destination ";
		switch(type) {
			case Type::queue:
				destination = session->createQueue(name);
				log += "Queue";
				break;
			case Type::topic:
				destination = session->createTopic(name);
				log += "Topic";
				break;
		}
		log += " '" + name + "' ";
		producer = session->createProducer(destination);
		consumer = session->createConsumer(destination);
		if(ACTIVEMQ_DEST_PERSISTENT) {
			producer->setDeliveryMode(DeliveryMode::NON_PERSISTENT);
			log += "(persistent) ";
		}
		log::debug(__FILE__, __LINE__, log);
	} catch(CMSException& e) {
		e.printStackTrace();
	}
}

mql4j::amq::ActivemqDestination::~ActivemqDestination() {
	try {
		producer->close();
	} catch(CMSException& e) {
		log::warn(__FILE__, __LINE__, "Failed to close producer: " + e.getMessage());
		e.printStackTrace();
	}
	try {
		consumer->close();
	} catch(CMSException& e) {
		log::warn(__FILE__, __LINE__, "Failed to close consumer: " + e.getMessage());
		e.printStackTrace();
	}
}

bool mql4j::amq::ActivemqDestination::sendMessage(const string str) {
	try {
		TextMessage* message = session->createTextMessage(str);
		producer->send(message);
		delete message;
		log::debug(__FILE__, __LINE__, "Sended message (" + to_string(str.length()) + " bytes)");
		return true;
	} catch(CMSException& e) {
		log::warn(__FILE__, __LINE__, "Failed to send message: " + e.getMessage());
		e.printStackTrace();
		return false;
	}
}

string mql4j::amq::ActivemqDestination::retrieveMessage() {
	try {
		const Message * message = consumer->receive();
		if(message == NULL) {
			log::warn(__FILE__, __LINE__, "Retrieved empty message");
			return string();
		}
		const TextMessage* textMessage = dynamic_cast<const TextMessage*>(message);
		if(textMessage == NULL) {
			log::warn(__FILE__, __LINE__, "Retrieved message is not a textMessage");
			return string();
		}
		string str = textMessage->getText();
		log::debug(__FILE__, __LINE__, "Retrieved message (" + to_string(str.length()) + " bytes)");
		return str;
	} catch(CMSException& e) {
		log::warn(__FILE__, __LINE__, "Failed to retrieve message: " + e.getMessage());
		e.printStackTrace();
		return string();
	}
}

string mql4j::amq::ActivemqDestination::retrieveMessage(const long timeoutMillis) {
	long start = (long) System::currentTimeMillis();
	while(System::currentTimeMillis() < start + timeoutMillis) {
		try {
			const Message * message = consumer->receiveNoWait();
			if(message == NULL) {
				Sleep(ACTIVEMQ_DEST_RECV_SLEEP_MILLIS);
				continue;
			}
			const TextMessage* textMessage = dynamic_cast<const TextMessage*>(message);
			if(textMessage == NULL) {
				log::warn(__FILE__, __LINE__, "Retrieved message is not a textMessage");
				return string();
			}
			string str = textMessage->getText();
			log::debug(__FILE__, __LINE__, "Retrieved message (" + to_string(str.length()) + " bytes)");
			return str;
		} catch(CMSException& e) {
			log::warn(__FILE__, __LINE__, "Failed to retrieve message: " + e.getMessage());
			e.printStackTrace();
		}
	}
	log::debug(__FILE__, __LINE__, "Retrieve timeout");
	return string();
}
