#pragma once

#ifndef HAN
#include <stdio.h>
#include <stdlib.h>
#include <string>

void exit_with_comment(const char *_comment, const char *_file, const int &_line);

std::string get_item_by_name_query(std::string name);
#define HAN
#endif