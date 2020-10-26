#include "Mouse.h"

Mouse::Mouse()
{
	handle_left_click = nullptr;
	handle_right_click = nullptr;
}

Mouse::~Mouse()
{
}

void Mouse::setEvent(MouseState state, std::function<void(void)> click)
{
	switch(state)
	{
	case MouseState::ON_LEFT_CLICK:
		handle_left_click = click;
		break;
	case MouseState::ON_RIGHT_CLICK:
		handle_right_click = click;
		break;
	}
}

bool Mouse::performClick(MouseState state = MouseState::ON_LEFT_CLICK)
{
	return onClick(state);
}

bool Mouse::onClick(MouseState state)
{
	bool result = true;

	switch(state)
	{
	case MouseState::ON_LEFT_CLICK:
	{
		if(handle_left_click)
		{
			handle_left_click();
		}
		else
		{
			result = false;
		}
	}
	break;

	case MouseState::ON_RIGHT_CLICK:
	{
		if(handle_right_click)
		{
			handle_right_click();
		}
		else
		{
			result = false;
		}
	}
	break;

	default:
		result = false;
	}

	return result;
}
