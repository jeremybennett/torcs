/* -*- Mode: C++; -*- */
/* VER: $Id$ */
// copyright (c) 2005 by Christos Dimitrakakis <dimitrak@idiap.ch>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "SimulationOptions.h"
#include "car.h"

SimulationOptions::SimulationOptions()
{
	option_list.AddOption<float> (PRM_DAMAGE_TYRES, &tyre_damage, 0.0);
	option_list.AddOption<bool> (PRM_DAMAGE_SUSPENSION, &suspension_damage, false);
	option_list.AddOption<bool> (PRM_DAMAGE_ALIGNMENT, &alignment_damage, true);
	option_list.AddOption<bool> (PRM_DAMAGE_AERO, &aero_damage, false);
	option_list.AddOption<AeroFlowModel> (PRM_MODEL_AEROFLOW, &aeroflow_model, SIMPLE);
	option_list.AddOption<bool> (PRM_MODEL_TYRE_TEMPERATURE, &tyre_temperature, false);
	option_list.AddOption<float> (PRM_MODEL_AERO_FACTOR, &aero_factor, 4.0f);
}

void SimulationOptions::SetFromSkill (int skill)
{
	switch (skill) {
	case 0:
	case 1:
		option_list.Set(PRM_DAMAGE_TYRES, 0.0f);
		option_list.Set(PRM_DAMAGE_SUSPENSION, false);
		option_list.Set(PRM_DAMAGE_ALIGNMENT, true);
		option_list.Set(PRM_DAMAGE_AERO, false);
		option_list.Set(PRM_MODEL_TYRE_TEMPERATURE, false);
		break;
	case 2:
		option_list.Set(PRM_DAMAGE_TYRES, 0.0f);
		option_list.Set(PRM_DAMAGE_SUSPENSION, false);
		option_list.Set(PRM_DAMAGE_ALIGNMENT, true);
		option_list.Set(PRM_DAMAGE_AERO, false);
		option_list.Set(PRM_MODEL_TYRE_TEMPERATURE, false);
		break;
	case 3:
		option_list.Set(PRM_DAMAGE_TYRES, 1.0f);
		option_list.Set(PRM_DAMAGE_SUSPENSION, true);
		option_list.Set(PRM_DAMAGE_ALIGNMENT, true);
		option_list.Set(PRM_DAMAGE_AERO, true);
		option_list.Set(PRM_MODEL_TYRE_TEMPERATURE, true);
		option_list.Set(PRM_MODEL_AERO_FACTOR, 4.0f);
		option_list.Set(PRM_MODEL_AEROFLOW, SIMPLE);
		break;
	}
}

/**
   After setting defaults, you can customise by loading values from a file.
   If values are not contained in the file then we just use the previously
   defined values.
*/
void SimulationOptions::LoadFromFile(void* handle) {
	GfParmGetStr(handle, SECT_SIMU_SETTINGS, PRM_DAMAGE_TYRES, "none");
	SetFloatFromGfParm (handle, PRM_DAMAGE_TYRES);
	SetBoolFromGfParm (handle, PRM_DAMAGE_SUSPENSION);
	SetBoolFromGfParm (handle, PRM_DAMAGE_ALIGNMENT);
	SetBoolFromGfParm (handle, PRM_DAMAGE_AERO);
	SetBoolFromGfParm (handle, PRM_MODEL_TYRE_TEMPERATURE);
	SetFloatFromGfParm (handle, PRM_MODEL_AERO_FACTOR);
}

void SimulationOptions::SetFloatFromGfParm(void* handle, char* name) {
	float v = option_list.Get<float>(name);
	v = GfParmGetNum (handle, SECT_SIMU_SETTINGS, name, (char*) NULL, v);
	option_list.Set(name, v);
}

void SimulationOptions::SetBoolFromGfParm(void* handle, char* name) {
	bool v = option_list.Get<bool>(name);
	char* s = GfParmGetStr (handle, SECT_SIMU_SETTINGS, name, "none");
	v = StrToBool (s, v);
	option_list.Set(name, v);
}

bool SimulationOptions::StrToBool (char* s, bool dontcare)
{
	if (!strcasecmp(s,"true")) {
		return true;
	}
	if (!strcasecmp(s,"false")) {
		return false;
	}
	return dontcare;
}

