#pragma once

#include <cstdio>
#include <format>
#include <iostream>
#include <string>
#include <unordered_map>

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

class CaenRpc : public DimRpc {
   private:
    std::string _command;
    CMD _cmd;
    std::string _par;
    unsigned _bd, _ch;
    bool _isGlobal;

    void rpcHandler() override {
        if (_cmd == CMD::MON) {
            send(_command);
            setData((char*)"Monitored value");
        } else {
            std::string val = getString();
            send(_command, val);
            setData((char*)"Success or failure");
        }
    }

    static std::string _nameFromParams(CMD cmd, std::string par) {
        return std::format("CAEN/{}/{}", par, cmd == CMD::MON ? "MON" : "SET");
    }

   public:
    CaenRpc(CMD cmd, std::string par, bool isGlobal = false, unsigned ch = 0, unsigned bd = 0)
        : DimRpc(_nameFromParams(cmd, par).c_str(), "C", "C"), _cmd(cmd), _par(par), _isGlobal(isGlobal), _ch(ch), _bd(bd) {
        std::cout << "Creating CaenRpc " << _nameFromParams(cmd, par) << '\n';
        
        if (_cmd == CMD::MON)
            _command = std::format("$BD:{:02},CMD:MON,CH:{:1},PAR:{}", _bd, _ch, _par);
            // _command = "dupa";
        else
            _command = std::format("$BD:{:02},CMD:SET,CH:{:1},PAR:{},VAL:", _bd, _ch, _par);
            // _command = "duppa";
    }
};