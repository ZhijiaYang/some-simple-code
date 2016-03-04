// a simple example with libcurl
// this is a tool to get a web page
// how to use this tool? just see the curl_test function
// libcurl needed
// gcc curl.c -lcurl

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>

struct MemoryStruct {
    char *memory;
    size_t size;
};

static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    struct MemoryStruct *mem = (struct MemoryStruct *)userp;

    mem->memory = realloc(mem->memory, mem->size + realsize + 1);
    if(mem->memory == NULL) {
        /* out of memory! */
        printf("not enough memory (realloc returned NULL)\n");
        return 0;
    }

    memcpy(&(mem->memory[mem->size]), contents, realsize);
    mem->size += realsize;
    mem->memory[mem->size] = 0;

    return realsize;
}


int curl(char* url, char** buff, size_t* size)
{
    CURL *curl_handle;
    CURLcode res;

    struct MemoryStruct chunk;

    chunk.memory = malloc(1);
    chunk.size = 0;
    curl_global_init(CURL_GLOBAL_ALL);
    curl_handle = curl_easy_init();
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
    curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    res = curl_easy_perform(curl_handle);
    if(res != CURLE_OK) {
        printf("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        *size = 0;
        *buff = NULL;
    }
    else {
        *size = chunk.size;
        *buff = chunk.memory;
    }
    curl_easy_cleanup(curl_handle);
    // free(chunk.memory); // need free by user
    curl_global_cleanup();
    return 0;
}

void curl_test()
{
    size_t size = 0;
    char* buff = NULL;
    curl("www.baidu.com", &buff, &size);
    if(size >0)
    {
        printf("size: %d\nbuff: %s\n", size, buff);
        free(buff);
    }
    else
    {
        printf("get nothing\n");
    }
    size = 0;
    buff = NULL;
    curl("www.baidu.com", &buff, &size);
    if(size >0)
    {
        printf("size: %d\nbuff: %s\n", size, buff);
        free(buff);
    }
    else
    {
        printf("get nothing\n");
    }
}
