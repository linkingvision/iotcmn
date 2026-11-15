//
// Copyright(c) 2019 linkingvision.com
// Distributed under Commercial license info@linkingvision.com
//
#ifndef __IOT_VIDEO_TYPE_H__
#define __IOT_VIDEO_TYPE_H__
#include "iottype.hpp"
#include <map>
#include <memory>

typedef enum __CodecType : u32
{
	CODEC_PCMU = 0, 
	CODEC_PCMA = 8,
	CODEC_G711A = 19,
	CODEC_G711U = 20, 
	CODEC_H264 = 96,
	CODEC_H265 = 98,
	CODEC_MPEG4 = 97,
	VID_CODEC_VP9 = 99,
	VID_CODEC_AV1 = 101,
	CODEC_MJPEG = 26,
	CODEC_AAC = 100,
	CODEC_PS = 200,
	CODEC_G722 = 201,
	CODEC_G726 = 202,
	CODEC_OPUS = 203,
	CODEC_ARAW = 204, //audio raw data
	CODEC_NONE = 254,
	CODEC_LAST = 1000
}CodecType;

typedef enum __VideoStreamType
{
	VIDEO_STREAM_VIDEO = 1,
	VIDEO_STREAM_AUDIO = 2,
	VIDEO_STREAM_INFO = 3,
	VIDEO_STREAM_TEXT = 4,
	VIDEO_STREAM_SDP = 5,
	VIDEO_STREAM_PBEVENT = 6,
	VIDEO_STREAM_MUXED = 7, //muxed ps ts
	VIDEO_STREAM_META_DATA = 8, 
	VIDEO_STREAM_END,
	VIDEO_STREAM_LAST
}VideoStreamType;

typedef enum __VideoNetStreamType
{
    VIDEO_NET_STREAM_MAIN = 1,
	VIDEO_NET_STREAM_SUB = 2,    
    VIDEO_NET_STREAM_EXTRA_2 = 3,
    VIDEO_NET_STREAM_LAST
}VideoNetStreamType;


typedef enum __VideoFrameType
{
	VIDEO_FRM_NONE = 0,
	VIDEO_FRM_I = 1,
	VIDEO_FRM_P = 2,
	VIDEO_FRM_B = 3,
	VIDEO_FRM_INFO = 4,
	VIDEO_FRM_AUDIO = 5,
	VIDEO_FRM_PBTIME = 6, //some NVR/DVR has playback time
	VIDEO_FRM_PBPOS = 7, //some NVR/DVR only have playback POS
	VIDEO_FRM_PBEND = 8, 
	VIDEO_FRM_MUXED = 9, //muxed ps ts
	VIDEO_FRM_TRANS_INFO = 10, 
	VIDEO_FRM_PBSPEED = 11, 
	VIDEO_FRM_PBSEEKED = 12, 
	VIDEO_FRM_PB_PAUSED = 13, //some backed will auto pause after seek
	VIDEO_FRM_META_ANA = 14,
	VIDEO_FRM_META_CELL_MOTION = 15,
	VIDEO_FRM_LAST
} VideoFrameType;

typedef struct __VideoFrame
{
	__VideoFrame()
		:rotation(0){}
	VideoStreamType streamType;
 	VideoFrameType frameType;
 	u64 secs;       /* timestamp in seconds */
	u32 msecs;      /* timestamp in mseconds */
	u32 dataLen; /* the length of the payload data */
	u8   *dataBuf;
	u32 bufLen;/* the length of the buffer */
	u32 ptsdiff;/* video Presentation timestamp - Decompression timestamp */
	u32 rotation;/* rotation of this frame, 0, 90, 180, 270 */
}VideoFrame;

typedef struct __VideoStreamInfo
{
	CodecType codec;
	int width;
	int height;
	int fps;
}VideoStreamInfo;

#ifdef _WIN32
#pragma pack(push)	
#pragma pack(1)
#endif
struct __VideoFrameHeader
{
	u32 streamType; /* VideoStreamType */
	u32 frameType; /* VideoFrameType */
	u32 seq;/* seq for frame lost */
	u64 secs;       /* timestamp in seconds */
	u32 msecs;      /* timestamp in mseconds */
	u32 dataLen;
	u32 ptsdiff;/* video Presentation timestamp - Decompression timestamp */
#ifdef _WIN32
};
#else
} __attribute__((packed));
#endif
typedef struct __VideoFrameHeader VideoFrameHeader;

