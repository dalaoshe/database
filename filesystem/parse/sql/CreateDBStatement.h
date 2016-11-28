#ifndef __CREATE_STATEMENT_H__
#define __CREATE_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {
    /**
     * Represents SQL CreateDB statements.
     * Example: "CREATE DATABASE orderDB"
     */
    struct CreateDBStatement : SQLStatement {

        CreateDBStatement() :
            SQLStatement(kStmtCreateDB),
            dbName(NULL)
            {};

        ~CreateStatement() {
            delete dbName;
        }

        const char* dbName;
    };

} // namespace hsql
#endif