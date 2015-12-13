/* Mql4j-util.cpp */
#include "stdafx.h"
#include "Mql4jUtil.h"

void mql4j::jvmStart() {
	if(!java::javaStart()) {
		exit(1);
	}
}

void mql4j::activemqSend(const string brokerURI, const bool useTopic, const string dest, const string message) {
	log::info(__FILE__, __LINE__, "Connecting " + brokerURI);
	void * activemq = amqConnect(toWArray(brokerURI));
	if(activemq == NULL) {
		log::error(__FILE__, __LINE__, "Failed to connect");
		exit(1);
	}
	void * destination = amqDest(activemq, toWArray(dest), useTopic);
	if(!amqSendMessage(destination, toWArray(message))) {
		log::error(__FILE__, __LINE__, "Failed to send message");
	} else {
		log::info(__FILE__, __LINE__, "Message sended");
	}
	amqClose(activemq);
}

void mql4j::activemqRecv(const string brokerURI, const bool useTopic, const string dest) {
	log::info(__FILE__, __LINE__, "Connecting " + brokerURI);
	void * activemq = amqConnect(toWArray(brokerURI));
	if(activemq == NULL) {
		log::error(__FILE__, __LINE__, "Failed to connect");
		exit(1);
	}
	void * destination = amqDest(activemq, toWArray(dest), useTopic);
	string message = toString(amqRecvMessage(destination));
	if(message.length() == 0) {
		log::warn(__FILE__, __LINE__, "No message retrieved");
	} else {
		log::info(__FILE__, __LINE__, "Message retrieved: " + message);
	}
	amqClose(activemq);
}

void printHelp() {
	printf_s("Usage: \n");
	printf_s("  activemqSend <brokerURI> <topic|queue> <dest> <message>\n");
	printf_s("  activemqRecv <brokerURI> <topic|queue> <dest>\n");
	printf_s("  jvmStart\n");
	printf_s("  help\n");
	printf_s("\n");
	exit(1);
}

bool getDestType(const string t) {
	if(t.compare("topic") == 0) {
		return true;
	} else if(t.compare("queue") == 0) {
		return false;
	} else {
		mql4j::log::error(__FILE__, __LINE__, "Invalid destination type '" + t + "'. Needs to be 'topic' or 'queue'");
		exit(1);
	}
}

string getArg(const int argc, const char * argv[], const int num) {
	if(num >= argc) {
		printf_s("To few arguments!\nSee %s help\n", argv[0]);
		exit(1);
	}
	return string(argv[num]);
}

int main(int argc, const char* argv[]) {
	if(argc < 2) {
		printHelp();
	}
	const string func = getArg(argc, argv, 1);
	if(func.compare("help") == 0) {
		printHelp();
	} else if(func.compare("activemqSend") == 0) {
		const string brokerURI = getArg(argc, argv, 2);
		const bool destType = getDestType(getArg(argc, argv, 3));
		const string dest = getArg(argc, argv, 4);
		const string message = getArg(argc, argv, 5);
		mql4j::activemqSend(brokerURI, destType, dest , message);
	} else if(func.compare("activemqRecv") == 0) {
		const string brokerURI = getArg(argc, argv, 2);
		const bool destType = getDestType(getArg(argc, argv, 3));
		const string dest = getArg(argc, argv, 4);
		mql4j::activemqRecv(brokerURI, destType, dest);
	} else if(func.compare("jvmStart") == 0) {
		mql4j::jvmStart();
	} else {
		printHelp();
	}
	return 0;
}
