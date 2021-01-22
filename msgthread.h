#ifndef _MSGTHREAD_H_
#define _MSGTHREAD_H_

#include <vdr/plugin.h>

class cMsgThread : public cThread {
private:
    const char *msg;
    
protected:
    virtual void Action(void);

public:
    cMsgThread(const char* _msg);
    
    void SetMessage(const char* _msg);
};

#endif //_MSGTHREAD_H_
