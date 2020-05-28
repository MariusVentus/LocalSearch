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
	const SettingsHandler& m_Set;
	unsigned m_LastAccuracy = 0;
};