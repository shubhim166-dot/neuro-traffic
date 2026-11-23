# NeuroTraffic V5.0

Intelligent Traffic Management System built using C++17 and SQLite.

## Features
- Traffic density analysis
- Ambulance emergency priority
- Adaptive green signal timing
- Basic historical average traffic prediction
- Dijkstra shortest-route algorithm
- SQLite traffic history storage

## Requirements
- G++ with C++17 support
- SQLite3 development library
- Make

## Build
```bash
make
```

## Run
```bash
./neurotraffic
```

## Clean build files
```bash
make clean
```

Note: Traffic prediction uses a simple arithmetic average of three manually
entered historical readings. The route network is simulated and does not use
live maps or real-time traffic data.
