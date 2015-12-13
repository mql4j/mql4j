/**
 *	Mql4j
 *
 *	Mql4j is a free and open source library written to create projects and code
 *	in java programming language in MetaQuotes MetaTrader 4 trading solution.
 *
 *	Copyright 2015 Michael Schmidt (michael . schmidt at mql4j . com)
 *	Licensed under the Apache License, Version 2.0 (the "License");
 *	you may not use this file except in compliance with the License.
 *	You may obtain a copy of the License at
 *
 *		http://www.apache.org/licenses/LICENSE-2.0
 *
 *	Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 */

#pragma once
#ifdef _DEBUG
	#define CRTDBG_MAP_ALLOC
#endif
#include "..\mql4j-activemq\Mql4jActivemq.h"
#include "..\mql4j-common\Mql4jLog.h"
#include "..\mql4j-common\Mql4jString.h"
#include "..\mql4j-java\Mql4jJava.h"

using namespace std;

namespace mql4j {
	/**
	 * jvmStart
	 *
	 * Start jvm
	 */
	void jvmStart();

	/**
	 * activemqSend
	 *
	 * Send a message to a running activemq topic / queue
	 *
	 * @param  brokerURI ActiveMQ URI to connect to broker. For details
	 *                   visit http://activemq.apache.org/broker-uri.html
	 * @param  useTopic  false for queue
	 *                   true  for topic
	 * @param  dest      Name of queue or topic
	 * @param  message   string
	 */
	void activemqSend(const string brokerURI, const bool useTopic, const string dest, const string message);

	/**
	 * activemqRecv
	 *
	 * Retrieve and display a message from a running activemq topic / queue
	 *
	 * @param  brokerURI ActiveMQ URI to connect to broker. For details
	 *                   visit http://activemq.apache.org/broker-uri.html
	 * @param  useTopic  false for queue
	 *                   true  for topic
	 * @param  dest      Name of queue or topic
	 */
	void activemqRecv(const string brokerURI, const bool useTopic, const string dest);
}
