//+------------------------------------------------------------------+
//|                                             Mql4J - Mql4activemq |
//|     Copyright 2015, Michael Schmidt, Apache License, Version 2.0 |
//|     http://www.apache.org/licenses/LICENSE-2.0                   |
//|                                             http://www.mql4j.com |
//+------------------------------------------------------------------+
#property copyright "Copyright 2015, GPL v3.0: http://www.gnu.org/licenses/gpl-3.0-standalone.html"
#property link      "https://www.mql4j.com"
#property version   "1.00"
#property strict
#property script_show_inputs
//--- include Mql4activemq header
#include <Mql4j.mqh>
//--- type DestType
enum DestType {QUEUE, TOPIC};
//--- input parameter
input string brokerURI="tcp://localhost:61616";
input string destName="TEST.FOO";
input DestType destType=TOPIC;
input string message="Mql4activemq rocks!";
input int messageCount=10;
//+------------------------------------------------------------------+
//| Script program start function                                    |
//+------------------------------------------------------------------+
void OnStart()
  {
//--- Connect
   Print("> Connecting");
   int amq=amqConnect(brokerURI);
   if(amq==NULL)
     {
      PrintFormat("Failed to connect to activemq broker '%s'",brokerURI);
      return;
     }
   else
     {
      PrintFormat("Successfully connect to activemq broker '%s'",brokerURI);
     }
//--- Destination
   Print("> Set destination");
   int dest = NULL;
   switch(destType)
     {
      case QUEUE:
         dest=amqDest(amq,destName,false);
         break;
      case TOPIC:
         dest=amqDest(amq,destName,true);
         break;
     }
   if(dest==NULL)
     {
      PrintFormat("Failed to set destination '%s'",destName);
      return;
     }
   else
     {
      PrintFormat("Successfully set destination '%s'",destName);
     }
//--- Send a given amount of messages
   Print("> Sending messages");
   for(int i=0; i<messageCount; i++)
     {
      string sendMessage=StringFormat("%s #%d",message,i+1);
      if(!amqSendMessage(dest,sendMessage))
        {
         PrintFormat("Failed to send message '%s'",sendMessage);
         return;
        }
      else
        {
         PrintFormat("Send message '%s'",sendMessage);
        }
     }
   PrintFormat("Successfully send %d message(s)",messageCount);
//--- Retrieve messages
   Print("> Retrieve messages");
   for(int i=0; i<messageCount; i++)
     {
      string recvMessage=amqRecvMessage(dest);
      if(StringLen(recvMessage)<2)
        {
         Print("Failed to retrieve message");
         //         return;
        }
      else
        {
         PrintFormat("Retreived message '%s'",recvMessage);
        }
     }
   PrintFormat("Successfully retreived %d message(s)",messageCount);
  }
//+------------------------------------------------------------------+
