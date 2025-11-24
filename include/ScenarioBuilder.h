#pragma once
#include "Mechanism.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <thread>
#include <chrono>
#include <pthread.h>
#include <stdexcept>

#define CAN_CMD_CONFIRMATION_WAIT_LIMIT_MS 500
#define CAN_CMD_CONFIRMATION_RECURSIVE_LIMIT 5

struct MechanismState {
	std::string name;
	bool isEmergency;
	bool isInWork;
	bool homingA;
	bool homingB;
	bool homingC;
	bool homingD;
	bool srvReady;
	bool inPosition;
	bool fault;
	bool brake;
	uint32_t position;
	bool outEn;
	bool outDir;
	bool outAlClr;
	bool outBrake;
	bool outReserv;
};

class ScenarioBuilder {
public:
	std::map<std::string, std::unique_ptr<Mechanism>> mechanisms;
	std::vector<std::string> commandQueue;

private:
	pthread_mutex_t hMutex;
	int recursiveCounter;
	bool recursiveFault;

public:
	ScenarioBuilder();
	~ScenarioBuilder();
	bool getRecursiveFault();

private:
	void setRecursiveFault(bool value);

public:
	void addMechanism(const std::string& name, std::unique_ptr<Mechanism> mech);
	void loadCommandsFromFile(const std::string& filename);
	void saveCommandsToFile(const std::string& filename);
	void stopAllMechanisms();
	void executeCommands();
	void executeSingleCommand(const std::string& command);
	void MoveToPosition(const std::string& mechName, int targetPosition);
	void waitTime(int ms);
	void waitUntilPosition(const std::string& mechName, uint32_t position);
	void waitUntilMoreThanPosition(const std::string& mechName, uint32_t position);
	void waitUntilLessThanPosition(const std::string& mechName, uint32_t position);
	void saveMechanismsToFile(const std::string& filename);
	bool detectFault();
	bool isInWork();
	void loadMechanismsFromFile(const std::string& filename);
	std::vector<MechanismState> getMechanismsStateList();

};