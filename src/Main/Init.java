package Main;

import com.sun.jna.Library;
import com.sun.jna.Native;
import com.sun.jna.Structure;

import java.util.List;

/**
 * Created by дом on 20.02.2018.
 */
public class Init {

    private static HCNetSDK hcNetSDK = (HCNetSDK) Native.loadLibrary("HCNetSDK.dll" , HCNetSDK.class);
   // private static LPNET_DVR_SDKSTATE.ByReference lpState = new LPNET_DVR_SDKSTATE.ByReference();

    public static interface HCNetSDK extends Library {
        boolean NET_DVR_Init();
        short NET_DVR_GetSDKVersion();
        short NET_DVR_GetSDKBuildVersion();
        boolean NET_DVR_GetSDKState (LPNET_DVR_SDKSTATE pSDKState);
    }

    public static class LPNET_DVR_SDKSTATE extends Structure {
        @Override
        protected List<String> getFieldOrder() {
            return null;
        }

        public static class ByRerefence extends LPNET_DVR_SDKSTATE implements Structure.ByReference {

            short dwTotalLoginNum;
            short dwTotalRealPlayNum;
            short dwTotalPlayBackNum;
            short dwTotalAlarmChanNum;
            short dwTotalFormatNum;
            short dwTotalFileSearchNum;
            short dwTotalLogSearchNum;
            short dwTotalSerialNum;
            short dwTotalUpgradeNum;
            short dwTotalVoiceComNum;
            short dwTotalBroadCastNum;
            short dwRes[] = new short[10];
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
