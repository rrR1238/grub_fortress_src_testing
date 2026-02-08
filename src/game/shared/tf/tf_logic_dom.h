//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Entities for use in the Robot Destruction TF2 game mode.
//
//=========================================================================//
#ifndef PLAYER_DESTRUCTION_H
#define PLAYER_DESTRUCTION_H
#pragma once

#include "cbase.h"
#include "tf_logic_robot_destruction.h"

#ifdef CLIENT_DLL
	#define CTFDomLogic C_TFDomLogic
	#define CDomDispenser C_DomDispenser
#endif

//-----------------------------------------------------------------------------
class CTFDomLogic : public CTFRobotDestructionLogic
{
public:
#ifdef GAME_DLL
	DECLARE_DATADESC();
#endif // GAME_DLL
	DECLARE_CLASS( CTFDomLogic, CTFRobotDestructionLogic )
	DECLARE_NETWORKCLASS();

	virtual EType GetType() const { return TYPE_DOMINATION; }

	CTFDomLogic();
	static CTFDomLogic* GetDomLogic();

#ifdef GAME_DLL
	virtual void Precache() OVERRIDE;

	virtual void FireGameEvent( IGameEvent *pEvent ) OVERRIDE;

	void InputScoreRedPoints( inputdata_t& inputdata );
	void InputScoreBluePoints( inputdata_t& inputdata );
	void InputEnableMaxScoreUpdating( inputdata_t& inputdata );
	void InputDisableMaxScoreUpdating( inputdata_t& inputdata );
	void InputSetCountdownTimer( inputdata_t& inputdata );
	void InputSetCountdownImage( inputdata_t& inputdata );

	void PlayPropDropSound( CTFPlayer *pPlayer );
	void PlayPropPickupSound( CTFPlayer *pPlayer );

	void CountdownThink( void );
	int GetPointsOnPlayerDeath( void ){ return m_nPointsOnPlayerDeath; }
	virtual int GetHealDistance( void ) OVERRIDE { return m_nHealDistance; }
	virtual void TeamWin( int nTeam ) OVERRIDE;

#endif // GAME_DLL

	string_t GetCountdownImage( void ) OVERRIDE { return m_iszCountdownImage; }
	virtual bool IsUsingCustomCountdownImage( void ) OVERRIDE{ return m_bUsingCountdownImage; }

private:
#ifdef GAME_DLL
	void PlaySound( const char *pszSound, CTFPlayer *pPlayer );
	virtual void OnRedScoreChanged() OVERRIDE;
	virtual void OnBlueScoreChanged() OVERRIDE;
	
	void EvaluatePlayerCount();

	void SetCountdownImage( string_t iszCountdownImage ) { m_iszCountdownImage = iszCountdownImage; }

	string_t m_iszPropModelName;
	string_t m_iszPropDropSound;
	string_t m_iszPropPickupSound;

	int m_nMinPoints;
	int m_nPointsPerPlayer;
	bool m_bMaxScoreUpdatingAllowed;

	int m_nFlagResetDelay;
	int m_nHealDistance;

	CObjectDispenser* CreateDispenser( int iTeam );
	CHandle< CObjectDispenser > m_hRedDispenser;
	CHandle< CObjectDispenser > m_hBlueDispenser;

	COutputFloat m_OnRedScoreChanged;
	COutputFloat m_OnBlueScoreChanged;

	COutputEvent m_OnCountdownTimerExpired;
#endif // GAME_DLL

	CNetworkHandle( CTFPlayer, m_hRedTeamLeader );
	CNetworkHandle( CTFPlayer, m_hBlueTeamLeader );

	CNetworkVar( bool, m_bUsingCountdownImage );

#ifdef CLIENT_DLL
	char		m_iszCountdownImage[MAX_PATH];
#else
	CNetworkVar( string_t, m_iszCountdownImage );
	int m_nPointsOnPlayerDeath;
#endif
};

class CDomDispenser :
#ifdef GAME_DLL
	public CObjectDispenser
#else
	public C_ObjectDispenser
#endif
{
#ifdef GAME_DLL
	DECLARE_CLASS( CDomDispenser, CObjectDispenser )
#else
	DECLARE_CLASS( CDomDispenser, C_ObjectDispenser )
#endif
	DECLARE_NETWORKCLASS();
	DECLARE_DATADESC();
public:
#ifdef GAME_DLL
	virtual float GetDispenserRadius( void ) OVERRIDE
	{
		if ( CTFDomLogic::GetRobotDestructionLogic() && ( CTFDomLogic::GetRobotDestructionLogic()->GetType() == CTFDomLogic::TYPE_PLAYER_DESTRUCTION ) )
		{
			return CTFDomLogic::GetRobotDestructionLogic()->GetHealDistance();
		}

		return 450;
	}

	virtual void Spawn( void ) OVERRIDE;
	void OnGoActive( void ) OVERRIDE;
	void GetControlPanelInfo( int nPanelIndex, const char *&pPanelName ) OVERRIDE;

#endif
};

#endif// PLAYER_DESTRUCTION_H
