#include "NetMsgCreate.h"

#include "ManagerGLView.h"
#include "WorldContainer.h"
#include "GLView.h"
#include "Model.h"

using namespace Aftr;
using namespace std;

NetMsgMacroDefinition(NetMsgCreate);

NetMsgCreate::NetMsgCreate() {
	this->setCamPos(Vector(0, 0, 0));
	this->setObjPos(Vector(0, 0, 0));
	this->setCamLookDir(Vector(0, 0, 0));
	this->setRotateZ(0.0f);
}

bool NetMsgCreate::toStream(NetMessengerStreamBuffer& os) const {
	os << this->objPos.x << this->objPos.y << this->objPos.z << this->camPos.x << this->camPos.y << this->camPos.z
		<< this->camLookDir.x << this->camLookDir.y << this->camLookDir.z << this->rotateZ;

	return true;
}

bool NetMsgCreate::fromStream(NetMessengerStreamBuffer& is) {
	is >> this->objPos.x >> this->objPos.y >> this->objPos.z >> this->camPos.x >> this->camPos.y >> this->camPos.z
		>> this->camLookDir.x >> this->camLookDir.y >> this->camLookDir.z >> this->rotateZ;

	return true;
}

void NetMsgCreate::onMessageArrived() {
	WorldContainer* actorList = ManagerGLView::getGLView()->getActorLst();

	if (actorList != nullptr && actorList->size() > 0) {
		actorList->at(0)->setPosition(this->getObjPos());
		actorList->at(0)->getModel()->rotateAboutGlobalZ(this->getRotateZ());
		ManagerGLView::getGLView()->getCamera()->setPosition(this->getCamPos());
		ManagerGLView::getGLView()->getCamera()->setCameraLookDirection(this->getCamLookDir());
	}
	else {
		WO* wo = WO::New(ManagerEnvironmentConfiguration::getSMM() + "/models/rcx_treads.wrl");
		wo->setPosition(this->getObjPos());
		wo->setLabel("Created by Net Msg");
		wo->getModel()->rotateAboutGlobalZ(this->getRotateZ());

		ManagerGLView::getGLView()->getWorldContainer()->push_back(wo);
		ManagerGLView::getGLView()->getActorLst()->push_back(wo);
		ManagerGLView::getGLView()->getCamera()->setPosition(this->getCamPos());
	}
}

string NetMsgCreate::toString() const {
	stringstream ss;
	ss << NetMsg::toString();
	ss << "Payload is: Object Position: " << this->objPos << "...\nCamera Position: " << this->camPos
		<< "....\nRotateZ: " << this->rotateZ << "....\nCamera Look Direction: " << this->camLookDir << endl;

	return ss.str();
}

Vector NetMsgCreate::getObjPos() {
	return this->objPos;
}

void NetMsgCreate::setObjPos(Vector v) {
	this->objPos = v;
}


Vector NetMsgCreate::getCamPos() {
	return this->camPos;
}

void NetMsgCreate::setCamPos(Vector v) {
	this->camPos = v;
}

Vector NetMsgCreate::getCamLookDir() {
	return this->camLookDir;
}

void NetMsgCreate::setCamLookDir(Vector dir) {
	this->camLookDir = dir;
}

float NetMsgCreate::getRotateZ() {
	return this->rotateZ;
}

void NetMsgCreate::setRotateZ(float rotate) {
	this->rotateZ = rotate;
}