struct __InfoFrameI /* All I frame use this */
{
	u32 video;/* CodecType */
	u32 vWidth;
	u32 vHeight;
#ifdef _WIN32
};
#else
} __attribute__((packed));
#endif
typedef struct __InfoFrameI InfoFrameI;

/* Must same with RAPID_MAX_EXTRA_SIZE don't change that !!!*/
#define EXTRA_MAX_SIZE 1024 * 4
struct __InfoFrame
{
	CodecType video;
	u32 vWidth;
	u32 vHeight;
	u32 vFps;
	u8 vExtra[EXTRA_MAX_SIZE];
	u32 vExtraLen;
	CodecType audio;
	u32 aSampleRate;
	u32 aSampleBit;
	u32 aChannels;
	u8 aExtra[EXTRA_MAX_SIZE];
	u32 aExtraLen;
	u32 padding1;
	u32 padding2;
	u32 padding3;
	u32 padding4;
	u32 padding5;
	u32 padding6;
	u32 padding7;
	u32 padding8;
#ifdef _WIN32
};
#else
} __attribute__((packed));
#endif
typedef struct __InfoFrame InfoFrame;


typedef enum __VidEncryptionAlgo
{
	VID_ENCRY_ALGO_NONE = 0,
	VID_ENCRY_ALGO_AES_128 = 1,
	VID_ENCRY_ALGO_AES_256 = 2,
	VID_ENCRY_ALGO_LAST
} VidEncryptionAlgo;

typedef enum __VidEncryptionType
{
	VID_ENCRY_TYPE_NONE = 0,
	VID_ENCRY_TYPE_I_FRAME = 1,
	VID_ENCRY_TYPE_FULL_FRAME = 2,
	VID_ENCRY_TYPE_LAST
} VidEncryptionType;

/* Encryption is store in database, user can change the key, each key has a ID, 
	the Info Frame store the key ID, if the key in database can't been read, 
	all the data can't be read*/

/*InfoFrameV1 add before each InfoFrameI (I frame), vfs need storage info for playback, vfs don't storage InfoFrameI*/
#define EXTRA_MAX_SIZEV1 16
struct __InfoFrameV1
{
	u16 ver;
	u16 aExtraLen;
	u8 aExtra[EXTRA_MAX_SIZEV1];
	CodecType video;
	u32 vWidth;
	u32 vHeight;
	u32 vFps;
	CodecType audio;
	u32 aSampleRate;
	u32 aSampleBit;
	u32 aChannels;
	u8 encryAlgo; //encryption VidEncryptionAlgo
	u8 encryType;  //encryption VidEncryptionType
	u16 padding1;
	u32 encryKeyId;
	u32 padding2;
	u32 padding3;
#ifdef _WIN32
};
#else
} __attribute__((packed));
#endif
typedef struct __InfoFrameV1 InfoFrameV1;


#ifdef _WIN32
#pragma pack(pop)				
#endif

typedef struct __VideoFrameHeaderLegacy
{
	u32 streamType; /* VideoStreamType */
 	u32 frameType; /* VideoFrameType */
	u32 seq;/* seq for frame lost */
 	u64 secs;       /* timestamp in seconds */
	u32 msecs;      /* timestamp in mseconds */
	u32 dataLen;
	u32 ptsdiff;/* video Presentation timestamp - Decompression timestamp */
}VideoFrameHeaderLegacy;



typedef struct __TransInfoFrame
{
	CodecType vSrc;
	u32 nSrcFPS;	
	u32 nSrcBitrate;	
	u32 nSrcWidth;
	u32 nSrcHeight;
	CodecType vDst;
	u32 nDstFPS;
	u32 nDstBitrate;
	u32 nDstWidth;
	u32 nDstHeight;

	u16 nEngine; /*0:CPU 1:GPU */
	u16 nEngineIdx; /* GPU index */ 
}TransInfoFrame;

typedef enum __VideoRawType
{
	VIDEO_RAW_VIDEO = 1,
	VIDEO_RAW_AUDIO,
	VIDEO_RAW_TEXT,
	VIDEO_RAW_LAST
}VideoRawType;

