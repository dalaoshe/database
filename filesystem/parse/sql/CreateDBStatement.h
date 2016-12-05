#ifndef __CREATEDB_STATEMENT_H__
#define __CREATEDB_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {
    /**
     * Represents SQL CreateDB statements.
     * Example: "CREATE DATABASE orderDB"
     */
    struct CreateDBStatement : SQLStatement {

        CreateDBStatement() :
            SQLStatement(kStmtCreateDB),
            DBname(NULL)
            {};

        ~CreateDBStatement() {
            delete DBname;
        }

        const char* DBname;
    };

} // namespace hsql
#endif