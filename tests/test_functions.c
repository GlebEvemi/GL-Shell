#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../inc/functions.h"

/* Test fixtures */
static char *original_dir;

void setup(void)
{
    original_dir = getcwd(NULL, 0);
}

void teardown(void)
{
    if (original_dir) {
        chdir(original_dir);
        free(original_dir);
    }
}

/* Tests for getCommandHandlerByName */
START_TEST(test_get_command_handler_ls)
{
    commandFuncType handler = getCommandHandlerByName("ls");
    ck_assert_ptr_eq(handler, ls);
}
END_TEST

START_TEST(test_get_command_handler_cd)
{
    commandFuncType handler = getCommandHandlerByName("cd");
    ck_assert_ptr_eq(handler, cd);
}
END_TEST

START_TEST(test_get_command_handler_pwd)
{
    commandFuncType handler = getCommandHandlerByName("pwd");
    ck_assert_ptr_eq(handler, pwd);
}
END_TEST

START_TEST(test_get_command_handler_mkdir)
{
    commandFuncType handler = getCommandHandlerByName("mkdir");
    ck_assert_ptr_eq(handler, createDir);
}
END_TEST

START_TEST(test_get_command_handler_rm)
{
    commandFuncType handler = getCommandHandlerByName("rm");
    ck_assert_ptr_eq(handler, rm);
}
END_TEST

START_TEST(test_get_command_handler_clear)
{
    commandFuncType handler = getCommandHandlerByName("clear");
    ck_assert_ptr_eq(handler, clear);
}
END_TEST

START_TEST(test_get_command_handler_pcsearch)
{
    commandFuncType handler = getCommandHandlerByName("pcsearch");
    ck_assert_ptr_eq(handler, findComputer);
}
END_TEST

START_TEST(test_get_command_handler_exit)
{
    commandFuncType handler = getCommandHandlerByName("exit");
    ck_assert_ptr_eq(handler, exitProgram);
}
END_TEST

START_TEST(test_get_command_handler_unknown)
{
    commandFuncType handler = getCommandHandlerByName("unknown_command");
    ck_assert_ptr_eq(handler, UNKNOWN_COMMAND);
}
END_TEST

START_TEST(test_get_command_handler_null)
{
    commandFuncType handler = getCommandHandlerByName(NULL);
    ck_assert_ptr_eq(handler, UNKNOWN_COMMAND);
}
END_TEST

START_TEST(test_get_command_handler_empty_string)
{
    commandFuncType handler = getCommandHandlerByName("");
    ck_assert_ptr_eq(handler, UNKNOWN_COMMAND);
}
END_TEST

/* Tests for mkdir/createDir */
START_TEST(test_mkdir_creates_directory)
{
    chdir("/tmp");
    const char *test_dir = "test_glshell_dir_12345";
    
    // Ensure directory doesn't exist
    rmdir(test_dir);
    
    createDir((char *)test_dir);
    
    struct stat st;
    int result = stat(test_dir, &st);
    
    ck_assert_msg(result == 0, "Directory was not created");
    ck_assert(S_ISDIR(st.st_mode));
    
    // Cleanup
    rmdir(test_dir);
}
END_TEST

START_TEST(test_mkdir_with_null_args)
{
    // Should print error but not crash
    createDir(NULL);
    ck_assert(1);
}
END_TEST

/* Tests for rm */
START_TEST(test_rm_deletes_file)
{
    chdir("/tmp");
    const char *test_file = "test_glshell_file_12345.txt";
    
    // Ensure file doesn't exist first
    remove(test_file);
    
    // Create test file
    FILE *f = fopen(test_file, "w");
    ck_assert_ptr_nonnull(f);
    fprintf(f, "test content");
    fclose(f);
    
    // Verify file exists
    struct stat st_before;
    ck_assert_msg(stat(test_file, &st_before) == 0, "Test file was not created");
    
    // Call rm function
    rm((char *)test_file);
    
    // Verify file is deleted
    struct stat st_after;
    int result = stat(test_file, &st_after);
    
    // Result should be -1 if file doesn't exist
    if (result == 0) {
        // If file still exists, try to clean up manually
        remove(test_file);
    }
    
    ck_assert_msg(result != 0, "File was not deleted by rm()");
}
END_TEST

START_TEST(test_rm_with_null_args)
{
    // Should print error but not crash
    rm(NULL);
    ck_assert(1);
}
END_TEST

/* Tests for cd */
START_TEST(test_cd_changes_directory)
{
    char *before = getcwd(NULL, 0);
    
    cd("/tmp");
    
    char *after = getcwd(NULL, 0);
    
    ck_assert_str_eq(after, "/tmp");
    
    free(before);
    free(after);
}
END_TEST

START_TEST(test_cd_with_null_args)
{
    char *before = getcwd(NULL, 0);
    
    cd(NULL);
    
    char *after = getcwd(NULL, 0);
    
    // Directory should not change
    ck_assert_str_eq(before, after);
    
    free(before);
    free(after);
}
END_TEST

START_TEST(test_cd_with_invalid_path)
{
    char *before = getcwd(NULL, 0);
    
    cd("/nonexistent_path_12345_xyz");
    
    char *after = getcwd(NULL, 0);
    
    // Directory should not change after failed cd
    ck_assert_str_eq(before, after);
    
    free(before);
    free(after);
}
END_TEST

/* Test suite creation */
Suite *functions_suite(void)
{
    Suite *s;
    TCase *tc_command_handler;
    TCase *tc_mkdir;
    TCase *tc_rm;
    TCase *tc_cd;

    s = suite_create("Functions");

    /* Command handler tests */
    tc_command_handler = tcase_create("CommandHandler");
    tcase_add_test(tc_command_handler, test_get_command_handler_ls);
    tcase_add_test(tc_command_handler, test_get_command_handler_cd);
    tcase_add_test(tc_command_handler, test_get_command_handler_pwd);
    tcase_add_test(tc_command_handler, test_get_command_handler_mkdir);
    tcase_add_test(tc_command_handler, test_get_command_handler_rm);
    tcase_add_test(tc_command_handler, test_get_command_handler_clear);
    tcase_add_test(tc_command_handler, test_get_command_handler_pcsearch);
    tcase_add_test(tc_command_handler, test_get_command_handler_exit);
    tcase_add_test(tc_command_handler, test_get_command_handler_unknown);
    tcase_add_test(tc_command_handler, test_get_command_handler_null);
    tcase_add_test(tc_command_handler, test_get_command_handler_empty_string);
    suite_add_tcase(s, tc_command_handler);

    /* mkdir tests */
    tc_mkdir = tcase_create("Mkdir");
    tcase_add_checked_fixture(tc_mkdir, setup, teardown);
    tcase_add_test(tc_mkdir, test_mkdir_creates_directory);
    tcase_add_test(tc_mkdir, test_mkdir_with_null_args);
    suite_add_tcase(s, tc_mkdir);

    /* rm tests */
    tc_rm = tcase_create("Rm");
    tcase_add_checked_fixture(tc_rm, setup, teardown);
    tcase_add_test(tc_rm, test_rm_deletes_file);
    tcase_add_test(tc_rm, test_rm_with_null_args);
    suite_add_tcase(s, tc_rm);

    /* cd tests */
    tc_cd = tcase_create("Cd");
    tcase_add_checked_fixture(tc_cd, setup, teardown);
    tcase_add_test(tc_cd, test_cd_changes_directory);
    tcase_add_test(tc_cd, test_cd_with_null_args);
    tcase_add_test(tc_cd, test_cd_with_invalid_path);
    suite_add_tcase(s, tc_cd);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = functions_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
