# CAEN + DIM
## Introduction
This repo contains the code being developed to communicate with a CAEN N1471HB power supply from a Linux PC, using the DIM and FRED technologies developed at CERN.

## Running
* Download [DIM](https://dim.web.cern.ch/dim_unix.html) (don't worry too much about the provided installation instructions, just unpack the `.zip` file and continue)
* copy the contents of the `dim` directory to `/usr/local/include/dim`
* copy the contents of the `linux` directory (having added the `x` permission to them) to `/usr/local/lib/dim`
* run `cmake ..` in the project's `build` directory, and then `make` to build
* run the `server` and `client` apps using the provided wrapper scripts - `server.sh` and `client.sh` respectively