package Main.ILibrary;

import Main.Main;
import com.sun.jna.NativeLong;
import com.sun.jna.Structure;
import com.sun.jna.platform.win32.WinDef;

import java.util.Arrays;
import java.util.List;

public class StructureImpl  {

    private LPNET_DVR_SDKSTATE sdkstate;
    private LPNET_DVR_SDKABL lpnetDvrSdkabl;
    private LPNET_DVR_DEVICEINFO_V30 lpnetDvrDeviceinfoV30;
    private LPNET_DVR_DISKABILITY_LIST lpnetDvrDiskabilityList;
    private LPNET_DVR_FINDDATA_V30 lpnetDvrFinddataV30;
    private NET_DVR_DESC_NODE netDvrDescNode;
    private NET_DVR_FILECOND netDvrFilecond;
    private NET_DVR_TIME netDvrTime;
    private LPNET_DVR_CLIENTINFO lpnetDvrClientinfo;


    public LPNET_DVR_SDKSTATE getSdkstate() {
        return sdkstate;
    }

    public LPNET_DVR_SDKABL getLpnetDvrSdkabl() {
        return lpnetDvrSdkabl;
    }

    public LPNET_DVR_DEVICEINFO_V30 getLpnetDvrDeviceinfoV30() {
        return lpnetDvrDeviceinfoV30;
    }

    public LPNET_DVR_DISKABILITY_LIST getLpnetDvrDiskabilityList() {
        return lpnetDvrDiskabilityList;
    }

    public LPNET_DVR_FINDDATA_V30 getLpnetDvrFinddataV30() {
        return lpnetDvrFinddataV30;
    }

    public NET_DVR_DESC_NODE getNetDvrDescNode() {
        return netDvrDescNode;
    }

    public NET_DVR_FILECOND getNetDvrFilecond() {
        return netDvrFilecond;
    }

    public NET_DVR_TIME getNetDvrTime() {
        return netDvrTime;
    }

    public void setSdkstate(LPNET_DVR_SDKSTATE sdkstate) {
        this.sdkstate = sdkstate;
    }

    public void setLpnetDvrSdkabl(LPNET_DVR_SDKABL lpnetDvrSdkabl) {
        this.lpnetDvrSdkabl = lpnetDvrSdkabl;
    }

    public void setLpnetDvrDeviceinfoV30(LPNET_DVR_DEVICEINFO_V30 lpnetDvrDeviceinfoV30) {
        this.lpnetDvrDeviceinfoV30 = lpnetDvrDeviceinfoV30;
    }

    public void setLpnetDvrDiskabilityList(LPNET_DVR_DISKABILITY_LIST lpnetDvrDiskabilityList) {
        this.lpnetDvrDiskabilityList = lpnetDvrDiskabilityList;
    }

    public void setLpnetDvrFinddataV30(LPNET_DVR_FINDDATA_V30 lpnetDvrFinddataV30) {
        this.lpnetDvrFinddataV30 = lpnetDvrFinddataV30;
    }

    public void setNetDvrDescNode(NET_DVR_DESC_NODE netDvrDescNode) {
        this.netDvrDescNode = netDvrDescNode;
    }

    public void setNetDvrFilecond(NET_DVR_FILECOND netDvrFilecond) {
        this.netDvrFilecond = netDvrFilecond;
    }

    public void setNetDvrTime(NET_DVR_TIME netDvrTime) {
        this.netDvrTime = netDvrTime;
    }

    public static class  LPNET_DVR_SDKSTATE extends Structure {

        public int dwTotalLoginNum;
        public int dwTotalRealPlayNum;
        public int dwTotalPlayBackNum;
        public int dwTotalAlarmChanNum;
        public int dwTotalFormatNum;
        public int dwTotalFileSearchNum;
        public int dwTotalLogSearchNum;
        public int dwTotalSerialNum;
        public int dwTotalUpgradeNum;
        public int dwTotalVoiceComNum;
        public int dwTotalBroadCastNum;
        public int[] dwRes = new int[10];

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

    public static class LPNET_DVR_SDKABL extends Structure {
        public int dwMaxLoginNum;
        public int dwMaxRealPlayNum;
        public int dwMaxPlayBackNum;
        public int dwMaxAlarmChanNum;
        public int dwMaxFormatNum;
        public int dwMaxFileSearchNum;
        public int dwMaxLogSearchNum;
        public int dwMaxSerialNum;
        public int dwMaxUpgradeNum;
        public int dwMaxVoiceComNum;
        public int dwMaxBroadCastNum;
        public int[] dwRes = new int[10];

