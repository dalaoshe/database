//
// Created by ykd on 16-11-28.
//

#ifndef DATABASE_SHOWTABLESTATEMENT_H
#define DATABASE_SHOWTABLESTATEMENT_H


#include "SQLStatement.h"

namespace hsql {

/**
 * @struct ShowTableStatement
 * @brief Represents "SHOW TABLES"
 */
    struct ShowTableStatement : SQLStatement {

        ShowTableStatement() :
                SQLStatement(kStmtShowTable){};

        virtual ~ShowTableStatement() {
        }

    };


}

#endif //DATABASE_SHOWTABLESTATEMENT_H
