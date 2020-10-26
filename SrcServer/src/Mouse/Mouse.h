#ifndef MOUSE_H
#define MOUSE_H

#include <functional>


enum class MouseState
{
	ON_LEFT_CLICK,
	ON_LEFT_DOUBLE_CLICK,
	ON_RIGHT_CLICK,
	ON_RIGHT_DOUBLE_CLICK,
	ON_ENTER,
	ON_LEAVE
};

struct MousePosition
{
	unsigned int x;
	unsigned int y;

	MousePosition()
	{
		x = 0;
		y = 0;
	}
};

struct EventArgs
{
	int AParam;
	int BParam;
	int CParam;
	int DParam;
	int EParam;
	int FParam;

	EventArgs()
	{
		AParam = 0;
		BParam = 0;
		CParam = 0;
		DParam = 0;
		EParam = 0;
		FParam = 0;
	}
};

class Mouse
{
private:
	std::function<void(void)> handle_left_click;
	std::function<void(void)> handle_right_click;

public:
	Mouse();
	virtual ~Mouse();
	void setEvent(MouseState state, std::function<void(void)> click);
	bool performClick(MouseState state);
	virtual bool onClick(MouseState state);
	virtual bool onMouseOver() = 0;
	virtual bool onMouseOut() = 0;

};


#endif // MOUSE_H