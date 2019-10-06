// flagThief.cpp : Defines the entry point for the DLL application.
//

#include "bzfsAPI.h"

class flagThief : public bz_Plugin
{
public:
  virtual const char* Name () {return "FlagThief";}
  virtual void Init(const char* config);
  virtual void Event(bz_EventData *eventData);
};

BZ_PLUGIN(flagThief)

void flagThief::Init( const char* /*commandLine*/ )
{
  bz_debugMessage(4,"flagThief plugin loaded");
  Register(bz_ePlayerDieEvent);
}

void flagThief::Event ( bz_EventData *eventData )
{
  if (eventData->eventType != bz_ePlayerDieEvent)
    return;

  bz_PlayerDieEventData_V1 *dieData = (bz_PlayerDieEventData_V1*)eventData;
  
  int killerWins   = bz_getPlayerWins(dieData->killerID);
  int killerLosses = bz_getPlayerLosses(dieData->killerID);
  int killerScore  = killerWins - killerLosses;
  if ((killerScore >= 4) && (dieData->flagKilledWith != "SH") && (dieData->flagKilledWith != "ID") && (dieData->flagKilledWith != "US"))
    bz_removePlayerFlag(dieData->killerID);
  
}
