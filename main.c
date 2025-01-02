/*
 * @Author: SingleBiu 854390236@qq.com
 * @Date: 2025-01-02 10:39:28
 * @LastEditors: SingleBiu 854390236@qq.com
 * @LastEditTime: 2025-01-02 11:01:57
 * @FilePath: /Code/drv_Sqlite3/main.c
 * @Description: 
 * 
 */
#include "sql.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    char buf[] = "Hello world";
    while (1)
    {
        handle_db(buf);
        sleep(1);
    }
    return 0;
}