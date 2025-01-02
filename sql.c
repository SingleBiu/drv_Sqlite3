/*
 * @Author: SingleBiu
 * @Date: 2021-09-13 15:27:10
 * @LastEditors: SingleBiu 854390236@qq.com
 * @LastEditTime: 2025-01-02 11:03:46
 * @Description: file content
 */
#include "sql.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

int insert_db_v2(sqlite3 *db, char buf[])
{
    char *zErrMsg = NULL;
    char buffer[64];
    // 数据拼接
    sprintf(buffer,"INSERT INTO 'data'(VALUE)VALUES('%s');",buf);

    printf("Buffer : %s\tbuf : %s\n",buffer,buf);

    // 执行插入操作
    sqlite3_exec(db, buffer, NULL, NULL, &zErrMsg);

    printf("Insert complete\n");

    return 0;
}

int handle_db(char *buf)
{
    sqlite3 *db = NULL;
    int len;
    int i = 0;
    int nrow = 0;
    int ncolumn = 0;
    char *zErrMsg = NULL;
    char **azResult = NULL; //二维数组存放结果
    
    /* 打开数据库 */
    len = sqlite3_open(DB_FILE, &db);
    if (len)
    {
        /*  fprintf函数格式化输出错误信息到指定的stderr文件流中  */
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db)); //sqlite3_errmsg(db)用以获得数据库打开错误码的英文描述。
        sqlite3_close(db);
        exit(1);
    }
    else
        printf("Database opened\n");

    /* 创建表 */
    char *sql = "CREATE TABLE data(\
                VALUE        TEXT\
                );";

    sqlite3_exec(db, sql, NULL, NULL, &zErrMsg);

    /*插入数据  */    
    insert_db_v2(db,buf);

    //   /* 查询数据 */
    //   sql="select *from SensorData";
    //   sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
    //   printf("nrow=%d ncolumn=%d\n",nrow,ncolumn);
    //   printf("the result is:\n");
    //   for(i=0;i<(nrow+1)*ncolumn;i++)
    //     {
    //       printf("azResult[%d]=%s\n",i,azResult[i]);
    //     }

    //  /* 删除某个特定的数据 */
    //   sql="delete from SensorData where SensorID = 1 ;";
    //   sqlite3_exec( db , sql , NULL , NULL , &zErrMsg );

    //   /* 查询删除后的数据 */
    //   sql = "SELECT * FROM SensorData ";
    //   sqlite3_get_table( db , sql , &azResult , &nrow , &ncolumn , &zErrMsg );
    //   printf( "row:%d column=%d\n " , nrow , ncolumn );
    //   printf( "After deleting , the result is : \n" );
    //   for( i=0 ; i<( nrow + 1 ) * ncolumn ; i++ )
    //   {
    //         printf( "azResult[%d] = %s\n", i , azResult[i] );
    //   }
    //   sqlite3_free_table(azResult);

    sqlite3_close(db);
    return 0;
}