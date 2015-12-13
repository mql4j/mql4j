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
 *  Unless required by applicable law or agreed to in writing, software
 *	distributed under the License is distributed on an "AS IS" BASIS,
 *	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *	See the License for the specific language governing permissions and
 *	limitations under the License.
 */

#pragma once
#ifdef MQL4J_EXPORTS
	#define MQL4J_API __declspec(dllexport)
#else
	#define MQL4J_API __declspec(dllimport)
#endif
#include "JavaJvm.h"
#include "JavaExecutor.h"
#include "JavaMethodDesc.h"
#include "..\mql4j-common\Mql4jLog.h"
#include "..\mql4j-common\Mql4jString.h"

#define MQL4J_JAVA_LAUNCHER_CLASS "com.mql4j.core.Mql4jService"

using namespace std;

namespace mql4j {
	namespace java {
		/**
		 * javaStart
		 *
		 * Start java jvm thread
		 *
		 * @return true on success, false on any failure
		 */
		MQL4J_API bool javaStart();

		/**
		 * javaStop
		 *
		 * Stop java jvm thread
		 *
		 * @return true on success, false on any failure
		 */
		MQL4J_API bool javaStop();

		/**
		 * javaStatus
		 *
		 * Status of java jvm thread
		 *
		 * @return true if running, elsewhere false
		 */
		MQL4J_API bool javaStatus();

		/**
		 * javaCall
		 *
		 * Call a static java function which needs one argument.
		 * The argument and the return value is on object of class
		 * com.java.lang.String
		 */
		MQL4J_API wchar_t * javaCall(wchar_t * className, wchar_t * methodName, wchar_t * arg);
	}
}
