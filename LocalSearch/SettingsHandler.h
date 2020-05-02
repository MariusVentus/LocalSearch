#pragma once
#include <vector>

class SettingsHandler {
public:
	SettingsHandler();
	void RefreshSettings(void);
	std::string GetSettingsFileLocation(void) const { return m_SettingsFileLocation; }
private:
	const std::string m_SettingsFileLocation = "Settings\\Settings.txt";
	std::vector<std::string> m_DatabaseFileList;

};