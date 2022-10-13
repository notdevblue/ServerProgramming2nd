#include "./mysql.h"
#include <iostream>


MySQL::MySQL(const char *_addr,
             const char *_db_id,
             const char *_db_pw,
             const char *_schema)
                : m_db_addr(_addr)
                , m_db_id(_db_id)
                , m_db_pw(_db_pw) {
    
    std::cout << "MySQL client version: " << mysql_get_client_info() << std::endl;

    m_db_con = mysql_init(nullptr);

    if (m_db_con == nullptr) {
        std::cerr << "Error at: " << __FILE__
            << "(" << __LINE__ << ")" << std::endl;
        exit(1);
    }

    if (mysql_real_connect(m_db_con, m_db_addr, m_db_id, m_db_pw,
                           _schema, 0, NULL, 0) == NULL) {
        finish_with_error(__FILE__, __LINE__);
    }
}

void MySQL::finish_with_error (const char* file, const long& line) {
    std::cerr << "Error " << mysql_error(m_db_con)
            << " at: " << file << " (" << line << ")" << std::endl;
    mysql_close(m_db_con);
    exit(1);
}

MySQL::~MySQL() {
    mysql_close(m_db_con);
}

MYSQL_RES* MySQL::select(const char* sql) {
    if (mysql_query(m_db_con, sql)) {
        finish_with_error(__FILE__, __LINE__);
    }

    MYSQL_RES *result = mysql_store_result(m_db_con);
    
    if (result == NULL) {
        finish_with_error(__FILE__, __LINE__);
    }

    return result;
}