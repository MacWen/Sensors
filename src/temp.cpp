#include "temp.h"
#include "process_handler.cpp"

Temp::Temp(long freq, long n, long procID, const std::string& name, long range)
: m_Range(range)
{
    setFreq(freq);
    setN(n);
    setProcID(procID);
    setName(name);
}

Temp::~Temp(){};

void Temp::setFreq(long freq)
{
    m_Freq = freq;
}

void Temp::setN(long n)
{
    m_N = n;
}
void Temp::setProcID(long procID)
{
    m_ProcID = procID;
}

void Temp::setName(const std::string& name)
{
    m_Name = name;
}

void Temp::setRange(long range)
{
    m_Range = range;
}

long Temp::getFreq()
{
    return m_Freq;
}

long Temp::getN()
{
    return m_N;
}

long Temp::getProcID()
{
    return m_ProcID;
}

long Temp::getRange()
{
    return m_Range;
}

void Temp::runClient(const std::string& port)
{
    process::launchProcess("client.exe", "localhost " + port + " " + m_Name + " " + std::to_string(m_Freq) + " " + std::to_string(m_N) + " " + std::to_string(m_Range));
}