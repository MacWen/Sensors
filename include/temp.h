#ifndef TEMP_H
#define TEMP_H

#include "sensor.h"

class Temp: public ISensor
{
public:
    Temp(long freq = 0, long n = 0, long procID = 0, const std::string& name = "", long range = 0);
    virtual ~Temp();

    virtual void setFreq(long freq);
    virtual void setN(long n);
    virtual void setProcID(long procID);
    virtual void setName(const std::string& name);
    virtual void setRange(long range);

    virtual long getFreq();
    virtual long getN();
    virtual long getProcID();
    virtual long getRange();

    virtual void runClient(const std::string& port);

protected:
    long m_Range;
};

#endif /* TEMP_H */