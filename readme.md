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

Only tested on Windows but theortically can be built on Linux with DPC++.

[Visual Studio 2022](https://visualstudio.microsoft.com/vs/)

[OneAPI - Base Toolkit](https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html)

[OneAPI - HPC](https://www.intel.com/content/www/us/en/developer/tools/oneapi/hpc-toolkit-download.html)

[(Optional) QT6](https://www.qt.io/download-qt-installer-oss?hsCtaTracking=99d9dd4f-5681-48d2-b096-470725510d34%7C074ddad0-fdef-4e53-8aa8-5e8a876d6ab4)

## Installation

\* - Means a step for getting the GUI application to work

1. Install Visual Studio 2022 with the "Desktop development with C++" workload
2. Run the OneAPI Base Toolkit installer then OneAPI HPC
3. Reboot your computer
4. *Install QT6 with QT/<QT_version>/MSVC 2022 64-bit module
5. *Add [QT VS Tools](https://doc.qt.io/qtvstools/qtvstools-how-to-install.html) extension to Visual Studio
6. *Add [QT Version](https://doc.qt.io/qtvstools/qtvstools-how-to-add-qt-versions.html) to Visual Studio
7. Open "TSP_Solution/TSP_Solution.sln"
8. If QT6 hasn't been installed open "build>Configuration Manager" and unselect TSP_GUI build
9. Build the solution Ctrl+Shift+B
10. If no errors are present and build succesfully then you can run the .exe in /x64 folder or select run options in Visual Studio

## Running
