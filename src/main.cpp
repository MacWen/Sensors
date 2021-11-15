#include <iostream>
#include <map>
#include <future>
#include "tinyxml2.h"
#include "sensor.h"
#include "sensorfactory.h"
#include "server.h"
#include "process_handler.cpp"

bool CreateSensorsFromXMLFile();
bool LoadXMLConfigFile(tinyxml2::XMLDocument* config);
bool CreateAndInitNewSensors(tinyxml2::XMLDocument* config);

bool CreateSensorsFromXMLFile()
{
    bool bSuccess = false;

    tinyxml2::XMLDocument config;
    if(LoadXMLConfigFile(&config))
        bSuccess = CreateAndInitNewSensors(&config);

    return bSuccess;
}

bool LoadXMLConfigFile(tinyxml2::XMLDocument* config)
{
    bool bSuccess = false;

    if(config != nullptr)
    {
        config->LoadFile("../../resources/sensors.xml");

        if(config->ErrorID() == 0)
            bSuccess = true;
        else
            std::cout << "Unable to load sensors.xml file from /resources.\nClosing program..." << std::endl;
    }

    return bSuccess;
}

bool CreateAndInitNewSensors(tinyxml2::XMLDocument* config)
{
    bool bCreatedAtLeatsOneShape = false;

    if(config != nullptr)
    {
        tinyxml2::XMLElement* model = config->FirstChildElement("Sensor");
        while(model != nullptr)
        {
            SensorFactory* myFactory = SensorFactory::GetInstance();
            if(myFactory != nullptr)
            {
                bCreatedAtLeatsOneShape |= myFactory->CreateSensorInstance(model->FirstChildElement("type")->GetText(), model->FirstChildElement("parameters"));
            }

            model = model->NextSiblingElement("Sensor");
        }
    }

    return bCreatedAtLeatsOneShape;
}

void runAllInstances()
{
    SensorFactory* myFactory = SensorFactory::GetInstance();
    if(myFactory != nullptr)
    {
        myFactory->RunAllInstances();
    }
}

int main()
{
    try
    {
        if(CreateSensorsFromXMLFile())
        {
            auto server = std::async(std::launch::async, runAllInstances);
            server.wait();
        }
        else
        {
            std::cout << "Can't create any object. Closing program..." << std::endl;
        }
    }
    catch(const std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
        return 1;
    }

    return 0;
}