#include "meeting_live_stream_wrap.h"
#include "meeting_service_wrap.h"
BEGIN_ZOOM_SDK_NAMESPACE

IMeetingLiveStreamItemImpl::IMeetingLiveStreamItemImpl(const zchar_t* liveStreamURL, const zchar_t* liveStreamURLDescription)
{
	_liveStreamURL = liveStreamURL;
	_liveStreamURLDescription = liveStreamURLDescription;
}

void IMeetingLiveStreamItemImpl::SetLiveStreamURL(const zchar_t* liveStreamURL)
{
	_liveStreamURL = liveStreamURL;
}

const zchar_t* IMeetingLiveStreamItemImpl::GetLiveStreamURL()
{
	return _liveStreamURL.c_str();
}

void IMeetingLiveStreamItemImpl::SetLiveStreamURLDescription(const zchar_t* liveStreamURLDescription)
{
	_liveStreamURLDescription = liveStreamURLDescription;
}

const zchar_t* IMeetingLiveStreamItemImpl::GetLiveStreamURLDescription()
{
	return _liveStreamURLDescription.c_str();
}

IMeetingLiveStreamController* InitIMeetingLiveStreamControllerFunc(IMeetingLiveStreamCtrlEvent* pEvent, IMeetingServiceWrap* pOwner)
{
	if (pOwner && pOwner->GetSDKObj())
	{
		ZOOM_SDK_NAMESPACE::IMeetingLiveStreamController* pObj = pOwner->GetSDKObj()->GetMeetingLiveStreamController();
		if (pObj)
		{
			pObj->SetEvent(pEvent);
		}
		return pObj;
	}

	return NULL;
}

void UninitIMeetingLiveStreamControllerFunc(IMeetingLiveStreamController* obj)
{
	if (obj)
	{
		obj->SetEvent(NULL);
	}
}

// virtual SDKError CanStartLiveStream() = 0;
IMPL_FUNC_0(IMeetingLiveStreamController, CanStartLiveStream, SDKError, SDKERR_UNINITIALIZE)
// virtual SDKError StartLiveStream(IMeetingLiveStreamItem* item_) = 0;
IMPL_FUNC_1(IMeetingLiveStreamController, StartLiveStream, SDKError, IMeetingLiveStreamItem*, item_, SDKERR_UNINITIALIZE)
// virtual SDKError StartLiveStreamWithSteamingURL(const zchar_t* streamingURL, const zchar_t* streamingKey, const zchar_t* broadcastURL) = 0;
IMPL_FUNC_3(IMeetingLiveStreamController, StartLiveStreamWithSteamingURL, SDKError, const zchar_t*, streamingURL, const zchar_t*, streamingKey, const zchar_t*, broadcastURL, SDKERR_UNINITIALIZE)
// virtual SDKError StopLiveStream() = 0;
IMPL_FUNC_0(IMeetingLiveStreamController, StopLiveStream, SDKError, SDKERR_UNINITIALIZE)
// virtual IList<IMeetingLiveStreamItem* >* GetSupportLiveStreamURL() = 0;
IMPL_FUNC_0(IMeetingLiveStreamController, GetSupportLiveStreamURL, IList<IMeetingLiveStreamItem*>*, NULL)
// virtual LiveStreamStatus GetCurrentLiveStreamStatus() = 0;
IMPL_FUNC_0(IMeetingLiveStreamController, GetCurrentLiveStreamStatus, LiveStreamStatus, LiveStreamStatus_None)
// virtual SDKError StopRawLiveStream() = 0;
IMPL_FUNC_0(IMeetingLiveStreamController, StopRawLiveStream, SDKError, SDKERR_UNINITIALIZE)
//virtual bool IsRawLiveStreamSupported() = 0;
IMPL_FUNC_0(IMeetingLiveStreamController, IsRawLiveStreamSupported, bool, false)
//virtual SDKError CanStartRawLiveStream() = 0;
IMPL_FUNC_0(IMeetingLiveStreamController, CanStartRawLiveStream, SDKError, SDKERR_UNINITIALIZE)
//virtual SDKError RemoveRawLiveStreamPrivilege(unsigned int userid) = 0;
IMPL_FUNC_1(IMeetingLiveStreamController, RemoveRawLiveStreamPrivilege, SDKError, unsigned int, userid, SDKERR_UNINITIALIZE)
//virtual IList<RawLiveStreamInfo>* GetRawLiveStreamingInfoList() = 0;
IMPL_FUNC_0(IMeetingLiveStreamController, GetRawLiveStreamingInfoList, IList<RawLiveStreamInfo>*, NULL)
//virtual IList<unsigned int>* GetRawLiveStreamPrivilegeUserList() = 0;
IMPL_FUNC_0(IMeetingLiveStreamController, GetRawLiveStreamPrivilegeUserList, IList<unsigned int>*, NULL)

END_ZOOM_SDK_NAMESPACE
