// Enum for Data_Type
enum class DataType {
    Coil,
    DiscreteInput,
    InputRegister,
    HoldingRegister
};

// Struct for Modbus Function Mapping
struct LabconCoilFunction {
    String    FunctionName;    // Name of the function
    uint16_t  Address;         // Address in Hex
    char      Description;     // Description of the function
    bool      Value;           // Value (for Coils.)
};

struct LabconRegisterFunction {
    String      FunctionName;    // Name of the function
    uint16_t  Address;         // Address in Hex
    char      Description;     // Description of the function
    uint16_t  Value;           // Value (for InputRegister, HoldingRegister, etc.)
};

// Create the virtual databases
LabconCoilFunction labconCoilsDatabase[] = {
  // Commands
  {"Hamper",           0xFFFF, "Hamper",                                          0},
  {"InitCalibration",  0x0001, "Command to initiate calibration",              0x00},
  {"ResetEnergyMeter", 0x0002, "Resetting the energy meter for the process",   0x00},
  {"ResetAlarm",       0x0003, "Resetting the external alarm",                 0x00},
  // Device configuration
  {"StpAtMaxMaterialTemp", 0x1000, "Allows to stop due to exceeding the max allowed material temp-re",    0x00},
  {"StpAtTimeOut",         0x1001, "Status that allows the device to stop because the time has expired",  0xFF},
  {"StpAtMaxTorque",       0x1002, "Allows to stop due to exceeding the maximum allowed torque",          0xFF},
  {"StpAtMaxCurrent",      0x1003, "Allows to stop due to exceeding the maximum allowed current",         0xFF},
  {"StpAtMaxVoltage",      0x1004, "Allows to stop due to exceeding the maximum allowed voltage",         0xFF},
  {"StpAtMaxPower",        0x1005, "Allows to stop due to exceeding the maximum allowed power",           0xFF},
  {"StpAtNullPower",       0x1006, "Allows to stop due to exceeding the minimum allowed power",           0xFF},
  {"TurnOnAlarm",          0x1007, "Status that allows the device to activate external alarm",            0xFF},
  {"AutoCalibration",      0x1008, "Calibration will begin with each new process",                        0xFF},
  {"ManualTurnOn",         0x1009, "Allows operator turn on the device by using ext-l StopStart button",  0xFF},
  {"ManualTurnOff",        0x100A, "Allows operator turn off the device by using ext-l StopStart button", 0xFF},
  //Monitoring Parameters
  {"StartStopButPress",    0x3000, "Button press definition",                                             0x00},
  {"EmergencyStop",        0x3001, "The status indicates an emergency stop of the device",                0x00},
  {"IsWorking",            0x3002, "The status indicates that the device is running at the current time.",0x00},
};
LabconRegisterFunction labconRegistersDatabase[] = {
  // Parametr Settings
  {"Hamper",               0xFFFE, "Hamper",                                                             0},
  {"StartStop",            0x0000, "Command for starting/stopping the process",                       0x00},
  {"SetMoldTemp",          0x2000, "Setting the mold temperature",                                     180},
  {"SetMaxTempMat",        0x2001, "Setting the maximum material temperature",                         220},
  {"SetTestTime",          0x2002, "Setting the nominal testing time, s",                               30},
  {"SetMaxTorque",         0x2003, "Setting the maximum torque for the device, Nm ",                     2},
  {"SetMaxCurrent",        0x2004, "Setting the maximum current for the device, A",                     180},
  {"SetMaxVoltage",        0x2005, "Setting the maximum voltage for the device, V",                    253},
  {"SetMaxPower",          0x2006, "Setting the maximum power for the device, W",                     3960},
  {"SetBaudRate",          0x2007, "Setting the baud rate, bod",                                      9600},
  {"SetSpeed",             0x2008, "Setting the speed of rotating main tool, rot/min",                 100},
  {"DelayTurnOff",         0x2009, "the motor shuts down if the current/voltage is close to zero, s",   30},
  //Monitoring Parameters
  {"Torque",               0x4000, "Store current torque of process, Nm",                                0},
  {"Speed",                0x4001, "Store current speed of the mixe, rot/min",                           0},
  {"MoldTemp",             0x4002, "Store current mold temperature, °C",                                 0},
  {"MaterialTemp",         0x4003, "Store current mix material temperature, °C",                         0},
  {"TestingTime",          0x4004, "Store current testing time, s",                                      0},
  {"Voltage",              0x4005, "Store measured voltage,V,  *10",                                     0},
  {"Current",              0x4006, "Store measured current, A, *1000",                                   0},
  {"Frequency",            0x4007, "Store measured frequency, Hz, *10",                                  0},
  {"Power",                0x4008, "Store power on current time, W, *10",                                0},
  {"Energy",               0x4009, "Store total energy on the current time, kWh, *1000",                 0},
  {"Alarm",                0x400A, "Store the reason of emergency stop(in bits):",                       0},
  {"CountDelay",           0x400B, "Store the current delay by power is zero",                           0},
};
/*
The reason of emergency stop(bits):
0.	Manual by operator
1.	has been achieved max torque
2.	has been achieved max temperature of material
3.	has been achieved max time of testing
4.	has been achieved max voltage
5.	has been achieved max current
6.	has been achieved max power
7.	has no electrical energy
*/

size_t const sizeCoilsDB = sizeof(labconCoilsDatabase) / sizeof(labconCoilsDatabase[0]);
size_t const sizeRegistersDB = sizeof(labconRegistersDatabase) / sizeof(labconRegistersDatabase[0]);

LabconCoilFunction* getCoilFunctionByAddress(uint16_t address) {
    for (auto& func : labconCoilsDatabase) {
        if (func.Address == address) {
            return &func;
        }
    }
    return &labconCoilsDatabase[0]; // Address not found
}

LabconRegisterFunction* getRegisterFunctionByAddress(uint16_t address) {
    for (auto& func : labconRegistersDatabase) {
        if (func.Address == address) {
            return &func;
        }
    }
    return &labconRegistersDatabase[0]; // Address not found
}

LabconCoilFunction* getCoilFunctionByName(String name) {
    for (auto& func : labconCoilsDatabase) {
        if (func.FunctionName.equals(name)) {
            return &func;
        }
    }
    return &labconCoilsDatabase[0]; // Address not found
}

LabconRegisterFunction* getRegisterFunctionByName(String name) {
    for (auto& func : labconRegistersDatabase) {
        if (func.FunctionName.equals(name)) {
            return &func;
        }
    }
    return &labconRegistersDatabase[0]; // Address not found
}

bool updateCoilValueByName(String name, bool newValue) {
    LabconCoilFunction* func = getCoilFunctionByName(name);
    if (func) {
        func->Value = newValue;
        return true;
    }
    return false;
}

bool updateRegisterValueByName(String name, uint16_t newValue) {
    LabconRegisterFunction* func = getRegisterFunctionByName(name);
    if (func) {
        func->Value = newValue;
        return true;
    }
    return false;
}