#ifndef _SETUP_H_
#define _SETUP_H_

class cAC3PluginSetupSettings 
{
public:
    int modeChangeNotification;
    int displayMainMenuEntry;
    
    cAC3PluginSetupSettings(void) 
    { 
	//define default values for parameters
	modeChangeNotification = true; 
	displayMainMenuEntry = true;
    }
    
    static cAC3PluginSetupSettings* GetCurrentSettings(void)
    {
	static cAC3PluginSetupSettings* actualSettings = NULL;
	
	if (!actualSettings)
	{
	    actualSettings = new cAC3PluginSetupSettings();
	}
	
	return actualSettings;
    }
};

class cAC3SetupMenu : public cMenuSetupPage {
protected:
    cAC3PluginSetupSettings settings;
    virtual void Store(void);

public:
    cAC3SetupMenu(void);
};

#endif //_SETUP_H_
