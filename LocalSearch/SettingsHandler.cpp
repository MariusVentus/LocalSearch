#include "SettingsHandler.h"
#include <direct.h>
#include <fstream>
#include <string>
#include <sstream>
#include <windows.h>


SettingsHandler::SettingsHandler()
{
	char* buffer = _getcwd(NULL, 0);
	m_WorkingDirectory = buffer;
	free(buffer);

	RefreshSettings();
}

void SettingsHandler::RefreshSettings(void)
{
	try {
		std::ifstream in(m_SettingsFileLocation, std::ifstream::binary);
		if (in) {
			std::string token = "";
			m_ContainerTitles.clear();
			do {
				do {
					token.clear();
					CleanGetline(in, token);
				} while (token.empty() && !in.eof());
				if (token == "[ContainerSchema]") {
					token.clear();
					CleanGetline(in, token);
					if (!token.empty()) {
						std::stringstream Schema(token);
						do {
							token.clear();
							std::getline(Schema, token, ',');
							m_ContainerTitles.push_back(token);
						} while (!Schema.eof());
					}
					else {
						throw std::runtime_error("Container Schema Missing!");
					}
				}
				else if (token == "[FirstRun]") {
					token.clear();
					CleanGetline(in, token);
					m_FirstRun = StoB(token);
				}

			} while (!in.eof());
		}
		else {
			throw std::runtime_error("Settings File Missing!");
		}
	}
	catch (const std::runtime_error e){
		MessageBox(NULL, e.what(), "Settings Error!", MB_ICONERROR | MB_OK);
	}
}

void SettingsHandler::SaveSettings(void) const
{
	std::ofstream out(m_SettingsFileLocation, std::ofstream::trunc | std::ofstream::binary);
	//Container Schema
	out << "[ContainerSchema]\n";
	if (m_ContainerTitles.size() != 0) {
		std::string tempOut = m_ContainerTitles[0];
		for (unsigned i = 1; i < m_ContainerTitles.size(); i++) {
			tempOut.append(",");
			tempOut.append(m_ContainerTitles[i]);
		}
		out << tempOut << "\n";
	}
	else {
		out << "No Schema\n";
	}
	//First Run
	out << "[FirstRun]\n";
	if (m_FirstRun) {
		out << "true";
	}
	else {
		out << "false";
	}

}

void SettingsHandler::CleanGetline(std::ifstream& inStream, std::string& inStr)
{
	std::getline(inStream, inStr);
	//Remove whitespace
	while (inStr.find(" ") != std::string::npos) {
		inStr.erase(inStr.find(" "), 1);
	}
	//Remove \r
	while (inStr.find("\r") != std::string::npos) {
		inStr.erase(inStr.find("\r"), 1);
	}
	//Remove "comments"
	if (inStr.find(";;") != std::string::npos) {
		inStr.erase(inStr.find(";;"));
	}
}

bool SettingsHandler::StoB(const std::string& inStr) const
{
	auto str = inStr;
	//Lower all Letters
	for (unsigned i = 0; i < str.size(); i++) {
		if (str[i] >= 65 && str[i] <= 90) {
			str[i] = str[i] + 32; //Make into lowercase
		}
	}
	//Bool
	if (str == "true") {
		return true;
	}
	else if (str == "false") {
		return false;
	}
	else {
		return false;
	}
}