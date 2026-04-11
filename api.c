#include "functions.h"

CURL *curl = NULL;
CURLcode result = NULL;
char *header = ""; // Add header here if needed
struct curl_slist *headers = NULL;

// Functions requests to server and gets all computers
int getAllComputers(){
    curl = curl_easy_init();
    if (curl){
        curl_easy_setopt(curl, CURLOPT_URL, "127.0.0.1:8080");
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);

        result = curl_easy_perform(curl);

        if(result != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        
        
    }
    curl_easy_cleanup(curl);
    return (int)result;
}



int getComputerByHostname(char *hostname){
    curl = curl_easy_init();
    if (curl){
        //WIP
    }
}