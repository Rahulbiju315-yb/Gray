#pragma once
#include "Log.h"


extern Gray::Application* Gray::CreateApplication();

int main(int argv, char** argc)
{
	Gray::Log::Init();
	GRAY_CORE_INFO("Started Gray");

	auto app = Gray::CreateApplication();
	app->Run();

	delete app;
}