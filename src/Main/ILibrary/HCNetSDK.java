package Main.ILibrary;

import Main.Main;
import com.sun.jna.Library;
import com.sun.jna.NativeLong;
import com.sun.jna.platform.win32.WinDef;

public interface HCNetSDK extends Library {

    boolean  NET_DVR_Init();
    boolean NET_DVR_Cleanup();
    boolean NET_DVR_GetSDKState (StructureImpl.LPNET_DVR_SDKSTATE pSDKState);
    boolean NET_DVR_GetSDKAbility(StructureImpl.LPNET_DVR_SDKABL ability);
    boolean NET_DVR_Logout(NativeLong userId);
    boolean NET_DVR_GetDiskList (NativeLong userId, StructureImpl.LPNET_DVR_DISKABILITY_LIST diskList);
    boolean NET_DVR_FindClose_V30(NativeLong lFindHandle);
    boolean NET_DVR_PlayBackControl_V40 (NativeLong getFileByTime, int commandCode, String inBuffer, int lenInParam, String outBuffer, int outParam);
    boolean NET_DVR_GetDVRConfig (NativeLong userId, int command, NativeLong chennal, StructureImpl.NET_DVR_TIME outBuffer, int outBufferSize, NativeLong sizeReturned);
    boolean NET_DVR_PlayBackControl(NativeLong getFileByTime, int command, int outValue);
    boolean NET_DVR_SetReconnect (NativeLong time, boolean enabled);
    boolean NET_DVR_SetConnectTime (NativeLong time, NativeLong reserved);
    int NET_DVR_GetSDKVersion();
    int NET_DVR_GetSDKBuildVersion();
    int NET_DVR_GetLastError();
    int NET_DVR_GetDownloadPos(NativeLong fileHandle);
    NativeLong NET_DVR_FindFile_V30 (NativeLong userId, StructureImpl.NET_DVR_FILECOND fileCondStruct);
    NativeLong NET_DVR_FindNextFile_V30(NativeLong userId, StructureImpl.LPNET_DVR_FINDDATA_V30 fileData);
    NativeLong NET_DVR_GetFileByTime (NativeLong userId, NativeLong cannel, StructureImpl.NET_DVR_TIME timeStart, StructureImpl.NET_DVR_TIME timeEnd, String filePath);
    NativeLong NET_DVR_PlayBackByName(NativeLong userId, String filename, WinDef.HWND whnd);
    NativeLong NET_DVR_Login_V30 (String ipAddress, short port, String userName, String password, StructureImpl.LPNET_DVR_DEVICEINFO_V30 deviceinfo_v30);
    NativeLong NET_DVR_RealPlay_V30 (NativeLong userId, StructureImpl.LPNET_DVR_CLIENTINFO clientinfo, NativeLong callback, NativeLong pUser, boolean bBlocked);

}