#include "cbase.h"

#include "tf_bot_behavior_manager.h"
#include "filesystem.h"

BEGIN_DATADESC(TFBotBehaviorManager)
DEFINE_INPUTFUNC(FIELD_STRING, "ParseFile", InputParse),
END_DATADESC()

LINK_ENTITY_TO_CLASS(tf_bot_behavior_manager, TFBotBehaviorManager)

TFBotBehaviorManager::TFBotBehaviorManager()
{

}

TFBotBehaviorManager::~TFBotBehaviorManager()
{

}

void TFBotBehaviorManager::Spawn()
{
	SetThink(&TFBotBehaviorManager::Think);
	SetNextThink(0.1);
	//if (!keyvalues->LoadFromFile(filesystem, "scripts/test.txt", "MOD")) {
	//	keyvalues->deleteThis();
	//	return;
	//}
	//FOR_EACH_SUBKEY(keyvalues, data)
	//{
	//	test.AddToTail(data);
	//}
	BaseClass::Spawn();
}

void TFBotBehaviorManager::Think()
{
	if (gpGlobals->curtime > m_flTest && parse < test.Count()) {
			parse = parse + 1;
			Msg("Test: %d \n", parse);
			const char* szTest = data->GetString("action");
			float fltest = data->GetFloat("duration");
			if (FStrEq(szTest, "forward")) {
				m_iAction = ACTION_FORWARD;
			}
			else if (FStrEq(szTest, "backward")) {
				m_iAction = ACTION_BACKWARD;
			}
			else if (FStrEq(szTest, "left")) {
				m_iAction = ACTION_LEFT;
			}
			else if (FStrEq(szTest, "right")) {
				m_iAction = ACTION_RIGHT;
			}
			else {
				m_iAction = ACTION_NONE;
			}
			Msg("Duration test: %f \n", fltest);
			m_flTest = gpGlobals->curtime + fltest;
			data = data->GetNextKey();
	}

	if (gpGlobals->curtime > m_flTest && parse == test.Count()) {
		Msg("End Reached");
		m_iAction = ACTION_NONE; // End reached.
	}

	switch (m_iAction) {
	case ACTION_FORWARD:
		Msg("Forward\n");
		m_iAction = ACTION_NONE;
		break;
	case ACTION_BACKWARD:
		Msg("Backward\n");
		m_iAction = ACTION_NONE;
		break;
	case ACTION_LEFT:
		Msg("Left\n");
		m_iAction = ACTION_NONE;
		break;
	case ACTION_RIGHT:
		Msg("Right\n");
		m_iAction = ACTION_NONE;
		break;
	}

	//if (gpGlobals->curtime > m_flTest) {
	//	parse = parse + 1;
	//	if (parse == 4) {
	//		Msg("Parse Ended\n");
	//	}
	//	else {
	//		m_flTest = gpGlobals->curtime + 4.5f;
	//		Msg("Parse: %d \n", parse);
	//	}
	//}
	SetNextThink(0.1);
}

void TFBotBehaviorManager::InputParse(inputdata_t& inputdata)
{
	test.RemoveAll();
	keyvalues->Clear();
	char filename[MAX_PATH];
	V_snprintf(filename, sizeof(filename), "scripts" "/%s.txt", inputdata.value.String());
	if (!keyvalues->LoadFromFile(filesystem, filename, "MOD")) {
		keyvalues->deleteThis();
		return;
	}
	FOR_EACH_SUBKEY(keyvalues, data)
	{
		test.AddToTail(data);
	}
	data = keyvalues->GetFirstSubKey();
	parse = 0;
}