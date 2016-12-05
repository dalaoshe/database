//
// Created by ykd on 16-11-28.
//

#ifndef DATABASE_DROPINDEXSTATEMENT_H
#define DATABASE_DROPINDEXSTATEMENT_H

#include "SQLStatement.h"

namespace hsql {

/**
 * @struct DropIndexStatement
 * @brief Represents "DROP INDEX customer(name)"
 */
    struct DropIndexStatement : SQLStatement {

        DropIndexStatement() :
                SQLStatement(kStmtDropIndex),
                table(NULL),
                column(NULL) {};

        virtual ~DropIndexStatement() {
            delete table;
            delete column;
        }

        const char* column;
        const char* table;
    };


} // namespace hsql
#endif //DATABASE_DROPINDEXSTATEMENT_H
