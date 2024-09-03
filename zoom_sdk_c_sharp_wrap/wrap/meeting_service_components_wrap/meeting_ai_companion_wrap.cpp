#include "meeting_ai_companion_wrap.h"
#include "meeting_service_wrap.h"
BEGIN_ZOOM_SDK_NAMESPACE
IMeetingAICompanionController* InitIMeetingAICompanionControllerFunc(IMeetingAICompanionCtrlEvent* pEvent, IMeetingServiceWrap* pOwner)
{
	if (pOwner && pOwner->GetSDKObj())
	{
		ZOOM_SDK_NAMESPACE::IMeetingAICompanionController* pObj = pOwner->GetSDKObj()->GetMeetingAICompanionController();
		if (pObj)
		{
			pObj->SetEvent(pEvent);
		}
		return pObj;
	}

	return NULL;
}

void UninitIMeetingAICompanionControllerFunc(IMeetingAICompanionController* obj)
{
	if (obj)
	{
		obj->SetEvent(NULL);
	}
}

IMPL_FUNC_AND_MEMBER(IMeetingAICompanionController, T_GetMeetingAICompanionSmartSummaryHelper, IMeetingAICompanionSmartSummaryHelperWrap);
#if (defined UserInterfaceClass)
IMPL_FUNC_0(IMeetingAICompanionController, GetMeetingAICompanionSmartSummaryHelper, IMeetingAICompanionSmartSummaryHelper*, NULL)
#endif

END_ZOOM_SDK_NAMESPACE