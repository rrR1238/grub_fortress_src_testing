//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: Entities for use in the Robot Destruction TF2 game mode.
//
//=========================================================================//

#include "cbase.h"
#include "tf_logic_dom.h"

#ifdef GAME_DLL
#include "tf_player.h"
#include "tf_gamerules.h"
#else
#include "c_tf_player.h"
#endif // GAME_DLL

#ifdef GAME_DLL
BEGIN_DATADESC( CTFDomLogic )
	DEFINE_KEYFIELD( m_nMinPoints, FIELD_INTEGER, "min_points" ),
	DEFINE_KEYFIELD( m_nPointsPerPlayer, FIELD_INTEGER, "points_per_player" ),

	DEFINE_INPUTFUNC( FIELD_VOID, "ScoreRedPoints", InputScoreRedPoints ),
	DEFINE_INPUTFUNC( FIELD_VOID, "ScoreBluePoints", InputScoreBluePoints ),
	DEFINE_INPUTFUNC( FIELD_VOID, "EnableMaxScoreUpdating", InputEnableMaxScoreUpdating ),
	DEFINE_INPUTFUNC( FIELD_VOID, "DisableMaxScoreUpdating", InputDisableMaxScoreUpdating ),
	DEFINE_INPUTFUNC( FIELD_INTEGER, "SetCountdownTimer", InputSetCountdownTimer ),
	DEFINE_INPUTFUNC( FIELD_STRING, "SetCountdownImage", InputSetCountdownImage ),

	DEFINE_OUTPUT( m_OnRedScoreChanged, "OnRedScoreChanged" ),
	DEFINE_OUTPUT( m_OnBlueScoreChanged, "OnBlueScoreChanged" ),
	DEFINE_OUTPUT( m_OnCountdownTimerExpired, "OnCountdownTimerExpired" ),
END_DATADESC()
#endif

LINK_ENTITY_TO_CLASS( tf_logic_dom, CTFDomLogic );
IMPLEMENT_NETWORKCLASS_ALIASED( TFDomLogic, DT_TFDomLogic )

BEGIN_NETWORK_TABLE( CTFDomLogic, DT_TFDomLogic )
#ifdef CLIENT_DLL
	RecvPropString( RECVINFO( m_iszCountdownImage ) ),
	RecvPropBool( RECVINFO( m_bUsingCountdownImage ) ),
#else
	SendPropStringT( SENDINFO( m_iszCountdownImage ) ),
	SendPropBool( SENDINFO( m_bUsingCountdownImage ) ),
#endif
END_NETWORK_TABLE()


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CTFDomLogic::CTFDomLogic()
{
#ifdef GAME_DLL
	m_iszPropModelName = MAKE_STRING( "models/flag/flag.mdl" );
	ListenForGameEvent( "player_disconnect" );
	m_bMaxScoreUpdatingAllowed = false;
	m_nFlagResetDelay = 60;
	m_nHealDistance = 450;
#endif // GAME_DLL
	m_bUsingCountdownImage = false;

#ifdef CLIENT_DLL
	m_iszCountdownImage[0] = '\0';
#else
	m_iszCountdownImage.Set( NULL_STRING );
#endif
}


//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CTFDomLogic* CTFDomLogic::GetDomLogic()
{
	return assert_cast< CTFDomLogic* >( CTFRobotDestructionLogic::GetRobotDestructionLogic() );
}


#ifdef GAME_DLL
//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTFDomLogic::Precache()
{
	BaseClass::Precache();
}

void CTFDomLogic::FireGameEvent( IGameEvent *pEvent )
{
	const char* pszName = pEvent->GetName();
	if ( FStrEq( pszName, "player_spawn" ) || FStrEq( pszName, "player_disconnect" ) )
	{
		EvaluatePlayerCount();
		return;
	}
	else if( FStrEq( pszName, "teamplay_pre_round_time_left" ) )
	{
		// Eat this event so the RD logic doesn't talk
		return;
	}

	BaseClass::FireGameEvent( pEvent );
}

void CTFDomLogic::OnRedScoreChanged()
{
	m_OnRedScoreChanged.Set( (float)m_nRedScore / m_nMaxPoints, this, this );
}

void CTFDomLogic::OnBlueScoreChanged()
{
	m_OnBlueScoreChanged.Set( (float)m_nBlueScore / m_nMaxPoints, this, this );
}

void CTFDomLogic::EvaluatePlayerCount()
{
	// Bail if we're not allowed
	if ( !m_bMaxScoreUpdatingAllowed )
		return;

	CUtlVector< CTFPlayer* > vecAllPlayers;
	CollectPlayers( &vecAllPlayers );

	m_nMaxPoints = Max( m_nMinPoints, m_nPointsPerPlayer * vecAllPlayers.Count() );
}

void CTFDomLogic::InputScoreRedPoints( inputdata_t& inputdata )
{
	ScorePoints( TF_TEAM_RED, 1, SCORE_CORES_COLLECTED, NULL );
}

void CTFDomLogic::InputScoreBluePoints( inputdata_t& inputdata )
{
	ScorePoints( TF_TEAM_BLUE, 1, SCORE_CORES_COLLECTED, NULL );
}

void CTFDomLogic::InputEnableMaxScoreUpdating( inputdata_t& inputdata )
{
	m_bMaxScoreUpdatingAllowed = true;
	EvaluatePlayerCount();
}

void CTFDomLogic::InputDisableMaxScoreUpdating( inputdata_t& inputdata )
{
	EvaluatePlayerCount();
	m_bMaxScoreUpdatingAllowed = false;
}

void CTFDomLogic::InputSetCountdownTimer( inputdata_t& inputdata )
{
	int nTime = inputdata.value.Int();

	if ( nTime > 0 )
	{
		SetCountdownEndTime( gpGlobals->curtime + nTime );
		SetThink( &CTFDomLogic::CountdownThink );
		SetNextThink( gpGlobals->curtime + 0.05f );
	}
	else
	{
		SetCountdownEndTime( -1.f );
		SetThink( NULL );
	}
}

void CTFDomLogic::CountdownThink( void )
{
	if ( m_flCountdownEndTime > -1.f )
	{
		// if we're done, just reset the end time
		if ( m_flCountdownEndTime < gpGlobals->curtime )
		{
			m_OnCountdownTimerExpired.FireOutput( this, this );
			m_flCountdownEndTime = -1.f;
			SetThink( NULL );
			return;
		}
	}

	SetNextThink( gpGlobals->curtime + 0.05f );
}

void CTFDomLogic::InputSetCountdownImage( inputdata_t& inputdata )
{
	m_bUsingCountdownImage = true;
	m_iszCountdownImage = inputdata.value.StringID();
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTFDomLogic::PlaySound( const char *pszSound, CTFPlayer *pPlayer )
{
	EmitSound_t params;
	params.m_pSoundName = pszSound;
	params.m_flSoundTime = 0;
	params.m_pflSoundDuration = 0;
	params.m_SoundLevel = SNDLVL_70dB;
	CPASFilter filter( pPlayer->GetAbsOrigin() );
	pPlayer->EmitSound( filter, pPlayer->entindex(), params );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CTFDomLogic::TeamWin( int nTeam )
{
	if ( TFGameRules() )
	{
		TFGameRules()->SetWinningTeam( nTeam, WINREASON_PD_POINTS );
	}
}
#endif // GAME_DLL
