#pragma once
#include "common_include.h"
BEGIN_ZOOM_SDK_NAMESPACE
class IMeetingServiceWrap;
IMeetingShareController* InitIMeetingShareControllerFunc(IMeetingShareCtrlEvent* pEvent, IMeetingServiceWrap* pOwner);
void UninitIMeetingShareControllerFunc(IMeetingShareController* obj);
BEGIN_CLASS_DEFINE_WITHCALLBACK(IMeetingShareController, IMeetingShareCtrlEvent)
NORMAL_CLASS(IMeetingShareController)
INIT_UNINIT_WITHEVENT_AND_OWNSERVICE(IMeetingShareController, IMeetingServiceWrap)
virtual SDKError SetEvent(IMeetingShareCtrlEvent* pEvent)
{
	external_cb = pEvent;
	return SDKERR_SUCCESS;
}
//virtual SDKError StartAppShare(HWND hwndSharedApp) = 0;
DEFINE_FUNC_1(StartAppShare, SDKError, HWND, hwndSharedApp)
//virtual SDKError StartMonitorShare(const zchar_t* monitorID) = 0;
DEFINE_FUNC_1(StartMonitorShare, SDKError, const zchar_t*, monitorID)
//virtual SDKError StartAirPlayShare() = 0;
DEFINE_FUNC_0(StartAirPlayShare, SDKError)
//virtual SDKError StartWhiteBoardShare() = 0;
DEFINE_FUNC_0(StartWhiteBoardShare, SDKError)
//virtual SDKError IsSupportAdvanceShareOption(AdvanceShareOption option_) = 0;
DEFINE_FUNC_1(IsSupportAdvanceShareOption, SDKError, AdvanceShareOption, option_)
//virtual SDKError StartShareFrame() = 0;
DEFINE_FUNC_0(StartShareFrame, SDKError)
//virtual SDKError StartSharePureComputerAudio() = 0;
DEFINE_FUNC_0(StartSharePureComputerAudio, SDKError)
//virtual SDKError StartShareCamera() = 0;
DEFINE_FUNC_0(StartShareCamera, SDKError)
//virtual SDKError ShowSharingAppSelectWnd() = 0;
DEFINE_FUNC_0(ShowSharingAppSelectWnd, SDKError)

//virtual SDKError StopShare() = 0;
DEFINE_FUNC_0(StopShare, SDKError)
//virtual SDKError BlockWindowFromScreenshare(bool bBlock, HWND hWnd) = 0;
DEFINE_FUNC_3(BlockWindowFromScreenshare, SDKError, bool, bBlock, HWND, hWnd, bool, bChangeWindowStyle)
#if defined(WIN32)
//virtual SDKError SwitchToFitWindowModeWhenViewShare(SDKViewType type) = 0;
DEFINE_FUNC_1(SwitchToFitWindowModeWhenViewShare, SDKError, SDKViewType, type)
//virtual SDKError ViewShare(unsigned int userid, SDKViewType type) = 0;
DEFINE_FUNC_2(ViewShare, SDKError, unsigned int, userid, SDKViewType, type)
#endif
//virtual SDKError PauseCurrentSharing() = 0;
DEFINE_FUNC_0(PauseCurrentSharing, SDKError)
//virtual SDKError ResumeCurrentSharing() = 0;
DEFINE_FUNC_0(ResumeCurrentSharing, SDKError)
//virtual IList<unsigned int >* GetViewableShareSourceList() = 0;
DEFINE_FUNC_0(GetViewableShareSourceList, IList<unsigned int >*)
//virtual SDKError GetViewableShareSourceByUserID(unsigned int userid, ViewableShareSource& shareSource) = 0;
DEFINE_FUNC_2(GetViewableShareSourceByUserID, SDKError, unsigned int, userid, ViewableShareSource&, shareSource)
//virtual SDKError ShowShareOptionDialog() = 0;
DEFINE_FUNC_0(ShowShareOptionDialog, SDKError)
//virtual bool CanStartShare() = 0;
DEFINE_FUNC_0(CanStartShare, bool)
//virtual SDKError IsShareLocked(bool& bLocked) = 0;
DEFINE_FUNC_1(IsShareLocked, SDKError, bool&, bLocked)

