/****************************************************************************
 * FCE Ultra 0.98.12
 * Nintendo Wii/Gamecube Port
 *
 * Tantric September 2008
 *
 * preferences.c
 *
 * Preferences save/load preferences utilities
 ****************************************************************************/

#include <gccore.h>
#include <stdio.h>
#include <string.h>
#include <ogcsys.h>
#include <mxml.h>

#include "menudraw.h"
#include "memcardop.h"
#include "fileop.h"
#include "fceugx.h"
#include "pad.h"

extern const unsigned short saveicon[1024];
extern int currconfig[4];

// button map configurations
extern unsigned int gcpadmap[];
extern unsigned int wmpadmap[];
extern unsigned int ccpadmap[];
extern unsigned int ncpadmap[];

char prefscomment[2][32];

/****************************************************************************
 * Prepare Preferences Data
 *
 * This sets up the save buffer for saving.
 ****************************************************************************/
mxml_node_t *xml;
mxml_node_t *data;
mxml_node_t *section;
mxml_node_t *item;
mxml_node_t *elem;

char temp[200];

const char * toStr(int i)
{
	sprintf(temp, "%d", i);
	return temp;
}

const char * FtoStr(float i)
{
	sprintf(temp, "%.2f", i);
	return temp;
}

void createXMLSection(const char * name, const char * description)
{
	section = mxmlNewElement(data, "section");
	mxmlElementSetAttr(section, "name", name);
	mxmlElementSetAttr(section, "description", description);
}

void createXMLSetting(const char * name, const char * description, const char * value)
{
	item = mxmlNewElement(section, "setting");
	mxmlElementSetAttr(item, "name", name);
	mxmlElementSetAttr(item, "value", value);
	mxmlElementSetAttr(item, "description", description);
}

void createXMLController(unsigned int controller[], const char * name, const char * description)
{
	item = mxmlNewElement(section, "controller");
	mxmlElementSetAttr(item, "name", name);
	mxmlElementSetAttr(item, "description", description);

	// create buttons
	int i;
	for(i=0; i < MAXJP; i++)
	{
		elem = mxmlNewElement(item, "button");
		mxmlElementSetAttr(elem, "number", toStr(i));
		mxmlElementSetAttr(elem, "assignment", toStr(controller[i]));
	}
}

const char * XMLSaveCallback(mxml_node_t *node, int where)
{
	const char *name;

	name = node->value.element.name;

	if(where == MXML_WS_BEFORE_CLOSE)
	{
		if(!strcmp(name, "file") || !strcmp(name, "section"))
			return ("\n");
		else if(!strcmp(name, "controller"))
			return ("\n\t");
	}
	if (where == MXML_WS_BEFORE_OPEN)
	{
		if(!strcmp(name, "file"))
			return ("\n");
		else if(!strcmp(name, "section"))
			return ("\n\n");
		else if(!strcmp(name, "setting") || !strcmp(name, "controller"))
			return ("\n\t");
		else if(!strcmp(name, "button"))
			return ("\n\t\t");
	}
	return (NULL);
}


