/* Mql4jJava.cpp */
#include "stdafx.h"
#include "Mql4jJava.h"

MQL4J_API bool mql4j::java::javaStart() {
	if(!java::JavaJvm::instance()->start()) {
		return false;
	}
	JNIEnv * env = JavaJvm::instance()->getEnv();
	jobjectArray arg = env->NewObjectArray(1, env->FindClass("java/lang/String"), env->NewStringUTF("start"));
	if(!JavaExecutor::callMain(env, MQL4J_JAVA_LAUNCHER_CLASS, arg)) {
		return false;
	}
	return true;
}

MQL4J_API bool mql4j::java::javaStop() {
	log::warn(__FILE__, __LINE__, "Unloading JVM is not possible. You need to restart the terminal");
	return true;
}

MQL4J_API bool mql4j::java::javaStatus() {
	return JavaJvm::instance()->isRunning();
}

MQL4J_API wchar_t * mql4j::java::javaCall(wchar_t * className, wchar_t * methodName, wchar_t * arg) {
	JNIEnv * env = JavaJvm::instance()->getEnv();
	string classNameStr = toString(className);
	string methodNameStr = toString(methodName);
	string argStr = toString(arg);
	string result = JavaExecutor::call(JavaJvm::instance()->getEnv(), classNameStr, methodNameStr, argStr);
	log::debug(__FILE__, __LINE__, "Call " + classNameStr + " " + methodNameStr + "(" + argStr + ") return " + result);
	return toWArray(result);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	return true;
}
