package Main;

import com.sun.jna.*;
import com.sun.jna.platform.win32.WinDef;

import java.util.Arrays;
import java.util.List;
import java.util.logging.Filter;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Created by дом on 20.02.2018.
 */
public class Init {
    public static Logger logger = Logger.getLogger("MyLogger");

    private static HCNetSDK hcNetSDK = (HCNetSDK) Native.loadLibrary("HCNetSDK.dll" , HCNetSDK.class);
    //private static LPNET_DVR_SDKSTATE.ByReference lpState = new LPNET_DVR_SDKSTATE.ByReference();
//    static {
//        Native.register(Platform.C_LIBRARY_NAME);
//    }
    public static interface HCNetSDK extends Library {
        boolean  NET_DVR_Init();
        boolean NET_DVR_Cleanup();
        int NET_DVR_GetSDKVersion();
        int NET_DVR_GetSDKBuildVersion();
        boolean NET_DVR_GetSDKState (StructureImpl.LPNET_DVR_SDKSTATE pSDKState);
        boolean NET_DVR_GetSDKAbility(StructureImpl.LPNET_DVR_SDKABL ability);
        NativeLong NET_DVR_Login_V30 (String ipAddress, short port, String userName, String password, StructureImpl.LPNET_DVR_DEVICEINFO_V30 deviceinfo_v30);
        boolean NET_DVR_Logout(NativeLong userId);
        boolean NET_DVR_GetDiskList (NativeLong userId, StructureImpl.LPNET_DVR_DISKABILITY_LIST diskList);
        int NET_DVR_GetLastError();
        NativeLong NET_DVR_FindFile_V30 (NativeLong userId, StructureImpl.NET_DVR_FILECOND fileCondStruct);
        boolean NET_DVR_FindClose_V30(NativeLong lFindHandle);
        NativeLong NET_DVR_FindNextFile_V30(NativeLong userId, StructureImpl.LPNET_DVR_FINDDATA_V30 fileData);
        NativeLong NET_DVR_GetFileByTime (NativeLong userId, NativeLong cannel, StructureImpl.NET_DVR_TIME timeStart, StructureImpl.NET_DVR_TIME timeEnd, String filePath);
        boolean NET_DVR_PlayBackControl_V40 (NativeLong getFileByTime, int commandCode, String inBuffer, int lenInParam, String outBuffer, int outParam);
        boolean NET_DVR_PlayBackControl(NativeLong getFileByTime, int command, int outValue);
        NativeLong NET_DVR_PlayBackByName(NativeLong userId, String filename, WinDef.HWND whnd);
        boolean NET_DVR_GetDVRConfig (NativeLong userId, int command, NativeLong chennal, StructureImpl.NET_DVR_TIME outBuffer, int outBufferSize, NativeLong sizeReturned);
    }



