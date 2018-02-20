# Microsoft Developer Studio Project File - Name="ClientDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ClientDemo - Win32 Debug En
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ClientDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ClientDemo.mak" CFG="ClientDemo - Win32 Debug En"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ClientDemo - Win32 Release En" (based on "Win32 (x86) Application")
!MESSAGE "ClientDemo - Win32 Debug En" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ClientDemo - Win32 Release En"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ClientDemo___Win32_Release_En"
# PROP BASE Intermediate_Dir "ClientDemo___Win32_Release_En"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ClientDemo___Win32_Release_En"
# PROP Intermediate_Dir "ClientDemo___Win32_Release_En"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O1 /I "../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /Zi /O1 /I "../incEn" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "DEMO_LAN_EN" /FAcs /Fa"En/" /FR"En/" /Fo"En/" /Fd"En/" /FD /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /I "../include" /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /I "../include" /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 HCNetSDK.lib PlayCtrl.lib ws2_32.lib DsSdk.lib winmm.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"msvcp60.lib" /out:"..\lib\ClientDemo.exe" /libpath:"../lib"
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 HCNetSDK.lib PlayCtrl.lib ws2_32.lib DsSdk.lib winmm.lib GdiPlus.lib /nologo /subsystem:windows /pdb:"VC60/ClientDemoEn.pdb" /map:"En/ClientDemoEn.map" /debug /machine:I386 /out:"../lib/ClientDemoEn.exe" /libpath:"../lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "ClientDemo - Win32 Debug En"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ClientDemo___Win32_Debug_En"
# PROP BASE Intermediate_Dir "ClientDemo___Win32_Debug_En"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug_En"
# PROP Intermediate_Dir "Debug_En"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "../incEn" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /D "DEMO_LAN_EN" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /I "../include" /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /I "../include" /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 HCNetSDK.lib PlayCtrl.lib ws2_32.lib DsSdk.lib winmm.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"msvcp60.lib" /out:"../lib/ClientDemo.exe" /pdbtype:sept /libpath:"../lib"
# SUBTRACT BASE LINK32 /pdb:none /nodefaultlib
# ADD LINK32 HCNetSDK.lib PlayCtrl.lib ws2_32.lib DsSdk.lib winmm.lib GdiPlus.lib /nologo /subsystem:windows /pdb:"En/ClientDemoEnD.pdb" /debug /machine:I386 /out:"../lib/ClientDemoEnD.exe" /libpath:"../lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ENDIF 

# Begin Target

# Name "ClientDemo - Win32 Release En"
# Name "ClientDemo - Win32 Debug En"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ClientDemo.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\ClientDemo.rc
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\ClientDemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ClientDemoEn.rc
# End Source File
# Begin Source File

SOURCE=.\DialogMultiNetCard.cpp
# End Source File
# Begin Source File

SOURCE=.\DialogRecordTimeSpan.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg67DVSCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAbilityAutoDetect.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAccessCameraCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAddDevice.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAES.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmCamCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHost.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostAudioAssociateAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostDialParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostEnableCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostEventTrigger.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostExternalModule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostFaultProcess.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostGPRS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostLED.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostLEDBrightness.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostLogSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostModuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostNetCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostReportMode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostRs485.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostSubsystem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostTransparent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostTriggerCode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostZoomAddr.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmKeyboardUser.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmNetUser.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmOperatorUser.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmOutCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAtmFrameFormatV30.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAudioUploadDownload.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgAudioUploadDownload.h
# End Source File
# Begin Source File

