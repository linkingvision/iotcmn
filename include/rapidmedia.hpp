//
// Copyright(c) 2019 linkingvision.com
// Distributed under Commercial license (info@linkingvision.com) 
//
#ifndef __V_RAPID_MEDIA_HPP__
#define __V_RAPID_MEDIA_HPP__
#include "utility/type.hpp"
#include "utility/videotype.hpp"

//using namespace std;

class RapidMediaData;
class VE_LIBRARY_API RapidMedia
{
public:
	RapidMedia();
	~RapidMedia();
public:
	/* The Decode one i frame  */
	static bool DecodeiFrame(VideoFrame& packet, RawFrame& pRaw, void**pDecoder);
	static bool DecodeiFrameFreeDec(void* pDec);
public:
	BOOL Init(bool bRealStream, bool bFile, std::string strUrl, std::string strUser,
			std::string strPass, bool bHWAccel = FALSE,
				VSCConnectType connectType = VSC_CONNECT_TCP, 
				double nSpeed = 1.0, bool bEnableAudio = false);
	BOOL PutData(VideoFrame& packet);
	void	SetDataHandler(RMDataHandler handle, void *pContext);
	void	SetRawDataHandler(RMRawVideoHandler handle, void *pContext);

	BOOL Start(time_t nPlayTime = 0);
	BOOL Stop();
	BOOL StartRaw();
	BOOL StopRaw();
	bool Pause();
	bool Resume();
	bool Seek(s64 nTime);
	bool SetSpeed(double nSpeed);
	int GetClientPort();
	bool SetSSRC(std::string strSSRC);
	bool ResetStartTime(s64 nTimeStart);
	
public:
	static std::string GetCodecName(CodecType codec);
public:
	static void SetUseRTPTS(bool bUse);
	static void SetUseLive555(bool bUse);
	static void SetLiteLive555(bool bLite);

public:
	RapidMediaData * m_data;
};
#endif /* __V_RAPID_MEDIA_HPP__ */
