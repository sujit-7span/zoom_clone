#pragma once
#include "common_include.h"
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnInitSDK)(ZOOM_SDK_NAMESPACE::InitParam& initParam);
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnCreateMeetingService)(ZOOM_SDK_NAMESPACE::IMeetingService** ppMeetingService);
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnDestroyMeetingService)(ZOOM_SDK_NAMESPACE::IMeetingService* pMeetingService);
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnCreateAuthService)(ZOOM_SDK_NAMESPACE::IAuthService** ppAuthService);
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnDestroyAuthService)(ZOOM_SDK_NAMESPACE::IAuthService* pAuthService);
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnCreateSettingService)(ZOOM_SDK_NAMESPACE::ISettingService** ppSettingService);
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnDestroySettingService)(ZOOM_SDK_NAMESPACE::ISettingService* pSettingService);
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnCreateNetworkConnectionHelper)(ZOOM_SDK_NAMESPACE::INetworkConnectionHelper** ppNetworkHelper);
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnDestroyNetworkConnectionHelper)(ZOOM_SDK_NAMESPACE::INetworkConnectionHelper* pNetworkHelper);
typedef const zchar_t*(*fnGetVersion)();
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnCleanUPSDK)();
#if defined(WIN32)
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnRetrieveUIHooker)(ZOOM_SDK_NAMESPACE::IUIHooker** ppUIHooker);
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnRetrieveCustomizedResourceHelper)(ZOOM_SDK_NAMESPACE::ICustomizedResourceHelper** ppCustomizedResourceHelper);
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnCreateCustomizedUIMgr)(ZOOM_SDK_NAMESPACE::ICustomizedUIMgr** ppCustomizedUIMgr);
typedef ZOOM_SDK_NAMESPACE::SDKError(*fnDestroyCustomizedUIMgr)(ZOOM_SDK_NAMESPACE::ICustomizedUIMgr* pCustomizedUIMgr);
#endif
typedef ZOOM_SDK_NAMESPACE::IZoomSDKVideoSourceHelper*(*fnGetRawdataVideoSourceHelper)();
typedef ZOOM_SDK_NAMESPACE::IZoomSDKAudioRawDataHelper*(*fnGetAudioRawdataHelper)();
typedef ZOOM_SDK_NAMESPACE::SDKError(*fncreateRenderer)(ZOOM_SDK_NAMESPACE::IZoomSDKRenderer** ppRenderer, ZOOM_SDK_NAMESPACE::IZoomSDKRendererDelegate* pDelegate);
typedef ZOOM_SDK_NAMESPACE::SDKError(*fndestroyRenderer)(ZOOM_SDK_NAMESPACE::IZoomSDKRenderer* pRenderer);
typedef bool(*fnHasRawDataLicense)();

class CSDKImpl
{
public:
	virtual ~CSDKImpl();
	static CSDKImpl& GetInst();

