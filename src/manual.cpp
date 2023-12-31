#include "manual.h"
#include "event.h"

ManualOverride::ManualOverride(EvseManager &evse) :
  _evse((&evse))
{
  _version = 0;
}

ManualOverride::~ManualOverride()
{
}

bool ManualOverride::claim()
{
  EvseProperties props(EvseState::Active == _evse->getState() ?  EvseState::Disabled : EvseState::Active);
  return claim(props);
}

bool ManualOverride::claim(EvseProperties &props)
{
  if (!props.hasAutoRelease()) props.setAutoRelease(true);
  return _evse->claim(EvseClient_OpenEVSE_Manual, EvseManager_Priority_Manual, props);
}

bool ManualOverride::release()
{
  return _evse->release(EvseClient_OpenEVSE_Manual);
}

bool ManualOverride::toggle()
{
  if(!isActive())
  {
    return claim();
  }

  return release();
}

bool ManualOverride::getProperties(EvseProperties &props)
{
  if(isActive()) {
    props = _evse->getClaimProperties(EvseClient_OpenEVSE_Manual);
    return true;
  }

  return false;
}

uint8_t ManualOverride::getVersion() {
   return _version;
}

uint8_t ManualOverride::setVersion(uint8_t version) {
  _version = version;
  return _version;
}
 
