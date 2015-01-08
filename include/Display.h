#ifndef DISPLAY_H
#define DISPLAY_H

struct DisplayInfo
{
	int _w;
	int _h;

	DisplayInfo(int w, int h)
	{
		_w = w; _h = h;
	}

};

class Display
{
private:
	static int _w;
	static int _h;

public:
	Display();
	~Display();

	static void Init(char* cwd);


	static inline DisplayInfo GetInfo()
	{
		return DisplayInfo(_w, _h);
	}

	static inline float AspectRatio()
	{
		return (float)_w / (float)_h;
	}

};

#endif