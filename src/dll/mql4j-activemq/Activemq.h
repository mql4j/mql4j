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
#include "ActivemqConnection.h"
#include "../mql4j-common/Mql4jLog.h"
#include <activemq/library/ActiveMQCPP.h>

using namespace std;
using namespace mql4j::amq;

namespace mql4j {
	namespace amq {
		/**
		 * Class Activemq
		 *
		 * Singleton
		 * Manages start and release of activemq-cpp library
		 */
		class Activemq {
		  private:
			static Activemq * _instance;
		  protected:
			/**
			 * Constructor
			 */
			Activemq();

			/**
			 * Destructor
			 */
			virtual ~Activemq();
		  public:
			/**
			 * instance
			 *
			 * Get singleton instance
			 *
			 * @return instance of class Activemq
			 */
			static Activemq * instance();

			/**
			 * release
			 *
			 * Release singleton instance
			 */
			void release();
		};
	}
}
