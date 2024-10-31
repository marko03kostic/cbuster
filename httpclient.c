#include "httpclient.h"
#include <curl/curl.h>
#include <curl/options.h>
#include <string.h>
#include <stdlib.h>

httpMethod loadHttpMethod(const char *HttpMethodString) {
    if (strcmp(HttpMethodString, "GET") == 0) return HTTP_GET;
    if (strcmp(HttpMethodString, "POST") == 0) return HTTP_POST;
    if (strcmp(HttpMethodString, "PUT") == 0) return HTTP_PUT;
    if (strcmp(HttpMethodString, "DELETE") == 0) return HTTP_DELETE;
    if (strcmp(HttpMethodString, "PATCH") == 0) return HTTP_PATCH;
    if (strcmp(HttpMethodString, "OPTIONS") == 0) return HTTP_OPTIONS;
    if (strcmp(HttpMethodString, "HEAD") == 0) return HTTP_HEAD;
    if (strcmp(HttpMethodString, "CONNECT") == 0) return HTTP_CONNECT;
    if (strcmp(HttpMethodString, "TRACE") == 0) return HTTP_TRACE;
    return HTTP_UNKNOWN;
}

httpRequestOptions* loadHttpRequestOptions(
    char *userAgent,
    char *username,
    char **headers,
    char **cookies,
    httpMethod method,
    char *host
) {
    httpRequestOptions* opts = createHttpRequestOptions();

    if (userAgent) {
        opts->userAgent = userAgent;
    }

    if (username) {
        opts->username = username;
    }

    if (headers) {
        opts->headers = headers;
    }

    if (cookies) {
        opts->cookies = cookies;
    }

    if (method) {
        opts->method = method;
    }

    if (host) {
        opts->host = host;
    }

    return opts;
}

httpRequestOptions* createHttpRequestOptions() {
    httpRequestOptions *opts = malloc(sizeof(httpRequestOptions));
    
    if (opts == NULL) {
        return NULL;
    }

    opts->userAgent = NULL;
    opts->username = NULL;
    opts->headers = NULL;
    opts->cookies = NULL;
    opts->method = HTTP_UNKNOWN;
    opts->host = NULL;

    return opts;
}

void freeHttpRequestOptions(httpRequestOptions* opts) {
    if (opts == NULL) {
        return;
    }

    free(opts->userAgent);
    free(opts->username);

    if (opts->headers) {
        for (char **header = opts->headers; *header != NULL; ++header) {
            free(*header);
        }
        free(opts->headers);
    }

    if (opts->cookies) {
        for (char **cookie = opts->cookies; *cookie != NULL; ++cookie) {
            free(*cookie);
        }
        free(opts->cookies);
    }

    free(opts->host);
    free(opts);
}

void performHttpRequest(httpRequestOptions opts) {
    CURL *curl = curl_easy_init();
    CURLcode res;
    
    curl_easy_setopt(curl, CURLOPT_URL, opts.host);
    
    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
}
