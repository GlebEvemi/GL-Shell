#include "functions.h"


size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);


typedef struct {
    char *memory;
    size_t size;
} MemoryStruct;

// Functions requests server and gets all computers
int getAllComputers(char *server_url, char *username, char *password){
    char new_url[256];
    snprintf(new_url, sizeof(new_url), "%s/api/pc", server_url);
    CURL *curl = NULL;
    CURLcode result;
    char *header = ""; // Add header here if needed
    struct curl_slist *headers = NULL;
    MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    
    // Initialize curl
    curl = curl_easy_init();
    if(!curl) return -1;

    curl_easy_setopt(curl, CURLOPT_URL, new_url);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // only for testing, remove in production (ignores TLS cert)
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // only for testing, remove in production (ignores TLS cert)
    curl_easy_setopt(curl, CURLOPT_USERNAME, username);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    result = curl_easy_perform(curl);

    if(result != CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        curl_easy_cleanup(curl);
        return -1;
    }

    cJSON *json = cJSON_Parse(chunk.memory);

    if(json == NULL){
        printf("JSON parse error\n");
    }
    else{

        int count = cJSON_GetArraySize(json);

        for(int i = 0; i < count; i++){

            cJSON *item = cJSON_GetArrayItem(json, i);

            printf("%s\n", item->valuestring);
        }

        cJSON_Delete(json);
    }
        
        
    
    curl_easy_cleanup(curl);
    free(chunk.memory);
    return (int)result;
}



int getComputerByHostname(char *server_url,char *hostname, char *username, char *password){
    CURL *curl = NULL;
    CURLcode result;
    char *header = ""; // Add header here if needed
    struct curl_slist *headers = NULL;

    char new_url[128];
    char *encoded = curl_easy_escape(curl, hostname, 0);
    snprintf(new_url, sizeof(new_url), "%s/api/pc/%s", server_url, encoded);
    curl_free(encoded);
    MemoryStruct chunk;
    chunk.memory = malloc(1);
    chunk.size = 0;

    // Initialize curl
    curl = curl_easy_init();
    if(!curl) return -1;

    curl_easy_setopt(curl, CURLOPT_URL, new_url);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); // only for testing, remove in production (ignores TLS cert)
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); // only for testing, remove in production (ignores TLS cert)
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_USERNAME, username);
    curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    result = curl_easy_perform(curl);

    if(result != CURLE_OK){
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(result));
        curl_easy_cleanup(curl);
        return -1;
    }

    cJSON *json = cJSON_Parse(chunk.memory);

    cJSON *jsonHostname = cJSON_GetObjectItem(json, "Hostname");
    cJSON *os = cJSON_GetObjectItem(json, "OSName");
    cJSON *ram = cJSON_GetObjectItem(json, "totalRam_Gb");

    printf("Hostname : %s\n", jsonHostname->valuestring);
    printf("OS       : %s\n", os->valuestring);
    printf("RAM      : %.2f GB\n", ram->valuedouble);

    cJSON_Delete(json);
    
    curl_easy_cleanup(curl);
    free(chunk.memory);
    return (int)result;


}


size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realSize = size * nmemb;

    MemoryStruct *mem = (MemoryStruct *)userp;

    char *ptr = realloc(mem->memory, mem->size + realSize + 1);

    if(ptr == NULL)
        return 0;

    mem->memory = ptr;

    memcpy(&(mem->memory[mem->size]), contents, realSize);

    mem->size += realSize;

    mem->memory[mem->size] = 0;

    return realSize;
}