//
// Created by ykd on 16-11-28.
//

#ifndef DATABASE_USEDBSTATEMENT_H
#define DATABASE_USEDBSTATEMENT_H


#include "SQLStatement.h"

namespace hsql {

/**
 * @struct UseDBStatement
 * @brief Represents "USE DATABASE Dbname"
 */
    struct UseDBStatement : SQLStatement {

        UseDBStatement() :
                SQLStatement(kStmtUseDB),
                DBname(NULL) {};

        virtual ~UseDBStatement() {
            delete DBname;
        }

        const char* DBname;
    };


}
#endif //DATABASE_USEDBSTATEMENT_H
