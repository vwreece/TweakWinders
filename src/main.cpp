#include <iostream>
#include <windows.h>
#include <string>
#include <locale>
#include <codecvt>
#include <stdlib.h>
#include "reg_command.h"

void setRegValue_regsz(HKEY hKey, const std::string name, const std::string value)
{
    auto valueData_Cstr = value.c_str();
    auto result = RegSetValueEx(hKey, name.c_str(), 0, REG_SZ, (BYTE*)valueData_Cstr, strlen(valueData_Cstr));
}

void setRegValue_dword(HKEY hKey, const std::string name, int value)
{
    DWORD value_dword = value;
    auto result = RegSetValueEx(hKey, name.c_str(), 0, REG_DWORD, (BYTE*)&value_dword, sizeof(value_dword));
}

void RunCommand(const Registry_command command)
{
    HKEY command_h_key;
    BYTE regValue[8192];
    DWORD bufferSize = sizeof (regValue);

    //TODO: implement read value registry value.

    auto resultQuery = RegOpenKeyEx(HKEY_CURRENT_USER,command.reg_path.c_str(),0, KEY_READ | KEY_WRITE, &command_h_key);

    std::cout << resultQuery << std::endl;

    //TODO:Create 
    if (resultQuery == ERROR_FILE_NOT_FOUND)
    {
        std::cerr << "Key does not exist. Creating now" << std::endl;
        auto resultCreateQuery =  RegCreateKeyEx(HKEY_CURRENT_USER, command.reg_path.c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &command_h_key, NULL);
        if (resultCreateQuery != ERROR_SUCCESS)
        {
            LPVOID msgBuf; 
            FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
                NULL, resultQuery, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                (LPTSTR)&msgBuf,0,NULL);
            std::cout << "There was an error creating the key. Message: " << (char*)msgBuf << std::endl;
        }

    }
    else if (resultQuery == ERROR_SUCCESS)
    {
        if (command.reg_value_type == DOUBLEWORD)
        {
            int val = std::stoi(command.reg_value_data);
            setRegValue_dword(command_h_key, command.reg_value_name, val);
        }
        else if (command.reg_value_type == STRINGZEROTERMINATED){
            setRegValue_regsz(command_h_key, command.reg_value_name, command.reg_value_data);
        }

        std::cout << command.completion_message;
    }
    else if (resultQuery != ERROR_SUCCESS)
    {
        LPVOID msgBuf; 
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL, resultQuery, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR)&msgBuf,0,NULL);
        std::cerr << "Key does not exist. Error Message: " << (char*)msgBuf << ": Please make sure you are running with administrative privelages." << std::endl;
    }
    
    std::cout << "Program has completed." << std::endl;

}


void ClearDirectory(std::string file_path)
{


}

int main(int argc, char* argv[]) 
{
    auto reg_command = Registry_command{};
    reg_command.reg_path = "Software\\Policies\\Microsoft\\Windows\\Explorer";
    reg_command.reg_value_name = "DisableSearchBoxSuggestions";
    reg_command.reg_value_data = "1";
    reg_command.reg_value_type = DOUBLEWORD;
    reg_command.completion_message = "Edge should be disabled in the windows start bar now. Please restart for changes to take effect.";

    RunCommand(reg_command);
}
