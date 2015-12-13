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
//--- include
#include <Mql4j.mqh>
//+------------------------------------------------------------------+
//| Script program start function                                    |
//+------------------------------------------------------------------+
void OnStart()
  {
   CMql4j *mql4j=new CMql4j();
   if(mql4j.getServiceStatus()==MQL4J_START)
     {
      MessageBox("Service is already running","MQL4J",MB_OK|MB_ICONERROR);
     }
   else if(!mql4j.startService())
     {
      MessageBox("Service start failed! See mql4j.log file for details","MQL4J",MB_OK|MB_ICONERROR);
     }
   else
     {
      MessageBox("Service started","MQL4J",MB_OK|MB_ICONINFORMATION);
     }
   delete mql4j;
  }
//+------------------------------------------------------------------+
