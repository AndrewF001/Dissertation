# Disertation

This is Andrew Foot(2177545) Masters dissertation for UoB computer science.

## Table of Contents

1. [Table of Contents](#table-of-contents)
2. [Project Discription](#project-discription)
3. [Dependiencies](#dependiencies)
4. [Installation](#installation)
5. [Running](#running)

## Project Discription

An indepth analysis of the performance of traverling saleperson problem compared to a lookahead convex hull insertion.

## Dependiencies

Only tested on Windows but theortically can be built on Linux.

[Visual Studio 2022](https://visualstudio.microsoft.com/vs/)

[(Optional) OneAPI - Base Toolkit](https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html)

[(Optional) OneAPI - HPC](https://www.intel.com/content/www/us/en/developer/tools/oneapi/hpc-toolkit-download.html)

[(Optional) QT6](https://www.qt.io/download-qt-installer-oss?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4)

[(Optional) libxlsxwriter](https://libxlsxwriter.github.io/getting_started.html)

[(Optional) gsl](https://github.com/microsoft/GSL)

## Installation

### Required

1. Install Visual Studio 2022 with the "Desktop development with C++" workload
2. Open "TSP_Solution/TSP_Solution.sln"

### (Optional)To compile with OneAPI

1. Run the OneAPI Base Toolkit installer then OneAPI HPC
2. Reboot your computer

### (Optional)To build GUI output of solution

1. Install QT6 with QT/<QT_version>/MSVC 2022 64-bit module
2. Add [QT VS Tools](https://doc.qt.io/qtvstools/qtvstools-how-to-install.html) extension to Visual Studio
3. Add [QT Version](https://doc.qt.io/qtvstools/qtvstools-how-to-add-qt-versions.html) to Visual Studio

### (Optional)To build file reader and Excel generator

1. Install vcpkg:
    1. `git clone https://github.com/microsoft/vcpkg.git`
    2. `cd vcpkg`
    3. `./bootstrap-vcpkg.bat`
2. Install libxlsxwriter: `./vcpkg install libxlsxwriter`
3. Install GSL: `./vcpkg install ms-gsl`
4. Integrate with Visual Studio: `./vcpkg integrate install`

## Building

If you didn't install all additional build tools use the table below to unselect the building of certain projects in Visual Studio `Build->Configuration Manager`

| Project            |  VS22 | QT6 |  CPP Libraries |
| :------:           | :---: | :--:|  :--:          |
| Empericial_Testing |   ✅ | ✅  | ✅             |
| File_Reader        |   ❌ | ❌  | ✅             |
| TSP_GUI            |   ❌ | ✅  | ❌             |
| Unit_Tests         |   ✅ | ✅  | ✅             |

Use `Ctrl+Shift+B` to build all projects, there should be zero errors but some warnings from external libraries.

## Running

Either run the newly created .exe files or select the project you want running in Visual Studio and run local debugger. To select the current project in VS2022:

1. Locate Solution Explorer
2. Click on Solution 'TSP_Solution' at the very top of the tree
3. Press `Alt+Enter`
4. Change the "Single startup project" drop down box to the project you want to run and save
5. Run the project with `ctrl+f5`
