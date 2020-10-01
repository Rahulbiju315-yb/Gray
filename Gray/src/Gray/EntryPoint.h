#pragma once
#include "Log.h"

extern Gray::Application* Gray::CreateApplication();

int main(int argv, char** argc)
{
	Gray::Log::Init();
	GRAY_CORE_INFO("Started Gray");
	GRAY_CORE_WARN("Warning Gray is incomplete");
	GRAY_FATAL("Nothing fatal");
	GRAY_WARN("Warning Gray is incomplete");

	auto app = Gray::CreateApplication();
	app->Run();
	delete app;
}