package Main.ILibrary;

import Main.Main;
import com.sun.jna.Library;
import com.sun.jna.NativeLong;
import com.sun.jna.platform.win32.WinDef;

public interface HCNetSDK extends Library {

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
    int NET_DVR_GetDownloadPos(NativeLong fileHandle);
}