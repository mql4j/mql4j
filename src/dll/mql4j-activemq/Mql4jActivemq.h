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

#ifdef MQL4JACTIVEMQ_EXPORTS
	#define MQL4JACTIVEMQ_API __declspec(dllexport)
#else
	#define MQL4JACTIVEMQ_API __declspec(dllimport)
#endif
#include "Activemq.h"
#include "ActivemqConnection.h"
#include "ActivemqDestination.h"
#include "../mql4j-common/Mql4jString.h"

using namespace std;

namespace mql4j {
	/**
	 * amqConnect
	 *
	 * Connect to an activemq broker
	 *
	 * @param  brokerURI   See activemq documentation
	 *                     Example: tcp://localhost:61616
	 *
	 * @return pointer to ActivemqConnection object or NULL at failure
	 */
	MQL4JACTIVEMQ_API void * amqConnect(const wchar_t * brokerUri);

	/**
	 * amqDest
	 *
	 * Create an ActiveMQ destinaion (queue or topic) object
	 *
	 * @param  connection  See activemq documentation
	 * @param  name        Name of topic or queue
	 * @param  useTopic    Set true for topic and false for queue
	 *
	 * @return pointer to ActivemqDestination object
	 */
	MQL4JACTIVEMQ_API void * amqDest(void * connection, const wchar_t * name, const bool useTopic);

	/**
	 * amqSendMessage
	 *
	 * Send a message to an activemq queue or topic
	 *
	 * @param  dest         Pointer created by amq_dest
	 * @param  msg          Message string
	 *
	 * @return true on success, false on any failure
	 */
	MQL4JACTIVEMQ_API bool amqSendMessage(void * dest, const wchar_t * msg);

	/**
	 * amqRecvMessage
	 *
	 * Retrieve a message from an activemq queue or topic
	 *
	 * @param  connection   Pointer created by amq_connect
	 * @param  dest         Pointer created by amq_dest
	 * @param  timeout      For sync mode (blocking) set to 0
	 *                      For async mode (non blocking) set the wait timeout in
	 *                      millisecounds
	 *
	 * @return retrieved message or empty string on failure or timeout
	 */
	MQL4JACTIVEMQ_API wchar_t * amqRecvMessage(void * dest);

	/**
	 * amqClose
	 *
	 * Close connection to activemq broker
	 *
	 * @param  connection   Pointer created by amq_connect
	 *
	 * @return retrieved message or empty string on failure or timeout
	 */
	MQL4JACTIVEMQ_API void amqClose(void * connection);
}
