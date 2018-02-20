package Main;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;

import java.util.Arrays;
import java.util.List;

/**
 * Created by дом on 20.02.2018.
 */
public class Init {

    private static HCNetSDK hcNetSDK = (HCNetSDK) Native.loadLibrary("HCNetSDK.dll" , HCNetSDK.class);
    //private static LPNET_DVR_SDKSTATE.ByReference lpState = new LPNET_DVR_SDKSTATE.ByReference();

    public static interface HCNetSDK extends Library {
        boolean NET_DVR_Init();
        short NET_DVR_GetSDKVersion();
        short NET_DVR_GetSDKBuildVersion();
        boolean NET_DVR_GetSDKState (LPNET_DVR_SDKSTATE pSDKState);
    }

    public static class LPNET_DVR_SDKSTATE extends Structure {
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
        public LPNET_DVR_SDKSTATE(){

        }


    }

    public static void init() {
        LPNET_DVR_SDKSTATE lpnetDvrSdkstate = null;
        System.out.println("init: " + hcNetSDK.NET_DVR_Init() + '\n' +
                            "versoin:  " + hcNetSDK.NET_DVR_GetSDKVersion() + '\n' +
                            "BuildVersion: " + hcNetSDK.NET_DVR_GetSDKBuildVersion() + '\n' +
                            "SDK State: " + hcNetSDK.NET_DVR_GetSDKState(lpnetDvrSdkstate));
    }

}
