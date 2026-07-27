//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: PDA Weapon
//
//=============================================================================

#ifndef TF_WEAPON_PDA_H
#define TF_WEAPON_PDA_H
#ifdef _WIN32
#pragma once
#endif

#include "tf_shareddefs.h"
#include "tf_weaponbase.h"

#if defined( CLIENT_DLL ) 
	#define CTFWeaponSapperTest C_TFWeaponSapperTest
#endif

class CTFWeaponSapperTest : public CTFWeaponBase
{
public:
	DECLARE_CLASS( CTFWeaponSapperTest, CTFWeaponBase );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();

#if !defined( CLIENT_DLL ) 
	DECLARE_DATADESC();
#endif

	CTFWeaponSapperTest();

	virtual void	Spawn();
	virtual void		Equip(CBaseCombatCharacter* pOwner);
	virtual void		Detach();
//	virtual void	Precache();
	virtual void	PrimaryAttack();
	virtual void	SecondaryAttack();
	virtual int		GetWeaponID( void ) const						{ return TF_WEAPON_SAPPER_TEST; }
	virtual bool	ShouldDrawCrosshair( void )						{ return false; }
	virtual bool	VisibleInWeaponSelection(void) { return false; }
	virtual bool	HasPrimaryAmmo()								{ return true; }
	virtual bool	CanBeSelected()									{ return true; }
#ifdef CLIENT_DLL
	virtual void	OnDataChanged( DataUpdateType_t type ) OVERRIDE;
	virtual void	UpdateOnRemove() OVERRIDE;
#endif


public:	
	CTFWeaponInfo	*m_pWeaponInfo;

private:
#ifdef CLIENT_DLL
	void HideBuildMenu() const;
#endif

	CTFWeaponSapperTest( const CTFWeaponSapperTest & ) {}
};


#endif // TF_WEAPON_PDA_H
