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

enum class CMD { MON,
           SET };

enum class PAR { VSET,
           VMIN,
           VMAX };

std::unordered_map<PAR, std::string> parMap{
        {PAR::VSET, "VSET"},
        {PAR::VMIN, "VMIN"},
        {PAR::VMAX, "VMAX"},
    };

template <CMD cmd, PAR par>
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
        name += parMap[par];
        return name;
    }
public:
    CaenRpc() : DimRpc(_nameFromParams().c_str(), "C", "C") {
        if(cmd == CMD::MON)
            _command = "$BD:0,CMD:MON,CH:0,PAR:" + parMap[par];
        else
            _command = "$BD:0,CMD:SET,CH:0,PAR:" + parMap[par] + ",VAL:";
    }
};