SOURCE=.\DlgAutoReboot.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgBroadCast.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCcdParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCertInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgChanInputAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgChannelInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCheckTime.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConfigAll.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgConfigFlash.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCreateVD.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCuntomProtocal.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgCurrentEncodeAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDecoderAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDecWinStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceAudioTalkCode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceState.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDiskQuota.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDoTest.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgDynChanAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEncodeAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEncodeJoint.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgESataMiniSasUsage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgEthernetIpv6Cfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFormatHD.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgFortify.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgGatewayCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHardDiskCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgHolidayCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInfrareCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInquestDvr.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInquestEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgInquestFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgDDNS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgEasyDDNS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgIPServer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgStreamServer.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPAddrFilterCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPCFrontAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPCSpecial.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIPDomeLocalCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgIscsiCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSBaseInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSImageMergeCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSIpcCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSOverlapCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSRoadInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSUpload.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgITSWorkState.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgJpegCaptureCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgJpegFTP.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgJPEGSnatchConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLEDTimerSwitch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLimitAngle.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLinkStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLocalConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLocalLogConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLocalRecordSchedule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgLogSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMatDecBigScrSplice.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMatDecodeChanJoint.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgMatUnitedSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetraEventVedio.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetraHttps.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetraRecordPackage.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetraSeries.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetworkAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetworkBonding.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNetworkFlowTest.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgNVRCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOutput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgOutputCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPdcCalibration.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPdcRuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPDCSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayBack.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayDvrRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayEvent.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayLocalFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayLockFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayMotion.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayRemoteFile.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPlayRemoteTime.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPositionTrackCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPPPCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPTZCruise.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPtzCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPTZPreset.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPtzScope.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgPUStream.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgQuickAddIpc.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRaidConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordLabel.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRecordStreamTransType.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRegionList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAdvanceNetConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmInHandle.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmInPtzInvoke.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControlAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteEmailAddReceiver.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteFanException.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteHideAlarm.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteHideArea.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteIPAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteKey.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteMotionDetect.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteNetNFS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemotePullException.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteRecordSchedule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteShowString.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteVideoInLost.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteVideoInput.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteZone.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgRtspConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSafetyCabin.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgScreenLogoCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSenceControl.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSensorAddPreview.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSensorCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSerialTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSizeFilter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSnmpCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgSoftHardAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTalkMREx.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTPSRuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUpgrade.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUploadLogo.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgUpnpCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaAidRuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBehaviorCalibrate.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBehaviorCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBlackList.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaChanCtrlCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDataBase.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDevAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDevAccessCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDrawMode.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaEnterRegion.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFace.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceDataBase.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceDetect.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceMatchLogSearch.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceSnapCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFindBackgroundPic.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFindSnapData.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaITSCalibrate.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaITSCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaIvmsCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaIvmsSched.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaLaneCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaLF.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaMaskRegion.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaParamkey.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaPositionRule.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaRuleCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSavePathConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSingleProcImg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSnapDatabase.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaTrackCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVcaWorkStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVideoOut.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgVoiceTalk.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWall.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWallCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWallWin.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWD1Enable.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWifi.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgWinPreview.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlAlarmAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlDecoderAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlEventAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlItcAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlJpegCapAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlNetAppAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlRaidAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlSerialAbility.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlVideoPic.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgXmlWallAblity.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgZeroChanCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\DrawFun.cpp
# End Source File
# Begin Source File

SOURCE=.\JPEGPicDownload.cpp
# End Source File
# Begin Source File

SOURCE=.\Markup.cpp
# End Source File
# Begin Source File

SOURCE=.\MatCodeSplitter.cpp
# End Source File
# Begin Source File

SOURCE=.\MatCycLink.cpp
# End Source File
# Begin Source File

SOURCE=.\MatDecDnsCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\MatDecoderStatus.cpp
# End Source File
# Begin Source File

SOURCE=.\MatDispChan.cpp
# End Source File
# Begin Source File

SOURCE=.\MatDispChanControl.cpp
# End Source File
# Begin Source File

SOURCE=.\MatDynamicTest.cpp
# End Source File
# Begin Source File

SOURCE=.\MatPassive.cpp
# End Source File
# Begin Source File

SOURCE=.\MatPlayBack.cpp
# End Source File
# Begin Source File

SOURCE=.\MatTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\MatVedioPlatform.cpp
# End Source File
# Begin Source File

SOURCE=.\Picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PTZButton.cpp
# End Source File
# Begin Source File

SOURCE=.\PTZButton1.cpp
# End Source File
# Begin Source File

SOURCE=.\SoundIn.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgAdapterCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgAlarmCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgArrayCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgATMInfoCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgChanCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgDeviceCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgExceptionCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgMatDecCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgPDCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgPreviewCfgV30.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgSerialCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgUserCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgVDCfg.cpp
# End Source File
# Begin Source File

