#include "msgthread.h"

cMsgThread::cMsgThread(const char* _msg)
    : cThread()
{
  msg = _msg;
}

void cMsgThread::Action(void)
{
  char buffer[1000];
  strcpy(buffer, "svdrpsend.pl MESG ");
  strcat(buffer, msg);
  //Skins.Message(mtInfo, msg, 20);
  SystemExec(buffer);
}

void cMsgThread::SetMessage(const char* _msg)
{
  msg = _msg;
}
