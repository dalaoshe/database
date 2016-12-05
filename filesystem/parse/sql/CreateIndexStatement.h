//
// Created by ykd on 16-11-28.
//

#ifndef DATABASE_CREATEINDEXSTATEMENT_H
#define DATABASE_CREATEINDEXSTATEMENT_H

#include "SQLStatement.h"

namespace hsql {
    /**
     * Represents SQL CreateIndex statements.
     * Example: "CREATE INDEX customer(name)"
     */
    struct CreateIndexStatement : SQLStatement {

        CreateIndexStatement() :
                SQLStatement(kStmtCreateIndex),
                column(NULL),
                table(NULL){};

        ~CreateIndexStatement() {
            delete column;
            delete table;
        }

        const char* column;
        const char* table;
    };

} // namespace hsql
#endif //DATABASE_CREATEINDEXSTATEMENT_H
