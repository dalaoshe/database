#ifndef PAGE_DEF
#define PAGE_DEF
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
/*
 * 一个页面中的字节数
 */
#define PAGE_SIZE 8192
/*
 * 一个页面中的整数个数
 */
#define PAGE_INT_NUM 2048
//pageid 偏移
/*
 * 页面字节数以2为底的指数
 */
#define PAGEID_INT_OFFSET 0
//标记该页是否已满的INT偏移
#define PAGE_SLOT_IS_FULL_INT_OFFSET 1
//记录该页已经使用的槽数的INT偏移
#define PAGE_SLOT_USED_NUMBER_INT_OFFSET 3
//记录该页最多能存的槽数的INT偏移
#define PAGE_SLOT_MAX_NUMBER_INT_OFFSET 2
//记录该页每个槽INT长度的INT偏移
#define PAGE_SLOT_INT_SIZE_INT_OFFSET 4
//记录该页使用了多少int位图的INT偏移
#define PAGE_SLOT_INT_NUM_INT_OFFSET 5
//最后32个byte为位图
#define RECORD_BITMAP_SIZE 32
//页头大小 8*4 = 32 byte
#define PAGE_HEADER_SIZE 32
#define PAGE_HEADER_INT_SIZE 8
#define PAGE_INT_SIZE 2048
#define PAGE_HEADER_ATTR_CNT 4

//数据页首页中字段定义的偏移


#define TABLE_RECORD_INT_SIZE_INT_OFFSET 1
#define TABLE_ATTR_COUNT_INT_OFFSET 2
#define TABLE_FREE_PAGE_INT_OFFSET 3
#define TABLE_LAST_PAGEID_INT_OFFSET 4
//CHECK 段信息的偏移
#define TABLE_CHECK_INT_OFFSET 512
//列数据类型信息偏移
#define ATTR_VALUE_TYPE_INT_OFFSET 5
//每一列名的最大长度
#define ATTR_NAME_MAX_SIZE 20
//列数据长度信息偏移
#define ATTR_VALUE_LENGTH_INT_OFFSET 6
//列是否可为空信息偏移
#define ATTR_NOT_NULL_INT_OFFSET 7
//列类型（索引，主键等）信息偏移
#define ATTR_TYPE_INT_OFFSET 8
//数据页头页中每个列的属性信息的INT大小
#define ATTR_INT_SIZE 10
//数据页头页中第一个列的属性信息的开始位置
#define ATTR_INT_OFFSET 8
#define PAGE_SIZE_IDX 13
//数据页头页中CHECK列的字段定义
//有几个约束选择
#define ATTR_CHECK_NUMBER_INT_OFFSET 0
//CHECK的头长度
#define ATTR_CHECK_RECORD_HEADER_INT_OFFSET 2
//每个列的CHECK最大长度
#define ATTR_CHECK_ENTRY_VALUES_INT_OFFSET 1
#define ATTR_CHECK_ENTRY_OP_INT_OFFSET 0
#define ATTR_CHECK_ENTRY_PADDING 4
//OP(4字节) VALUES（最大长度）
#define ATTR_CHECK_INT_SIZE 256

#define MAX_FMT_INT_NUM 128
//#define BUF_PAGE_NUM 65536
#define MAX_FILE_NUM 128
#define MAX_TYPE_NUM 256

//数据行的存储偏移(字节)
#define RECORD_TAG_A 0
#define RECORD_TAG_B 1
#define RECORD_FIX_LENGTH 2
#define RECORD_NULL_BITMAP 3
#define RECORD_FIX_DATA 8
#define RECORD_NULL_BITMAP_SIZE (RECORD_FIX_DATA - RECORD_NULL_BITMAP)
#define RECORD_MIN_FREE_NUMBER 10
//最小数据行INT长度
#define RECORD_MIN_INT_SIZE 8

/*
 * 缓存中页面个数上限
 */
#define CAP 60000
/*
 * hash算法的模
 */
#define MOD 60000
#define IN_DEBUG 0
#define DEBUG_DELETE 0
#define DEBUG_ERASE 1
#define DEBUG_NEXT 1
/*
 * 一个表中列的上限
 */
#define MAX_COL_NUM 31
/*
 * 数据库中表的个数上限
 */
#define MAX_TB_NUM 31
#define RELEASE 1
typedef unsigned int* BufType;
typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;
typedef unsigned long long ull;
typedef long long ll;
typedef double db;
typedef int inter;
typedef int(cf)(uchar*, uchar*);
int current = 0;
int tt = 0;

#endif
