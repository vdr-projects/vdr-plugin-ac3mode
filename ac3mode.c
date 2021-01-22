/*
 * ac3mode.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#include <vdr/plugin.h>
#include "ac3audio.h"
#include "ac3modes.h"
#include "setup.h"
//#include "i18n.h"

static const char *VERSION        = "0.1";
static const char *DESCRIPTION    = "Displays currently active AC3-Mode.";

class cPluginAc3mode : public cPlugin {
private:
  // Add any member variables or functions you may need here.
  cAC3ModeAudio* ac3Audio;

public:
  cPluginAc3mode(void);
  virtual ~cPluginAc3mode();
  virtual const char *Version(void) { return VERSION; }
  virtual const char *Description(void) { return DESCRIPTION; }
  virtual const char *CommandLineHelp(void);
  virtual bool ProcessArgs(int argc, char *argv[]);
  virtual bool Initialize(void);
  virtual bool Start(void);
  virtual void Stop(void);
  virtual void Housekeeping(void);
  virtual const char *MainMenuEntry(void);
  virtual cOsdObject *MainMenuAction(void);
  virtual cMenuSetupPage *SetupMenu(void);
  virtual bool SetupParse(const char *Name, const char *Value);
  };

cPluginAc3mode::cPluginAc3mode(void)
{
  // Initialize any member variables here.
  ac3Audio = NULL;
}

const char* cPluginAc3mode::MainMenuEntry(void)
{
  if (cAC3PluginSetupSettings::GetCurrentSettings()->displayMainMenuEntry)
    return tr("AC3 Mode");
  else
    return NULL;
}

cPluginAc3mode::~cPluginAc3mode()
{
  // Clean up after yourself!
}

const char *cPluginAc3mode::CommandLineHelp(void)
{
  // Return a string that describes all known command line options.
  return NULL;
}

bool cPluginAc3mode::ProcessArgs(int argc, char *argv[])
{
  // Implement command line argument processing here if applicable.
  return true;
}

bool cPluginAc3mode::Initialize(void)
{
  // register language codes
//  RegisterI18n(Phrases);

  // Create Audio-Object, which will show AC3 mode. Object will self-register.
  if (ac3Audio == NULL)
    ac3Audio = new cAC3ModeAudio( cAC3PluginSetupSettings::GetCurrentSettings()->modeChangeNotification);

  return true;
}

bool cPluginAc3mode::Start(void)
{
  // Start any background activities the plugin shall perform.
  return true;
}

void cPluginAc3mode::Stop(void)
{
  // Stop any background activities the plugin shall perform.
  //ac3Audio = NULL;
}

void cPluginAc3mode::Housekeeping(void)
{
  // Perform any cleanup or other regular tasks.
}

cOsdObject *cPluginAc3mode::MainMenuAction(void)
{
  // Perform the action when selected from the main VDR menu.
  if (!ac3Audio)
    ac3Audio = new cAC3ModeAudio(cAC3PluginSetupSettings::GetCurrentSettings()->modeChangeNotification);
  
  if (ac3Audio)
  {
    Skins.Message(mtInfo, GetAC3ModeName( ac3Audio->getAC3Mode() ), 10);
  }

  return NULL;
}

cMenuSetupPage *cPluginAc3mode::SetupMenu(void)
{
  // Return a setup menu in case the plugin supports one.
  return new cAC3SetupMenu();
}

bool cPluginAc3mode::SetupParse(const char *Name, const char *Value)
{
  // Parse your own setup parameters and store their values.
  cAC3PluginSetupSettings *settings = cAC3PluginSetupSettings::GetCurrentSettings();
  if (!strcasecmp(Name, "ModeChangeNotification"))
    settings->modeChangeNotification = atoi(Value);
  else if (!strcasecmp(Name, "DisplayMainMenuEntry"))
    settings->displayMainMenuEntry = atoi(Value);
  else
    return false;
  
  return true;
}

VDRPLUGINCREATOR(cPluginAc3mode); // Don't touch this!
