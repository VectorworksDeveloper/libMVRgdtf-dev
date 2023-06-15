//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "SceneDataExchange.h"
#include "Include/IMediaRessourceVectorInterface.h"

namespace VectorworksMVR
{
	//----------------------------------------------------------------------------------------
	class CMVRxchangeServiceImpl : public VCOMImpl<IMVRxchangeService>
	{
	public:
		CMVRxchangeServiceImpl();
		virtual ~CMVRxchangeServiceImpl();
		
		//Interface
	public:
        virtual VCOMError VCOM_CALLTYPE     ConnectToLocalService(const ConnectToLocalServiceArgs& service);
        virtual VCOMError VCOM_CALLTYPE     LeaveLocalService();
        virtual VCOMError VCOM_CALLTYPE     GetLocalServices(GetLocalServicesArgs& arg);

		virtual VCOMError VCOM_CALLTYPE     ConnectToRemoteService(const ConnectToRemoteServiceArgs& service);
		virtual VCOMError VCOM_CALLTYPE     LeaveRemoteService();

		virtual VCOMError VCOM_CALLTYPE     OnMessage(MVRxchangeMessageHandler& messageHandler);
		virtual VCOMError VCOM_CALLTYPE     SendMessage(const SendMessageArgs& messageHandler);


	};
}
