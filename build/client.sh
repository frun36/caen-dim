#!/bin/bash

export DIM_DNS_NODE="localhost"

if pgrep -x "dns" > /dev/null
then
    echo "dns already running (PID $(pgrep -x "dns"))"
else
    /usr/local/lib/dim/dns &
    sleep 1
fi

./client/client