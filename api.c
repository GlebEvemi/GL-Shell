#include "functions.h"

CURL *curl;
CURLcode result;

//example of a function that sends data to a server using libcurl
int senddata(){
    curl = curl_easy_init();
    if (curl){
        curl_easy_setopt(curl, CURLOPT_URL, "127.0.0.1:8080");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "data=HelloWorld");

        result = curl_easy_perform(curl);

        if(result != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));

    }
    curl_easy_cleanup(curl);
    return (int)result;
}