#pragma once

class tag_HighScore
{
private:
	HWND hWnd;

	int Tex[16];
	int H_Tex[26] = { 0 };
	bool Fade_Counter;
	bool Restart;
	int Restart_Count;
	struct save
	{
		int Time;
		int Name[5];
	};
	save Save[6] = {};
	save Temp = {};
	save T_Temp = {};
public:

	int F_Time(int index);
	void Init(void);
	void Update(void);
	void Draw(void);
	int namae(int index, int i);

};
