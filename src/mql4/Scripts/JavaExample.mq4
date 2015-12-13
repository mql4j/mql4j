//+------------------------------------------------------------------+
//|                                                            Mql4J |
//|     Copyright 2015, Michael Schmidt, Apache License, Version 2.0 |
//|     http://www.apache.org/licenses/LICENSE-2.0                   |
//|                                             http://www.mql4j.com |
//+------------------------------------------------------------------+
#property copyright "Copyright 2015 Michael Schmidt, Apache License, Version 2.0 http://www.apache.org/licenses/LICENSE-2.0"
#property link      "http://www.mql4j.com"
#property version   "1.00"
#property description "This example script calls one of the following java methods:"
#property description ""
#property description "        com.mql4j.examples.Codec.md5(String str);"
#property description "        com.mql4j.examples.Codec.sha2(String str);";
#property description "        com.mql4j.examples.Codec.uuid(String str);";
#property description "        com.mql4j.examples.Network.ping(String host);";
#property description "        com.mql4j.examples.Network.host(String host);";
#property description "        com.mql4j.examples.System.exec(String cmd);";
#property strict
#property script_show_inputs
//--- include header(s)
#include <Mql4j.mqh>
//--- typedef
enum Example
  {
   CODEC_MD5,
   CODEC_SHA2,
   CODEC_UUID,
   NETWORK_PING,
   NETWORK_HOST,
   SYSTEM_EXEC
  };
//--- input parameter
input Example example=CODEC_MD5;
input string inputString="";
//+------------------------------------------------------------------+
//| Script program start function                                    |
//+------------------------------------------------------------------+
void OnStart()
  {
   if(StringLen(inputString)<1)
     {
      MessageBox("The inputString can not be empty","MQL4J Java",MB_OK|MB_ICONERROR);
      return;
     }

   if(!javaStatus())
     {
      if(javaStart())
        {
         Print("Mql4j service started");
        }
      else
        {
         MessageBox("Mql4j service start failed. See mql4j.log / mql4j.java.log for details","MQL4J Java Example",MB_OK|MB_ICONERROR);
         return;
        }
     }
   string className="";
   string methodName="";
   switch(example)
     {
      case CODEC_MD5:
         className="com.mql4j.examples.Codec";
         methodName="md5";
         break;
      case CODEC_SHA2:
         className="com.mql4j.examples.Codec";
         methodName="sha2";
         break;
      case CODEC_UUID:
         className="com.mql4j.examples.Codec";
         methodName="uuid";
         break;
      case NETWORK_PING:
         className="com.mql4j.examples.Network";
         methodName="ping";
         break;
      case NETWORK_HOST:
         className="com.mql4j.examples.Network";
         methodName="host";
         break;
      case SYSTEM_EXEC:
         className="com.mql4j.examples.System";
         methodName="exec";
         break;
     }
   PrintFormat("Calling java method %s.%s(%s);",className,methodName,inputString);
   string output=javaCall(className,methodName,inputString);
   if(StringLen(output)<1)
     {
      MessageBox("Call failed. See mql4j.log / mql4j.java.log for details","MQL4J Java Example",MB_OK|MB_ICONERROR);
     }
   else
     {
      PrintFormat("Result = %s",output);
      MessageBox(StringFormat("Result: %s",output),"MQL4J Java Example",MB_OK|MB_ICONINFORMATION);
     }
   return;
  }
//+------------------------------------------------------------------+
