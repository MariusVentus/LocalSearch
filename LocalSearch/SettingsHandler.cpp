#include "SettingsHandler.h"
#include <direct.h>

SettingsHandler::SettingsHandler()
{
	char* buffer = _getcwd(NULL, 0);
	m_WorkingDirectory = buffer;
	free(buffer);

	RefreshSettings();
}

void SettingsHandler::RefreshSettings(void)
{
}
