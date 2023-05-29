#pragma once

#include "Options.h"

#include <iostream>
#include <string>

Options * getOptions(std::string path);
bool isFileEmpty(std::ifstream& pFile);