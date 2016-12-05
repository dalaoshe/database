//
// Created by ykd on 16-11-28.
//

#ifndef DATABASE_DESCSTATEMENT_H
#define DATABASE_DESCSTATEMENT_H

#include "SQLStatement.h"

namespace hsql {

/**
 * @struct DescStatement
 * @brief Represents "DESC table_name"
 */
    struct DescStatement : SQLStatement {

        DescStatement() :
                SQLStatement(kStmtDesc),
                table_name(NULL) {};

        virtual ~DescStatement() {
            delete table_name;
        }

        const char* table_name;
    };


}
#endif //DATABASE_DESCSTATEMENT_H
