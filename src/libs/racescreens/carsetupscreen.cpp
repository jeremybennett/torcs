/***************************************************************************

    file        : carsetupscreen.cpp
    created     : Wed Aug 21 13:27:34 CET 2013
    copyright   : (C) 2013 Bernhard Wymann
    email       : berniw@bluewin.ch
    version     : $Id$                                  

 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <stdlib.h>
#ifdef WIN32
#include <windows.h>
#endif
#include <tgfclient.h>
#include <car.h>
#include <portability.h>
#include <racescreens.h>
#include <robottools.h>
#include <vector>

static void *scrHandle = NULL;
static void	*prevHandle = NULL;

static tCarElt	*rmCar;
static tRmInfo  *rmInfo;

static void rmSet(void *vp);
static void rmUpdateMM(void *vp);
static void rmUpdateM(void *vp);
static void rmUpdateP(void *vp);
static void rmUpdatePP(void *vp);

class cGuiSetupValue {
	private:
		void* scr;	// screen
		tCarPitSetupValue* v;
		int id;	// GUI widget id
		tdble steerincs;
		tdble steerdecs;
		tdble steerincb;
		tdble steerdecb;
		const char* unit;
		const char* format;
	
		void setValue(tdble value)
		{
			if (value > v->max) {
				value = v->max;
			} else if (value < v->min) {
				value = v->min;
			}
			v->value = value;
			value = GfParmSI2Unit(unit, value);
			const int BUFSIZE = 32;
			char buf[BUFSIZE];

			snprintf(buf, BUFSIZE, format, value);
			GfuiEditboxSetString(scr, id, buf);
		}

	public:
		void set()
		{
			const char *val = GfuiEditboxGetString(scr, id);
			tdble value = (tdble) atof(val);
			value = GfParmUnit2SI(unit, value);
			setValue(value);
		}

		void updateMM() { update(steerdecb); }
		void updateM()	{ update(steerdecs); }
		void updateP()	{ update(steerincs); }
		void updatePP() { update(steerincb); }

		void update(tdble delta)
		{
			tdble value = v->value;
			value += delta;
			setValue(value);
		}

		cGuiSetupValue(void* scr, tCarPitSetupValue* v, const char* unit, const char* format, int font, int x, int y, int w, int len):
			scr(scr),
			v(v),
			unit(unit),
			format(format)
		{
			const int BUFSIZE = 256;
			char buf[BUFSIZE];

			steerincb = (v->max - v->min)/10.0f;
			steerdecb = -steerincb;
			steerincs = steerincb/10.0f;
			steerdecs = -steerincs;

			snprintf(buf, BUFSIZE, format, GfParmSI2Unit(unit, v->value));
			const int sp = 3;
			const int bw = 10;
			const int minw = 30+4*(bw+sp);
			if (w < minw) w = minw; // Minimal width;
			id = GfuiEditboxCreate(scr, buf, font, x + 2*(bw+sp) + 5, y, w - 4*(bw+sp) - 10, len, this, (tfuiCallback)NULL, rmSet, 5);

			tdble bid;
			bid = GfuiLeanButtonCreate(scr, "-", font, x+bw/2, y, bw, GFUI_ALIGN_HC_VB, 1,
				this, rmUpdateMM, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
			bid = GfuiLeanButtonCreate(scr, "-", font, x+bw/2+bw+sp, y, bw, GFUI_ALIGN_HC_VB, 1,
				this, rmUpdateM, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
			bid = GfuiLeanButtonCreate(scr, "+", font, x+w-(bw+sp+bw/2), y, bw, GFUI_ALIGN_HC_VB, 1,
				this, rmUpdateP, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
			bid = GfuiLeanButtonCreate(scr, "+", font, x+w-bw/2, y, bw, GFUI_ALIGN_HC_VB, 1,
				this, rmUpdatePP, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
		}
	
};


static void rmSet(void *vp)
{
	cGuiSetupValue* c = static_cast<cGuiSetupValue*>(vp);
	c->set();
}

static void rmUpdateMM(void *vp)
{
	cGuiSetupValue* c = static_cast<cGuiSetupValue*>(vp);
	c->updateMM();
}

static void rmUpdateM(void *vp)
{
	cGuiSetupValue* c = static_cast<cGuiSetupValue*>(vp);
	c->updateM();
}

static void rmUpdateP(void *vp)
{
	cGuiSetupValue* c = static_cast<cGuiSetupValue*>(vp);
	c->updateP();
}

static void rmUpdatePP(void *vp)
{
	cGuiSetupValue* c = static_cast<cGuiSetupValue*>(vp);
	c->updatePP();
}


static void onSave(void * /* dummy */)
{
	RtSaveCarPitSetup(
		rmCar->_carHandle,
		&(rmCar->pitcmd.setup),
		PRACTICE,
		rmCar->_modName,
		rmCar->_driverIndex,
		rmInfo->track->internalname,
		rmCar->_carName
	);
}


