//
// Created by ykd on 16-11-28.
//

#ifndef DATABASE_DROPINDEXSTATEMENT_H
#define DATABASE_DROPINDEXSTATEMENT_H

#include "SQLStatement.h"

namespace hsql {

/**
 * @struct DropDBStatement
 * @brief Represents "DROP DATABASE Dbname"
 */
    struct DropIndexStatement : SQLStatement {

        DropIndexStatement() :
                SQLStatement(kStmtDropIndex),
                DBname(NULL) {};

        virtual ~DropIndexStatement() {
            delete DBname;
        }

        const char* DBname;
    };


} // namespace hsql
#endif //DATABASE_DROPINDEXSTATEMENT_H
