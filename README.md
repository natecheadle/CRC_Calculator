# CRC_Calculator
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

CRC Calulator Template class written in C++

There are 2 ways to use this repository:
- Implement new CRC class using CRCHelper Template. It can be used as a base class or as a dependency to another class as the developer prefers.
- Utilize one of the existing CRC classes and instantiate directly or through the CRC Factory.

The code in this repository is mostly based on [this](https://sourceforge.net/projects/crccalculator/) code in C. At a base level the code in this repo uses C++ templates instead of macros as used in the C code.

This repository uses google test to do a quick validation of all the CRC classes using the standard "123456789" check.

The CRC table is always calculated in this implementation, if you would prefer not to store the crc table feel free to clone and comment out or remove that portion of the code. 
