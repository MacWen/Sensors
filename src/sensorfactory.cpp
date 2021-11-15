#include <iostream>
#include "sensorfactory.h"
#include <future>
#include "sensor.h"
#include "server.h"

SensorFactory* SensorFactory::iInstance = nullptr;

SensorFactory* SensorFactory::GetInstance()
{
    if(iInstance == nullptr)
        iInstance = new SensorFactory();

    if(iInstance == nullptr)
        std::cout << "Can't create a Factory!\nClosing program..." << std::endl;

    return iInstance;
}

bool SensorFactory::CreateSensorInstance(const std::string& sensorType, tinyxml2::XMLElement* model)
{
    if(enumMap[sensorType] == eTemp)
    {
        int range, freq, n;
        std::string name = model->Attribute("name");
        model->QueryIntAttribute("range", &range);
        model->QueryIntAttribute("freq", &freq);
        model->QueryIntAttribute("n", &n);
        children.push_back(new Temp(freq, n, 0, name, range));
        std::cout << "New sensor " << name << " created." << std::endl;
    }
    else
    {
        std::cout << "Couldn't create a sensor." << std::endl;
        return false;
    }

    return true;
}

void SensorFactory::ClearList()
{
    try
    {
        for(auto it = children.begin() ; it != children.end(); ++it)
            delete (*it);

        children.clear();
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }
}

SensorFactory::~SensorFactory()
{
    ClearList();
    delete iInstance;
}

void SensorFactory::RunAllInstances()
{
    std::vector<std::future<void>> async_vec;
    int port = 2000;
    for(auto& child : children)
    {
        async_vec.push_back(std::async(std::launch::async, runServer, std::to_string(port)));
        child->runClient(std::to_string(port));
        ++port;
    }

    for(const auto& work : async_vec)
        work.wait();
}

void SensorFactory::runServer(const std::string& port)
{
    Server server;
    server.run(port.c_str());
}