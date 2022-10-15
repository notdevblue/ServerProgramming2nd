#include <string.h>
#include <stdio.h>
#include <functional>
#include "./mysql.h"
#include "../han.h"
// 근본과 무근본의 융합

MySQL::MySQL(const char *_addr,
             const char *_db_id,
             const char *_db_pw,
             const char *_schema)
                : m_db_addr(_addr)
                , m_db_id(_db_id)
                , m_db_pw(_db_pw) {

    printf("MySQL client version %s\n", mysql_get_client_info());

    m_db_con = mysql_init(nullptr);

    if (m_db_con == nullptr) {
        exit_with_comment("", __FILE__, __LINE__);
    }

    if (mysql_real_connect(m_db_con, m_db_addr, m_db_id, m_db_pw,
                           _schema, 0, NULL, 0) == NULL) {
        finish_with_error(__FILE__, __LINE__);
    }
}

MySQL::~MySQL() {
    mysql_close(m_db_con);
}

void MySQL::finish_with_error (const char* file, const int& line) {
    fprintf(stderr, "Error %s at: %s (%d)\n", mysql_error(m_db_con), file, line);
    mysql_close(m_db_con);
    exit(1);
}


void MySQL::select(const char* sql, std::function<void(const char *)> callback) {

    // 쿼리
    if (mysql_query(m_db_con, sql)) { 
        finish_with_error(__FILE__, __LINE__);
    }

    MYSQL_RES *result = mysql_store_result(m_db_con);

    if (result == NULL) {
        finish_with_error(__FILE__, __LINE__);
    }

    char *field_res_str = (char *)calloc(1024, sizeof(char));
    if (!field_res_str) {
        exit_with_comment("Failed calloc", __FILE__, __LINE__);
    }
    const unsigned int num_fields = mysql_num_fields(result);
    MYSQL_ROW row;
    MYSQL_FIELD *field;

    // 컬럼명 직렬화
    while ((field = mysql_fetch_field(result))) {
        memcpy(field_res_str + strlen(field_res_str), field->name, field->name_length);
        field_res_str[strlen(field_res_str)] = ',';
    }

    // 컬럼명과 값 구분을 위해
    field_res_str[strlen(field_res_str) - 1] = '#';

    while ((row = mysql_fetch_row(result))) {

        for (int i = 0; i < num_fields; ++i) {
            const char *fetched_row = (row[i] ? row[i] : "NULL");
            memcpy(field_res_str + strlen(field_res_str), fetched_row, strlen(fetched_row));
            field_res_str[strlen(field_res_str)] = ',';
        }
    }

    // 문자열 끝 구분을 위해
    field_res_str[strlen(field_res_str) - 1] = ';';

    // resize (encluding null terminator)
    field_res_str = (char *)realloc(field_res_str, strlen(field_res_str) + sizeof(char));

    if (callback)
        callback(field_res_str);

    mysql_free_result(result);
    free(field_res_str);
}