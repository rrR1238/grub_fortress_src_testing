// ALL SKIP STATEMENTS THAT AFFECT THIS SHADER!!!
// ($EMISSIVEBLEND == 0 && $NOFLOW == 1)

#pragma once
#include "shaderlib/cshader.h"
class lux_emissive_ps30_Static_Index
{
	unsigned int m_nEMISSIVEBLEND : 2;
	unsigned int m_nNOFLOW : 2;
	unsigned int m_nDETAILTEXTURE : 2;
	unsigned int m_nSELFILLUMTEXTURE : 2;
	unsigned int m_nMINIMUMLIGHT : 2;
#ifdef _DEBUG
	bool m_bEMISSIVEBLEND : 1;
	bool m_bNOFLOW : 1;
	bool m_bDETAILTEXTURE : 1;
	bool m_bSELFILLUMTEXTURE : 1;
	bool m_bMINIMUMLIGHT : 1;
#endif	// _DEBUG
public:
	void SetEMISSIVEBLEND( int i )
	{
		Assert( i >= 0 && i <= 2 );
		m_nEMISSIVEBLEND = i;
#ifdef _DEBUG
		m_bEMISSIVEBLEND = true;
#endif	// _DEBUG
	}

	void SetNOFLOW( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nNOFLOW = i;
#ifdef _DEBUG
		m_bNOFLOW = true;
#endif	// _DEBUG
	}

	void SetDETAILTEXTURE( int i )
	{
		Assert( i >= 0 && i <= 2 );
		m_nDETAILTEXTURE = i;
#ifdef _DEBUG
		m_bDETAILTEXTURE = true;
#endif	// _DEBUG
	}

	void SetSELFILLUMTEXTURE( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nSELFILLUMTEXTURE = i;
#ifdef _DEBUG
		m_bSELFILLUMTEXTURE = true;
#endif	// _DEBUG
	}

	void SetMINIMUMLIGHT( int i )
	{
		Assert( i >= 0 && i <= 1 );
		m_nMINIMUMLIGHT = i;
#ifdef _DEBUG
		m_bMINIMUMLIGHT = true;
#endif	// _DEBUG
	}

	lux_emissive_ps30_Static_Index(  )
	{
		m_nEMISSIVEBLEND = 0;
		m_nNOFLOW = 0;
		m_nDETAILTEXTURE = 0;
		m_nSELFILLUMTEXTURE = 0;
		m_nMINIMUMLIGHT = 0;
#ifdef _DEBUG
		m_bEMISSIVEBLEND = false;
		m_bNOFLOW = false;
		m_bDETAILTEXTURE = false;
		m_bSELFILLUMTEXTURE = false;
		m_bMINIMUMLIGHT = false;
#endif	// _DEBUG
	}

	int GetIndex() const
	{
		Assert( m_bEMISSIVEBLEND && m_bNOFLOW && m_bDETAILTEXTURE && m_bSELFILLUMTEXTURE && m_bMINIMUMLIGHT );
		AssertMsg( !( ( m_nEMISSIVEBLEND == 0 ) && ( m_nNOFLOW == 1 ) ), "Invalid combo combination ( ( EMISSIVEBLEND == 0 ) && ( NOFLOW == 1 ) )" );
		return ( 1 * m_nEMISSIVEBLEND ) + ( 3 * m_nNOFLOW ) + ( 6 * m_nDETAILTEXTURE ) + ( 18 * m_nSELFILLUMTEXTURE ) + ( 36 * m_nMINIMUMLIGHT ) + 0;
	}
};

#define shaderStaticTest_lux_emissive_ps30 psh_forgot_to_set_static_EMISSIVEBLEND + psh_forgot_to_set_static_NOFLOW + psh_forgot_to_set_static_DETAILTEXTURE + psh_forgot_to_set_static_SELFILLUMTEXTURE + psh_forgot_to_set_static_MINIMUMLIGHT


class lux_emissive_ps30_Dynamic_Index
{
public:
	lux_emissive_ps30_Dynamic_Index(  )
	{
	}

	int GetIndex() const
	{
		return 0;
	}
};

#define shaderDynamicTest_lux_emissive_ps30 1

