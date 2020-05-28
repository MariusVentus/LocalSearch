#pragma once
#include <vector>

class SettingsHandler {
public:
	SettingsHandler();
	void RefreshSettings(void);
	
	//Get
	std::string GetSettingsFileLocation(void) const { return m_SettingsFileLocation; }
	std::string GetOrigWorkingDirectory(void) const { return m_WorkingDirectory; }
private:
	const std::string m_SettingsFileLocation = "Settings\\Settings.txt";
	std::string m_WorkingDirectory = "";
};