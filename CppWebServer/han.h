#pragma once
#include <stdio.h>
#include <stdlib.h>

void exit_with_comment(const char* _comment, const char* _file, const int& _line) {
    fprintf(stderr, "Error %s at: %s (%d)\n", _comment, _file, _line);
    exit(1);
}