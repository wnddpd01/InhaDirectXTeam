#pragma once
class BasicObserver
{
public:
	BasicObserver();
	~BasicObserver();

	void Event(void* parameter);
};

