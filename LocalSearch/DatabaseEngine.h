#pragma once
#include "Containers.h"
#include "NeuralNet.h"
#include "SettingsHandler.h"

class DatabaseEngine {
public:
	DatabaseEngine() = delete;
	DatabaseEngine(const SettingsHandler& inSet);
	void InitializeDB(void); //Pulls info from ContainerList and SearchPool
	void RebuildDB(void); //Scrub ActiveContainerList && ActiveSearchPool for "Bad" state containers, remove, overwrite. Restructure NeuralNet and re-train. 
	std::vector<float> SearchDB(const std::string& SearchString);
	void TrainDB(void);

	//Get
	unsigned GetDBAccuracy(void) { return m_LastAccuracy; }

	//Var
private:
	const std::string m_InitialSearchpool = "Databases\\InitialSearchPool.csv";
	const std::string m_InitialContainerList = "Databases\\InitialContainerList.csv";
	const std::string m_ActiveSearchpool = "Databases\\ActiveSearchPool.csv";
	const std::string m_ActiveContainerList = "Databases\\ActiveContainerList.csv";

	std::vector<RContainer> m_ResultContainers;
	std::vector<SContainer> m_SearchContainers;
	const SettingsHandler& m_Set;
	unsigned m_LastAccuracy = 0;
};