  /*  public static class LPNET_DVR_SDKSTATE extends Structure {

        public short dwTotalLoginNum;
        public short dwTotalRealPlayNum;
        public short dwTotalPlayBackNum;
        public short dwTotalAlarmChanNum;
        public short dwTotalFormatNum;
        public short dwTotalFileSearchNum;
        public short dwTotalLogSearchNum;
        public short dwTotalSerialNum;
        public short dwTotalUpgradeNum;
        public short dwTotalVoiceComNum;
        public short dwTotalBroadCastNum;
        public short dwRes[] = new short[10];


        @Override
        protected List<String> getFieldOrder() {
            return Arrays.asList(
                    "dwTotalLoginNum",
                    "dwTotalRealPlayNum",
                    "dwTotalPlayBackNum",
                    "dwTotalAlarmChanNum",
                    "dwTotalFormatNum",
                    "dwTotalFileSearchNum",
                    "dwTotalLogSearchNum",
                    "dwTotalSerialNum",
                    "dwTotalUpgradeNum",
                    "dwTotalVoiceComNum",
                    "dwTotalBroadCastNum",
                    "dwRes"
            );
        }
    }
*/
    public static void init() {
//        LPNET_DVR_SDKSTATE structure = new StructureImpl.LPNET_DVR_SDKSTATE();
//        LPNET_DVR_SDKSTATE lpnetDvrSdkstate = new LPNET_DVR_SDKSTATE();
        logger.setLevel(Level.OFF);
        int buildVersion;
        int version;
        int error;
        NativeLong fileSearch = new NativeLong();
        NativeLong fileSearchByTime = new NativeLong();
        boolean trueOrFalse = false;
        StructureImpl.LPNET_DVR_SDKSTATE state = StructureImpl.getLPNET_DVR_SDKSTATE();
        StructureImpl.LPNET_DVR_SDKABL ability = StructureImpl.getLPNET_DVR_SDKABL();
        StructureImpl.LPNET_DVR_DEVICEINFO_V30 deviceinfo_v30 = StructureImpl.getLPNET_DVR_DEVICEINFO_V30();
        StructureImpl.LPNET_DVR_DISKABILITY_LIST abilityList = StructureImpl.getLPNET_DVR_DISKABILITY_LIST();
        StructureImpl.NET_DVR_TIME timeBegin = StructureImpl.getNET_DVR_TIME();
        StructureImpl.NET_DVR_TIME timeEnd = StructureImpl.getNET_DVR_TIME();
        StructureImpl.NET_DVR_FILECOND filecond = StructureImpl.getNET_DVR_FILECOND();
        StructureImpl.LPNET_DVR_FINDDATA_V30 fileData = StructureImpl.getLPNET_DVR_FINDDATA_V30();
        StructureImpl.NET_DVR_TIME timeServer = StructureImpl.getNET_DVR_TIME();



        System.out.println("init: " + hcNetSDK.NET_DVR_Init() + '\n' +
                            "versoin:  " + (version = hcNetSDK.NET_DVR_GetSDKVersion()) + '\n' +
                            "BuildVersion: " + (buildVersion = hcNetSDK.NET_DVR_GetSDKBuildVersion()) + '\n' +
                            "SDK State: " + hcNetSDK.NET_DVR_GetSDKState(state));
        logger.info( "state: " + state);
        logger.info(" version: " + Integer.toHexString(version));
        logger.info("build version : " + Integer.toHexString(buildVersion));

        trueOrFalse = false;
        trueOrFalse = hcNetSDK.NET_DVR_GetSDKAbility(ability);
        logger.info("Ability: " + trueOrFalse);
        logger.info("AbilityMaxLogin: " + Integer.toHexString(ability.dwMaxLoginNum));

        NativeLong userId = new NativeLong();
        userId = hcNetSDK.NET_DVR_Login_V30("192.168.1.14", (short)8000, "admin", "12345", deviceinfo_v30);
        logger.info("deviceInfo: " + deviceinfo_v30.byDVRType);
        logger.info("userId: " + userId);
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
        trueOrFalse = hcNetSDK.NET_DVR_GetDVRConfig(userId, 118, new NativeLong(1), timeServer, buffersize,  size);
        error = hcNetSDK.NET_DVR_GetLastError();
        System.out.println("GetCFG: " + " " + trueOrFalse + timeServer + "error: " + error );

        logger.info("deviceInfo: \n\n" + String.valueOf(serial));
        logger.info("deviceInfo: " );

        trueOrFalse = false;
        trueOrFalse = hcNetSDK.NET_DVR_GetDiskList(userId, abilityList);
        error = hcNetSDK.NET_DVR_GetLastError();
        logger.info("Error: " + error);
        logger.info("diskList: " + trueOrFalse);
        logger.info("DiskList: " + abilityList.struDescNode[0]);

        timeBegin.dwYear = 2018;
        timeBegin.dwMonth = 3;
        timeBegin.dwDay = 18;
        timeBegin.dwHour = 15;
        timeBegin.dwMinute = 1;
        timeBegin.dwSecond = 0;

        timeEnd.dwYear = 2018;
        timeEnd.dwMonth = 3;
        timeEnd.dwDay = 18;
        timeEnd.dwHour = 15;
        timeEnd.dwMinute = 10;
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
        fileSearchByTime = hcNetSDK.NET_DVR_GetFileByTime(userId, channel, timeBegin, timeEnd, "videoHik.mp4");
        System.out.println("fileSearchByTime: " + fileSearchByTime);

        trueOrFalse = false;
        int value = 0;
        trueOrFalse = hcNetSDK.NET_DVR_PlayBackControl_V40(fileSearchByTime, 1, "", 0,"",0);
        System.out.println("Playback:" + trueOrFalse);
        try {
            Thread.sleep(5000);
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
        trueOrFalse = hcNetSDK.NET_DVR_FindClose_V30(fileSearch);
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
