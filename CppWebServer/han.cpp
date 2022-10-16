#include "./han.h"

void exit_with_comment(const char* _comment, const char* _file, const int& _line) {
    fprintf(stderr, "Error %s at: %s (%d)\n", _comment, _file, _line);
    exit(1);
}

void get_items(MySQL &_con, const std::function<void(const char *)> &callback) {
    _con.select(
        "SELECT `Item`.`ID`, `Item`.`ItemName`, `Explanation`, `CreaterData`.`Name`, `Date`, `TableData` FROM `Item` LEFT JOIN `CreaterData` ON `Item`.`ItemName` = `CreaterData`.`ItemName` LEFT JOIN `TableData` ON `Item`.`ItemName` = `TableData`.`ItemName`",
        callback);
}

void search_item_by_name(MySQL &_con, const std::string &_name, const std::function<void(const char *)> &callback) {
    const std::string query = "SELECT `Item`.`ID`, `Item`.`ItemName`, `Explanation`, `CreaterData`.`Name`, `Date`, `TableData` FROM `Item` LEFT JOIN `CreaterData` ON `Item`.`ItemName` = `CreaterData`.`ItemName` LEFT JOIN `TableData` ON `Item`.`ItemName` = `TableData`.`ItemName` WHERE `Item`.`ItemName` LIKE \"%" + _name + "%\"";
    _con.select(query.c_str(), callback);
}

void insert_new_item(MySQL &_con,
                 const std::string &_item_name,
                 const std::string &_item_explanation,
                 const std::string &_creater_name,
                 const std::string &_table_data,
                 const std::function<void(const char *)> &_err_callback,
                 const std::function<void()> &_callback) {
    // 일정 길이 이상 넘어가면 문자열이 짤리는 이슈가 있어서
    const std::string item_query      = "INSERT INTO `Item`(ItemName, Explanation) VALUES(\"" + _item_name + "\", \"" + _item_explanation + "\"); ";
    const std::string creater_query   = "INSERT INTO `CreaterData`(ItemName, Name) VALUES(\"" + _item_name + "\", \"" + _creater_name + "\"); ";
    const std::string table_query     = "INSERT INTO `TableData`(ItemName, TableData) VALUES(\"" + _item_name + "\", \"" + _table_data + "\");";

    _con.insert(item_query.c_str(), _err_callback, _callback);
    _con.insert(creater_query.c_str(), _err_callback, _callback);
    _con.insert(table_query.c_str(), _err_callback, _callback);
}

// char g_packet_filter[] = {'@', ';', ',', '#'};