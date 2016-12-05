//
// Created by ykd on 16-11-28.
//

#ifndef DATABASE_DROPDBSTATEMENT_H
#define DATABASE_DROPDBSTATEMENT_H
#include "SQLStatement.h"

namespace hsql {

/**
 * @struct DropDBStatement
 * @brief Represents "DROP DATABASE Dbname"
 */
    struct DropDBStatement : SQLStatement {

        DropDBStatement() :
                SQLStatement(kStmtDropDB),
                DBname(NULL) {};

        virtual ~DropDBStatement() {
            delete DBname;
        }

        const char* DBname;
    };


} // namespace hsql
#endif //DATABASE_DROPDBSTATEMENT_H
