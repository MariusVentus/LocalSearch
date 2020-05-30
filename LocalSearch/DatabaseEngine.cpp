#include "DatabaseEngine.h"



DatabaseEngine::DatabaseEngine(const SettingsHandler& inSet)
	:
	m_Set(inSet)
{
}

void DatabaseEngine::InitializeDB(void)
{

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
