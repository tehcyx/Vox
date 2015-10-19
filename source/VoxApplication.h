#pragma once


class VoxApplication
{
public:
	/* Public methods */
	VoxApplication();
	~VoxApplication();

	void Create();
	void Destroy();
	void Update(float dt);

	int ShouldCloseApplication();

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
};