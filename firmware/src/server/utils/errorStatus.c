#include "errorStatus.h"

const char *getHttpStatusText(int code)
{
    switch (code)
    {
    case 200:
        return "200 OK";
    case 400:
        return "400 Bad Request";
    case 401:
        return "401 Unauthorized";
    case 403:
        return "403 Forbidden";
    case 404:
        return "404 Not Found";
    case 500:
    default:
        return "500 Internal Server Error";
    }
}
