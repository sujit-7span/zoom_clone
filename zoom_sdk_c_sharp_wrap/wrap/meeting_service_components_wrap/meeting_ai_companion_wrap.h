#pragma once
#include "common_include.h"
#include "meeting_ai_companion_smart_summary_wrap.h"

BEGIN_ZOOM_SDK_NAMESPACE
class IMeetingServiceWrap;
IMeetingAICompanionController* InitIMeetingAICompanionControllerFunc(IMeetingAICompanionCtrlEvent* pEvent, IMeetingServiceWrap* pOwner);
void UninitIMeetingAICompanionControllerFunc(IMeetingAICompanionController* obj);
BEGIN_CLASS_DEFINE_WITHCALLBACK(IMeetingAICompanionController, IMeetingAICompanionCtrlEvent)
NORMAL_CLASS(IMeetingAICompanionController)
INIT_UNINIT_WITHEVENT_AND_OWNSERVICE(IMeetingAICompanionController, IMeetingServiceWrap)
virtual SDKError SetEvent(IMeetingAICompanionCtrlEvent* pEvent)
{
	external_cb = pEvent;
	return SDKERR_SUCCESS;
}


#if (defined UserInterfaceClass)
private:
DEFINE_FUNC_0(GetMeetingAICompanionSmartSummaryHelper, IMeetingAICompanionSmartSummaryHelper*)
public:
#define T_GetMeetingAICompanionSmartSummaryHelper _GetMeetingAICompanionSmartSummaryHelper
#else
#define T_GetMeetingAICompanionSmartSummaryHelper GetMeetingAICompanionSmartSummaryHelper
#endif
DEFINE_FUNC_AND_MEMBER(T_GetMeetingAICompanionSmartSummaryHelper, IMeetingAICompanionSmartSummaryHelperWrap)

//virtual void onAICompanionFeatureTurnOffByParticipant(IAICompanionFeatureTurnOnAgainHandler* handler) = 0;
CallBack_FUNC_1(onAICompanionFeatureTurnOffByParticipant, IAICompanionFeatureTurnOnAgainHandler*, handler)
//virtual void onAICompanionFeatureSwitchRequested(IAICompanionFeatureSwitchHandler* handler) = 0
CallBack_FUNC_1(onAICompanionFeatureSwitchRequested, IAICompanionFeatureSwitchHandler*, handler)
//virtual void onAICompanionFeatureSwitchRequestResponse(bool bTimeout, bool bAgree, bool bTurnOn) = 0;
CallBack_FUNC_3(onAICompanionFeatureSwitchRequestResponse, bool, bTimeout, bool, bAgree, bool, bTurnOn)
//virtual void onAICompanionFeatureCanNotBeTurnedOff(IList<AICompanionFeature>* features) = 0
CallBack_FUNC_1(onAICompanionFeatureCanNotBeTurnedOff, IList<AICompanionFeature>*, features)

END_CLASS_DEFINE(IMeetingAICompanionController)
END_ZOOM_SDK_NAMESPACE