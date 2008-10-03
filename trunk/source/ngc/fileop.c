/****************************************************************************
 * FCE Ultra 0.98.12
 * Nintendo Wii/Gamecube Port
 *
 * Tantric September 2008
 *
 * fileop.c
 *
 * File operations
 ****************************************************************************/

#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ogcsys.h>
#include <zlib.h>

#include "common.h"
#include "fceuconfig.h"
#include "fileop.h"
#include "gcunzip.h"
#include "menudraw.h"
#include "filesel.h"

FILE * filehandle;

/****************************************************************************
 * fat_is_mounted
 * to check whether FAT media are detected.
 ****************************************************************************/

bool FatIsMounted(PARTITION_INTERFACE partition) {
    char prefix[] = "fatX:/";
    prefix[3] = partition + '0';
    DIR_ITER *dir = diropen(prefix);
    if (dir) {
        dirclose(dir);
        return true;
    }
    return false;
}

/****************************************************************************
 * changeFATInterface
 * Checks if the device (method) specified is available, and
 * sets libfat to use the device
****************************************************************************/
bool ChangeFATInterface(int method, bool silent)
{
	bool devFound = false;

	if(method == METHOD_SD)
	{
		// check which SD device is loaded

		#ifdef HW_RVL
		if (FatIsMounted(PI_INTERNAL_SD))
		{
			devFound = true;
			fatSetDefaultInterface(PI_INTERNAL_SD);
		}
		#endif

		if (!devFound && FatIsMounted(PI_SDGECKO_A))
		{
			devFound = true;
			fatSetDefaultInterface(PI_SDGECKO_A);
		}
		if(!devFound && FatIsMounted(PI_SDGECKO_B))
		{
			devFound = true;
			fatSetDefaultInterface(PI_SDGECKO_B);
		}
		if(!devFound)
		{
			if(!silent)
				WaitPrompt ((char *)"SD card not found!");
		}
	}
	else if(method == METHOD_USB)
	{
		#ifdef HW_RVL
		if(FatIsMounted(PI_USBSTORAGE))
		{
			devFound = true;
			fatSetDefaultInterface(PI_USBSTORAGE);
		}
		else
		{
			if(!silent)
				WaitPrompt ((char *)"USB flash drive not found!");
		}
		#endif
	}

	return devFound;
}

/***************************************************************************
 * Browse FAT subdirectories
 ***************************************************************************/
int
ParseFATdirectory(int method)
{
	int nbfiles = 0;
	DIR_ITER *fatdir;
	char filename[MAXPATHLEN];
	struct stat filestat;
	char msg[128];

	// initialize selection
	selection = offset = 0;

	// Clear any existing values
	memset (&filelist, 0, sizeof (FILEENTRIES) * MAXFILES);

	// open the directory
	fatdir = diropen(currentdir);
	if (fatdir == NULL)
	{
		sprintf(msg, "Couldn't open %s", currentdir);
		WaitPrompt(msg);

		// if we can't open the dir, open root dir
		sprintf(currentdir,"%s",ROOTFATDIR);

		fatdir = diropen(currentdir);

		if (fatdir == NULL)
		{
			sprintf(msg, "Error opening %s", currentdir);
			WaitPrompt(msg);
			return 0;
		}
	}

	// index files/folders
	while(dirnext(fatdir,filename,&filestat) == 0)
	{
		if(strcmp(filename,".") != 0)
		{
			memset(&filelist[nbfiles], 0, sizeof(FILEENTRIES));
			strncpy(filelist[nbfiles].filename, filename, MAXPATHLEN);
			strncpy(filelist[nbfiles].displayname, filename, MAXDISPLAY+1);	// crop name for display
			filelist[nbfiles].length = filestat.st_size;
			filelist[nbfiles].flags = (filestat.st_mode & _IFDIR) == 0 ? 0 : 1; // flag this as a dir
			nbfiles++;
		}
	}

	// close directory
	dirclose(fatdir);

	// Sort the file list
	qsort(filelist, nbfiles, sizeof(FILEENTRIES), FileSortCallback);

	return nbfiles;
}

/****************************************************************************
 * LoadFATFile
 ****************************************************************************/
int
LoadFATFile ()
{
	char zipbuffer[2048];
	char filepath[MAXPATHLEN];
	FILE *handle;
	u32 size;

	/* Check filename length */
	if ((strlen(currentdir)+1+strlen(filelist[selection].filename)) < MAXPATHLEN)
		sprintf(filepath, "%s/%s",currentdir,filelist[selection].filename);
	else
	{
		WaitPrompt((char*) "Maximum filepath length reached!");
		return -1;
	}

	handle = fopen (filepath, "rb");
	if (handle > 0)
	{
		fread (zipbuffer, 1, 2048, handle);

		int r = IsZipFile (zipbuffer);

		if(r == 2) // 7z
		{
			WaitPrompt ((char *)"7z files are not supported!");
			return 0;
		}

		if (r)
		{
			size = UnZipFATFile (nesrom, handle); // unzip from FAT
		}
		else
		{
			// Just load the file up
			fseek(handle, 0, SEEK_END);
			size = ftell(handle);				// get filesize
			fseek(handle, 2048, SEEK_SET);		// seek back to point where we left off
			memcpy (nesrom, zipbuffer, 2048);	// copy what we already read
			fread (nesrom + 2048, 1, size - 2048, handle);
		}
		fclose (handle);
		return size;
	}
	else
	{
		WaitPrompt((char*) "Error opening file");
		return 0;
	}

	return 0;
}

/****************************************************************************
 * Load savebuffer from FAT file
 ***************************************************************************/

// no buffer is specified - so use savebuffer
int
LoadSaveBufferFromFAT (char *filepath, bool silent)
{
	return LoadBufferFromFAT((char *)savebuffer, filepath, silent);
}

int
LoadBufferFromFAT (char * sbuffer, char *filepath, bool silent)
{
	FILE *handle;
    int size = 0;

    handle = fopen (filepath, "rb");

    if (handle <= 0)
    {
        if ( !silent )
        {
            char msg[100];
            sprintf(msg, "Couldn't open %s", filepath);
            WaitPrompt (msg);
        }
        return 0;
    }

    // Just load the file up
	fseek(handle, 0, SEEK_END); // go to end of file
	size = ftell(handle); // get filesize
	fseek(handle, 0, SEEK_SET); // go to start of file
	fread (sbuffer, 1, size, handle);
    fclose (handle);

    return size;
}

/****************************************************************************
 * Write savebuffer to FAT card file
 ****************************************************************************/
int
SaveBufferToFAT (char *filepath, int datasize, bool silent)
{
	FILE *handle;

    if (datasize)
    {
        handle = fopen (filepath, "wb");

        if (handle <= 0)
        {
            char msg[100];
            sprintf(msg, "Couldn't save %s", filepath);
            WaitPrompt (msg);
            return 0;
        }

        fwrite (savebuffer, 1, datasize, handle);
        fclose (handle);
    }
    return datasize;
}
