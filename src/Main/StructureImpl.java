package Main;

import com.sun.jna.NativeLong;
import com.sun.jna.Structure;

import java.util.Arrays;
import java.util.List;

public class StructureImpl  {

    public static LPNET_DVR_SDKSTATE getLPNET_DVR_SDKSTATE() {
        return new LPNET_DVR_SDKSTATE();
    }
    public static LPNET_DVR_SDKABL getLPNET_DVR_SDKABL() {
        return new LPNET_DVR_SDKABL();
    }
    public static LPNET_DVR_DEVICEINFO_V30 getLPNET_DVR_DEVICEINFO_V30() {
        return  new LPNET_DVR_DEVICEINFO_V30();
    }
    public static LPNET_DVR_DISKABILITY_LIST getLPNET_DVR_DISKABILITY_LIST() {
        return new LPNET_DVR_DISKABILITY_LIST();
    }
    public static NET_DVR_DESC_NODE getNET_DVR_DESC_NODE() {
        return new NET_DVR_DESC_NODE();
    }
    public static NET_DVR_FILECOND getNET_DVR_FILECOND() {
        return new NET_DVR_FILECOND();
    }
    public static NET_DVR_TIME getNET_DVR_TIME() {
        return new NET_DVR_TIME();
    }
    public static LPNET_DVR_FINDDATA_V30  getLPNET_DVR_FINDDATA_V30 () {
        return new LPNET_DVR_FINDDATA_V30();
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
