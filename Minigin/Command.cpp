#include "Command.h"
Command::Command(std::function<void()>& function)
	: m_Function{ function }
{}