SOURCE=.\SubDlgWndSequence.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveSound.cpp
# End Source File
# Begin Source File

SOURCE=.\XmlUserAbility.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ClientDemo.h
# End Source File
# Begin Source File

SOURCE=.\ClientDemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\DialogMultiNetCard.h
# End Source File
# Begin Source File

SOURCE=.\DialogRecordTimeSpan.h
# End Source File
# Begin Source File

SOURCE=.\Dlg67DVSCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAbilityAutoDetect.h
# End Source File
# Begin Source File

SOURCE=.\DlgAccessCameraCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAddDevice.h
# End Source File
# Begin Source File

SOURCE=.\DlgAES.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmCamCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHost.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostAudioAssociateAlarm.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostDialParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostEnableCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostEventTrigger.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostExternalModule.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostFaultProcess.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostGPRS.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostLED.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostLEDBrightness.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostLogSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostModuleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostNetCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostReportMode.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostRs485.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmhostSubsystem.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostTransparent.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostTriggerCode.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmHostZoomAddr.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmKeyboardUser.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmNetUser.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmOperatorUser.h
# End Source File
# Begin Source File

SOURCE=.\DlgAlarmOutCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgAtmFrameFormatV30.h
# End Source File
# Begin Source File

SOURCE=.\DlgAutoReboot.h
# End Source File
# Begin Source File

SOURCE=.\DlgBroadCast.h
# End Source File
# Begin Source File

SOURCE=.\DlgCcdParam.h
# End Source File
# Begin Source File

SOURCE=.\DlgCertInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgChanInputAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgChannelInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgCheckTime.h
# End Source File
# Begin Source File

SOURCE=.\DlgConfigAll.h
# End Source File
# Begin Source File

SOURCE=.\DlgConfigFlash.h
# End Source File
# Begin Source File

SOURCE=.\DlgCreateVD.h
# End Source File
# Begin Source File

SOURCE=.\DlgCuntomProtocal.h
# End Source File
# Begin Source File

SOURCE=.\DlgCurrentEncodeAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgDecoderAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgDecWinStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceAudioTalkCode.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgDeviceState.h
# End Source File
# Begin Source File

SOURCE=.\DlgDiskQuota.h
# End Source File
# Begin Source File

SOURCE=.\DlgDoTest.h
# End Source File
# Begin Source File

SOURCE=.\DlgDynChanAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgEncodeAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgEncodeJoint.h
# End Source File
# Begin Source File

SOURCE=.\DlgESataMiniSasUsage.h
# End Source File
# Begin Source File

SOURCE=.\DlgEthernetIpv6Cfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgFormatHD.h
# End Source File
# Begin Source File

SOURCE=.\DlgFortify.h
# End Source File
# Begin Source File

SOURCE=.\DlgGatewayCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgHardDiskCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgHolidayCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgInfrareCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgInquestDvr.h
# End Source File
# Begin Source File

SOURCE=.\DlgInquestEvent.h
# End Source File
# Begin Source File

SOURCE=.\DlgInquestFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgDDNS.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgEasyDDNS.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgIPServer.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPAccessCfgStreamServer.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPAddrFilterCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPCFrontAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPCSpecial.h
# End Source File
# Begin Source File

SOURCE=.\DlgIPDomeLocalCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgIscsiCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSBaseInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSImageMergeCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSIpcCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSOverlapCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSRoadInfo.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSUpload.h
# End Source File
# Begin Source File

SOURCE=.\DlgITSWorkState.h
# End Source File
# Begin Source File

SOURCE=.\DlgJpegCaptureCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgJpegFTP.h
# End Source File
# Begin Source File

SOURCE=.\DlgJPEGSnatchConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgLEDTimerSwitch.h
# End Source File
# Begin Source File

SOURCE=.\DlgLimitAngle.h
# End Source File
# Begin Source File

SOURCE=.\DlgLinkStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgLocalConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgLocalLogConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgLocalRecordSchedule.h
# End Source File
# Begin Source File

