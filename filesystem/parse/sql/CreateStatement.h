#ifndef __CREATE_STATEMENT_H__
#define __CREATE_STATEMENT_H__

#include "SQLStatement.h"

namespace hsql {
    /**
     * Represents definition of a table column
     */
    struct ColumnDefinition {
        enum DataType {
            TEXT,
            INT,
            DOUBLE
        };

        ColumnDefinition(char* name1, DataType type1,int64_t size1, bool not_null1,Expr* expr1) :
            name(name1),
            type(type1),
            size(size1),
            not_null(not_null1),
            check_expr(expr1){}

        virtual ~ColumnDefinition() {
            delete name;
        }

        char* name;
        DataType type;
        int64_t size;
        bool not_null;
        Expr* check_expr;
    };

    /**
     * Represents SQL Create statements.
     * Example: "CREATE TABLE students (name TEXT, student_number INTEGER, city TEXT, grade DOUBLE)"
     */
    struct CreateStatement : SQLStatement {
        enum CreateType {
            kTable,
            kTableFromTbl // Hyrise file format
        };

        CreateStatement(CreateType type) :
            SQLStatement(kStmtCreate),
            type(type),
            ifNotExists(false),
            filePath(NULL),
            tableName(NULL),
            columns(NULL),
            primary_key(NULL){};

        virtual ~CreateStatement() {
            delete columns;
            delete filePath;
            delete tableName;
            delete primary_key;
        }

        CreateType type;

        bool ifNotExists;
        const char* filePath;
        const char* tableName;
        const char* primary_key;
        std::vector<ColumnDefinition*>* columns;
    };

} // namespace hsql
#endif