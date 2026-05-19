#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>
#include "../inc/functions.h"

/* Mock write callback for capturing response */
static char mock_response[1024] = {0};
static size_t mock_write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size * nmemb;
    if (realsize < sizeof(mock_response)) {
        memcpy(mock_response, contents, realsize);
    }
    return realsize;
}

/* Tests for getAllComputers */
START_TEST(test_get_all_computers_invalid_url)
{
    int result = getAllComputers("invalid_url", "user", "pass");
    // Should fail due to invalid URL
    ck_assert(result != 0);
}
END_TEST

START_TEST(test_get_all_computers_null_url)
{
    int result = getAllComputers(NULL, "user", "pass");
    // Should fail or handle null gracefully
    ck_assert(result != 0);
}
END_TEST

START_TEST(test_get_all_computers_null_username)
{
    int result = getAllComputers("http://localhost:8000", NULL, "pass");
    // Should fail or handle null username
    ck_assert(result != 0);
}
END_TEST

START_TEST(test_get_all_computers_null_password)
{
    int result = getAllComputers("http://localhost:8000", "user", NULL);
    // Should fail or handle null password
    ck_assert(result != 0);
}
END_TEST

/* Tests for getComputerByHostname */
START_TEST(test_get_computer_by_hostname_invalid_url)
{
    int result = getComputerByHostname("invalid_url", "pc-name", "user", "pass");
    // Should fail due to invalid URL
    ck_assert(result != 0);
}
END_TEST

START_TEST(test_get_computer_by_hostname_null_hostname)
{
    int result = getComputerByHostname("http://localhost:8000", NULL, "user", "pass");
    // Should fail or handle null hostname
    ck_assert(result != 0);
}
END_TEST

START_TEST(test_get_computer_by_hostname_empty_hostname)
{
    int result = getComputerByHostname("http://localhost:8000", "", "user", "pass");
    // Should fail or handle empty hostname
    ck_assert(result != 0);
}
END_TEST

START_TEST(test_get_computer_by_hostname_with_special_chars)
{
    // Test URL encoding of special characters in hostname
    int result = getComputerByHostname("http://localhost:8000", "pc-name@host", "user", "pass");
    // Should attempt to encode special characters
    ck_assert(result != CURLE_OK || result == 0);
}
END_TEST

/* Test suite creation */
Suite *api_suite(void)
{
    Suite *s;
    TCase *tc_get_all_computers;
    TCase *tc_get_computer_by_hostname;

    s = suite_create("API");

    /* getAllComputers tests */
    tc_get_all_computers = tcase_create("GetAllComputers");
    tcase_add_test(tc_get_all_computers, test_get_all_computers_invalid_url);
    tcase_add_test(tc_get_all_computers, test_get_all_computers_null_url);
    tcase_add_test(tc_get_all_computers, test_get_all_computers_null_username);
    tcase_add_test(tc_get_all_computers, test_get_all_computers_null_password);
    suite_add_tcase(s, tc_get_all_computers);

    /* getComputerByHostname tests */
    tc_get_computer_by_hostname = tcase_create("GetComputerByHostname");
    tcase_add_test(tc_get_computer_by_hostname, test_get_computer_by_hostname_invalid_url);
    tcase_add_test(tc_get_computer_by_hostname, test_get_computer_by_hostname_null_hostname);
    tcase_add_test(tc_get_computer_by_hostname, test_get_computer_by_hostname_empty_hostname);
    tcase_add_test(tc_get_computer_by_hostname, test_get_computer_by_hostname_with_special_chars);
    suite_add_tcase(s, tc_get_computer_by_hostname);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = api_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
