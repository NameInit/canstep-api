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
    ScenarioBuilder() {
        recursiveCounter = 0;
        recursiveFault = false;
        pthread_mutex_init(&hMutex, nullptr);
    }

    ~ScenarioBuilder() {
        pthread_mutex_destroy(&hMutex);
    }

    bool getRecursiveFault() {
        pthread_mutex_lock(&hMutex);
        bool result = recursiveFault;
        pthread_mutex_unlock(&hMutex);
        return result;
    }

private:
    void setRecursiveFault(bool value) {
        pthread_mutex_lock(&hMutex);
        recursiveFault = value;
        pthread_mutex_unlock(&hMutex);
    }

public:
    void addMechanism(const std::string& name, std::unique_ptr<Mechanism> mech) {
        mechanisms[name] = std::move(mech);
    }

    void loadCommandsFromFile(const std::string& filename) {
        commandQueue.clear();
        std::ifstream file(filename);
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                commandQueue.push_back(line);
            }
        }
    }

    void saveCommandsToFile(const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& cmd : commandQueue) {
            file << cmd << std::endl;
        }
    }

    void stopAllMechanisms() {
        for (const auto& pair : mechanisms) {
            pair.second->stop();
        }
    }

    void executeCommands() {
        for (const auto& cmd : commandQueue) {
            executeSingleCommand(cmd);
        }
    }
    
    void executeSingleCommand(const std::string& command) {
        recursiveCounter += 1;

        std::stringstream ss(command);
        std::string part;
        std::vector<std::string> parts;
        while (ss >> part) {
            parts.push_back(part);
        }

        if (parts.size() < 2) return;

        std::string mechName = parts[0];
        std::string action = parts[1];

        auto it = mechanisms.find(mechName);
        if (it != mechanisms.end()) {
            Mechanism* mech = it->second.get();
            
            try {
                if (action == "SET_STEPS" && parts.size() > 2) {
                    mech->setSteps(std::stoi(parts[2]));
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                } else if (action == "MOVE_FORWARD") {
                    mech->runForward();
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                } else if (action == "MOVE_BACKWARD") {
                    mech->runBackward();
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                } else if (action == "MOVE_TO" && parts.size() > 2) {
                    MoveToPosition(mechName, std::stoi(parts[2]));
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                } else if (action == "STOP") {
                    mech->stop();
                } else if (action == "HOMING_ZERO") {
                    mech->HomingZero();
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                } else if (action == "HOMING_MAX") {
                    mech->HomingMax();
                    std::this_thread::sleep_for(std::chrono::milliseconds(50));
                } else if (action == "BRAKE_ON") {
                    mech->BrakeOn();
                } else if (action == "BRAKE_OFF") {
                    mech->BrakeOff();
                } else if (action == "REZERV_ON") {
                    mech->RezervOn();
                } else if (action == "REZERV_OFF") {
                    mech->RezervOff();
                } else if (action == "MOSFET_ON") {
                    mech->Mosfet_On();
                } else if (action == "MOSFET_OFF") {
                    mech->Mosfet_Off();
                } else if (action == "SET_ALARM_RESET_ON") {
                    mech->AlarmResetOn();
                } else if (action == "SET_ALARM_RESET_OFF") {
                    mech->AlarmResetOff();
                } else if (action == "WAIT_TIME" && parts.size() > 2) {
                    waitTime(std::stoi(parts[2]));
                    recursiveCounter = 0;
                } else if (action == "WAIT_POS_EQUAL" && parts.size() > 2) {
                    waitUntilPosition(mechName, std::stoul(parts[2]));
                    recursiveCounter = 0;
                } else if (action == "WAIT_POS_MORE" && parts.size() > 2) {
                    waitUntilMoreThanPosition(mechName, std::stoul(parts[2]));
                    recursiveCounter = 0;
                } else if (action == "WAIT_POS_LESS" && parts.size() > 2) {
                    waitUntilLessThanPosition(mechName, std::stoul(parts[2]));
                    recursiveCounter = 0;
                } else if (action == "WAIT_IN_WORK") {
                    while (mech->getInWork()) {
                        std::this_thread::sleep_for(std::chrono::milliseconds(50));
                    }
                    recursiveCounter = 0;
                } else if (action == "SET_SPEED" && parts.size() > 2) {
                    mech->setSpeed(std::stof(parts[2]));
                } else if (action == "SET_ACCEL" && parts.size() > 2) {
                    mech->setCurrAccel(std::stoi(parts[2]));
                } else if (action == "SET_DECEL" && parts.size() > 2) {
                    mech->setCurrDecel(std::stoi(parts[2]));
                }
            } catch (const std::invalid_argument& e) {
                // Handle parsing error, e.g., log it
            } catch (const std::out_of_range& e) {
                // Handle out of range error
            }

            recursiveCounter = 0;
        }
    }

    void MoveToPosition(const std::string& mechName, int targetPosition) {
        auto it = mechanisms.find(mechName);
        if (it == mechanisms.end()) return;

        Mechanism* mech = it->second.get();
        int currentPosition = mech->GetPosition(true);
        int stepsNeeded = targetPosition - currentPosition;

        if (stepsNeeded == 0) return;

        mech->setSteps(std::abs(stepsNeeded));
        std::this_thread::sleep_for(std::chrono::milliseconds(250));

        if (stepsNeeded > 0) {
            mech->runForward();
        } else {
            mech->runBackward();
        }
    }

    void waitTime(int ms) {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    void waitUntilPosition(const std::string& mechName, uint32_t position) {
        auto it = mechanisms.find(mechName);
        if (it == mechanisms.end()) return;
        Mechanism* mech = it->second.get();
        while (mech->GetPosition(true) != position) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void waitUntilMoreThanPosition(const std::string& mechName, uint32_t position) {
        auto it = mechanisms.find(mechName);
        if (it == mechanisms.end()) return;
        Mechanism* mech = it->second.get();
        while (mech->GetPosition(true) < position) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void waitUntilLessThanPosition(const std::string& mechName, uint32_t position) {
        auto it = mechanisms.find(mechName);
        if (it == mechanisms.end()) return;
        Mechanism* mech = it->second.get();
        while (mech->GetPosition(true) > position) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void saveMechanismsToFile(const std::string& filename) {
        std::ofstream file(filename);
        for (const auto& pair : mechanisms) {
            file << pair.first << " " << static_cast<int>(pair.second->getNumBoard()) << " " << static_cast<int>(pair.second->getGroup(false)) << std::endl;
        }
    }

    bool detectFault() {
        for (const auto& pair : mechanisms) {
            if (pair.second->getFAULT())
                return true;
        }
        return false;
    }

    bool isInWork() {
        for (const auto& pair : mechanisms) {
            if (pair.second->getInWork())
                return true;
        }
        return false;
    }

    void loadMechanismsFromFile(const std::string& filename) {
        mechanisms.clear();
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string name;
            int numBoard_int, group_int;
            
            if (ss >> name >> numBoard_int >> group_int) {
                uint8_t numBoard = static_cast<uint8_t>(numBoard_int);
                uint8_t group = static_cast<uint8_t>(group_int);
                
                auto newMech = std::make_unique<Mechanism>(numBoard, group);
                mechanisms[name] = std::move(newMech);
            }
        }
    }

    std::vector<MechanismState> getMechanismsStateList() {
        std::vector<MechanismState> stateList;
        for (const auto& pair : mechanisms) {
            Mechanism* mech = pair.second.get();
            MechanismState state;
            state.name = pair.first;
            state.isEmergency = mech->getEmergency();
            state.isInWork = mech->getInWork();
            state.homingA = mech->getHomingA(true);
            state.homingB = mech->getHomingB(true);
            state.homingC = mech->getHomingC(true);
            state.homingD = mech->getHomingD(true);
            state.srvReady = mech->getSRVRDY();
            state.inPosition = mech->getINPOS();
            state.fault = mech->getFAULT();
            state.brake = mech->getBRAKE();
            state.position = mech->GetPosition(true);
            state.outEn = mech->getOutEn(true);
            state.outDir = mech->getOutDIR(true);
            state.outAlClr = mech->getOutAL_CLR(true);
            state.outBrake = mech->getOutBRAKE(true);
            state.outReserv = mech->getOutReserv(true);
            stateList.push_back(state);
        }
        return stateList;
    }
};