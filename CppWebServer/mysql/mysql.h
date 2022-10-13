#include <mysql.h>

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

    void finish_with_error(const char* file, const long& line);

public:
    MYSQL_RES* select(const char* sql);
    void insert();
};