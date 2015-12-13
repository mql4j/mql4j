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
#include "ActivemqDestination.h"
#include <activemq/core/ActiveMQConnectionFactory.h>
#include <activemq/util/Config.h>
#include <activemq/library/ActiveMQCPP.h>
#include <cms/Connection.h>
#include <cms/Session.h>
#include <cms/TextMessage.h>
#include <decaf/lang/System.h>

using namespace activemq;
using namespace activemq::core;
using namespace decaf;
using namespace decaf::lang;
using namespace cms;
using namespace std;

namespace mql4j {
	namespace amq {
		class ActivemqConnection {
		  private:
			string brokerURI;
			bool transactions;
			Connection * connection;
			Session * session;
		  public:
			/**
			 * Constructor
			 *
			 * @param brokerURI ActiveMQ URI to connect to broker. For details
			 *                  visit http://activemq.apache.org/broker-uri.html
			 */
			ActivemqConnection(const string brokerURI);

			/**
			 * Destructor
			 */
			~ActivemqConnection();

			/**
			 * connect
			 *
			 * Connect to activemq broker
			 *
			 * @return true on success, false on any failure
			 */
			bool connect();

			/**
			 * isConnect
			 *
			 * Check if connected to broker
			 *
			 * @return true if connection to broker is esteblished, elsewhere false
			 */
			bool isConnected();

			/**
			 * createDestination
			 *
			 * Creates a destination object to a queue / topic
			 *
			 * @param  name of queue or topic
			 * @param  type queue / topic
			 *
			 * @return Object of class ActivemqDestination
			 */
			ActivemqDestination * createDestination(const string name, ActivemqDestination::Type type);

			/**
			 * getSession
			 *
			 * Get connection session
			 *
			 * @return Connection session
			 */
			Session * getSession();
		};
	}
}
