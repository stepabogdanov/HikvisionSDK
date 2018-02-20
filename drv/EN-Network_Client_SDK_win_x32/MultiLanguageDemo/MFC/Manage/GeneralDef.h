
#ifndef GENERALDEF_H
#define GENERALDEF_H

#include "../../../incEn/HCNetSDK.h"
#include "../../../incEn/plaympeg4.h"



#define MAX_CHANS      24     //
#define MAX_DEVICE     10     //
#define MAX_OUTPUTS	   16	//
#define MAX_PREVIEWS   512	//

//
#define TREE_ALL_T	 0        //
#define DEVICETYPE 	 1		  //
#define CHANNELTYPE	 2	      //


#define DEMO_FULL_WIDTH 1024	//
#define DEMO_FULL_HEIGHT 768	//
#define OUTPUT_INTERVAL 4		//


//
#define UPGRADE_TIMER			6		//
#define FORMAT_TIMER			10		//

typedef struct STRU_CHANNEL_INFO
{
	char    chChanName[40];     //
	int		iChanIndex;			// 
	int		iPicResolution;				//
	int		iPicQuality;				//
	char	chAccessChanIP[16];     //
	BOOL    bEnable;              //

	STRU_CHANNEL_INFO()
	{
		chChanName[0]       ='\0';
		iChanIndex          = -1;
		iPicResolution		= 0;
		iPicQuality			= 2;
		chAccessChanIP[0]	= '\0';	
		bEnable             = FALSE;
	}
}CHANNEL_INFO,*pCHANNEL_INFO;

typedef struct STRU_DEVICE_INFO
{

	char    chDevName[100];        //
	char    sSerialNumber[100];     //
	char    chDevIP[40];            //
	LONG    lLoginID;
	int		iDeviceChanNum;		    //
	int		iStartChan;				//
	int 	iIPChanNum;				//
	int		iEnableChanNum;			//
	BOOL    bIPRet;                 //
	BYTE    byDiskNum;				    //
    BYTE    byDVRType;				    //
	
	CHANNEL_INFO struChanInfo[MAX_CHANNUM_V30];


	STRU_DEVICE_INFO()
	{
         chDevName[0]        = '\0';
		 sSerialNumber[0]    = '\0';
		 chDevIP[0]          = '\0';
		 lLoginID = -1;
		 iDeviceChanNum      =  -1;
		 iStartChan          = 0;
		 iIPChanNum          = 0;
		 iEnableChanNum      = -1;
		 bIPRet              = FALSE;
		 byDiskNum           = 0;
         byDVRType           = 0;
	}	 
}LOCAL_DEVICE_INFO,*pLOCAL_DEVICE_INFO;




#endif