//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================

#include "cbase.h"

#ifdef CLIENT_DLL
#include "iinput.h"
#endif

#include "tf_weapon_sapper_test.h"
#include "in_buttons.h"
#include "tf_gamerules.h"
#include "tf_weaponbase_gun.h"

// Server specific.
#if !defined( CLIENT_DLL )
	#include "tf_player.h"
	#include "tf_obj_dispenser.h"
	#include "vguiscreen.h"
// Client specific.
#else
	#include "c_tf_player.h"
	#include <igameevents.h>
	#include "tf_hud_menu_engy_build.h"
	#include "tf_hud_menu_engy_destroy.h"
	#include "tf_hud_menu_spy_disguise.h"
	#include "prediction.h"
#endif

//=============================================================================
//
// TFWeaponBase Melee tables.
//
IMPLEMENT_NETWORKCLASS_ALIASED( TFWeaponSapperTest, DT_TFWeaponSapperTest )

BEGIN_NETWORK_TABLE( CTFWeaponSapperTest, DT_TFWeaponSapperTest )
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CTFWeaponSapperTest )
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS(tf_weapon_sapper_test, CTFWeaponSapperTest)

// Server specific.
#if !defined( CLIENT_DLL ) 
BEGIN_DATADESC( CTFWeaponSapperTest )
END_DATADESC()
#endif


CTFWeaponSapperTest::CTFWeaponSapperTest()
{
}


void CTFWeaponSapperTest::Spawn()
{
	PrecacheModel("models/mvm/weapons/v_models/v_pda_spy_bot.mdl");

	BaseClass::Spawn();
}

//-----------------------------------------------------------------------------
// Purpose: cancel menu
//-----------------------------------------------------------------------------
void CTFWeaponSapperTest::PrimaryAttack( void )
{
}

//-----------------------------------------------------------------------------
// Purpose: toggle invis
//-----------------------------------------------------------------------------
void CTFWeaponSapperTest::SecondaryAttack( void )
{
}


//-----------------------------------------------------------------------------
// Purpose: 
// Output : Returns true on success, false on failure.
//-----------------------------------------------------------------------------

#ifdef CLIENT_DLL
void CTFWeaponSapperTest::OnDataChanged( DataUpdateType_t type )
{
	if ( m_iState != m_iOldState && GetOwner() == C_TFPlayer::GetLocalTFPlayer() )
	{
		// Was active, now not
		if ( m_iOldState == WEAPON_IS_ACTIVE && m_iState != m_iOldState )
		{
			CHudBaseBuildMenu *pBuildMenu = GetBuildMenu();
			Assert( pBuildMenu );
			if ( pBuildMenu )
			{
				pBuildMenu->SetBuilderEquipped( false );
			}
		}
		else if ( m_iState == WEAPON_IS_ACTIVE && m_iOldState == WEAPON_IS_CARRIED_BY_PLAYER ) // Was inactive, now is
		{
			CHudBaseBuildMenu *pBuildMenu = GetBuildMenu();
			Assert( pBuildMenu );
			if ( pBuildMenu )
			{
				pBuildMenu->SetBuilderEquipped( true );
			}
		}
	}

	BaseClass::OnDataChanged( type );
}


void CTFWeaponSapperTest::UpdateOnRemove()
{
	CHudBaseBuildMenu *pBuildMenu = GetBuildMenu();
	Assert( pBuildMenu );
	if ( pBuildMenu )
	{
		pBuildMenu->SetBuilderEquipped( false );
	}
	return BaseClass::UpdateOnRemove();
}

#endif

//==============================

//-----------------------------------------------------------------------------
// Purpose: Kill all buildings when pda is changed.
//-----------------------------------------------------------------------------
void CTFWeaponSapperTest::Equip(CBaseCombatCharacter* pOwner)
{
	BaseClass::Equip( pOwner );
}
//-----------------------------------------------------------------------------
// Purpose: Kill all buildings when pda is changed.
//-----------------------------------------------------------------------------
void CTFWeaponSapperTest::Detach(void)
{
	BaseClass::Detach();
}