SOURCE=.\DlgLogSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgMatDecBigScrSplice.h
# End Source File
# Begin Source File

SOURCE=.\DlgMatDecodeChanJoint.h
# End Source File
# Begin Source File

SOURCE=.\DlgMatUnitedSystem.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetraEventVedio.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetraHttps.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetraRecordPackage.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetraSeries.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetworkAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetworkBonding.h
# End Source File
# Begin Source File

SOURCE=.\DlgNetworkFlowTest.h
# End Source File
# Begin Source File

SOURCE=.\DlgNVRCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgOutput.h
# End Source File
# Begin Source File

SOURCE=.\DlgOutputCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgPdcCalibration.h
# End Source File
# Begin Source File

SOURCE=.\DlgPdcRuleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPDCSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayBack.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayDvrRecord.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayLocalFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayLockFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayMotion.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayRemoteFile.h
# End Source File
# Begin Source File

SOURCE=.\DlgPlayRemoteTime.h
# End Source File
# Begin Source File

SOURCE=.\DlgPositionTrackCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPPPCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgPTZCruise.h
# End Source File
# Begin Source File

SOURCE=.\DlgPtzCtrl.h
# End Source File
# Begin Source File

SOURCE=.\DlgPTZPreset.h
# End Source File
# Begin Source File

SOURCE=.\DlgPtzScope.h
# End Source File
# Begin Source File

SOURCE=.\DlgPUStream.h
# End Source File
# Begin Source File

SOURCE=.\DlgQuickAddIpc.h
# End Source File
# Begin Source File

SOURCE=.\DlgRaidConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordLabel.h
# End Source File
# Begin Source File

SOURCE=.\DlgRecordStreamTransType.h
# End Source File
# Begin Source File

SOURCE=.\DlgRegionList.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmInHandle.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteAlarmInPtzInvoke.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteControlAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteEmailAddReceiver.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteFanException.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteHideAlarm.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteHideArea.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteIPAccess.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteKey.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteMotionDetect.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteNetNFS.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemotePullException.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteRecordSchedule.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteShowString.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteVideoInLost.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteVideoInput.h
# End Source File
# Begin Source File

SOURCE=.\DlgRemoteZone.h
# End Source File
# Begin Source File

SOURCE=.\DlgRtspConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgSafetyCabin.h
# End Source File
# Begin Source File

SOURCE=.\DlgScreenLogoCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgSenceControl.h
# End Source File
# Begin Source File

SOURCE=.\DlgSensorAddPreview.h
# End Source File
# Begin Source File

SOURCE=.\DlgSensorCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgSerialTrans.h
# End Source File
# Begin Source File

SOURCE=.\DlgSizeFilter.h
# End Source File
# Begin Source File

SOURCE=.\DlgSnmpCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgSoftHardAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgTalkMREx.h
# End Source File
# Begin Source File

SOURCE=.\DlgTPSRuleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgUpgrade.h
# End Source File
# Begin Source File

SOURCE=.\DlgUploadLogo.h
# End Source File
# Begin Source File

SOURCE=.\DlgUpnpCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaAidRuleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBehaviorCalibrate.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBehaviorCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaBlackList.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaChanCtrlCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDataBase.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDevAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDevAccessCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaDrawMode.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaEnterRegion.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFace.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceDataBase.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceDetect.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceMatchLogSearch.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFaceSnapCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFindBackgroundPic.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaFindSnapData.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaITSCalibrate.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaITSCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaIvmsCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaIvmsSched.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaLaneCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaLF.h
# End Source File
# Begin Source File

SOURCE=.\DlgvcaMaskRegion.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaParamkey.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaPositionRule.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaRuleCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSavePathConfig.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSingleProcImg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaSnapDatabase.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaTrackCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgVcaWorkStatus.h
# End Source File
# Begin Source File

SOURCE=.\DlgVideoOut.h
# End Source File
# Begin Source File

SOURCE=.\DlgVoiceTalk.h
# End Source File
# Begin Source File

SOURCE=.\DlgWall.h
# End Source File
# Begin Source File

SOURCE=.\DlgWallCfg.h
# End Source File
# Begin Source File

