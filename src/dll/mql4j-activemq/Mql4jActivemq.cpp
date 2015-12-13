/* Mql4Activemq.cpp */
#include "stdafx.h"
#include "Mql4jActivemq.h"

MQL4JACTIVEMQ_API void * mql4j::amqConnect(const wchar_t * brokerUri) {
	log::trace(__FILE__, __LINE__, "Connect");
	Activemq::instance();
	ActivemqConnection * con = new ActivemqConnection(toString(brokerUri));
	if(con == nullptr || !con->connect()) {
		return nullptr;
	} else {
		return con;
	}
}

MQL4JACTIVEMQ_API void * mql4j::amqDest(void * connection, const wchar_t * name, const bool useTopic) {
	log::trace(__FILE__, __LINE__, "Select destination");
	if(connection == nullptr) {
		return nullptr;
	}
	ActivemqConnection * con = static_cast<ActivemqConnection *>(connection);
	if(con == nullptr) {
		return nullptr;
	}
	if(useTopic) {
		return new ActivemqDestination(toString(name), ActivemqDestination::Type::topic, con->getSession());
	} else {
		return new ActivemqDestination(toString(name), ActivemqDestination::Type::queue, con->getSession());
	}
}

MQL4JACTIVEMQ_API bool mql4j::amqSendMessage(void * dest, const wchar_t * msg) {
	log::trace(__FILE__, __LINE__, "Send message");
	if(dest == nullptr) {
		return false;
	} else {
		ActivemqDestination * dst = static_cast<ActivemqDestination *>(dest);
		return dst->sendMessage(toString(msg));
	}
}

MQL4JACTIVEMQ_API wchar_t * mql4j::amqRecvMessage(void * dest) {
	log::trace(__FILE__, __LINE__, "Retrieve message");
	if(dest == nullptr) {
		return nullptr;
	}
	ActivemqDestination * dst = static_cast<ActivemqDestination *>(dest);
	if(dst == nullptr) {
		return nullptr;
	}
	return toWArray(dst->retrieveMessage());
}

MQL4JACTIVEMQ_API void mql4j::amqClose(void * connection) {
	log::trace(__FILE__, __LINE__, "Close");
	if(connection != nullptr) {
		ActivemqConnection * con = static_cast<ActivemqConnection *>(connection);
		if(con != nullptr) {
			delete con;
		}
	}
	Activemq::instance()->release();
}
