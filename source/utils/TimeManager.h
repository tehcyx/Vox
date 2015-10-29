// ******************************************************************************
//
// Filename:	TimeManager.h
// Project:		Utils
// Author:		Steven Ball
//
// Purpose:
//	 A Manager class to handle all time related functionality. Can be used
//	 to get elapsed time, current tick count and also for a change in time
//	 on a frame by frame basis, to allow for time based animations.
//
// Revision History:
//   Initial Revision - 15/07/08
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

#include "CountdownTimer.h"

#include <windows.h>  // Needed for LARGE_INTEGER

#include <vector>
#include <algorithm>

typedef std::vector<CountdownTimer*> CountdownTimerList;


class TimeManager
{
public:
	/* Public methods */
	static TimeManager* GetInstance();
	void Destroy();

	bool HasCountdownTimers() const;
	void AddCountdownTimer(CountdownTimer* countdownTimer);
	void RemoveCountdownTimer(CountdownTimer* countdownTimer);
	void RemoveCountdownTimers();

	// Update
	void Update(float dt);

protected:
	/* Protected methods */
	TimeManager();
	TimeManager(const TimeManager&);
	TimeManager &operator=(const TimeManager&);

private:
	/* Private methods */

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	// A dynamic array of our countdown timers
	CountdownTimerList m_vpCountdownTimers;

	// Singleton instance
	static TimeManager *c_instance;
};
