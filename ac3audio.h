#ifndef _AC3AUDIO_H_
#define _AC3AUDIO_H_

#include <vdr/audio.h>
#include "msgthread.h"

class cAC3ModeAudio : public cAudio {
private:
    enum { ac3_none = 0 };

    uchar ac3Mode;
    uchar ac3Modeold;
    bool modeChangeNotification;
    cMsgThread* msgThread;
    
    void setAC3Mode(uchar newMode);
    
public:
    cAC3ModeAudio(bool _ModeChangeNotification);
    
    virtual void Play(const uchar* Data, int Length, uchar Id);
    virtual void PlayTs(const uchar* Data, int Length);
    virtual void Mute(bool on);
    virtual void Clear(void);
    uchar getAC3Mode() { return ac3Mode; }
    void setModeChangeNotification(bool notify) { modeChangeNotification = notify; }
};

#endif //_AC3AUDIO_H_
