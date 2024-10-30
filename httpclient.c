#include "httpclient.h"
#include <curl/curl.h>
#include <curl/options.h>
#include <string.h>
#include <curl/curl.h>

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

void performHttpRequest(httpRequestOptions opts) {
    CURL *curl = curl_easy_init();
    CURLcode res;
    
    curl_easy_setopt(curl, CURLOPT_URL, opts.host);
    
    res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
}
