// ******************************************************************************
//
// Filename:	TimeManager.cpp
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

#include "TimeManager.h"

#include <stdio.h>


// Initialize the singleton instance
TimeManager *TimeManager::c_instance = 0;

TimeManager* TimeManager::GetInstance()
{
	if(c_instance == 0)
		c_instance = new TimeManager;

	return c_instance;
}

void TimeManager::Destroy()
{
	if(c_instance)
	{
		for(unsigned int i = 0; i < m_vpCountdownTimers.size(); i++)
		{
			delete m_vpCountdownTimers[i];
			m_vpCountdownTimers[i] = 0;
		}
		m_vpCountdownTimers.clear();

		delete c_instance;
	}
}

TimeManager::TimeManager()
{
}

bool TimeManager::HasCountdownTimers() const
{
	return(m_vpCountdownTimers.size() > 0);
}

void TimeManager::AddCountdownTimer(CountdownTimer* countdownTimer)
{
	m_vpCountdownTimers.push_back(countdownTimer);
}

void TimeManager::RemoveCountdownTimer(CountdownTimer* countdownTimer)
{
	m_vpCountdownTimers.erase(std::remove(m_vpCountdownTimers.begin(), m_vpCountdownTimers.end(), countdownTimer), m_vpCountdownTimers.end());
}

void TimeManager::RemoveCountdownTimers()
{
	m_vpCountdownTimers.clear();
}

// Update
void TimeManager::Update(float dt)
{
	// Also update all our countdown timers
	CountdownTimerList::iterator iterator;
	for(iterator = m_vpCountdownTimers.begin(); iterator != m_vpCountdownTimers.end(); ++iterator)
	{
		(*iterator)->UpdateCountdown(dt);
	}
}