SOURCE=.\DlgWallWin.h
# End Source File
# Begin Source File

SOURCE=.\DlgWD1Enable.h
# End Source File
# Begin Source File

SOURCE=.\DlgWifi.h
# End Source File
# Begin Source File

SOURCE=.\DlgWinPreview.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlAlarmAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlDecoderAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlEventAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlItcAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlJpegCapAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlNetAppAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlRaidAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlSerialAbility.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlVideoPic.h
# End Source File
# Begin Source File

SOURCE=.\DlgXmlWallAblity.h
# End Source File
# Begin Source File

SOURCE=.\DlgZeroChanCfg.h
# End Source File
# Begin Source File

SOURCE=.\DrawFun.h
# End Source File
# Begin Source File

SOURCE=.\GeneralDef.h
# End Source File
# Begin Source File

SOURCE=..\..\src\export\header\InterfaceBase.h
# End Source File
# Begin Source File

SOURCE=.\JPEGPicDownload.h
# End Source File
# Begin Source File

SOURCE=.\Markup.h
# End Source File
# Begin Source File

SOURCE=.\MatCodeSplitter.h
# End Source File
# Begin Source File

SOURCE=.\MatCycLink.h
# End Source File
# Begin Source File

SOURCE=.\MatDecDnsCfg.h
# End Source File
# Begin Source File

SOURCE=.\MatDecoderStatus.h
# End Source File
# Begin Source File

SOURCE=.\MatDispChan.h
# End Source File
# Begin Source File

SOURCE=.\MatDispChanControl.h
# End Source File
# Begin Source File

SOURCE=.\MatDynamicTest.h
# End Source File
# Begin Source File

SOURCE=.\MatPassive.h
# End Source File
# Begin Source File

SOURCE=.\MatPlayBack.h
# End Source File
# Begin Source File

SOURCE=.\MatTrans.h
# End Source File
# Begin Source File

SOURCE=.\MatVedioPlatform.h
# End Source File
# Begin Source File

SOURCE=.\Picture.h
# End Source File
# Begin Source File

SOURCE=.\PTZButton.h
# End Source File
# Begin Source File

SOURCE=.\PTZButton1.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SoundIn.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgAdapterCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgAlarmCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgArrayCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgATMInfoCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgChanCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgDeviceCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgExceptionCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgMatDeccfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgPDCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgPreviewCfgV30.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgSerialCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgUserCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgVDCfg.h
# End Source File
# Begin Source File

SOURCE=.\SubDlgWndSequence.h
# End Source File
# Begin Source File

SOURCE=.\WaveSound.h
# End Source File
# Begin Source File

SOURCE=.\XmlUserAbility.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Alarm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\audio.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap_c.bmp
# End Source File
# Begin Source File

SOURCE=.\res\camera.bmp
# End Source File
# Begin Source File

SOURCE=.\res\camera.ico
# End Source File
# Begin Source File

SOURCE=.\res\ClientDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\ClientDemo.rc2
# End Source File
# Begin Source File

SOURCE=.\res\dev_alarm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fortify.bmp
# End Source File
# Begin Source File

SOURCE=.\res\fortify_alarm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00002.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00003.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00004.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00005.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00006.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00007.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00008.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00009.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00010.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico00011.ico
# End Source File
# Begin Source File

SOURCE=.\res\ico1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon2.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon8.ico
# End Source File
# Begin Source File

SOURCE=.\res\IPChan.bmp
# End Source File
# Begin Source File

SOURCE=.\res\login.bmp
# End Source File
# Begin Source File

SOURCE=.\res\logout.bmp
# End Source File
# Begin Source File

SOURCE=.\res\p_r_a.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PAUSE_ENABLE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\play.bmp
# End Source File
# Begin Source File

SOURCE=.\res\PLAY_DISABLE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\PLAY_ENABLE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\playAndAlarm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rec.bmp
# End Source File
# Begin Source File

SOURCE=.\res\rec_play.bmp
# End Source File
# Begin Source File

SOURCE=.\res\step_disable.ico
# End Source File
# Begin Source File

SOURCE=.\res\STOP.ICO
# End Source File
# Begin Source File

SOURCE=.\res\STOP_DISABLE.ICO
# End Source File
# Begin Source File