//virtual bool	 IsSupportEnableShareComputerSound(bool& bCurEnableOrNot) = 0;
DEFINE_FUNC_1(IsSupportEnableShareComputerSound, bool, bool&, bCurEnableOrNot)
//virtual bool	 IsSupportEnableOptimizeForFullScreenVideoClip(bool& bCurEnableOrNot) = 0;
DEFINE_FUNC_1(IsSupportEnableOptimizeForFullScreenVideoClip, bool, bool&, bCurEnableOrNot)
//virtual SDKError EnableShareComputerSound(bool bEnable) = 0;
DEFINE_FUNC_1(EnableShareComputerSound, SDKError, bool, bEnable)
//virtual SDKError EnableOptimizeForFullScreenVideoClip(bool bEnable) = 0;
DEFINE_FUNC_1(EnableOptimizeForFullScreenVideoClip, SDKError, bool, bEnable)
//virtual SDKError SetMultiShareSettingOptions(MultiShareOption shareOption) = 0;
DEFINE_FUNC_1(SetMultiShareSettingOptions, SDKError, MultiShareOption, shareOption)
//virtual SDKError GetMultiShareSettingOptions(MultiShareOption& shareOption) = 0;
DEFINE_FUNC_1(GetMultiShareSettingOptions, SDKError, MultiShareOption&, shareOption)
//virtual SDKError DisableViewerAnnotate(bool bDisable) = 0;
DEFINE_FUNC_1(DisableViewerAnnotate, SDKError, bool, bDisable)
//virtual bool IsWhiteboardLegalNoticeAvailable() = 0;
DEFINE_FUNC_0(IsWhiteboardLegalNoticeAvailable, bool)
//virtual const zchar_t* getWhiteboardLegalNoticesPrompt() = 0;
DEFINE_FUNC_0(getWhiteboardLegalNoticesPrompt, const zchar_t*)
//virtual const zchar_t* getWhiteboardLegalNoticesExplained() = 0;
DEFINE_FUNC_0(getWhiteboardLegalNoticesExplained, const zchar_t*)
//virtual SDKError SetAudioShareMode(AudioShareMode mode) = 0;
DEFINE_FUNC_1(SetAudioShareMode, SDKError, AudioShareMode, mode)
//virtual SDKError GetAudioShareMode(AudioShareMode& mode) = 0;
DEFINE_FUNC_1(GetAudioShareMode, SDKError, AudioShareMode&, mode)

//virtual void onSharingStatus(SharingStatus status, unsigned int userId) = 0;
CallBack_FUNC_2(onSharingStatus, SharingStatus, status, unsigned int, userId)
//virtual void onLockShareStatus(bool bLocked) = 0;
CallBack_FUNC_1(onLockShareStatus, bool, bLocked)
//virtual void onShareContentNotification(ShareInfo& shareInfo) = 0;
CallBack_FUNC_1(onShareContentNotification, ShareInfo&, shareInfo)
//virtual void onMultiShareSwitchToSingleShareNeedConfirm(IShareSwitchMultiToSingleConfirmHandler* handler_) = 0;	
CallBack_FUNC_1(onMultiShareSwitchToSingleShareNeedConfirm, IShareSwitchMultiToSingleConfirmHandler*, handler_)
//virtual void onShareSettingTypeChangedNotification(ShareSettingType type) = 0;
CallBack_FUNC_1(onShareSettingTypeChangedNotification, ShareSettingType, type)
//virtual void onSharedVideoEnded() = 0;
CallBack_FUNC_0(onSharedVideoEnded)
//virtual void onVideoFileSharePlayError(ZoomSDKVideoFileSharePlayError error) = 0;
CallBack_FUNC_1(onVideoFileSharePlayError, ZoomSDKVideoFileSharePlayError, error)
END_CLASS_DEFINE(IMeetingShareController)
END_ZOOM_SDK_NAMESPACE