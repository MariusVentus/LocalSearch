#pragma once
#include <vector>

class SettingsHandler {
public:
	SettingsHandler();
	void RefreshSettings(void);
	void SaveSettings(void) const;

	//Get
	std::string GetContainerTitle(unsigned container) const { return m_ContainerTitles[container]; }
	unsigned GetContainerTitleCount(void) const { return m_ContainerTitles.size(); }
	std::string GetSettingsFileLocation(void) const { return m_SettingsFileLocation; }
	std::string GetOrigWorkingDirectory(void) const { return m_WorkingDirectory; } 
	//Set
	void SetFirstRun(bool set) { m_FirstRun = set; }

private:
	const std::string m_SettingsFileLocation = "Settings\\Settings.txt";
	std::string m_WorkingDirectory = "";
	//Settings
	std::vector<std::string> m_ContainerTitles;
	bool m_FirstRun = true;


	//Private Func
	void CleanGetline(std::ifstream& inStream, std::string& inStr);
	bool StoB(const std::string& inStr) const;
};