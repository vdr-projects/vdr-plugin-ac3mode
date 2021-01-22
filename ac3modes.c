#include "ac3modes.h"

const char* GetAC3ModeName(uchar mode)
{
  const char* ac3ModeNames[] = {"PCM Sound.",
				"AC3 Mono.",
				"Dolby Digital 2.0",
				"3 Front Channels",
				"2 Front, 1 Rear",
				"3 Front, 1 Rear",
				"2 Front, 2 Rear",
				"Dolby Digital 5.1" };
  
  if (mode < sizeof(ac3ModeNames) / sizeof(ac3ModeNames[0]))
    return ac3ModeNames[mode];
  else
    return "Undefined Mode.";
}
