#pragma once
#include <functional>

class Command final
{
public:
	Command(std::function<void()>& function);
	~Command() = default;

	virtual void execute() = 0;
	
private:
	const std::function<void()> m_Function{};
};