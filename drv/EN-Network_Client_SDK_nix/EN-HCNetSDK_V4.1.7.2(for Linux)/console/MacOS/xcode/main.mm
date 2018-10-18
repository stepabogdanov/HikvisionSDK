//
//  main.m
//  sdkDemo
//
//  Created by shi yanming on 11-5-12.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include <stdio.h>
#include <iostream>
#include "GetStream.h"
#include "public.h"
#include "ConfigParams.h"
#include "Alarm.h"
#include "CapPicture.h"
#include "playback.h"
#include "Voice.h"

using namespace std;

int main()
{
    NET_DVR_Init();
    char cUserChoose = 'r';
    
    //Login device
    NET_DVR_DEVICEINFO_V30 struDeviceInfo = {0};
    LONG lUserID = NET_DVR_Login_V30("172.10.3.166", 8000, "admin", "12345", &struDeviceInfo);
    if (lUserID < 0)
    {
        printf("pyd---Login error, %d\n", NET_DVR_GetLastError());
        printf("Press any key to quit...\n");
        cin>>cUserChoose;
		
        NET_DVR_Cleanup();
        return HPR_ERROR;
    }
	
    while ('q' != cUserChoose)
    {
        printf("\n");
        printf("Input 1, Test GetStream\n");
        printf("      2, Test Configure params\n");
        printf("      3, Test Alarm\n");
        printf("      4, Test Capture Picture\n");
        printf("      5, Test play back\n");
        printf("      6, Test Voice\n");
        printf("      7, Test SDK ability\n");
		
        /*
		 printf("      4, Test User Manage\n");
		 printf("      5, Test tool interface\n");
		 printf("      6, Test net search\n");
		 printf("      7, Test Matrix decode\n");
		 printf("      8, Test PTZ\n");
		 printf("      9, Test Format\n");
		 printf("      0, Test Update\n");
		 printf("      a, Test Serial trans\n");
		 printf("      b, Test Configure Params\n");
		 printf("      c, Test VCA && IVMS\n");
		 */
        printf("      q, Quit.\n");
        printf("Input:");
		
        cin>>cUserChoose;
        switch (cUserChoose)
        {
			case '1':
				Demo_GetStream_V30(); //Get stream.
				break;
			case '2':
				Demo_ConfigParams(lUserID);  //Setting params.
				break;
			case '3':
				Demo_Alarm();         //Alarm & listen.
				break;
			case '4':
				Demo_Capture();
				break;
			case '5':
				Demo_PlayBack(lUserID);
				break;
			case '6':
				Demo_Voice();
				break;
			case '7':
				Demo_SDK_Ability();
				break;
			default:
				break;
        }
    }
	
    //logout
    NET_DVR_Logout_V30(lUserID);
    NET_DVR_Cleanup();
    return 0;
}
