#pragma once

#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_map>

#include "Caen.hpp"
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

class CaenRpc : public DimRpc {
   private:
    Caen& _caen;

    void rpcHandler() override {
        std::string message = std::string(getString());
        _caen.sendMessage(message);
        std::cout << "[SENT]: " << message << '\n';
        std::string response;
        try {
            response = _caen.readMessage();
        } catch(std::runtime_error e) {
            response = "ERR:\"" + std::string(e.what()) + "\"";
        }
        std::cout << "[RECEIVED]: " << response << '\n';
        setData(const_cast<char*>(response.c_str()));  // Potentially unsafe?
    }

   public:
    CaenRpc(std::string name, Caen& caen)
        : DimRpc(name.c_str(), "C", "C"), _caen(caen) {
        std::cout << "Creating CaenRpc " << name << '\n';
    }
};