        @Override
        protected List<String> getFieldOrder() {
            return Arrays.asList(
            "dwMaxLoginNum",
            "dwMaxRealPlayNum",
            "dwMaxPlayBackNum",
            "dwMaxAlarmChanNum",
            "dwMaxFormatNum",
            "dwMaxFileSearchNum",
            "dwMaxLogSearchNum",
            "dwMaxSerialNum",
            "dwMaxUpgradeNum",
            "dwMaxVoiceComNum",
            "dwMaxBroadCastNum",
             "dwRes");
        }
    }
    public static class LPNET_DVR_DEVICEINFO_V30 extends Structure {
        public byte[] sSerialNumber = new byte[28];
        public byte byAlarmInPortNum;
        public byte byAlarmOutPortNum;
        public byte byDiskNum;
        public byte byDVRType;
        public byte byChanNum;
        public byte byStartChan;
        public byte byAudioChanNum;
        public byte byIPChanNum;
        public byte byZeroChanNum;
        public byte byMainProto;
        public byte bySubProto;
        public byte bySupport;
        public byte bySupport1;
        public byte bySupport2;
        public byte wDevType;
        public byte[] byRes2 = new byte[16];

        @Override
        protected List<String> getFieldOrder() {
            return Arrays.asList(
                "sSerialNumber",
                "byAlarmInPortNum",
                "byAlarmOutPortNum",
                "byDiskNum",
                "byDVRType",
                "byChanNum",
                "byStartChan",
                "byAudioChanNum",
                "byIPChanNum",
                "byZeroChanNum",
                "byMainProto",
                "bySubProto",
                "bySupport",
                "bySupport1",
                "bySupport2",
                "wDevType",
                "byRes2"
            );
        }
    }
    public static class LPNET_DVR_DISKABILITY_LIST extends Structure {
        public int dwSize;
        public int dwNodeNum;
        public NET_DVR_DESC_NODE[] struDescNode = new NET_DVR_DESC_NODE[5];

        @Override
        protected List<String> getFieldOrder() {
            return Arrays.asList(
                    "dwSize",
                    "dwNodeNum",
                    "struDescNode"
            );
        }
    }

    public static class NET_DVR_DESC_NODE extends Structure {
        public int iValue;
        public byte[] byDescribe = new byte[32];
        public int dwFreeSpace;
        public byte[] byRes = new byte[10];

        @Override
        protected List<String> getFieldOrder() {
            return Arrays.asList(
                    "iValue",
                    "byDescribe",
                    "dwFreeSpace",
                    "byRes"
                    );
        }
    }
    public static class NET_DVR_FILECOND extends Structure {
        public NativeLong lChannel = new NativeLong();
        public int dwFileType;
        public int dwIsLocked;
        public int dwUseCardNo;
        public byte[] sCardNumber = new byte[32];
        public NET_DVR_TIME struStartTime = new NET_DVR_TIME();
        public NET_DVR_TIME struStopTime = new NET_DVR_TIME();
//        public byte byDrawFrame;
//        public byte[] byRes = new byte[63];

        @Override
        protected List<String> getFieldOrder() {
            return Arrays.asList(
                "lChannel",
                "dwFileType",
                "dwIsLocked",
                "dwUseCardNo",
                "sCardNumber",
                "struStartTime",
                "struStopTime"
//                "byDrawFrame",
//                "byRes"
            );
        }
    }
    public static class NET_DVR_TIME extends Structure {
        public int dwYear;
        public int dwMonth;
        public int dwDay;
        public int dwHour;
        public int dwMinute;
        public int dwSecond;

        @Override
        protected List<String> getFieldOrder() {
            return Arrays.asList(
                "dwYear",
                "dwMonth",
                "dwDay",
                "dwHour",
                "dwMinute",
                "dwSecond"
            );
        }
    }
    public static class LPNET_DVR_CLIENTINFO extends Structure {
        public NativeLong    lChannel;
        public NativeLong   lLinkMode;
        public WinDef.HWND hPlayWnd;
        public String sMultiCastIP;

        @Override
        protected List<String> getFieldOrder() {
            return Arrays.asList(
                "lChannel",
                "lLinkMode",
                "hPlayWnd",
                "sMultiCastIP"
            );

        }
    }

    public static class LPNET_DVR_FINDDATA_V30 extends Structure {
        public char[] sFileName = new char[100];
        public NET_DVR_TIME struStartTime;
        public NET_DVR_TIME struStopTime;
        public int dwFileSize;
        public char[] sCardNum = new char[32];
        public byte byLocked;
        public byte byFileType;
        public byte[] byRes = new byte[2];

        @Override
        protected List<String> getFieldOrder() {
            return Arrays.asList(
                "sFileName",
                "struStartTime",
                "struStopTime",
                "dwFileSize",
                "sCardNum",
                "byLocked",
                "byFileType",
                "byRes"
            );
        }
    }

}
