#pragma once

#ifndef HAN
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "./mysql/mysql.h"

void exit_with_comment(const char *_comment, const char *_file, const int &_line);

void search_item_by_name(MySQL &_con, const std::string &_name, const std::function<void(const char *)> &callback);

void get_items(MySQL &_con, const std::function<void(const char *)> &callback);

void insert_new_item(MySQL &_con,
                     const std::string &_item_name,
                     const std::string &_item_explanation,
                     const std::string &_creater_name,
                     const std::string &_table_data,
                     const std::function<void(const char *)> &_err_callback,
                     const std::function<void()> &_callback);

#define HAN
#endif