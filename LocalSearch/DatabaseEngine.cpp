#include "DatabaseEngine.h"
#include <Windows.h> //Sleep



DatabaseEngine::DatabaseEngine(const SettingsHandler& inSet)
	:
	m_Set(inSet)
{

}

void DatabaseEngine::InitializeDB(void)
{
	Sleep(6000);//Testing
}

void DatabaseEngine::RebuildDB(void)
{
}

std::vector<float> DatabaseEngine::SearchDB(const std::string & SearchString)
{
	return std::vector<float>();
}

void DatabaseEngine::TrainDB(void)
{
}
