#ifndef __CREATE_STATEMENT_H__
#define __CREATE_STATEMENT_H__

#include "SQLStatement.h"
#include "../../utils/base.h"
namespace hsql {
    /**
     * Represents definition of a table column
     */
    struct ColumnDefinition {
//        enum DataType {
//            TEXT,
//            INT,
//            DOUBLE
//        };

        ColumnDefinition(char* name1, AttrType type1,int64_t size1, bool not_null1) :
            name(name1),
            type(type1),
            size(size1),
            not_null(not_null1){}

        ColumnDefinition(Expr* expr1) :
            check_expr(expr1){}

        virtual ~ColumnDefinition() {
            delete name;
            delete check_expr;

        }
        Expr* check_expr;
        char* name;
        AttrType type;
        int64_t size;
        bool not_null;

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