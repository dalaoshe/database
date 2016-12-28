#ifndef REDBASE_H
#define REDBASE_H

// Please DO NOT include any other files in this file.
#include <iostream>
#include <cmath>
#include <cassert>

//
// Globally-useful defines
//
#define MAXNAME       24                // maximum length of a relation
// or attribute name
#define MAXSTRINGLEN  255               // maximum length of a
// string-type attribute
#define MAXATTRS      40                // maximum number of attributes
// in a relation

//
// Return codes
//


#define OK_RC         0    // OK_RC return code is guaranteed to always be 0

#define START_PF_ERR  (-1)
#define END_PF_ERR    (-100)
#define START_RM_ERR  (-101)
#define END_RM_ERR    (-200)
#define START_IX_ERR  (-201)
#define END_IX_ERR    (-300)
#define START_SM_ERR  (-301)
#define END_SM_ERR    (-400)
#define START_QL_ERR  (-401)
#define END_QL_ERR    (-500)

#define START_PF_WARN  1
#define END_PF_WARN    100
#define START_RM_WARN  101
#define END_RM_WARN    200
#define START_IX_WARN  201
#define END_IX_WARN    300
#define START_SM_WARN  301
#define END_SM_WARN    400
#define START_QL_WARN  401
#define END_QL_WARN    500

// ALL_PAGES is defined and used by the ForcePages method defined in RM
// and PF layers
const int ALL_PAGES = -1;

//
// Attribute types
//
enum AttrType {
    INT ,//0
    FLOAT,//1
    STRING,//2
};

enum ColType {
    PRIMARY ,//0
    UNIQUE,//1
    INDEX,//2
    NORMAL,//3
};

//
// Comparison operators
//
enum CompOp {
    NO_OP,                                      // no comparison
    EQ_OP, NE_OP, LT_OP, GT_OP, LE_OP, GE_OP,    // binary atomic operators
    LIKE_OP, ISNULL_OP,
    IN_OP
};

//
// Aggregation functions for group by
//
enum AggFun {
    NO_F,
    MIN_F, MAX_F, COUNT_F,
    SUM_F, AVG_F           // numeric args only
};

//
// Pin Strategy Hint
//
enum ClientHint {
    NO_HINT                                     // default value
};

//
// TRUE, FALSE and BOOLEAN
//
#ifndef BOOLEAN
typedef char Boolean;
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef NULL
#define NULL 0
#endif

#define CreateDBOK 1
#define CreateDBW 2
#define DropDBOK 3
#define DropDBW 4
#define CreateTableOK 5
#define CreateTableW 6
#define DropTableOK 7
#define DropTableW 8
#define UseDBOK 9
#define UseDBW 10
#define InsertOK 11
#define DeleteOK 12
#define UpdateOK 13
#define SelectOK 14
#define CreateIndexOK 15
#define DropIndexOK 16
#define ShowDBOK 17
#define ShowTablesOK 18

#define DumplicatePrimaryKey 19
#define InsertW 20
#define DeleteW 21
#define UpdateW 22
#define SelectW 23
#define InvalidInput 24
#define InsertPrimaryW 25
#define InsertIndexW 26
#define OperateW 27
#define DataTypeW 28
#define CheckW 29
#define DeleteIndexW 30
#define SearchByWhereOK 31


#endif