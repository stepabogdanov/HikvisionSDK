package Main;

import Main.ILibrary.HCNetSDK;
import Main.ILibrary.StructureImpl;
import com.sun.jna.*;
import com.sun.jna.platform.win32.WinDef;

import javax.swing.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Created by дом on 20.02.2018.
 */
public class Init {

    public static Logger logger = Logger.getLogger("MyLogger");

    StructureImpl bigStrucrure = new StructureImpl();
    static NativeLong userId;
    static StructureImpl.LPNET_DVR_DEVICEINFO_V30 dvrDeviceInfoV30 = new StructureImpl.LPNET_DVR_DEVICEINFO_V30();


    private static HCNetSDK hcNetSDK = (HCNetSDK) Native.load("/home/home/Java/HikvisionSDK/libhcnetsdk.so" , HCNetSDK.class);

    static void init() {
        logger.setLevel(Level.OFF);
        boolean init = false;
        init = hcNetSDK.NET_DVR_Init();
        init = hcNetSDK.NET_DVR_SetConnectTime(new NativeLong(2000), new NativeLong(1));
        init = hcNetSDK.NET_DVR_SetReconnect(new NativeLong(2000), true);

        System.out.println("initStatus: " + init);

    }

    static void cleanup() {
        boolean cleanup = hcNetSDK.NET_DVR_Cleanup();
        System.out.println("cleanupStatus: " + cleanup);
    }

    static StructureImpl.LPNET_DVR_SDKSTATE getSDKState() throws InterruptedException {
        StructureImpl.LPNET_DVR_SDKSTATE sdkstate = new StructureImpl.LPNET_DVR_SDKSTATE();
        boolean sdkStateGetSuccess = hcNetSDK.NET_DVR_GetSDKState(sdkstate);
        System.out.println("sdkStateSuccess: " + sdkStateGetSuccess );
        logger.info( "" + '\n' + sdkstate);
        return sdkstate;
    }

    static NativeLong login(String login, String password, String ipAddress, short port) {
        userId = hcNetSDK.NET_DVR_Login_V30(ipAddress, port, login, password, dvrDeviceInfoV30);
        System.out.println("LOGGING : " + hcNetSDK.NET_DVR_GetLastError());

        System.out.println("UserID: " + userId);
        logger.info('\n' + "" + dvrDeviceInfoV30);
        return userId;

    }

    static void getSDKAbility () {
        StructureImpl.LPNET_DVR_SDKABL abilityList = new StructureImpl.LPNET_DVR_SDKABL();
        hcNetSDK.NET_DVR_GetSDKAbility(abilityList);
        logger.info("abilityList: " + abilityList);
    }

    static String getSerialNumbre() {
        return new String(dvrDeviceInfoV30.sSerialNumber);
    }

    static void downloadFileByTime(NativeLong userId, NativeLong channel ) throws InterruptedException {
        StructureImpl.NET_DVR_TIME timeBegin = new StructureImpl.NET_DVR_TIME();
        StructureImpl.NET_DVR_TIME timeEnd = new StructureImpl.NET_DVR_TIME();
        NativeLong getFileStatus;
        timeBegin.dwYear = 2018;
        timeBegin.dwMonth = 10;
        timeBegin.dwDay = 19;
        timeBegin.dwHour = 22;
        timeBegin.dwMinute = 20;
        timeBegin.dwSecond = 0;

        timeEnd.dwYear = 2018;
        timeEnd.dwMonth = 10;
        timeEnd.dwDay = 19;
        timeEnd.dwHour = 22;
        timeEnd.dwMinute = 10;
        timeEnd.dwSecond = 0;

        getFileStatus = hcNetSDK.NET_DVR_GetFileByTime(userId, channel, timeBegin, timeEnd, "video.mp4");
        while (hcNetSDK.NET_DVR_GetDownloadPos(getFileStatus) == 100) {
            System.out.println("Download status: " + hcNetSDK.NET_DVR_GetDownloadPos(getFileStatus));
            Thread.sleep(1000);
        }


    }