int
preparePrefsData (int method)
{
	int offset = 0;
	memset (savebuffer, 0, SAVEBUFFERSIZE);

	// add save icon and comments for Memory Card saves
	if(method == METHOD_MC_SLOTA || method == METHOD_MC_SLOTB)
	{
		offset = sizeof (saveicon);

		// Copy in save icon
		memcpy (savebuffer, saveicon, offset);

		// And the comments
		sprintf (prefscomment[0], "%s Prefs", APPNAME);
		sprintf (prefscomment[1], "Preferences");
		memcpy (savebuffer + offset, prefscomment, 64);
		offset += 64;
	}

	xml = mxmlNewXML("1.0");
	mxmlSetWrapMargin(0); // disable line wrapping

	data = mxmlNewElement(xml, "file");
	mxmlElementSetAttr(data, "app",APPNAME);
	mxmlElementSetAttr(data, "version",APPVERSION);

	createXMLSection("File", "File Settings");

	createXMLSetting("AutoLoad", "Auto Load", toStr(GCSettings.AutoLoad));
	createXMLSetting("AutoSave", "Auto Save", toStr(GCSettings.AutoSave));
	createXMLSetting("LoadMethod", "Load Method", toStr(GCSettings.LoadMethod));
	createXMLSetting("SaveMethod", "Save Method", toStr(GCSettings.SaveMethod));
	createXMLSetting("LoadFolder", "Load Folder", GCSettings.LoadFolder);
	createXMLSetting("SaveFolder", "Save Folder", GCSettings.SaveFolder);
	//createXMLSetting("CheatFolder", "Cheats Folder", GCSettings.CheatFolder);
	createXMLSetting("VerifySaves", "Verify Memory Card Saves", toStr(GCSettings.VerifySaves));

	createXMLSection("Network", "Network Settings");

	createXMLSetting("smbip", "Share Computer IP", GCSettings.smbip);
	createXMLSetting("smbshare", "Share Name", GCSettings.smbshare);
	createXMLSetting("smbuser", "Share Username", GCSettings.smbuser);
	createXMLSetting("smbpwd", "Share Password", GCSettings.smbpwd);

	createXMLSection("Emulation", "Emulation Settings");

	createXMLSetting("currpal", "Palette", toStr(GCSettings.currpal));
	createXMLSetting("timing", "Timing", toStr(GCSettings.timing));
	createXMLSetting("slimit", "8 Sprite Limit", toStr(GCSettings.slimit));
	createXMLSetting("Zoom", "Zoom On/Off", toStr(GCSettings.Zoom));
	createXMLSetting("ZoomLevel", "Zoom Level", FtoStr(GCSettings.ZoomLevel));
	createXMLSetting("render", "Video Filtering", toStr(GCSettings.render));
	createXMLSetting("widescreen", "Aspect Ratio Correction", toStr(GCSettings.widescreen));
	createXMLSetting("hideoverscan", "Video Cropping", toStr(GCSettings.hideoverscan));

	createXMLSection("Controller", "Controller Settings");

	createXMLSetting("FourScore", "Four Score", toStr(GCSettings.FourScore));
	createXMLSetting("zapper", "Zapper", toStr(GCSettings.zapper));
	createXMLSetting("crosshair", "Zapper Crosshair", toStr(GCSettings.crosshair));
	createXMLController(gcpadmap, "gcpadmap", "GameCube Pad");
	createXMLController(wmpadmap, "wmpadmap", "Wiimote");
	createXMLController(ccpadmap, "ccpadmap", "Classic Controller");
	createXMLController(ncpadmap, "ncpadmap", "Nunchuk");

	int datasize = mxmlSaveString(xml, (char *)savebuffer, SAVEBUFFERSIZE, XMLSaveCallback);

	mxmlDelete(xml);

	return datasize;
}


/****************************************************************************
 * Decode Preferences Data
 ****************************************************************************/
void loadXMLSettingStr(char * var, const char * name, int maxsize)
{
	item = mxmlFindElement(xml, xml, "setting", "name", name, MXML_DESCEND);
	if(item)
		snprintf(var, maxsize, "%s", mxmlElementGetAttr(item, "value"));
}
void loadXMLSettingInt(int * var, const char * name)
{
	item = mxmlFindElement(xml, xml, "setting", "name", name, MXML_DESCEND);
	if(item)
		*var = atoi(mxmlElementGetAttr(item, "value"));
}
void loadXMLSettingFloat(float * var, const char * name)
{
	item = mxmlFindElement(xml, xml, "setting", "name", name, MXML_DESCEND);
	if(item)
		*var = atof(mxmlElementGetAttr(item, "value"));
}
void loadXMLSettingBool(bool * var, const char * name)
{
	item = mxmlFindElement(xml, xml, "setting", "name", name, MXML_DESCEND);
	if(item)
		*var = atoi(mxmlElementGetAttr(item, "value"));
}

void loadXMLController(unsigned int controller[], const char * name)

{
	item = mxmlFindElement(xml, xml, "controller", "name", name, MXML_DESCEND);

	if(item)
	{
		// populate buttons
		int i;
		for(i=0; i < MAXJP; i++)
		{
			elem = mxmlFindElement(item, xml, "button", "number", toStr(i), MXML_DESCEND);
			if(elem)
				controller[i] = atoi(mxmlElementGetAttr(elem, "assignment"));
		}
	}
}