	bool ConfigSDKModule(const zchar_t* sdkpath);
	void Uninit();
	//
	virtual	ZOOM_SDK_NAMESPACE::SDKError InitSDK(ZOOM_SDK_NAMESPACE::InitParam& initParam);
	virtual ZOOM_SDK_NAMESPACE::SDKError CreateMeetingService(ZOOM_SDK_NAMESPACE::IMeetingService** ppMeetingService);
	virtual ZOOM_SDK_NAMESPACE::SDKError DestroyMeetingService(ZOOM_SDK_NAMESPACE::IMeetingService* pMeetingService);
	virtual ZOOM_SDK_NAMESPACE::SDKError CreateAuthService(ZOOM_SDK_NAMESPACE::IAuthService** ppAuthService);
	virtual ZOOM_SDK_NAMESPACE::SDKError DestroyAuthService(ZOOM_SDK_NAMESPACE::IAuthService* pAuthService);
	virtual ZOOM_SDK_NAMESPACE::SDKError CreateSettingService(ZOOM_SDK_NAMESPACE::ISettingService** ppSettingService);
	virtual ZOOM_SDK_NAMESPACE::SDKError DestroySettingService(ZOOM_SDK_NAMESPACE::ISettingService* pSettingService);
	virtual ZOOM_SDK_NAMESPACE::SDKError(CreateNetworkConnectionHelper)(ZOOM_SDK_NAMESPACE::INetworkConnectionHelper** ppNetworkHelper);
	virtual ZOOM_SDK_NAMESPACE::SDKError(DestroyNetworkConnectionHelper)(ZOOM_SDK_NAMESPACE::INetworkConnectionHelper* pNetworkHelper);
	virtual const zchar_t*(GetSDKVersion)();
	virtual ZOOM_SDK_NAMESPACE::SDKError(CleanUPSDK)();
#if defined(WIN32)
	virtual ZOOM_SDK_NAMESPACE::SDKError(RetrieveUIHooker)(ZOOM_SDK_NAMESPACE::IUIHooker** ppUIHooker);
	virtual ZOOM_SDK_NAMESPACE::SDKError(RetrieveCustomizedResourceHelper)(ZOOM_SDK_NAMESPACE::ICustomizedResourceHelper** ppCustomizedResourceHelper);
	virtual ZOOM_SDK_NAMESPACE::SDKError(CreateCustomizedUIMgr)(ZOOM_SDK_NAMESPACE::ICustomizedUIMgr** ppCustomizedUIMgr);
	virtual ZOOM_SDK_NAMESPACE::SDKError(DestroyCustomizedUIMgr)(ZOOM_SDK_NAMESPACE::ICustomizedUIMgr* pCustomizedUIMgr);
#endif
	virtual ZOOM_SDK_NAMESPACE::IZoomSDKVideoSourceHelper*(GetRawdataVideoSourceHelper)();
	virtual ZOOM_SDK_NAMESPACE::IZoomSDKAudioRawDataHelper*(GetAudioRawdataHelper)();
	virtual ZOOM_SDK_NAMESPACE::SDKError(createRenderer)(ZOOM_SDK_NAMESPACE::IZoomSDKRenderer** ppRenderer, ZOOM_SDK_NAMESPACE::IZoomSDKRendererDelegate* pDelegate);
	virtual ZOOM_SDK_NAMESPACE::SDKError(destroyRenderer)(ZOOM_SDK_NAMESPACE::IZoomSDKRenderer* pRenderer);
	virtual bool (HasRawDataLicense)();
private:
	CSDKImpl();
	void Reset();
private:
	bool m_bInit;
#if defined(WIN32)
	HMODULE m_hSdk;
#else
	void* m_hSdk;
#endif
	fnInitSDK m_fnInitSDK;
	fnCleanUPSDK m_fnCleanUPSDK;
	fnCreateMeetingService m_fnCreateMeetingService;
	fnDestroyMeetingService m_fnDestroyMeetingService;
	fnCreateAuthService m_fnCreateAuthService;
	fnDestroyAuthService m_fnDestroyAuthService;
	fnCreateSettingService m_fnCreateSettingService;
	fnDestroySettingService m_fnDestroySettingService;
	fnCreateNetworkConnectionHelper m_fnCreateNetworkConnectionHelper;
	fnDestroyNetworkConnectionHelper m_fnDestroyNetworkConnectionHelper;
	fnGetVersion m_fnGetVersion;
#if defined(WIN32)
	fnRetrieveUIHooker m_fnRetrieveUIHooker;
	fnRetrieveCustomizedResourceHelper m_fnRetrieveCustomizedResouceHelper;
	fnCreateCustomizedUIMgr m_fnCreateCustomizedUIMgr;
	fnDestroyCustomizedUIMgr m_fnDestroyCustomizedUIMgr;
#endif
	fnGetRawdataVideoSourceHelper m_fnGetRawdataVideoSourceHelper;
	fnGetAudioRawdataHelper m_fnGetAudioRawdataHelper;
	fncreateRenderer m_fncreateRenderer;
	fndestroyRenderer m_fndestroyRenderer;
	fnHasRawDataLicense	m_fnHasRawDataLicense;
};