//+------------------------------------------------------------------+
//|                                                            Mql4j |
//|     Copyright 2015, Michael Schmidt, Apache License, Version 2.0 |
//|     http://www.apache.org/licenses/LICENSE-2.0                   |
//|                                             http://www.mql4j.com |
//+------------------------------------------------------------------+
//| Class                                                            |
//|        CMql4jMessage                                             |
//|                                                                  |
//| Object for commands and data - mql to java and java to mql       |
//+------------------------------------------------------------------+
class CMql4jMessage {
private:
   string mCommand;
public:
   CMql4jMessage();
   CMql4jMessage(const string pCommand);
   ~CMql4jMessage();
   string getCommand();
   void setCommand(const string pCommand);
   string toJson();
};
//+------------------------------------------------------------------+
//| Method  Constructor                                              |
//+------------------------------------------------------------------+
CMql4jMessage::CMql4jMessage() {
   mCommand = NULL;
}
//+------------------------------------------------------------------+
//| Method  Constructor                                              |
//+------------------------------------------------------------------+
CMql4jMessage::CMql4jMessage(const string pCommand) {
   mCommand = pCommand;
}
//+------------------------------------------------------------------+
//| Method  Destructor                                               |
//+------------------------------------------------------------------+
CMql4jMessage::~CMql4jMessage() {
}
//+------------------------------------------------------------------+
//| Method  getCommand                                               |
//+------------------------------------------------------------------+
string CMql4jMessage::getCommand() {
   return mCommand;
}
//+------------------------------------------------------------------+
//| Method  setCommand                                               |
//+------------------------------------------------------------------+
void CMql4jMessage::setCommand(const string pCommand) {
   mCommand = pCommand;
}
//+------------------------------------------------------------------+
//| Method  toJson                                                   |
//+------------------------------------------------------------------+
string CMql4jMessage::toJson() {
   string json = StringConcatenate("{ \"command\": \"", mCommand, "\" }");
   return json;
}
//+------------------------------------------------------------------+
