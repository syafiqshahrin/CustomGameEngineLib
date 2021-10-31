#pragma once
#include "Vector.h"
struct Input
{
public:
	Input();
	Vector2 mousePosition;
	bool IsLeftClicked;
	bool IsRightClicked;
	bool mouseInWindow;
	bool UpButtonPressed;
	bool DownButtonPressed;
	bool LeftButtonPressed;
	bool RightButtonPressed;
	bool E_ButtonPressed;
	bool Q_ButtonPressed;
	bool EnterButtonPressed;
};