SOURCE=.\res\tree.bmp
# End Source File
# End Group
# Begin Group "includeCn"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\incCn\DataType.h
# End Source File
# Begin Source File

SOURCE=..\incCn\DecodeCardSdk.h
# End Source File
# Begin Source File

SOURCE=..\incCn\HCNetSDK.h
# End Source File
# Begin Source File

SOURCE=..\incCn\plaympeg4.h
# End Source File
# End Group
# Begin Group "includeEn"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\incEn\DataType.h
# End Source File
# Begin Source File

SOURCE=..\incEn\DecodeCardSdk.h
# End Source File
# Begin Source File

SOURCE=..\incEn\HCNetSDK.h
# End Source File
# Begin Source File

SOURCE=..\incEn\plaympeg4.h
# End Source File
# End Group
# Begin Group "xml"

# PROP Default_Filter ""
# Begin Source File

SOURCE=tinystr.cpp
# End Source File
# Begin Source File

SOURCE=tinystr.h
# End Source File
# Begin Source File

SOURCE=tinyxml.cpp
# End Source File
# Begin Source File

SOURCE=tinyxml.h
# End Source File
# Begin Source File

SOURCE=tinyxmlerror.cpp
# End Source File
# Begin Source File

SOURCE=tinyxmlparser.cpp
# End Source File
# Begin Source File

SOURCE=XmlBase.cpp
# End Source File
# Begin Source File