    static void logOut() {
        boolean logOut = hcNetSDK.NET_DVR_Logout(userId);
        System.out.println("LOGGING_OUT: " + logOut);
    }

    static void realPlay(WinDef.HWND window) {
        StructureImpl.LPNET_DVR_CLIENTINFO lpnet_dvr_clientinfo = new StructureImpl.LPNET_DVR_CLIENTINFO();
        lpnet_dvr_clientinfo.lChannel = new NativeLong(1);
        lpnet_dvr_clientinfo.lLinkMode = new NativeLong(0);
        lpnet_dvr_clientinfo.hPlayWnd = window;
        lpnet_dvr_clientinfo.sMultiCastIP = null;
        hcNetSDK.NET_DVR_RealPlay_V30(userId, lpnet_dvr_clientinfo, null, null, false);


    }






       public static void initOld() {
//        LPNET_DVR_SDKSTATE structure = new StructureImpl.LPNET_DVR_SDKSTATE();
//        LPNET_DVR_SDKSTATE lpnetDvrSdkstate = new LPNET_DVR_SDKSTATE();
        logger.setLevel(Level.OFF);
        int buildVersion;
        int version;
        int error;
        NativeLong fileSearch = new NativeLong();
        NativeLong fileSearchByTime = new NativeLong();
        boolean trueOrFalse = false;
        StructureImpl.LPNET_DVR_SDKSTATE state = new StructureImpl.LPNET_DVR_SDKSTATE();
        StructureImpl.LPNET_DVR_SDKABL ability = new StructureImpl.LPNET_DVR_SDKABL();
        StructureImpl.LPNET_DVR_DEVICEINFO_V30 deviceinfo_v30 = new StructureImpl.LPNET_DVR_DEVICEINFO_V30();
        StructureImpl.LPNET_DVR_DISKABILITY_LIST abilityList = new StructureImpl.LPNET_DVR_DISKABILITY_LIST();
        StructureImpl.NET_DVR_TIME timeBegin = new StructureImpl.NET_DVR_TIME();
        StructureImpl.NET_DVR_TIME timeEnd = new StructureImpl.NET_DVR_TIME();
        StructureImpl.NET_DVR_FILECOND filecond = new StructureImpl.NET_DVR_FILECOND();
        StructureImpl.LPNET_DVR_FINDDATA_V30 fileData = new StructureImpl.LPNET_DVR_FINDDATA_V30();
        StructureImpl.NET_DVR_TIME timeServer = new StructureImpl.NET_DVR_TIME();



        System.out.println("initOld: " + hcNetSDK.NET_DVR_Init() + '\n' +
                            "versoin:  " + (version = hcNetSDK.NET_DVR_GetSDKVersion()) + '\n' +
                            "BuildVersion: " + (buildVersion = hcNetSDK.NET_DVR_GetSDKBuildVersion()));
        logger.info("SDK State: " + hcNetSDK.NET_DVR_GetSDKState(state));


        logger.info( "state: " + state);
        System.out.println(" version: " + Integer.toHexString(version));
        System.out.println("build version : " + Integer.toHexString(buildVersion));

        trueOrFalse = false;
        trueOrFalse = hcNetSDK.NET_DVR_GetSDKAbility(ability);
        System.out.println("Ability: " + trueOrFalse);
        logger.info("AbilityMaxLogin: " + Integer.toHexString(ability.dwMaxLoginNum));

        NativeLong userId = new NativeLong();
        userId = hcNetSDK.NET_DVR_Login_V30("192.168.1.12", (short)8000, "admin", "12345", deviceinfo_v30);
        logger.info("deviceInfo: " + deviceinfo_v30.byDVRType);
        System.out.println("userId: " + userId);
        char [] serial = new char[28];
        for (int i=0; i<28;i++) {
            serial[i] = (char) deviceinfo_v30.sSerialNumber[i];
        }
        //Pointer
        System.out.println("Channels: " + deviceinfo_v30.byChanNum);
        System.out.println("ChannelsStart: " + deviceinfo_v30.byStartChan);

        NativeLong size = new NativeLong();
        int buffersize = 0;
        error = 0;
        trueOrFalse = false;
//      trueOrFalse = hcNetSDK.NET_DVR_GetDVRConfig(userId, 118, new NativeLong(1), timeServer, buffersize,  size);
        error = hcNetSDK.NET_DVR_GetLastError();
        logger.info("GetCFG: " + " " + trueOrFalse + timeServer + "error: " + error );

        System.out.println("deviceInfo: \n\n" + String.valueOf(serial));
        System.out.println("deviceInfo: " );

        trueOrFalse = false;
//        trueOrFalse = hcNetSDK.NET_DVR_GetDiskList(userId, abilityList);
        error = hcNetSDK.NET_DVR_GetLastError();
        logger.info("Error: " + error);
        logger.info("diskList: " + trueOrFalse);
        logger.info("DiskList: " + abilityList.struDescNode[0]);

        timeBegin.dwYear = 2018;
        timeBegin.dwMonth = 10;
        timeBegin.dwDay = 19;
        timeBegin.dwHour = 22;
        timeBegin.dwMinute = 10;
        timeBegin.dwSecond = 0;

        timeEnd.dwYear = 2018;
        timeEnd.dwMonth = 10;
        timeEnd.dwDay = 19;
        timeEnd.dwHour = 22;
        timeEnd.dwMinute = 15;
        timeEnd.dwSecond = 0;



        filecond.lChannel = new NativeLong(1);
        filecond.dwFileType = 0;
        filecond.dwIsLocked = 0xff;
        filecond.dwUseCardNo = 0;
        filecond.sCardNumber[0] = (byte) 0;
        filecond.struStartTime = timeBegin;
        filecond.struStopTime = timeEnd;

        logger.info("StructFindFile: \n" + filecond);

        NativeLong channel = new NativeLong(1);
        //fileSearch = hcNetSDK.NET_DVR_FindFile_V30(userId, filecond);
//        fileSearchByTime = hcNetSDK.NET_DVR_GetFileByTime(userId, channel, timeBegin, timeEnd, "videoHik.mp4");
        System.out.println("fileSearchByTime: " + fileSearchByTime);

        trueOrFalse = false;
        int value = 0;
//        trueOrFalse = hcNetSDK.NET_DVR_PlayBackControl_V40(fileSearchByTime, 1, "", 0,"",0);
        System.out.println("Playback:" + trueOrFalse);
        try {
            Thread.sleep(500);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }


//        trueOrFalse = false;
//        trueOrFalse = hcNetSDK.NET_DVR_FindClose_V30(fileSearch);
//        error = 0;
//        error = hcNetSDK.NET_DVR_GetLastError();
//        logger.info("findFileClose: " + trueOrFalse + " " + error);
//        System.out.println("Fileclose: " + trueOrFalse + " " + error);


        error = 0;
        error = hcNetSDK.NET_DVR_GetLastError();
        logger.info("findFile: " + fileSearch + " " + error);


        error = 0;
        //hcNetSDK.NET_DVR_FindNextFile_V30(fileSearch, fileData);
        error = hcNetSDK.NET_DVR_GetLastError();
        char[] fileName = new char[100];
        for (int i=0; i<100; i++) {
            fileName[i] = fileData.sFileName[i];
        }
        System.out.println("File Name: " + new String(fileName) + "Error: " + error);

        logger.info("FileData: \n\n" + fileData );



        trueOrFalse = false;
//        trueOrFalse = hcNetSDK.NET_DVR_FindClose_V30(fileSearch);
        error = 0;
        error = hcNetSDK.NET_DVR_GetLastError();
        logger.info("findFileClose: " + trueOrFalse + " " + error);


        trueOrFalse = false;

        trueOrFalse = hcNetSDK.NET_DVR_Logout(userId);
        logger.info("Logout: " + trueOrFalse);

        boolean cleanup;
        cleanup = hcNetSDK.NET_DVR_Cleanup();
        logger.info("cleanUp: " + cleanup);


    }



}
