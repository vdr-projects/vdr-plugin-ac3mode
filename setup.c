/*
 * setup.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 * Implements VDR setup
 *
 * $Id$
 */

#include <vdr/plugin.h>
#include "setup.h"

cAC3SetupMenu::cAC3SetupMenu()
{
  const char* hint = tr("Settings will be applied on VDR restart");
  char buffer[200];
  strcpy(buffer, "----- ");
  strcat(buffer, hint);
  strcat(buffer, " -----");
  cOsdItem *hintItem = new cOsdItem(buffer);
  hintItem->SetSelectable(false);
  Add( hintItem );

  settings = *cAC3PluginSetupSettings::GetCurrentSettings();
  Add( new cMenuEditBoolItem(tr("Notify on AC3 Mode Change"), &settings.modeChangeNotification) );
  Add( new cMenuEditBoolItem(tr("Display Main Menu entry"), &settings.displayMainMenuEntry) );
}

void cAC3SetupMenu::Store(void)
{
  *cAC3PluginSetupSettings::GetCurrentSettings() = settings;
  SetupStore("ModeChangeNotification", settings.modeChangeNotification);
  SetupStore("DisplayMainMenuEntry", settings.displayMainMenuEntry);
}
