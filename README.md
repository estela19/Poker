# Poker
[![Build Status](https://travis-ci.org/estela19/Poker.svg?branch=master)](https://travis-ci.org/estela19/Poker)
[![License: MIT](https://img.shields.io/badge/License-MIT-brightgreen.svg)](https://opensource.org/licenses/MIT)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/ed666f3b75d7460784186e2ea9f78741)](https://www.codacy.com/manual/estela19/Poker?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=estela19/Poker&amp;utm_campaign=Badge_Grade)
[![codecov](https://codecov.io/gh/estela19/Poker/branch/master/graph/badge.svg)](https://codecov.io/gh/estela19/Poker) 
[![Build status](https://ci.appveyor.com/api/projects/status/cse5g0b2f9ttt6kt?svg=true)](https://ci.appveyor.com/project/estela19/poker)
[![Total alerts](https://img.shields.io/lgtm/alerts/g/estela19/Poker.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/estela19/Poker/alerts/)
[![Language grade: C/C++](https://img.shields.io/lgtm/grade/cpp/g/estela19/Poker.svg?logo=lgtm&logoWidth=18)](https://lgtm.com/projects/g/estela19/Poker/context:cpp)
[![CodeFactor](https://www.codefactor.io/repository/github/estela19/poker/badge)](https://www.codefactor.io/repository/github/estela19/poker)

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