//========= Copyright Valve Corporation, All rights reserved. ============//
//
//
//=============================================================================
#include "cbase.h"
#include "tf_weapon_Physcannon.h"
#include "../"
//=============================================================================
//
// Weapon SMG tables.
//
IMPLEMENT_NETWORKCLASS_ALIASED( TFPhyscannon, DT_WeaponPhyscannon )

BEGIN_NETWORK_TABLE( CTFPhyscannon, DT_WeaponPhyscannon )
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CTFPhyscannon )
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS( tf_weapon_Physcannon, CTFPhyscannon );
PRECACHE_WEAPON_REGISTER( tf_weapon_Physcannon);

// Server specific.
#ifndef CLIENT_DLL
BEGIN_DATADESC( CTFPhyscannon )
END_DATADESC()
#endif

//=============================================================================
//
// Weapon Physcannon functions.
//

void CWeaponPhysCannon::SecondaryAttack(void)
{
	if (m_flNextSecondaryAttack > gpGlobals->curtime)
		return;

	CBasePlayer* pOwner = ToBasePlayer(GetOwner());

	if (pOwner == NULL)
		return;

	// See if we should drop a held item
	if ((m_bActive) && (pOwner->m_afButtonPressed & IN_ATTACK2))
	{
		// Drop the held object
		m_flNextPrimaryAttack = gpGlobals->curtime + 0.5;
		m_flNextSecondaryAttack = gpGlobals->curtime + 0.5;

		DetachObject();

		DoEffect(EFFECT_READY);

		SendWeaponAnim(ACT_VM_PRIMARYATTACK);
	}
	else
	{
		// Otherwise pick it up
		FindObjectResult_t result = FindObject();
		switch (result)
		{
		case OBJECT_FOUND:
			WeaponSound(SPECIAL1);
			SendWeaponAnim(ACT_VM_PRIMARYATTACK);
			m_flNextSecondaryAttack = gpGlobals->curtime + 0.5f;

			// We found an object. Debounce the button
			m_nAttack2Debounce |= pOwner->m_nButtons;
			break;

		case OBJECT_NOT_FOUND:
			m_flNextSecondaryAttack = gpGlobals->curtime + 0.1f;
			CloseElements();
			break;

		case OBJECT_BEING_DETACHED:
			m_flNextSecondaryAttack = gpGlobals->curtime + 0.01f;
			break;
		}

		DoEffect(EFFECT_HOLDING);
	}
}