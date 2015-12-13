/**
 *	Mql4jActiveMQ
 *
 *	This is an implementation of the activemq-cpp library for MetaTrader 4
 *	to be used in MQL4 code.
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
#include "../mql4j-common/Mql4jLog.h"
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/transport/DefaultTransportListener.h>
#include <activemq/util/Config.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <decaf/lang/System.h>

using namespace activemq;
using namespace activemq::core;
using namespace activemq::transport;
using namespace decaf;
using namespace decaf::lang;
using namespace cms;
using namespace std;

#define ACTIVEMQ_DEST_PERSISTENT false
#define ACTIVEMQ_DEST_RECV_SLEEP_MILLIS 10

namespace mql4j {
	namespace amq {
		/**
		 * Class ActivemqDestination
		 *
		 * Destination for consumer / producer for queue / topic
		 */
		class ActivemqDestination {
		  public:
			/**
			 * Type
			 *
			 * Type of destination (queue / topic
			 */
			enum class Type { queue, topic };
		  private:
			Session * session;
			Destination * destination;
			MessageProducer * producer;
			MessageConsumer * consumer;
		  public:
			/**
			 * Constructor
			 *
			 * @param name    Queue or topic name
			 * @param type    Queue / topic
			 * @param session Connection session created by class ActivemqConnection
			 */
			ActivemqDestination(const string name, const Type type, Session * session);

			/**
			 * Destructor
			 */
			~ActivemqDestination();

			/**
			 * sendMessage
			 *
			 * Send a message to a queue or topic
			 *
			 * @param  str Message to send
			 *
			 * @return true on success or false on failure
			 */
			bool sendMessage(const string str);

			/**
			 * retrieveMessage
			 *
			 * Retrieve a message from queue or topic
			 * This method is blocking. It will wait for a message
			 *
			 * @return string Message
			 */
			string retrieveMessage();

			/**
			 * retrieveMessage
			 *
			 * Retrieve a message from queue or topic
			 * This method waits a given time for a message.
			 *
			 * @param  timeoutMillis Sets the timeout in milliseconds
			 *
			 * @return string Message on success or a string with zero
			 *                on timeout or any other failure
			 */
			string retrieveMessage(const long timeoutMillis);
		};
	}
}
