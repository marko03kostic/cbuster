#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

typedef enum {
    HTTP_GET,
    HTTP_POST,
    HTTP_PUT,
    HTTP_DELETE,
    HTTP_PATCH,
    HTTP_OPTIONS,
    HTTP_HEAD,
    HTTP_CONNECT,
    HTTP_TRACE,
    HTTP_UNKNOWN,
} httpMethod;

typedef struct {
    char *userAgent;
    char *username;
    char **headers;
    char **cookies;
    httpMethod method;
    char *host;
} httpRequestOptions;

void performHttpRequest(httpRequestOptions opts);

httpMethod loadHttpMethod(const char *HttpMethodString);

#endif
