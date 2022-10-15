#include "./han.h"

void exit_with_comment(const char* _comment, const char* _file, const int& _line) {
    fprintf(stderr, "Error %s at: %s (%d)\n", _comment, _file, _line);
    exit(1);
}

std::string get_item_by_name_query(std::string name) {
    return "SELECT `Item`.`ItemName`, `Explanation`, `CreaterData`.`Name`, `Date`, `TableData` FROM `Item` LEFT JOIN `CreaterData` ON `Item`.`ItemName` = `CreaterData`.`ItemName` LEFT JOIN `TableData` ON `Item`.`ItemName` = `TableData`.`ItemName` WHERE `Item`.`ItemName` = \"" + name + "\"";
}

// char g_packet_filter[] = {'@', ';', ',', '#'};