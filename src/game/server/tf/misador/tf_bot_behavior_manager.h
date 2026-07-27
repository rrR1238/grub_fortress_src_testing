#ifndef TF_BOT_MANAGER_H
#define TF_BOT_MANAGER_H

#define ACTION_NONE 0;
#define ACTION_FORWARD 1
#define ACTION_BACKWARD 2
#define ACTION_LEFT 3
#define ACTION_RIGHT 4

#include "baseentity.h"

class TFBotBehaviorManager : public CPointEntity
{
public:
	DECLARE_DATADESC();
	TFBotBehaviorManager( void );
	~TFBotBehaviorManager( void );
	virtual void Spawn(void);
	virtual void Think(void);
	void InputParse(inputdata_t &inputdata);
	float m_flTest;
	int parse;
	int m_iAction;
	KeyValues* keyvalues = new KeyValues("test");
	KeyValues* data;
	CUtlVector <KeyValues*> test;
};


#endif