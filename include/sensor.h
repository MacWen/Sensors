#ifndef SENSOR_H
#define SENSOR_H

#include <string>

class ISensor
{
public:
    virtual ~ISensor(){};

    virtual void setFreq(long freq) = 0;
    virtual void setN(long n) = 0;
    virtual void setProcID(long procID) = 0;
    virtual void setName(const std::string& name) = 0;

    virtual long getFreq() = 0;
    virtual long getN() = 0;
    virtual long getProcID() = 0;

    virtual void runClient(const std::string& port) = 0;

protected:
    long m_Freq;
    long m_N;
    long m_ProcID;
    std::string m_Name;
};

#endif /* SENSOR_H */