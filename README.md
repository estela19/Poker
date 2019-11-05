# Poker
Poker implement with C++17

## Key Features
- C++17 based Poker environment
- C++ API

## TODO Features
- Reinforcement learning agent
- Python API

## Quick Start
First of all, clone the code:
```
git clone --recursive https://github.com/estela19/Poker.git
cd Poker
```

## C++ API
For Linux, macOS or Windows Subsystem for Linux(WSL):
```
make build && build
cmake ..
make
```

For Windows:
```
mkdir build
cd build
cmake .. -G"Visual Studio 16 2019" -A x64
MSBuild Poker.sln /p:Configuration=Release
```

## License
This project is licensed under the [MIT License](https://opensource.org/licenses/MIT):  
Copyright (C) 2019 [Sooyeon Kim](https://github.com/estela19), [Gyeonguk Chae](https://github.com/ShyRoute), [Junyeong Park](https://github.com/JYPark09)