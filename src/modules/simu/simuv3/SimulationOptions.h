/* -*- Mode: C++; -*- */
/* VER: $Id$ */
// copyright (c) 2004 by Christos Dimitrakakis <dimitrak@idiap.ch>
/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef SIMULATION_OPTIONS_H
#define SIMULATION_OPTIONS_H

#include "Options.h"


///	Aerodynamic flow model
enum AeroFlowModel {
	SIMPLE, ///< A simple plane surface model.
	SEGMENTS ///< A segmented surface model.
};

/**
   Simulation options for easy handling of default options.
   
   You can read/write the options directly but there is support for
   setting them through strings.
 */
class SimulationOptions
{
public:

	float tyre_damage; 	///< Amount of tyre wear, 1.0 is normal wear, 0.0 is no wear.
	bool suspension_damage; ///< If true, the suspension shocks can be damaged from large bumps.
	bool alignment_damage; ///< If true, the suspension can become misaligned from large bumps.
	bool aero_damage; ///< If true, damage can cause changes to the aerodynamic profile.
	enum AeroFlowModel aeroflow_model; ///< Experimental option

	SimulationOptions()
	{
		option_list.AddOption<float> (PRM_DAMAGE_TYRES, &tyre_damage, 0.0);
		option_list.AddOption<bool> (PRM_DAMAGE_SUSPENSION, &suspension_damage, false);
		option_list.AddOption<bool> (PRM_DAMAGE_ALIGNMENT, &alignment_damage, true);
		option_list.AddOption<bool> (PRM_DAMAGE_AERO, &aero_damage, false);
		option_list.AddOption<AeroFlowModel> (PRM_MODEL_AEROFLOW, &aeroflow_model, SIMPLE);
	}
	/// Set the appropriate values for the driver's skill
	void SetFromSkill (int skill) {
		switch (skill) {
		case 0:
		case 1:
			option_list.Set(PRM_DAMAGE_TYRES, 0.0f);
			option_list.Set(PRM_DAMAGE_SUSPENSION, false);
			option_list.Set(PRM_DAMAGE_ALIGNMENT, true);
			option_list.Set(PRM_DAMAGE_AERO, false);
			break;
		case 2:
			option_list.Set(PRM_DAMAGE_TYRES, 0.0f);
			option_list.Set(PRM_DAMAGE_SUSPENSION, false);
			option_list.Set(PRM_DAMAGE_ALIGNMENT, true);
			option_list.Set(PRM_DAMAGE_AERO, false);
			break;
		case 3:
			option_list.Set(PRM_DAMAGE_TYRES, 1.0f);
			option_list.Set(PRM_DAMAGE_SUSPENSION, true);
			option_list.Set(PRM_DAMAGE_ALIGNMENT, true);
			option_list.Set(PRM_DAMAGE_AERO, true);
			break;
		}
	}
	/**
	   After setting defaults, you can customise by loading values from a file.
	   If values are not contained in the file then we just use the previously
	   defined values.
	*/
	void LoadFromFile(void* handle) {
		GfParmGetStr(handle, SECT_SIMU_SETTINGS, PRM_DAMAGE_TYRES, "none");
		SetFloatFromGfParm (handle, PRM_DAMAGE_TYRES);
		SetBoolFromGfParm (handle, PRM_DAMAGE_SUSPENSION);
		SetBoolFromGfParm (handle, PRM_DAMAGE_ALIGNMENT);
		SetBoolFromGfParm (handle, PRM_DAMAGE_AERO);
	}
	/// Get a single option
	template <typename T>
	T Get (char* name)
	{
		return option_list.Get(name);
	}
	/// Set a single option
	template <typename T>
	void Set (char* name, T value)
	{
		option_list.Set(name, value);
	}
private:
	OptionList option_list;
	void SetFloatFromGfParm(void* handle, char* name) {
		float v = option_list.Get<float>(name);
		v = GfParmGetNum (handle, SECT_SIMU_SETTINGS, name, (char*) NULL, v);
		option_list.Set(name, v);
	}
	void SetBoolFromGfParm(void* handle, char* name) {
		bool v = option_list.Get<bool>(name);
		char* s = GfParmGetStr (handle, SECT_SIMU_SETTINGS, name, "none");
		v = StrToBool (s, v);
		option_list.Set(name, v);
	}
	bool StrToBool (char* s, bool dontcare=false)
	{
		if (!strcasecmp(s,"true")) {
			return true;
		}
		if (!strcasecmp(s,"false")) {
			return false;
		}
		return dontcare;
	}
};

#endif
