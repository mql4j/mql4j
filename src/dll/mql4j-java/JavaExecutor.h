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
#include "JavaException.h"
#include "JavaMethodDesc.h"
#include "..\mql4j-common\Mql4jLog.h"
#include <cstdarg>
#include <jni.h>

using namespace std;

namespace mql4j {
	namespace java {
		/**
		 * Class JavaExcutor
		 *
		 * Executes calls of native java methods
		 */
		class JavaExecutor {
		  public:
			/**
			 * callMain
			 *
			 * Java call a class main method. The main method needs the default
			 * layout:
			 *		static void main(String[] args)
			 *
			 * @param  env       Java JVM environment
			 * @param  className Full path of java class including package
			 *                   Example: com.foo.Bar
			 * @param  args      Java array of string objects
			 *
			 * @return true on success, false on any failure
			 */
			static bool callMain(JNIEnv * env, string className, jobjectArray args);

			/**
			 * call
			 *
			 * Java call a static method with layout:
			 *		static String methodName(String arg)
			 */
			static string call(JNIEnv * env, string className, string methodName, string arg);
		};
	}
}
