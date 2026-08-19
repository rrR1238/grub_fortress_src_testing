//========= Copyright Valve Corporation, All rights reserved. ============//
//
//
//=============================================================================
#ifndef TF_WEAPON_Physcannon_H
#define TF_WEAPON_Physcannon_H
#ifdef _WIN32
#pragma once
#endif

#include "tf_weaponbase_gun.h"

// Client specific.
#ifdef CLIENT_DLL
#define CTFPhyscannon C_TFPhyscannon
#endif

//=============================================================================
//
// TF Weapon Sub-machine gun.
//
class CTFPhyscannon : public CTFWeaponBaseGun
{
public:

	DECLARE_CLASS( CTFPhyscannon, CTFWeaponBaseGun );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

	// Server specific.
#ifdef GAME_DLL
	DECLARE_DATADESC();
#endif

	CTFPhyscannon() {}
	~CTFPhyscannon() {}

	void SecondaryAttack();

	virtual int		GetWeaponID( void ) const			{ return TF_WEAPON_PHYSCANNON; }

private:

	CTFPhyscannon( const CTFPhyscannon & ) {}
};

#endif // TF_WEAPON_Physcannon_H
