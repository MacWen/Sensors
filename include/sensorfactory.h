
#ifndef SENSORFACTORY_H
#define SENSORFACTORY_H

#include <string>
#include <vector>
#include <map>
#include "temp.h"
#include "tinyxml2.h"

enum SensorEnum
{
  eTemp=1,

  eIncorrectSensor
};

class SensorFactory
{
public:
    ~SensorFactory();
    static SensorFactory* GetInstance();
    bool CreateSensorInstance(const std::string& sensorType, tinyxml2::XMLElement* model);
    void RunAllInstances();
    void ClearList();
    std::map<std::string, SensorEnum> enumMap = {{"Temp", SensorEnum::eTemp}};
private:
    SensorFactory(){};
    static SensorFactory* iInstance;
    std::vector<ISensor*>children;
    static void runServer(const std::string& port);
};

#endif /* SENSORFACTORY_H */