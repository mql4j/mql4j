//+------------------------------------------------------------------+
//|                                                            Mql4j |
//|     Copyright 2015, Michael Schmidt, Apache License, Version 2.0 |
//|     http://www.apache.org/licenses/LICENSE-2.0                   |
//|                                             http://www.mql4j.com |
//+------------------------------------------------------------------+
#include <Mql4jMessage.mqh>
//+------------------------------------------------------------------+
//| Import mql4j-java.dll                                            |
//+------------------------------------------------------------------+
#import "mql4j-activemq.dll"
   int      amqConnect(string brokerUri);
   int      amqDest(int connection,string name,const bool useTopic);
   bool     amqSendMessage(int dest,string msg);
   string   amqRecvMessage(int dest);
#import
//+------------------------------------------------------------------+
//| Import mql4j-activemq.dll                                        |
//+------------------------------------------------------------------+
#import "mql4j-java.dll"
   bool     javaStart();
   bool     javaStatus();
   string   javaCall(string className, string methodName, string arg);
#import
//+------------------------------------------------------------------+
//| Constants                                                        |
//+------------------------------------------------------------------+
#define MQL4J_START                 true
#define MQL4J_STOP                  false
#define MQL4J_EVENT_QUEUE           "com.mql4j.java.events"
#define MQL4J_ACTIVEMQ_BROKER_URI   "tcp://localhost:61616"
//+------------------------------------------------------------------+
//| Class                                                            |
//|        CMql4j                                                    |
//|                                                                  |
//| Controll and communiation with mql4j services                    |
//+------------------------------------------------------------------+
class CMql4j {
private:
   int mActivemq;
   int mJavaEventQueue;
public:
   CMql4j(void);
   ~CMql4j(void);
   bool getServiceStatus();
   bool startService();
   bool ping();
   string javaExec(string pClassName, string pMethodName, string pArg);
private:
   bool queueConnect();
   bool queueSend(CMql4jMessage * pMessage);
};
//+------------------------------------------------------------------+
//| Method  Constructor                                              |
//+------------------------------------------------------------------+
CMql4j::CMql4j() {
   mActivemq = NULL;
   mJavaEventQueue = NULL;
}
//+------------------------------------------------------------------+
//| Method Destructor                                                |
//+------------------------------------------------------------------+
CMql4j::~CMql4j() {
   mActivemq = NULL;
   mJavaEventQueue = NULL;
}
//+------------------------------------------------------------------+
//| Method  getServiceStatus                                         |
//+------------------------------------------------------------------+
bool CMql4j::getServiceStatus() {
   return javaStatus();
}
//+------------------------------------------------------------------+
//| Method  startService                                             |
//+------------------------------------------------------------------+
bool CMql4j::startService() {
   if(getServiceStatus()) {
      Print("startService failed: Java service is allready running");
      return false;
   } else if(!javaStart()) {
      Print("startService failed: See mql4j.log / mql4j.java.log for details");
      return false;
   } else {
      Print("startService succeeded");
      return true;
   }
}
//+------------------------------------------------------------------+
//| Method  ping                                                     |
//+------------------------------------------------------------------+
bool CMql4j::ping() {
   CMql4jMessage * messageObject = new CMql4jMessage("PING");
   if(!queueSend(messageObject)) {
      Print("ping failed: See mql4j.log / mql4j.java.log for details");
      delete messageObject;
      return false;
   } else {
      //Print("ping: succeeded");
      delete messageObject;
      return true;
   }
}
//+------------------------------------------------------------------+
//| Method  javaExec                                                 |
//+------------------------------------------------------------------+
string CMql4j::javaExec(string pClassName, string pMethodName, string pArg) {
   if(!getServiceStatus()) {
      PrintFormat("Java exec '%s.%s' failed: Java service is not running", pClassName, pMethodName);
      return NULL;
   }
   return javaCall(pClassName, pMethodName, pArg);
}
//+------------------------------------------------------------------+
//| Method  queueConnect                                             |
//+------------------------------------------------------------------+
bool CMql4j::queueConnect() {
   if(mActivemq != NULL && mJavaEventQueue != NULL) {
      return true;
   }
   mActivemq = amqConnect(MQL4J_ACTIVEMQ_BROKER_URI);
   if(mActivemq == NULL) {
      Print("Connect to queue failed: See mql4j.log / mql4j.java.log for details");
      return false;
   }
   mJavaEventQueue = amqDest(mActivemq,MQL4J_EVENT_QUEUE,false);
   if(mJavaEventQueue == NULL) {
      Print("Select queue destination failed: See mql4j.log / mql4j.java.log for details");
      return false;
   }
   Print("Connect to queue succeeded");
   return true;
}
//+------------------------------------------------------------------+
//| Method  queueSend                                                |
//+------------------------------------------------------------------+
bool CMql4j::queueSend(CMql4jMessage * pMessage) {
   if(!queueConnect()) {
      return false;
   } else if(!amqSendMessage(mJavaEventQueue, pMessage.toJson())) {
      Print("Send message to queue failed: See mql4j.log / mql4j.java.log for details");
      return false;
   } else {
      //Print("Send message to queue succeeded");
      return true;
   }
}
//+------------------------------------------------------------------+
