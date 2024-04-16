#pragma once

#include <string>
#include <unordered_map>
#include <cstdio>
#include <iostream>

#include "dim/dis.hxx"

/*
Command format:
$BD:**,CMD:***,CH*,PAR:***,VAL:***.**<CR, LF >

The fields that form the command are:
BD : 0..31 module address (to send the command)
CMD : MON, SET (monitor or set)
CH : 0..4 (4 for the commands related to all Channels)
PAR : (see parameters tables)
VAL : (numerical value must have a Format compatible with resolution and range)
*/

void send(std::string command, std::string data = "") {
    std::cout << command << data << "\r\n";
}

struct Parameter {
    std::string name;
    bool isGlobal;

    Parameter(std::string name = "", bool isGlobal = false) : name(name), isGlobal(isGlobal) {}
};

enum class CMD { MON,
           SET };

enum class PAR { VSET,
           VMIN,
           VMAX,
           BDNAME };

std::unordered_map<PAR, Parameter> parMap{
        {PAR::VSET, Parameter("VSET")},
        {PAR::VMIN, Parameter("VMIN")},
        {PAR::VMAX, Parameter("VMAX")},
        {PAR::BDNAME, Parameter("BDNAME", true)},
    };

template <CMD cmd, PAR par, unsigned bd = 0, unsigned ch = 0>
class CaenRpc : public DimRpc {
   private:
    std::string _command;

    void rpcHandler() override {
        if(cmd == CMD::MON) {
            send(_command);
            setData((char*)"Monitored value");
        } else {
            std::string val = getString();
            send(_command, val);
            setData((char*)"Success or failure");
        }
    }

    static std::string _nameFromParams() { 
        std::string name = "CAEN/";
        name += (cmd == CMD::MON ? "MON_" : "SET_");
        name += parMap[par].name;
        return name;
    }
public:
    CaenRpc() : DimRpc(_nameFromParams().c_str(), "C", "C") {
        if(cmd == CMD::MON)
            _command = "$BD:" + std::to_string(bd) + ",CMD:MON," + (parMap[par].isGlobal ? "" : "CH:" + std::to_string(ch) + ",PAR:") + parMap[par].name;
        else
            _command = "$BD:0,CMD:SET,CH:0,PAR:" + parMap[par].name + ",VAL:";
    }
};