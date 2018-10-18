#ifndef __LINUX_PLAYM4_H__
#define __LINUX_PLAYM4_H__

#ifdef __cplusplus
	extern "C" 
	{
#endif

//typedef unsigned int HWND;
//typedef void * HDC;

#define PLAYM4_API 

#define __stdcall

typedef struct tagSystemTime
{
	short wYear;
	short wMonth;
	short wDayOfWeek;
	short wDay;
	short wHour;
	short wMinute;
	short wSecond;
	short wMilliseconds;
}SYSTEMTIME;

#ifndef CALLBACK
#define CALLBACK
#endif
//Max channel numbers
#define PLAYM4_MAX_SUPPORTS 500
//Wave coef range;
#define MIN_WAVE_COEF -100
#define MAX_WAVE_COEF 100

//Timer type
#define TIMER_1 1 //Only 16 timers for every process.Default TIMER;
#define TIMER_2 2 //Not limit;But the precision less than TIMER_1; 

//BUFFER TYPE
#define BUF_VIDEO_SRC 1
#define BUF_AUDIO_SRC 2
#define BUF_VIDEO_RENDER 3
#define BUF_AUDIO_RENDER 4

//Error code
#define  PLAYM4_NOERROR					0	//no error
#define	 PLAYM4_PARA_OVER				1	//input parameter is invalid;
#define  PLAYM4_ORDER_ERROR				2	//The order of the function to be called is error.
#define	 PLAYM4_TIMER_ERROR				3	//Create multimedia clock failed;
#define  PLAYM4_DEC_VIDEO_ERROR			4	//Decode video data failed.
#define  PLAYM4_DEC_AUDIO_ERROR			5	//Decode audio data failed.
#define	 PLAYM4_ALLOC_MEMORY_ERROR		6	//Allocate memory failed.
#define  PLAYM4_OPEN_FILE_ERROR			7	//Open the file failed.
#define  PLAYM4_CREATE_OBJ_ERROR		8	//Create thread or event failed
#define  PLAYM4_CREATE_DDRAW_ERROR		9	//Create DirectDraw object failed.
#define  PLAYM4_CREATE_OFFSCREEN_ERROR 10	//failed when creating off-screen surface.
#define  PLAYM4_BUF_OVER			   11	//buffer is overflow
#define  PLAYM4_CREATE_SOUND_ERROR	   12	//failed when creating audio device.	
#define	 PLAYM4_SET_VOLUME_ERROR	   13	//Set volume failed
#define  PLAYM4_SUPPORT_FILE_ONLY	   14	//The function only support play file.
#define  PLAYM4_SUPPORT_STREAM_ONLY	   15	//The function only support play stream.
#define  PLAYM4_SYS_NOT_SUPPORT		   16	//System not support.
#define  PLAYM4_FILEHEADER_UNKNOWN     17	//No file header.
#define  PLAYM4_VERSION_INCORRECT	   18	//The version of decoder and encoder is not adapted.  
#define  PLAYM4_INIT_DECODER_ERROR     19	//Initialize decoder failed.
#define  PLAYM4_CHECK_FILE_ERROR	   20	//The file data is unknown.
#define  PLAYM4_INIT_TIMER_ERROR	   21	//Initialize multimedia clock failed.
#define	 PLAYM4_BLT_ERROR			   22	//Blt failed.
#define  PLAYM4_UPDATE_ERROR		   23	//Update failed.
#define  PLAYM4_OPEN_FILE_ERROR_MULTI  24   //openfile error, streamtype is multi
#define  PLAYM4_OPEN_FILE_ERROR_VIDEO  25   //openfile error, streamtype is video
#define  PLAYM4_JPEG_COMPRESS_ERROR    26   //JPEG compress error
#define  PLAYM4_EXTRACT_NOT_SUPPORT    27	//Don't support the version of this file.
#define  PLAYM4_EXTRACT_DATA_ERROR     28	//extract video data failed.
#define  PLAYM4_SECRET_KEY_ERROR       29	//Secret key is error //add 20071218
#define  PLAYM4_DECODE_KEYFRAME_ERROR  30   //add by hy 20090318
#define  PLAYM4_NEED_MORE_DATA         31   //add by hy 20100617
#define  PLAYM4_INVALID_PORT		   32	//add by cj 20100913

#define  PLAYM4_FAIL_UNKNOWN		   99   //Fail, but the reason is unknown;	

//Max display regions.
#define MAX_DISPLAY_WND 4

//Display type
#define DISPLAY_NORMAL  1   
#define DISPLAY_QUARTER 2
#define DISPLAY_YC_SCALE 4	//add by gb 20091116

//Display buffers
#define MAX_DIS_FRAMES 50
#define MIN_DIS_FRAMES 1

//Locate by
#define BY_FRAMENUM  1
#define BY_FRAMETIME 2

//Source buffer
#define SOURCE_BUF_MAX	1024*100000
#define SOURCE_BUF_MIN	1024*50

//Stream type
#define STREAME_REALTIME 0
#define STREAME_FILE	 1

//frame type
#define T_AUDIO16	101
#define T_AUDIO8	100
#define T_UYVY		1
#define T_YV12		3
#define T_RGB32		7

//capability
#define SUPPORT_DDRAW		1 
#define SUPPORT_BLT         2 
#define SUPPORT_BLTFOURCC   4 
#define SUPPORT_BLTSHRINKX  8 
#define SUPPORT_BLTSHRINKY  16
#define SUPPORT_BLTSTRETCHX 32
#define SUPPORT_BLTSTRETCHY 64
#define SUPPORT_SSE         128
#define SUPPORT_MMX			256 

// HIK_MEDIAINFO
#define FOURCC_HKMI			0x484B4D49	// "HKMI" HIK_MEDIAINFO
// System in package format
#define SYSTEM_NULL			0x0	       // no system layer,  pure audio or video streams
#define SYSTEM_HIK          0x1				// HIKVISION file layer
#define SYSTEM_MPEG2_PS     0x2				// PS Package
#define SYSTEM_MPEG2_TS     0x3				// TS Package
#define SYSTEM_RTP          0x4				// rtp Package
#define SYSTEM_RTPHIK       0x401				// rtp Package

// Video encoding type
#define VIDEO_NULL          0x0 // No video
#define VIDEO_H264          0x1 // The standard H.264 HIKVISION H.264 can use this definition
#define VIDEO_MPEG4         0x3 // standardMPEG4
#define VIDEO_MJPEG			0x4
#define VIDEO_AVC264        0x0100

//Audio coding type
#define AUDIO_NULL          0x0000 // No Audio
#define AUDIO_ADPCM         0x1000 // ADPCM 
#define AUDIO_MPEG          0x2000 // MPEG The series audio decoder Adaptive variety of MPEG audio
// G Series of audio
#define AUDIO_RAW_DATA8		0x7000      //The 8k the original data of the sampling rate
#define AUDIO_RAW_UDATA16	0x7001      //16k of the original data of the sampling rate
#define AUDIO_G711_U		0x7110
#define AUDIO_G711_A		0x7111
#define AUDIO_G722_1		0x7221
#define AUDIO_G723_1        0x7231
#define AUDIO_G726_U        0x7260
#define AUDIO_G726_A        0x7261
#define AUDIO_G729          0x7290
#define AUDIO_AMR_NB		0x3000

#define SYNCDATA_VEH	    1 //Sync data: vehicle info	
#define SYNCDATA_IVS	    2 Syncdata: smart info

typedef struct tagHKRect
{
	unsigned long nLeft;	
	unsigned long nTop;
	unsigned long nRight;
	unsigned long nBottom;
}HKRECT;
//Frame position
typedef struct{
	int nFilePos;
	int nFrameNum;
	int nFrameTime;
	int nErrorFrameNum;
	SYSTEMTIME *pErrorTime;
	int nErrorLostFrameNum;
	int nErrorFrameSize;
}FRAME_POS,*PFRAME_POS;

//Frame Info
typedef struct{
	int nWidth; // audio Sample Rate
	int nHeight; // audio Sample bits
	int nStamp;
	int nType;
	int nFrameRate; // audio channel
	unsigned int dwFrameNum;
}FRAME_INFO;

//Frame 
typedef struct{
	char *pDataBuf;
	int  nSize;
	int  nFrameNum;
	int  bIsAudio;
	int  nReserved;
}FRAME_TYPE;

//Watermark Info	//add by gb 080119
typedef struct{
	char *pDataBuf;
	int  nSize;
	int  nFrameNum;
	int  bRsaRight;
	int  nReserved;
}WATERMARK_INFO;

typedef struct SYNCDATA_INFO 
{
	unsigned int dwDataType;		
	unsigned int dwDataLen;		
	unsigned char* pData;			
} SYNCDATA_INFO;

#ifndef _HIK_MEDIAINFO_FLAG_
#define _HIK_MEDIAINFO_FLAG_
typedef struct _HIK_MEDIAINFO_				// modified by gb 080425
{
	unsigned int    media_fourcc;			// "HKMI": 0x484B4D49 Hikvision Media Information
	unsigned short  media_version;			// Version: refers to the information structure version 
                                                        //number, currently 0x0101, Version 1.01, 01:
                                                        //Major version number; 01: sub-version number.
	unsigned short  device_id;				// device ID 		
    
	unsigned short  system_format;          // System package layer
    unsigned short  video_format;           // Video encoding type
	
    unsigned short  audio_format;           // Audio coding type
	unsigned char   audio_channels;         //channel no.  
    unsigned char   audio_bits_per_sample;  // Like bit rate
    unsigned int    audio_samplesrate;      // Sampling rate
    unsigned int    audio_bitrate;          //Compressed audio bit rate, units£ºbit
	
    unsigned int    reserved[4];            // 
}HIK_MEDIAINFO;
#endif

typedef struct  
{
	int nPort;
	char * pBuf;
	int nBufLen;
	int nWidth;
	int nHeight;
	int nStamp;
	int nType;
	int nUser;
}DISPLAY_INFO;
typedef struct PLAYM4_SYSTEM_TIME  
{
	unsigned int dwYear;	 
	unsigned int dwMon;	 
	unsigned int dwDay;	 
	unsigned int dwHour;	 
	unsigned int dwMin;	 
	unsigned int dwSec;	
	unsigned int dwMs;		
} PLAYM4_SYSTEM_TIME;
//////////////////////////////////////////////////////////////////////////////
//API
//////////////////////////////////////////////////////////////////////////////

////////////////ver 1.0///////////////////////////////////////
//Initialize DirecDraw.Now invalid.
 int   PlayM4_InitDDraw(HWND hWnd);
//Release directDraw; Now invalid.
 int  PlayM4_RealeseDDraw();

 int  PlayM4_OpenFile(int nPort,char * sFileName);
 int  PlayM4_CloseFile(int nPort);
 int  PlayM4_Play(int nPort, HWND hWnd);
 int  PlayM4_Stop(int nPort);
 int  PlayM4_Pause(int nPort,unsigned int nPause);
 int  PlayM4_Fast(int nPort);
 int  PlayM4_Slow(int nPort);
 int  PlayM4_OneByOne(int nPort);
 int  PlayM4_SetPlayPos(int nPort,float fRelativePos);
 float  PlayM4_GetPlayPos(int nPort);
 int  PlayM4_SetFileEndMsg(int nPort,HWND hWnd,unsigned int nMsg);
 int  PlayM4_SetVolume(int nPort,unsigned short nVolume);
 int  PlayM4_StopSound();
 int  PlayM4_PlaySound(int nPort);
 int  PlayM4_OpenStream(int nPort,unsigned char * pFileHeadBuf,unsigned int nSize,unsigned int nBufPoolSize);
 int  PlayM4_InputData(int nPort,unsigned char * pBuf,unsigned int nSize);
 int  PlayM4_CloseStream(int nPort);
 int    PlayM4_GetCaps();
 unsigned int  PlayM4_GetFileTime(int nPort);
 unsigned int  PlayM4_GetPlayedTime(int nPort);
		int	 PlayM4_GetFileTimeEx(int nPort, unsigned int* pStart, unsigned int* pStop, unsigned int* pRev);
 unsigned int  PlayM4_GetPlayedFrames(int nPort);

////////////////ver 2.0 added///////////////////////////////////////
 int 	PlayM4_SetDecCallBack(int nPort,void (CALLBACK* DecCBFun)(int nPort,char * pBuf,int nSize,FRAME_INFO * pFrameInfo, int nReserved1,int nReserved2));
 int 	PlayM4_SetDisplayCallBack(int nPort,void (CALLBACK* DisplayCBFun)(int nPort,char * pBuf,int nSize,int nWidth,int nHeight,int nStamp,int nType,int nReserved));

 int 	PlayM4_ConvertToBmpFile(char * pBuf,int nSize,int nWidth,int nHeight,int nType,char *sFileName);

 unsigned int 	PlayM4_GetFileTotalFrames(int nPort);
 unsigned int 	PlayM4_GetCurrentFrameRate(int nPort);
 unsigned int 	PlayM4_GetPlayedTimeEx(int nPort);
 int 	PlayM4_SetPlayedTimeEx(int nPort,unsigned int nTime);
 unsigned int 	PlayM4_GetCurrentFrameNum(int nPort);
 int 	PlayM4_SetStreamOpenMode(int nPort,unsigned int nMode);
 unsigned int 	PlayM4_GetFileHeadLength();
 unsigned int 	PlayM4_GetSdkVersion();

////////////////ver 2.2 added///////////////////////////////////////
 unsigned int   PlayM4_GetLastError(int nPort);
 int  PlayM4_RefreshPlay(int nPort);
// int  PlayM4_SetOverlayMode(int nPort,int bOverlay,COLORREF colorKey);
 int  PlayM4_GetPictureSize(int nPort,int *pWidth,int *pHeight);
 int  PlayM4_SetPicQuality(int nPort,int bHighQuality);
 int  PlayM4_PlaySoundShare(int nPort);
 int  PlayM4_StopSoundShare(int nPort);

////////////////ver 2.4 added///////////////////////////////////////
 int  PlayM4_GetStreamOpenMode(int nPort);
 int  PlayM4_GetOverlayMode(int nPort);
// COLORREF  PlayM4_GetColorKey(int nPort);
 unsigned short  PlayM4_GetVolume(int nPort);
 int  PlayM4_GetPictureQuality(int nPort,int *bHighQuality);
 unsigned int  PlayM4_GetSourceBufferRemain(int nPort);
 int  PlayM4_ResetSourceBuffer(int nPort);
 int  PlayM4_SetSourceBufCallBack(int nPort,unsigned int nThreShold,void (CALLBACK * SourceBufCallBack)(int nPort,unsigned int nBufSize,unsigned int dwUser,void*pResvered),unsigned int dwUser,void *pReserved);
 int  PlayM4_ResetSourceBufFlag(int nPort);
 int  PlayM4_SetDisplayBuf(int nPort,unsigned int nNum);
 unsigned int  PlayM4_GetDisplayBuf(int nPort);
 int  PlayM4_OneByOneBack(int nPort);
 int  PlayM4_SetFileRefCallBack(int nPort, void (__stdcall *pFileRefDone)(unsigned int nPort,unsigned int nUser),unsigned int nUser);
 int  PlayM4_SetCurrentFrameNum(int nPort,unsigned int nFrameNum);
 int  PlayM4_GetKeyFramePos(int nPort,unsigned int nValue, unsigned int nType, PFRAME_POS pFramePos);
 int  PlayM4_GetNextKeyFramePos(int nPort,unsigned int nValue, unsigned int nType, PFRAME_POS pFramePos);
#if (WINVER >= 0x0400)
//Note: These funtion must be builded under win2000 or above with Microsoft Platform sdk.
//	    You can download the sdk from "http://www.microsoft.com/msdownload/platformsdk/sdkupdate/";
 int  PlayM4_InitDDrawDevice();
 void  PlayM4_ReleaseDDrawDevice();
 unsigned int  PlayM4_GetDDrawDeviceTotalNums();
 int  PlayM4_SetDDrawDevice(int nPort,unsigned int nDeviceNum);
 int  PlayM4_GetDDrawDeviceInfo(unsigned int nDeviceNum,char *  lpDriverDescription,unsigned int nDespLen,char * lpDriverName ,unsigned int nNameLen,HMONITOR *hhMonitor);
 int    PlayM4_GetCapsEx(unsigned int nDDrawDeviceNum);
#endif
 int  PlayM4_ThrowBFrameNum(int nPort,unsigned int nNum);

////////////////ver 2.5 added///////////////////////////////////////
 int  PlayM4_SetDisplayType(int nPort,int nType);
 int  PlayM4_GetDisplayType(int nPort);
 int  PlayM4_SyncToAudio(int nPort, int bSyncToAudio);

////////////////ver 3.0 added///////////////////////////////////////
 int  PlayM4_SetDecCBStream(int nPort,unsigned int nStream);
 int  PlayM4_SetDisplayRegion(int nPort,unsigned int nRegionNum, HKRECT *pSrcRect, HWND hDestWnd, int bEnable);
 int  PlayM4_RefreshPlayEx(int nPort,unsigned int nRegionNum);
#if (WINVER >= 0x0400)
//Note: The funtion must be builded under win2000 or above with Microsoft Platform sdk.
//	    You can download the sdk from http://www.microsoft.com/msdownload/platformsdk/sdkupdate/;
 int  PlayM4_SetDDrawDeviceEx(int nPort,unsigned int nRegionNum,unsigned int nDeviceNum);
#endif
/////////////////v3.2 added/////////////////////////////////////////

 int  PlayM4_GetRefValue(int nPort,unsigned char  *pBuffer, unsigned int *pSize);
 int  PlayM4_SetRefValue(int nPort,unsigned char  *pBuffer, unsigned int nSize);
 int  PlayM4_OpenStreamEx(int nPort,unsigned char * pFileHeadBuf,unsigned int nSize,unsigned int nBufPoolSize);
 int  PlayM4_CloseStreamEx(int nPort);
 int  PlayM4_InputVideoData(int nPort,unsigned char * pBuf,unsigned int nSize);
 int  PlayM4_InputAudioData(int nPort,unsigned char * pBuf,unsigned int nSize);
 int  PlayM4_RegisterDrawFun(int nPort,void (CALLBACK* DrawFun)(int nPort,HDC hDc,int nUser),int nUser);
 int  PlayM4_RigisterDrawFun(int nPort,void (CALLBACK* DrawFun)(int nPort,HDC hDc,int nUser),int nUser);
//////////////////v3.4/////////////////////////////////////////////////////
 int  PlayM4_SetTimerType(int nPort,unsigned int nTimerType,unsigned int nReserved);
 int  PlayM4_GetTimerType(int nPort,unsigned int *pTimerType,unsigned int *pReserved);
 int  PlayM4_ResetBuffer(int nPort,unsigned int nBufType);
 unsigned int  PlayM4_GetBufferValue(int nPort,unsigned int nBufType);
//////////////////V3.6/////////////////////////////////////////////////////////
 int  PlayM4_AdjustWaveAudio(int nPort,int nCoefficient);
 int  PlayM4_SetVerifyCallBack(int nPort, unsigned int nBeginTime, unsigned int nEndTime, void (__stdcall * funVerify)(int nPort, FRAME_POS * pFilePos, unsigned int bIsVideo, unsigned int nUser),  unsigned int  nUser);
 int  PlayM4_SetAudioCallBack(int nPort, void (__stdcall * funAudio)(int nPort, char * pAudioBuf, int nSize, int nStamp, int nType, int nUser), int nUser);
 int  PlayM4_SetEncTypeChangeCallBack(int nPort,void(CALLBACK *funEncChange)(int nPort,int nUser),int nUser);
 int  PlayM4_SetColor(int nPort, unsigned int nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);
 int  PlayM4_GetColor(int nPort, unsigned int nRegionNum, int *pBrightness, int *pContrast, int *pSaturation, int *pHue);
 int  PlayM4_SetEncChangeMsg(int nPort,HWND hWnd,unsigned int nMsg);
 int  PlayM4_GetOriginalFrameCallBack(int nPort, int bIsChange,int bNormalSpeed,int nStartFrameNum,int nStartStamp,int nFileHeader,void(CALLBACK *funGetOrignalFrame)(int nPort,FRAME_TYPE *frameType, int nUser),int nUser);
 int  PlayM4_GetFileSpecialAttr(int nPort, unsigned int *pTimeStamp,unsigned int *pFileNum ,unsigned int *pReserved);
 unsigned int  PlayM4_GetSpecialData(int nPort);
 int  PlayM4_SetCheckWatermarkCallBack(int nPort,void(CALLBACK* funCheckWatermark)(int nPort,WATERMARK_INFO* pWatermarkInfo,unsigned int nUser),unsigned int nUser);
 int  PlayM4_SetImageSharpen(int nPort,unsigned int nLevel);
 int  PlayM4_GetThrowBFrameCallBack(int nPort,void(CALLBACK* funThrowBFrame)(int nPort,unsigned int nBFrame,unsigned int nUser),unsigned int nUser);
 int  PlayM4_SetDecodeFrameType(int nPort,unsigned int nFrameType);
 int  PlayM4_SetPlayMode(int nPort,int bNormal);
 int  PlayM4_SetGetUserDataCallBack(int nPort,void(CALLBACK* funGetUserData)(int nPort,unsigned char  *pUserBuf,unsigned int nBufLen,unsigned int nUser),unsigned int nUser);
 int  PlayM4_SetOverlayFlipMode(int nPort,int bTrue);
 unsigned int  PlayM4_GetAbsFrameNum(int nPort); 

//////////////////V4.7.0.0//////////////////////////////////////////////////////
////convert yuv to jpeg
 int  PlayM4_ConvertToJpegFile(char * pBuf,int nSize,int nWidth,int nHeight,int nType,char *sFileName);
 int  PlayM4_SetJpegQuality(int nQuality);
//set deflash
 int  PlayM4_SetDeflash(int nPort,int bDefalsh);
 int  PlayM4_SetDecCallBackEx(int nPort,void (CALLBACK* DecCBFun)(int nPort,char * pBuf,int nSize,FRAME_INFO * pFrameInfo, int nReserved1,int nReserved2), char* pDest, int nDestSize);
//////////////////V4.8.0.0/////////////////////////////////////////////////////////
//check discontinuous frame number as error data?
 int  PlayM4_CheckDiscontinuousFrameNum(int nPort, int bCheck);
//get bmp or jpeg
 int  PlayM4_GetBMP(int nPort,unsigned char * pBitmap,unsigned int nBufSize,unsigned int* pBmpSize);
 int  PlayM4_GetJPEG(int nPort,unsigned char * pJpeg,unsigned int nBufSize,unsigned int* pJpegSize);
//dec call back mend
 int  PlayM4_SetDecCallBackMend(int nPort,void (CALLBACK* DecCBFun)(int nPort,char * pBuf,int nSize,FRAME_INFO * pFrameInfo, int nUser,int nReserved2), int nUser);

 int  PlayM4_SetSecretKey(int nPort, int lKeyType, char *pSecretKey, int lKeyLen);

// add by gb 2007-12-23
 int  PlayM4_SetFileEndCallback(int nPort, void(CALLBACK*FileEndCallback)(int nPort, void *pUser), void *pUser);

// add by gb 080131 version 4.9.0.1
 int  PlayM4_GetPort(int* nPort);
 int  PlayM4_FreePort(int nPort);

 int  PlayM4_SetDisplayCallBackEx(int nPort,void (CALLBACK* DisplayCBFun)(DISPLAY_INFO *pstDisplayInfo), int nUser);
 int  PlayM4_SkipErrorData(int nPort, int bSkip);

 int  PlayM4_SetDecCallBackExMend(int nPort, void (CALLBACK* DecCBFun)(int nPort, char* pBuf, int nSize, FRAME_INFO* pFrameInfo, 
																							int nUser, int nReserved2), char* pDest, int nDestSize, int nUser);

 int  PlayM4_ReversePlay(int nPort);

int PlayM4_SetSyncRef(int nPort, int nAccuracy, int nSyncFlag);
 
/*Params: nAccuracy --- 
 
         nSyncFlag --- REF_ONCE:   Reference time, that inform the benchmark port starting global time synchronization Timeline£»
                            REF_ALWAYS: Always refer to the reference port requires real-time global time assigned to the synchronized timeline; currently support this mode first */

int  PlayM4_SyncToRef(int nPort, int nSyncRefPort ,int bEnable);

/*Params:  nSyncRefPort --- Set to the port number of the synchronization time basis;*/


#ifdef __cplusplus
	}
#endif
			
#endif
