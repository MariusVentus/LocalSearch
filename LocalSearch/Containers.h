#pragma once
#include <vector>

class RContainer {
public:
	RContainer(unsigned inCID, bool inState, const std::vector<std::string>& inInfo)
		:
		m_CellID(inCID),
		isStateGood(inState),
		m_Info(inInfo)
	{}
	//Get
	unsigned GetCID(void) const { return m_CellID; }
	bool GetState(void) const { return isStateGood; }
	std::vector<std::string> GetAllInfo(void) const { return m_Info; }
	std::string GetXInfo(unsigned Iterator) const { return m_Info[Iterator]; }
	//Set
	void SetState(bool inState) { isStateGood = inState; }

private:
	unsigned m_CellID = -1;
	bool isStateGood = false;
	std::vector<std::string> m_Info;
};

class SContainer {
public:
	SContainer(unsigned inCID, std::string inEntry)
		:
		m_CellID(inCID),
		m_SearchEntry(inEntry)
	{}
private:
	unsigned m_CellID = -1;
	std::string m_SearchEntry = "";
};