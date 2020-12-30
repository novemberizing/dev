#include <x/types.h>
#include <x/log.h>

#include "_log.h"

int check_log_function(int total)
{
    FILE * fp = fopen("/dev/null", "w");
    xlogfobjset(fp);
    for(int i = 0; i < total; i++)
    {
        xfunction("check_log_function(%d)", i);
    }
    fclose(fp);
    xlogfobjset(xnil);
    return true;
}

int check_log_critical(int total)
{
    FILE * fp = fopen("/dev/null", "w");
    xlogfobjset(fp);
    for(int i = 0; i < total; i++)
    {
        xcritical("critical => %d", i);
    }
    fclose(fp);
    xlogfobjset(xnil);
    return true;
}

int check_log_error(int total)
{
    FILE * fp = fopen("/dev/null", "w");
    xlogfobjset(fp);
    for(int i = 0; i < total; i++)
    {
        xerror("error => %d", i);
    }
    fclose(fp);
    xlogfobjset(xnil);
    return true;
}

int check_log_warning(int total)
{
    FILE * fp = fopen("/dev/null", "w");
    xlogfobjset(fp);
    for(int i = 0; i < total; i++)
    {
        xwarning("warning => %d", i);
    }
    fclose(fp);
    xlogfobjset(xnil);
    return true;
}

int check_log_caution(int total)
{
    FILE * fp = fopen("/dev/null", "w");
    xlogfobjset(fp);
    for(int i = 0; i < total; i++)
    {
        xcaution("caution => %d", i);
    }
    fclose(fp);
    xlogfobjset(xnil);
    return true;
}

int check_log_notice(int total)
{
    FILE * fp = fopen("/dev/null", "w");
    xlogfobjset(fp);
    for(int i = 0; i < total; i++)
    {
        xnotice("notice => %d", i);
    }
    fclose(fp);
    xlogfobjset(xnil);
    return true;
}

int check_log_information(int total)
{
    FILE * fp = fopen("/dev/null", "w");
    xlogfobjset(fp);
    for(int i = 0; i < total; i++)
    {
        xinformation("information => %d", i);
    }
    fclose(fp);
    xlogfobjset(xnil);
    return true;
}

int check_log_debug(int total)
{
    FILE * fp = fopen("/dev/null", "w");
    xlogfobjset(fp);
    for(int i = 0; i < total; i++)
    {
        xdebug("debug => %d", i);
    }
    fclose(fp);
    xlogfobjset(xnil);
    return true;
}

int check_log_verbose(int total)
{
    FILE * fp = fopen("/dev/null", "w");
    xlogfobjset(fp);
    for(int i = 0; i < total; i++)
    {
        xverbose("verbose => %d", i);
    }
    fclose(fp);
    xlogfobjset(xnil);
    return true;
}

int check_log_assertion(int total)
{
    FILE * fp = fopen("/dev/null", "w");
    xlogfobjset(fp);
    xabortset(false);
    for(int i = 0; i < total; i++)
    {
        xassertion(random() % 2, "assertion => %d", i);
    }
    xabortset(true);
    fclose(fp);
    xlogfobjset(xnil);
    return true;
}

static int __check_log_function(int condition, int i)
{
    xcheck(condition, xfail, "assertion => %d", i);
    return xsuccess;
}

static void __check_log_function_void(int condition, int i)
{
    xcheckvoid(condition, "assertion => %d", i);
}


int check_log_check(int total)
{
    FILE * fp = fopen("/dev/null", "w");
    xlogfobjset(fp);
    for(int i = 0; i < total; i++)
    {
        int condition = random() % 2;
        int ret = __check_log_function(condition, i);
        xlogfobjset(xnil);
        xassertion(condition ? ret != xfail : ret != xsuccess, "xcheck %d %d %d %d", condition, i, ret, ret == xsuccess);
        xlogfobjset(fp);
    }
    fclose(fp);
    xlogfobjset(xnil);
    return true;
}

int check_log_checkvoid(int total)
{
    FILE * fp = fopen("/dev/null", "w");
    xlogfobjset(fp);
    for(int i = 0; i < total; i++)
    {
        int condition = random() % 2;
        __check_log_function_void(condition, i);
    }
    fclose(fp);
    xlogfobjset(xnil);
    return true;
}

int check_log_all(int total)
{
    fprintf(stdout, "[check/log] function => %s\n", check_log_function(total) ? "ok" : "fail");
    fprintf(stdout, "[check/log] critical => %s\n", check_log_critical(total) ? "ok" : "fail");
    fprintf(stdout, "[check/log] error => %s\n", check_log_error(total) ? "ok" : "fail");
    fprintf(stdout, "[check/log] warning => %s\n", check_log_warning(total) ? "ok" : "fail");
    fprintf(stdout, "[check/log] caution => %s\n", check_log_caution(total) ? "ok" : "fail");
    fprintf(stdout, "[check/log] notice => %s\n", check_log_notice(total) ? "ok" : "fail");
    fprintf(stdout, "[check/log] information => %s\n", check_log_information(total) ? "ok" : "fail");
    fprintf(stdout, "[check/log] debug => %s\n", check_log_debug(total) ? "ok" : "fail");
    fprintf(stdout, "[check/log] verbose => %s\n", check_log_verbose(total) ? "ok" : "fail");
    fprintf(stdout, "[check/log] assertion => %s\n", check_log_assertion(total) ? "ok" : "fail");
    fprintf(stdout, "[check/log] check => %s\n", check_log_check(total) ? "ok" : "fail");
    fprintf(stdout, "[check/log] checkvoid => %s\n", check_log_checkvoid(total) ? "ok" : "fail");

    return true;
}