bool
decodePrefsData (int method)
{
	int offset = 0;

	// skip save icon and comments for Memory Card saves
	if(method == METHOD_MC_SLOTA || method == METHOD_MC_SLOTB)
	{
		offset = sizeof (saveicon);
		offset += 64; // sizeof prefscomment
	}

	xml = mxmlLoadString(NULL, (char *)savebuffer+offset, MXML_TEXT_CALLBACK);

	// check settings version
	// we don't do anything with the version #, but we'll store it anyway
	char * version;
	item = mxmlFindElement(xml, xml, "file", "version", NULL, MXML_DESCEND);
	if(item) // a version entry exists
		version = (char *)mxmlElementGetAttr(item, "version");
	else // version # not found, must be invalid
		return false;

	// this code assumes version in format X.X.X
	// XX.X.X, X.XX.X, or X.X.XX will NOT work
	int verMajor = version[0] - '0';
	int verMinor = version[2] - '0';
	int verPoint = version[4] - '0';
	int curMajor = APPVERSION[0] - '0';
	int curMinor = APPVERSION[2] - '0';
	int curPoint = APPVERSION[4] - '0';

	// first we'll check that the versioning is valid
	if(!(verMajor >= 0 && verMajor <= 9 &&
		verMinor >= 0 && verMinor <= 9 &&
		verPoint >= 0 && verPoint <= 9))
		return false;

	if(verMajor == 2 && verPoint < 7) // less than version 2.0.7
		return false; // reset settings
	else if(verMajor > curMajor || verMinor > curMinor || verPoint > curPoint) // some future version
		return false; // reset settings

	// File Settings

	loadXMLSettingInt(&GCSettings.AutoLoad, "AutoLoad");
	loadXMLSettingInt(&GCSettings.AutoSave, "AutoSave");
	loadXMLSettingInt(&GCSettings.LoadMethod, "LoadMethod");
	loadXMLSettingInt(&GCSettings.SaveMethod, "SaveMethod");
	loadXMLSettingStr(GCSettings.LoadFolder, "LoadFolder", sizeof(GCSettings.LoadFolder));
	loadXMLSettingStr(GCSettings.SaveFolder, "SaveFolder", sizeof(GCSettings.SaveFolder));
	//loadXMLSettingStr(GCSettings.CheatFolder, "CheatFolder", sizeof(GCSettings.CheatFolder));
	loadXMLSettingInt(&GCSettings.VerifySaves, "VerifySaves");

	// Network Settings

	loadXMLSettingStr(GCSettings.smbip, "smbip", sizeof(GCSettings.smbip));
	loadXMLSettingStr(GCSettings.smbshare, "smbshare", sizeof(GCSettings.smbshare));
	loadXMLSettingStr(GCSettings.smbuser, "smbuser", sizeof(GCSettings.smbuser));
	loadXMLSettingStr(GCSettings.smbpwd, "smbpwd", sizeof(GCSettings.smbpwd));

	// Emulation Settings

	loadXMLSettingInt(&GCSettings.currpal, "currpal");
	loadXMLSettingInt(&GCSettings.timing, "timing");
	loadXMLSettingInt(&GCSettings.slimit, "slimit");
	loadXMLSettingInt(&GCSettings.Zoom, "Zoom");
	loadXMLSettingFloat(&GCSettings.ZoomLevel, "ZoomLevel");
	loadXMLSettingInt(&GCSettings.render, "render");
	loadXMLSettingInt(&GCSettings.widescreen, "widescreen");
	loadXMLSettingInt(&GCSettings.hideoverscan, "hideoverscan");

	// Controller Settings
	loadXMLSettingInt(&GCSettings.FourScore, "FSDisable");
	loadXMLSettingInt(&GCSettings.zapper, "zapper");
	loadXMLSettingInt(&GCSettings.crosshair, "crosshair");

	loadXMLController(gcpadmap, "gcpadmap");
	loadXMLController(wmpadmap, "wmpadmap");
	loadXMLController(ccpadmap, "ccpadmap");
	loadXMLController(ncpadmap, "ncpadmap");

	mxmlDelete(xml);

	return true;
}

/****************************************************************************
 * Save Preferences
 ***************************************************************************/
bool
SavePrefs (bool silent)
{
	char filepath[1024];
	int datasize;
	int offset = 0;

	// We'll save using the first available method (probably SD) since this
	// is the method preferences will be loaded from by default
	int method = autoSaveMethod(silent);

	if(!MakeFilePath(filepath, FILE_PREF, method))
		return false;

	if (!silent)
		ShowAction ("Saving preferences...");

	AllocSaveBuffer ();
	datasize = preparePrefsData (method);

	offset = SaveFile(filepath, datasize, method, silent);

	FreeSaveBuffer ();

	if (offset > 0)
	{
		if (!silent)
			WaitPrompt ("Preferences saved");
		return true;
	}
	return false;
}

/****************************************************************************
 * Load Preferences from specified method
 ***************************************************************************/
bool
LoadPrefsFromMethod (int method)
{
	bool retval = false;
	char filepath[1024];
	int offset = 0;

	if(!MakeFilePath(filepath, FILE_PREF, method))
		return false;

	AllocSaveBuffer ();

	offset = LoadFile(filepath, method, SILENT);

	if (offset > 0)
		retval = decodePrefsData (method);

	FreeSaveBuffer ();

	return retval;
}

/****************************************************************************
 * Load Preferences
 * Checks sources consecutively until we find a preference file
 ***************************************************************************/
bool LoadPrefs()
{
	ShowAction ("Loading preferences...");
	bool prefFound = false;
	if(ChangeInterface(METHOD_SD, SILENT))
		prefFound = LoadPrefsFromMethod(METHOD_SD);
	if(!prefFound && ChangeInterface(METHOD_USB, SILENT))
		prefFound = LoadPrefsFromMethod(METHOD_USB);
	if(!prefFound && TestCard(CARD_SLOTA, SILENT))
		prefFound = LoadPrefsFromMethod(METHOD_MC_SLOTA);
	if(!prefFound && TestCard(CARD_SLOTB, SILENT))
		prefFound = LoadPrefsFromMethod(METHOD_MC_SLOTB);
	if(!prefFound && ChangeInterface(METHOD_SMB, SILENT))
		prefFound = LoadPrefsFromMethod(METHOD_SMB);

	return prefFound;
}
