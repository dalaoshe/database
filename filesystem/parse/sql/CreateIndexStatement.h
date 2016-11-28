//
// Created by ykd on 16-11-28.
//

#ifndef DATABASE_CREATEINDEXSTATEMENT_H
#define DATABASE_CREATEINDEXSTATEMENT_H

#include "SQLStatement.h"

namespace hsql {
    /**
     * Represents SQL CreateDB statements.
     * Example: "CREATE DATABASE orderDB"
     */
    struct CreateIndexStatement : SQLStatement {

        CreateIndexStatement() :
                SQLStatement(kStmtCreateIndex),
                indexName(NULL){};

        ~CreateIndexStatement() {
            delete indexName;
        }

        const char* indexName;
    };

} // namespace hsql
#endif //DATABASE_CREATEINDEXSTATEMENT_H
