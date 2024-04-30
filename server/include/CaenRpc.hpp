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
        _caen.sendMessage(std::string(getString()));
        setData(const_cast<char*>(_caen.readMessage().c_str()));  // Potentially unsafe?
    }

   public:
    CaenRpc(std::string name, Caen& caen)
        : DimRpc(name.c_str(), "C", "C"), _caen(caen) {
        std::cout << "Creating CaenRpc " << name << '\n';
    }
};