typedef struct __RawFrame {
	VideoRawType type;
	CodecType codec;
	u64 secs;       /* timestamp in seconds */
	u32 msecs;      /* timestamp in mseconds */
#define VE_NUM_POINTERS 8
	char *data[VE_NUM_POINTERS];
	u64 offset[VE_NUM_POINTERS];
	int linesize[VE_NUM_POINTERS];
	int width, height;
	int format; //AVPixelFormat defined in ffmpeg AV_PIX_FMT_YUV420P 
	u16 aSampleRate;
	u16 aSampleBit;
	u16 aChannels;
	std::shared_ptr<uint8_t> data1;//for cann output data
} RawFrame;

typedef struct __PbEventFrame
{
	s64 nPos;
	float fSpeed;
}PbEventFrame;

inline std::string VidGetCodecName(CodecType codec)
{
	switch (codec)
	{
		case CODEC_PCMU:{return "PCMU";break;}
		case CODEC_PCMA:{return "PCMA";break;}
		case CODEC_G711A:{return "G711A";break;}
		case CODEC_G711U:{return "G711U";break;}
		case CODEC_H264:{return "H264";break;}
		case CODEC_H265:{return "H265";break;}
		case CODEC_MPEG4:{return "MPEG4";break;}
		case CODEC_MJPEG:{return "MJPEG";break;}
		case CODEC_AAC:{return "AAC";break;}
		case VID_CODEC_VP9:{return "VP9";break;}
		case VID_CODEC_AV1:{return "AV1";break;}
		default: return "NONE";
	};
}

inline bool InfoFrameToV1(InfoFrame &pInfo, InfoFrameV1 & pV1)
{
	pV1.ver = 1;
	pV1.aExtraLen = pInfo.aExtraLen;
	if (pV1.aExtraLen > EXTRA_MAX_SIZEV1)
	{
		pV1.aExtraLen = EXTRA_MAX_SIZEV1;
	}
	
	if (pV1.aExtraLen > 0)
	{
		memcpy(pV1.aExtra, pInfo.aExtra, pV1.aExtraLen);
	}
	pV1.video = pInfo.video;
	pV1.vWidth = pInfo.vWidth;
	pV1.vHeight = pInfo.vHeight;
	pV1.vFps = pInfo.vFps;
	pV1.audio= pInfo.audio;
	pV1.aSampleRate = pInfo.aSampleRate;
	pV1.aSampleBit = pInfo.aSampleBit;
	pV1.aChannels = pInfo.aChannels;
	pV1.encryAlgo = 0;
	pV1.encryType = 0;
	pV1.encryKeyId = 0;
	pV1.padding1 = 0;
	pV1.padding2 = 0;
	pV1.padding3 = 0;
	
	return true;
}

inline bool InfoFrameFromV1(InfoFrameV1 & pV1, InfoFrame &pInfo)
{
	memset(&pInfo, 0, sizeof(InfoFrame));
	pInfo.aExtraLen = pV1.aExtraLen;
	
	if (pInfo.aExtraLen > 0)
	{
		memcpy(pInfo.aExtra, pV1.aExtra, pInfo.aExtraLen);
	}
	
	pInfo.vExtraLen = 0;
	
	pInfo.video = pV1.video;
	pInfo.vWidth = pV1.vWidth;
	pInfo.vHeight = pV1.vHeight;
	pInfo.vFps = pV1.vFps;
	pInfo.audio= pV1.audio;
	pInfo.aSampleRate = pV1.aSampleRate;
	pInfo.aSampleBit = pV1.aSampleBit;
	pInfo.aChannels = pV1.aChannels;

	return true;
}



class VidSrcFrameCallback
{
public: 
	VidSrcFrameCallback()
	:bFirstFrame(true){}
	virtual ~VidSrcFrameCallback(){}

public:
	virtual void OnFrame(VideoFrame& frame) = 0;
	virtual void OnBeforeFilterFrame(InfoFrame &pInfoData, VideoFrame& frame){};
public:
	bool bFirstFrame;
};

typedef std::map<VidSrcFrameCallback *, VidSrcFrameCallback *> VidFrameCallbackMap;

class VidOnStreamCallback
{
public:
	VidOnStreamCallback(){}
	virtual ~VidOnStreamCallback(){}

public:
	virtual bool OnRegStreamCallback(std::string strToken, VideoNetStreamType nStream, VidSrcFrameCallback *pCallback)  = 0;
	virtual bool OnUnRegStreamCallback(std::string strToken, VideoNetStreamType nStream, VidSrcFrameCallback *pCallback)  = 0;

};

#endif /* __IOT_VIDEO_TYPE_H__ */
