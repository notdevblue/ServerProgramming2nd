#pragma once
#include <mysql.h>
#include <functional>

class MySQL {
public:
    MySQL(
        const char *_addr,
        const char *_db_id,
        const char *_db_pw,
        const char* _schema);
    ~MySQL();

private:
    MYSQL *m_db_con;
    const char *m_db_addr;
    const char *m_db_id;
    const char *m_db_pw;

    void finish_with_error(const char* file, const int& line);
    const char *print_error();

public:
    void select(const char* sql, std::function<void(const char *)> callback);

    void insert(const char* sql,
                std::function<void(const char *)> error_callback, 
                std::function<void()> callback);
};