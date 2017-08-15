#pragma once
#include "Stdafx.h"
#include "CLEO.h"
#include "samp.h"

BOOL setupTextdraws();
BOOL InitOpcodes();
OpcodeResult WINAPI op0C36(CScriptThread *thread);
OpcodeResult WINAPI op0C37(CScriptThread *thread);

#define INVALID_TEXTDRAW	(-1)
#define TDHANDLER_ATTACH	(1)
#define TDHANDLER_UPDATE	(2)

#define THEME_STANDARD		1
#define THEME_CLASSIC		2
#define THEME_ROBIN		3

// ----------------------

#define THEME			THEME_STANDARD
#define SNOOP 1
//#define DOTRACE 1

// ----------------------

#if DOTRACE
char gDbgStr[100];
DWORD gDbgW;
HANDLE hDbgFile = NULL;
#define TRACE1(x,y) sprintf(gDbgStr, x, y);WriteFile(hDbgFile, gDbgStr, strlen(gDbgStr), &gDbgW, NULL);
#define TRACE(x) TRACE1(x,0)
#else
#define TRACE(x)
#define TRACE1(x,y)
#endif

typedef void (*TDHANDLER)(struct SPLHXTEXTDRAW *hxtd, struct stTextdraw *samptd, int reason);

struct SPLHXTEXTDRAW
{
	int			iHandle;
	float			fX;
	float			fY;
	float			fTargetX;
	float			fTargetY;
	TDHANDLER		handler;
};

void removehandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);
void airspeedhandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);
void boxremovehandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);
void fuelpricehandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);
void gpshandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);
void headinghandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);
void altitudehandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);
void progressbarpatchhandler(struct SPLHXTEXTDRAW *hxd, struct stTextdraw *samptd, int reason);

enum PLTEXTDRAWS
{
	PLTD_FUEL,
	PLTD_DAMAGE,
	PLTD_STATUSBARBOX,
	PLTD_FUELDMGBOX,
	PLTD_FUELPRICE,
	PLTD_SATISF,
	PLTD_FUELBAR,
	PLTD_STATUSBAR,
	PLTD_DMGBAR,
	PLTD_ODO,
	PLTD_AIRSPEED,
	PLTD_ALTITUDE,
	PLTD_GPS,
	PLTD_DESTNEAREST,
	PLTD_FUELPCT,
	PLTD_DAMAGEPCT,
	PLTD_HEADING,
	PLTDCOUNT,
};

struct SGAMEDATA
{
	int		carhp;
	int		carheading;
	float		carspeedx;
	float		carspeedy;
	float		carspeedz;
	int		carspeed;
	int		altitude;
};

#define INCAR (gamedata.carhp != -1)

void setupTD(int tdidx, unsigned int x, unsigned int y, unsigned int targetX, unsigned int targetY, TDHANDLER handler);

extern SGAMEDATA gamedata;
extern stSAMP *g_SAMP;
