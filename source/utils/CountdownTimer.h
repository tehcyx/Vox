// ******************************************************************************
//
// Filename:	CountdownTimer.h
// Project:		Utils
// Author:		Steven Ball
//
// Purpose:
//	 A Countdown timer that triggers a function callback upon reaching the
//	 countdown time specified. Can also be a looping timer so that the callback
//	 happens every 'n' amount of time.
//
// Revision History:
//   Initial Revision - 15/07/08
//
// Copyright (c) 2005-2006, Steven Ball
//
// ******************************************************************************

#pragma once

typedef void(*FunctionCallback)(void *lpData);

class CountdownTimer
{
public:
	/* Public methods */
	CountdownTimer();

	~CountdownTimer();

	void SetCallBackFunction(FunctionCallback lFunction);
	void SetCallBackData(void *lpData);

	void StartCountdown();
	void ResetCountdown();

	void PauseCountdown();
	void ResumeCountdown();
	bool IsPaused() const;

	float GetElapsedTime() const;
	float GetRemainingTime() const;

	void SetCountdownTime(float lTimeOut);

	void SetLooping(bool lLoop);

	void UpdateCountdown(float dt);

protected:
	/* Protected methods */

private:
	/* Private methods */

public:
	/* Public members */

protected:
	/* Protected members */

private:
	/* Private members */
	float m_elapsedTime;

	float m_timeOutTime;

	bool m_bStarted;
	bool m_bLooping;
	bool m_bPaused;
	bool m_bFinished;

	FunctionCallback m_Callback;
	void *m_pCallbackData;
};
