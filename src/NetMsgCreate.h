#pragma once
#include "NetMsg.h"
#include "Vector.h"
#ifdef AFTR_CONFIG_USE_BOOST

namespace Aftr {

	class NetMsgCreate : public NetMsg {
	public:
		NetMsgMacroDeclaration(NetMsgCreate);

		NetMsgCreate();
		//virtual ~NetMsgCreate();
		virtual bool toStream(NetMessengerStreamBuffer& os) const;
		virtual bool fromStream(NetMessengerStreamBuffer& is);
		virtual void onMessageArrived();
		virtual std::string toString() const;

		//getters and setters
		Vector getObjPos();
		void setObjPos(Vector v);
		Vector getCamPos();
		void setCamPos(Vector v);
		Vector getCamLookDir();
		void setCamLookDir(Vector dir);
		float getRotateZ();
		void setRotateZ(float rotate);

	protected:
		Vector objPos; //object position
		Vector camPos; //camera position
		Vector camLookDir; //camera look direction
		float rotateZ; //rotate on Z axis
	};
}

#endif
