#include <iostream>
#include <mysql.h>

using namespace std;

int main()
{
    mysql_library_init(0, NULL, NULL);
    MYSQL *mysql = mysql_init(NULL);
    if (!mysql_real_connect(mysql, "localhost", "root", "cross2000", "mangos", 0, NULL, 0))
    {
        cout << "Error:" << mysql_error(mysql) <<  endl;
    }
    else
    {
        cout << "Connected" << endl;
        char* query = "select entry from creature_template";
        int queryres = mysql_real_query(mysql, query, strlen(query));
        if (queryres != 0)
        {
            cout << "Error: " << mysql_error(mysql) << endl;
        }
        else
        {
            MYSQL_RES* res = mysql_use_result(mysql);

            MYSQL_ROW row;
            int numfields = mysql_num_fields(res);
            MYSQL_FIELD* fields[numfields];
            for (unsigned int i = 0; i < numfields; i++) {
                MYSQL_FIELD* field = mysql_fetch_field(res);
                fields[i] = field;
            }
            while ((row = mysql_fetch_row(res)))
            {
                unsigned long *len;
                len = mysql_fetch_lengths(res);
                for (unsigned int i = 0; i < numfields; i++)
                {
                    MYSQL_FIELD* field = fields[i];
                    char* value = row[i];
                    if (!value) {
                        value = (char*)"NULL";
                    }
                    /*
                    int test = 0;
                    switch (field->type) {
                        case MYSQL_TYPE_INT24:
                            test = (int)row[i];
                            break;
                    }
                    */
                    cout <<  field->name << ": " << field->type << ":" << value << ";" << endl;
                }
            }

            mysql_free_result(res);
        }
        mysql_close(mysql);
    }

    mysql_library_end();
    return 0;
}