SOURCE=XmlBase.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Modification.txt
# End Source File
# End Target
# End Project
# Section ClientDemo : {6F074DA6-14D7-4D83-A83D-38AA1D52F1AB}
# 	1:16:IDD_DLG_CCDPARAM:122
# 	2:16:Resource Include:resource.h
# 	2:19:CLASS: CDlgCcdParam:CDlgCcdParam
# 	2:16:IDD_DLG_CCDPARAM:IDD_DLG_CCDPARAM
# 	2:10:ENUM: enum:enum
# 	2:13:DlgCcdParam.h:DlgCcdParam1.h
# 	2:15:DlgCcdParam.cpp:DlgCcdParam1.cpp
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {C4D53BEA-6961-4DBF-A97C-BECE76F174E2}
# 	1:23:IDD_DLG_ITS_OVERLAP_CFG:117
# 	2:16:Resource Include:resource.h
# 	2:18:DlgITSOverlapCfg.h:DlgITSOverlapCfg.h
# 	2:23:IDD_DLG_ITS_OVERLAP_CFG:IDD_DLG_ITS_OVERLAP_CFG
# 	2:10:ENUM: enum:enum
# 	2:24:CLASS: CDlgITSOverlapCfg:CDlgITSOverlapCfg
# 	2:19:Application Include:clientdemo.h
# 	2:20:DlgITSOverlapCfg.cpp:DlgITSOverlapCfg.cpp
# End Section
# Section ClientDemo : {0AB6E01E-87F8-4D59-B775-181DA72B2C1C}
# 	1:21:IDD_DLG_IPADDR_FILTER:123
# 	2:16:Resource Include:resource.h
# 	2:20:DlgIPAddrFilterCfg.h:DlgIPAddrFilterCfg.h
# 	2:10:ENUM: enum:enum
# 	2:26:CLASS: CDlgIPAddrFilterCfg:CDlgIPAddrFilterCfg
# 	2:22:DlgIPAddrFilterCfg.cpp:DlgIPAddrFilterCfg.cpp
# 	2:19:Application Include:clientdemo.h
# 	2:21:IDD_DLG_IPADDR_FILTER:IDD_DLG_IPADDR_FILTER
# End Section
# Section ClientDemo : {6F468570-AD65-43E5-9091-746055444805}
# 	1:21:IDD_DLG_ITS_WORKSTATE:120
# 	2:16:Resource Include:resource.h
# 	2:10:ENUM: enum:enum
# 	2:17:DlgITSWorkState.h:DlgITSWorkState.h
# 	2:19:DlgITSWorkState.cpp:DlgITSWorkState.cpp
# 	2:23:CLASS: CDlgITSWorkState:CDlgITSWorkState
# 	2:21:IDD_DLG_ITS_WORKSTATE:IDD_DLG_ITS_WORKSTATE
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {E54C74B0-DD75-49AF-A78B-0337531F5594}
# 	1:24:IDD_DLG_ITS_ROADINFO_GET:118
# 	2:16:Resource Include:resource.h
# 	2:16:DlgITSRoadInfo.h:DlgITSRoadInfo.h
# 	2:22:CLASS: CDlgITSRoadInfo:CDlgITSRoadInfo
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:clientdemo.h
# 	2:24:IDD_DLG_ITS_ROADINFO_GET:IDD_DLG_ITS_ROADINFO_GET
# 	2:18:DlgITSRoadInfo.cpp:DlgITSRoadInfo.cpp
# End Section
# Section ClientDemo : {4A699F8F-19B5-4BEE-8864-ECD1131BB9DB}
# 	1:18:IDD_DLG_ITS_UPLOAD:119
# 	2:16:Resource Include:resource.h
# 	2:18:IDD_DLG_ITS_UPLOAD:IDD_DLG_ITS_UPLOAD
# 	2:14:DlgITSUpload.h:DlgITSUpload.h
# 	2:20:CLASS: CDlgITSUpload:CDlgITSUpload
# 	2:16:DlgITSUpload.cpp:DlgITSUpload.cpp
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:clientdemo.h
# End Section
# Section ClientDemo : {B46A1241-4AD1-4D81-8676-F1468A1473B5}
# 	1:22:IDD_DLG_ITS_DEVICE_CFG:114
# 	2:16:Resource Include:resource.h
# 	2:20:CLASS: CDlgITSConfig:CDlgITSConfig
# 	2:16:DlgITSConfig.cpp:DlgITSConfig.cpp
# 	2:10:ENUM: enum:enum
# 	2:14:DlgITSConfig.h:DlgITSConfig.h
# 	2:19:Application Include:clientdemo.h
# 	2:22:IDD_DLG_ITS_DEVICE_CFG:IDD_DLG_ITS_DEVICE_CFG
# End Section
# Section ClientDemo : {CC235959-24D2-45A3-BE5F-92BA470B268B}
# 	1:24:IDD_DLG_ITS_GET_BASEINFO:113
# 	2:16:Resource Include:resource.h
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:clientdemo.h
# 	2:16:DlgITSBaseInfo.h:DlgITSBaseInfo.h
# 	2:18:DlgITSBaseInfo.cpp:DlgITSBaseInfo.cpp
# 	2:22:CLASS: CDlgITSBaseInfo:CDlgITSBaseInfo
# 	2:24:IDD_DLG_ITS_GET_BASEINFO:IDD_DLG_ITS_GET_BASEINFO
# End Section
# Section ClientDemo : {34AAB9D9-263E-406A-91C7-53822DF1CDB5}
# 	1:27:IDD_DLG_XML_ITC_ITS_ABILITY:121
# 	2:16:Resource Include:resource.h
# 	2:27:IDD_DLG_XML_ITC_ITS_ABILITY:IDD_DLG_XML_ITC_ITS_ABILITY
# 	2:24:CLASS: CDlgXmlItcAbility:CDlgXmlItcAbility
# 	2:20:DlgXmlItcAbility.cpp:DlgXmlItcAbility.cpp
# 	2:10:ENUM: enum:enum
# 	2:19:Application Include:clientdemo.h
# 	2:18:DlgXmlItcAbility.h:DlgXmlItcAbility.h
# End Section
# Section ClientDemo : {D2305316-2798-4705-BDA2-1C0C71A687D5}
# 	1:21:IDD_DLG_VCA_BLACKLIST:104
# 	2:16:Resource Include:resource.h
# 	2:19:DlgVcaBlackList.cpp:DlgVcaBlackList.cpp
# 	2:17:DlgVcaBlackList.h:DlgVcaBlackList.h
# 	2:10:ENUM: enum:enum
# 	2:21:IDD_DLG_VCA_BLACKLIST:IDD_DLG_VCA_BLACKLIST
# 	2:23:CLASS: CDlgVcaBlackList:CDlgVcaBlackList
# 	2:19:Application Include:clientdemo.h
# End Section
