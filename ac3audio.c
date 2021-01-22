#include <vdr/plugin.h>
#include "ac3audio.h"
#include "ac3modes.h"

cAC3ModeAudio::cAC3ModeAudio(bool _ModeChangeNotification)
    : cAudio()
{
  ac3Mode = ac3_none;
  ac3Modeold = ac3_none;
  msgThread = new cMsgThread(NULL);
  modeChangeNotification = _ModeChangeNotification;
}

void cAC3ModeAudio::Play(const uchar* Data, int Length, uchar Id)
{
  //only analyze every 10th package
  static uchar packages = 10;
    
  if (packages++ != 10)
    return;
  else
    packages = 0;
    
  if (0x80 <= Id && Id <= 0x87 || Id == 0xBD) { //AC3
    int written = Data[8] + 9; //skip PES header
	
    if (Id != 0xBD)
      written += 4; //skip AC3 bytes
	
    setAC3Mode( (written + 6 <= Length) ? Data[written + 6] >> 5 : ac3_none);
  }
  else
    setAC3Mode( ac3_none );
}

void cAC3ModeAudio::setAC3Mode(uchar newMode)
{
  if (newMode != ac3Mode && newMode != ac3Modeold)
  {
  ac3Modeold = newMode;
  }
  else
  {
  if (newMode != ac3Mode)
  {
    if (modeChangeNotification)
    {
      if (!msgThread->Active())
      {
        msgThread->SetMessage(GetAC3ModeName(newMode));
        msgThread->Start();
      }
      else
      {
        //virtual ignore the change of ac3 mode
        //and try to redisplay the state in a few seconds
        newMode = ac3Mode;
      }
    }
        
    ac3Mode = newMode;
  }
  }
}

void cAC3ModeAudio::PlayTs(const uchar* Data, int Length)
{
  //only analyze every 10th package
  static uchar packages = 10;

  if (packages++ != 10)
    return;
  else
    packages = 0;

  //only analyse if first packet (Payload=1)
  int packetnumber = ( Data[1] & ~0xbf );
  packetnumber = ( packetnumber>>6 );
  if ( packetnumber == 0 ) return;

    /* TS-Frame && Payload, correct AudioPID ? */
    if (Data[0] != 0x47 || !(Data[3] & 0x10)) {// || audiopid != ((Data[1] & 0x1f)<<8) + Data[2])) {
        return;
        }

    int offset = TS_SIZE - 1;

    if ((Data[1] & 0x40) == 0x40) {                                     // 1.TS-Frame
        offset = ((Data[3] & 0x20)>>4) ? Data[4] + 5 : 4;                               // Header+ADFL  
        if (Data[offset] == 0x00 && Data[offset+1] == 0x00 && Data[offset+2] == 0x01 && // PES-Startcode
            Data[offset+3] >= 0xc0 && Data[offset+3] <= 0xdf) {                         // PES-Audiostream MP1/2
            setAC3Mode( ac3_none );
            return;
            }
        }

  //the begin of PES-Header must be in the first 20 bytes (usally iffset 18)
  for (int i = 0; i < 20; i++) {
  if (Data[i] == 0x0b && Data[i+1] == 0x77) {
  offset = i;
  break; }
  }
  if ( offset == 0 ) return;

  //in byte 7 (offset+6) first 3 bits are AcMod
  int AcMod = ( Data[offset+6] & ~0x1f );
  AcMod = ( AcMod>>5 );

        // some extra checks
        if (Data[offset+4]>=230) return; // reserved

        setAC3Mode( AcMod );

}

void cAC3ModeAudio::Mute(bool on) 
{ 
  //ignore
}

void cAC3ModeAudio::Clear(void)
{
  //ignore
}
