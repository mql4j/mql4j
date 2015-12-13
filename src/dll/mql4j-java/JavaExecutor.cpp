/* JavaExecutor.cpp */
#include "stdafx.h"
#include "JavaExecutor.h"

bool mql4j::java::JavaExecutor::callMain(JNIEnv * env, string className, jobjectArray args) {
	if(env == NULL) {
		log::error(__FILE__, __LINE__, "Invalid JVM environment");
		return false;
	}
	JavaMethodDesc * desc = new JavaMethodDesc(className, "main");
	desc->addArray(Jid::String);
	desc->setReturn(Jid::Void);
	jclass cls = env->FindClass(desc->getClassName().c_str());
	if(cls == NULL) {
		log::error(__FILE__, __LINE__, "Java class '" + desc->getClassName() + "' not found");
		delete desc;
		return false;
	}
	jmethodID mid = env->GetStaticMethodID(cls, desc->getMethodName().c_str(), desc->getSignature().c_str());
	if(mid == NULL) {
		log::error(__FILE__, __LINE__, "Java method '" + desc->getMethodName() + " " + desc->getSignature() +
		           "' not found in java class '" + desc->getClassName() + "'");
		delete desc;
		return false;
	}
	env->CallStaticVoidMethod(cls, mid, args);
	if(env->ExceptionCheck()) {
		JavaException * exception = JavaException::create(env);
		log::warn(__FILE__, __LINE__, "Java call '" + desc->getClassName() + " " + desc->getMethodName() + " " +
		          desc->getSignature() + "' throws an excaption:");
		exception->printMessage();
		delete exception;
		delete desc;
		return false;
	} else {
		log::info(__FILE__, __LINE__, "Java call '" + desc->getClassName() + " " + desc->getMethodName() + " " +
		          desc->getSignature() + "' succeeded");
		delete desc;
		return true;
	}
}

string mql4j::java::JavaExecutor::call(JNIEnv * env, string className, string methodName, string arg) {
	if(env == NULL) {
		log::error(__FILE__, __LINE__, "Invalid JVM environment");
		return string();
	}
	JavaMethodDesc * desc = new JavaMethodDesc(className, methodName);
	desc->add(Jid::String);
	desc->setReturn(Jid::String);
	jclass cls = env->FindClass(desc->getClassName().c_str());
	if(cls == NULL) {
		log::error(__FILE__, __LINE__, "Java class '" + desc->getClassName() + "' not found");
		return string();
	}
	jmethodID mid = env->GetStaticMethodID(cls, desc->getMethodName().c_str(), desc->getSignature().c_str());
	if(mid == NULL) {
		log::error(__FILE__, __LINE__, "Java method '" + desc->getMethodName() + " " + desc->getSignature() +
		           "' not found in java class '" + desc->getClassName() + "'");
		return string();
	}
	jstring resultObj = (jstring) env->CallStaticObjectMethod(cls, mid, env->NewStringUTF(arg.c_str()));
	if(env->ExceptionCheck()) {
		JavaException * exception = JavaException::create(env);
		log::warn(__FILE__, __LINE__, "Java call '" + desc->getClassName()  + " " + desc->getMethodName() + " " +
		          desc->getSignature() + "' throws an excaption:");
		exception->printMessage();
		delete exception;
		return string();
	}
	log::info(__FILE__, __LINE__, "Java call '" + desc->getClassName() + " " + desc->getMethodName() + " " +
	          desc->getSignature() + "' succeeded");
	const char* resultStr = env->GetStringUTFChars(resultObj, 0);
	string str = string(resultStr);
	env->ReleaseStringUTFChars(resultObj, resultStr);
	env->DeleteLocalRef(resultObj);
	return str;
}