static std::vector<cGuiSetupValue*> values;

static const char* unitdeg = "deg";
static const char* unitkpa = "kPa";
static const char* unitlbsin = "lbs/in";
static const char* unitmm = "mm";
static const char* unitlbsins = "lbs/in/s";
static const char* unitNm = "N.m";

static const char* f52 = "%5.2f";
static const char* f43 = "%4.3f";
static const char* d3 = "%3.0f";
static const char* d5 = "%5.0f";


void *RmCarSetupScreenInit(void *prevMenu, tCarElt *car, tRmInfo* reInfo)
{
	const int BUFSIZE = 1024;
	char buf[BUFSIZE];
	
	prevHandle = prevMenu;
	
	rmCar = car;
	rmInfo = reInfo;

	if (scrHandle) {
		GfuiScreenRelease(scrHandle);
		for (std::vector<cGuiSetupValue*>::iterator it = values.begin(); it != values.end(); ++it) {
			delete *it;
		}
		values.clear();
	}
	
	scrHandle = GfuiMenuScreenCreate("Car Setup");


	static const int x0 = 20;
	static const int y0 = 415;
	static const int dy = -12;
	static const int xoff = 112;
	static const int xoff2 = 40;

	int i;
	static const int font = GFUI_FONT_SMALL_C;
	int col = 0;

	// Suspension/Wheel settings
	GfuiLabelCreate(scrHandle, "Ride height [mm]:", font, x0, y0 + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Camber [deg]:", font, x0, y0 + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Toe [deg]:", font, x0, y0 + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	int y = y0 + (3.3f * dy);
	col = 0;
	GfuiLabelCreate(scrHandle, "Spring [lbs/in]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Packers [mm]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Slow bump [lbs/in/s]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Slow rebound [lbs/in/s]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Fast bump [lbs/in/s]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Fast rebound [lbs/in/s]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);

	static const char* wheellabel[4] = {"Front right wheel", "Front left wheel", "Rear right wheel", "Rear left wheel"};

	for (i = 0; i < 4; i++) {
		col = 0;
		GfuiLabelCreate(scrHandle, wheellabel[i], font, x0 + xoff*(i+1) + xoff2, y0 - dy, GFUI_ALIGN_HL_VB, 0);
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.wheelrideheight[i]), unitmm, d3, font, x0 + xoff*(i+1) + xoff2, y0 + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.wheelcamber[i]), unitdeg, f52, font, x0 + xoff*(i+1) + xoff2, y0 + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.wheeltoe[i]), unitdeg, f52, font, x0 + xoff*(i+1) + xoff2, y0 + (col++ * dy), 102, 5));
		y = y0 + (3.3f * dy);
		col = 0;	
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.suspspring[i]), unitlbsin, d5, font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.susppackers[i]), unitmm, d3, font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.suspslowbump[i]), unitlbsins, d5, font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.suspslowrebound[i]), unitlbsins, d5, font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.suspfastbump[i]), unitlbsins, d5, font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.suspfastrebound[i]), unitlbsins, d5, font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), 102, 5));
	
	}

	// Steer, brake and axle settings
	y = y0 + 9.8f*dy;
	col = 1;
	GfuiLabelCreate(scrHandle, "Various settings", font, x0 + xoff + xoff2, y, GFUI_ALIGN_HL_VB, 0);

	GfuiLabelCreate(scrHandle, "Steer lock [deg]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Brake front-rear [-]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Brake pressure [kPa]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Front wing [deg]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Rear wing [deg]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	
	col = 1;
	values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.steerLock), unitdeg, f52, font, x0 + xoff + xoff2, y + (col++ * dy), 102, 5));
	values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.brakeRepartition), NULL, f43, font, x0 + xoff + xoff2, y + (col++ * dy), 102, 5));
	values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.brakePressure), unitkpa, d5, font, x0 + xoff + xoff2, y + (col++ * dy), 102, 5));
	values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.wingangle[0]), unitdeg, f52, font, x0 + xoff + xoff2, y + (col++ * dy), 102, 5));
	values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.wingangle[1]), unitdeg, f52, font, x0 + xoff + xoff2, y + (col++ * dy), 102, 5));

	col = 1;
	i = 2;
	GfuiLabelCreate(scrHandle, "ARB spring [lbs/in]:", font, x0 + xoff*i + xoff2, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "3rd spring [lbs/in]:", font, x0 + xoff*i + xoff2, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "3rd bump [lbs/in/s]:", font, x0 + xoff*i + xoff2, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "3rd rebound [lbs/in/s]:", font, x0 + xoff*i + xoff2, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "3rd X0 [mm]:", font, x0 + xoff*i + xoff2, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	
	static const char* axlelabel[2] = {"Front axle", "Rear axle"};

	int j;
	for (j = 0; j < 2; j++) {
		col = 1;
		i = j + 3;

		GfuiLabelCreate(scrHandle, axlelabel[j], font, x0 + xoff*i + xoff2, y, GFUI_ALIGN_HL_VB, 0);
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.arbspring[j]), unitlbsin, d5, font, x0 + xoff*i + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.thirdspring[j]), unitlbsin, d5, font, x0 + xoff*i + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.thirdbump[j]), unitlbsins, d5, font, x0 + xoff*i + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.thirdrebound[j]), unitlbsins, d5, font, x0 + xoff*i + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.thirdX0[j]), unitmm, d3, font, x0 + xoff*i + xoff2, y + (col++ * dy), 102, 5));


	}

	// Differential and gears
	y = y + 6.8f*dy;
	col = 1;
	GfuiLabelCreate(scrHandle, "Type:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Ratio [-]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Front min bias [-]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Front max bias [-]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Slip bias [-]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Accel locking torque [Nm]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
	GfuiLabelCreate(scrHandle, "Brake locking torque [Nm]:", font, x0, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);

	// enum TDiffType { NONE = 0, SPOOL = 1, FREE = 2, LIMITED_SLIP = 3, VISCOUS_COUPLER = 4};
	static const char* diffPos[3] = {"Front differential", "Rear differential", "Center differential"};
	static const char* diffType[5] = {"None", "Spool", "Free", "1.5 way LSD", "Viscous coupler"};

	for (i = 0; i < 3; i++) {
		col = 0;
		
		GfuiLabelCreate(scrHandle, diffPos[i], font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
		GfuiLabelCreate(scrHandle, diffType[rmCar->pitcmd.setup.diffType[i]], font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.diffratio[i]), NULL, f43, font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.diffmintqbias[i]), NULL, f43, font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.diffmaxtqbias[i]), NULL, f43, font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.diffslipbias[i]), NULL, f43, font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.difflockinginputtq[i]), unitNm, d5, font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), 102, 5));
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.difflockinginputbraketq[i]), unitNm, d5, font, x0 + xoff*(i+1) + xoff2, y + (col++ * dy), 102, 5));
	}

	col = 0;
	GfuiLabelCreate(scrHandle, "Gearbox ratios", font, x0 + xoff*4 + xoff2, y + (col++ * dy), GFUI_ALIGN_HL_VB, 0);

	for (i = 0; i < 8; i++) {
		snprintf(buf, BUFSIZE, "%d:", i + 1);
		GfuiLabelCreate(scrHandle, buf, font, x0 + xoff*4 + xoff2, y + (col * dy), GFUI_ALIGN_HL_VB, 0);
		values.push_back(new cGuiSetupValue(scrHandle, &(rmCar->pitcmd.setup.gearsratio[i]), NULL, f43, font, x0 + xoff*4 + xoff2 + 12, y + (col++ * dy), 90, 5));
	}

//	GfuiScreenAddBgImg(scrHandle, "data/img/splash-mouseconf.png");	
//	GfuiMenuDefaultKeysAdd(scrHandle);

	//GfuiAddKey(scrHandle, 13, "Save", NULL, onSave, NULL);
	GfuiButtonCreate(scrHandle, "Save", GFUI_FONT_LARGE, 160, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
		NULL, onSave, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);


	GfuiButtonCreate(scrHandle, "Cancel", GFUI_FONT_LARGE, 480, 40, 150, GFUI_ALIGN_HC_VB, GFUI_MOUSE_UP,
				prevMenu, GfuiScreenActivate, NULL, (tfuiCallback)NULL, (tfuiCallback)NULL);
		
	return scrHandle;
}
