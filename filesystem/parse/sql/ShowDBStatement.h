//
// Created by ykd on 16-11-28.
//

#ifndef DATABASE_SHOWDBSTATEMENT_H
#define DATABASE_SHOWDBSTATEMENT_H


#include "SQLStatement.h"

namespace hsql {

/**
 * @struct ShowDBStatement
 * @brief Represents "SHOW DATABASES"
 */
    struct ShowDBStatement : SQLStatement {

        ShowDBStatement() :
                SQLStatement(kStmtShowDB){};

        virtual ~ShowDBStatement() {
        }

    };


}
#endif //DATABASE_SHOWDBSTATEMENT_H
