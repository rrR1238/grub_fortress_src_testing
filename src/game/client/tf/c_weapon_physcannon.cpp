#include "cbase.h"
#include "tf_weaponbase.h"

class C_WeaponPhysCannon : public C_TFWeaponBase
{
	DECLARE_CLASS(C_WeaponPhysCannon, C_TFWeaponBase);
public:
	DECLARE_CLIENTCLASS();
	DECLARE_PREDICTABLE();

};

IMPLEMENT_NETWORKCLASS_ALIASED(WeaponPhysCannon, DT_WeaponPhysCannon)

BEGIN_NETWORK_TABLE(C_WeaponPhysCannon, DT_WeaponPhysCannon)
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA(C_WeaponPhysCannon)
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS(tf_weapon_physcannon, C_WeaponPhysCannon);