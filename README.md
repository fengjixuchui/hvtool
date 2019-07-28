# hvtool

[![Licence](https://img.shields.io/github/license/Biswa96/hvtool.svg)](https://www.gnu.org/licenses/gpl-3.0.en.html)
[![Top Language](https://img.shields.io/github/languages/top/Biswa96/hvtool.svg)](https://github.com/Biswa96/hvtool.git)
[![Code size](https://img.shields.io/github/languages/code-size/Biswa96/hvtool.svg)]()

Experiments with Hyper-V VM and container managing APIs.


## How to build

Clone this repository. Open the solution (.sln) or project (.vcxproj) file
in Visual Studio and build it. Alternatively, run Visual Studio developer
command prompt, go to the cloned folder and run `msbuild` command.
This project can also be built with mingw-w64 toolchain. Open terminal in the
cloned folder and run `make` command. The binaries will be in `/bin` folder. 

### Build export libraries:

* Generate DEF file:

<!-- -->
    
    gendef /c/Windows/System32/computecore.dll

* For MSVC:

<!-- -->
    
    lib /DEF:computecore.def /MACHINE:X64

* For mingw-w64/GCC:

<!-- -->
    
    dlltool -D /c/Windows/System32/computecore.dll -d computecore.def -l libcomputecore.a


## How to use

All the APIs require administrator privilege or user need to be member of
Hyper-V Administrators group. Here are the valid options for hvtool:

```
Usage: WslReverse.exe [option] [argument]

Options:
  endp                  List network endpoints
  kill    [VM Id]       Kill the VM
  list                  List all the VMs
  net                   List networks
```


## Project layout

* hcs: Function declarations of Hyper-V Host Compute Service.
* helper: Helper functions for logging, output parsing.
* hvtool: wrapper functions which calls underlying APIs.


## License

hvtool is licensed under the GNU General Public License v3.
A full copy of the license is provided in [LICENSE](LICENSE).

    hvtool -- Experiments with Hyper-V VM and container managing APIs.
    Copyright (c) 2019 Biswapriyo Nath
    
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
