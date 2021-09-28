#pragma once
#include "SingleElement.h"
class Switch :
    public SingleElement
{
public:
    Switch(bool closed = false);
    void Open() { _closed = false; }
    void Close() { _closed = true;  }
    void Toggle() { _closed = !_closed;  }
    // Inherited via SingleElement
    virtual ElementType getType() override;
protected:
    // Inherited via SingleElement
    virtual CurrentVoltageCharacteristic* calcCurrentVoltageCharacteristic(double freq) override;
    virtual void printInfo(std::ostream& os) override;
private:
    bool _closed;
    static int idPool;

};

