//+------------------------------------------------------------------+
//|                                                            Mql4J |
//|     Copyright 2015, Michael Schmidt, Apache License, Version 2.0 |
//|     http://www.apache.org/licenses/LICENSE-2.0                   |
//|                                             http://www.mql4j.com |
//+------------------------------------------------------------------+
#property copyright "Copyright 2015 Michael Schmidt, Apache License, Version 2.0 http://www.apache.org/licenses/LICENSE-2.0"
#property link      "http://www.mql4j.com"
#property version   "1.00"
#property strict
#property script_show_inputs
//--- include Mql4activemq header
#include <Mql4j.mqh>
//--- input parameter
input int numMessages=1000;
//+------------------------------------------------------------------+
//| Script program start function                                    |
//+------------------------------------------------------------------+
void OnStart() 
  {
   CMql4j *mql4j=new CMql4j();
   if(!mql4j.getServiceStatus()) 
     {
      Print("Starting service");
      if(!mql4j.startService()) 
        {
         delete mql4j;
         return;
        }
     }
   long time =(long) TimeLocal();
   for(int i=0; i<numMessages; i++) 
     {
      if(!mql4j.ping()) 
        {
         delete mql4j;
         return;
        }
     }
   time=((long) TimeLocal())-time;
   double msgTime=(double) time/(double) numMessages*1000.0;
   PrintFormat("%d messages sended in %d sec (%.1f ms per message)",numMessages,time,msgTime);
   delete mql4j;
  }
//+------------------------------------------------------------------+
