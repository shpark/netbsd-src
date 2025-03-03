/*	$NetBSD: run-authkeys.c,v 1.1.1.6.8.1 2018/04/11 02:58:46 msaitoh Exp $	*/

/* AUTOGENERATED FILE. DO NOT EDIT. */

//=======Test Runner Used To Run Each Test Below=====
#define RUN_TEST(TestFunc, TestLineNum) \
{ \
  Unity.CurrentTestName = #TestFunc; \
  Unity.CurrentTestLineNumber = TestLineNum; \
  Unity.NumberOfTests++; \
  if (TEST_PROTECT()) \
  { \
      setUp(); \
      TestFunc(); \
  } \
  if (TEST_PROTECT() && !TEST_IS_IGNORED) \
  { \
    tearDown(); \
  } \
  UnityConcludeTest(); \
}

//=======Automagically Detected Files To Include=====
#include "unity.h"
#include <setjmp.h>
#include <stdio.h>
#include "config.h"
#include "ntp.h"
#include "ntp_stdlib.h"
#include "ntp_calendar.h"
#include <limits.h>

//=======External Functions This Runner Calls=====
extern void setUp(void);
extern void tearDown(void);
extern void test_AddTrustedKeys(void);
extern void test_AddUntrustedKey(void);
extern void test_HaveKeyCorrect(void);
extern void test_HaveKeyIncorrect(void);
extern void test_AddWithAuthUseKey(void);
extern void test_EmptyKey(void);
extern void test_auth_log2(void);
extern void test_AddrMatch_anull(void);
extern void test_AddrMatch_self4(void);
extern void test_AddrMatch_self6(void);
extern void test_AddrMatch_afmix(void);
extern void test_AddrMatch_ipv4(void);
extern void test_AddrMatch_ipv6(void);


//=======Suite Setup=====
static void suite_setup(void)
{
extern int change_logfile(const char*, int);
change_logfile("stderr", 0);
}

//=======Test Reset Option=====
void resetTest(void);
void resetTest(void)
{
  tearDown();
  setUp();
}

char const *progname;


//=======MAIN=====
int main(int argc, char *argv[])
{
  progname = argv[0];
  suite_setup();
  UnityBegin("authkeys.c");
  RUN_TEST(test_AddTrustedKeys, 79);
  RUN_TEST(test_AddUntrustedKey, 92);
  RUN_TEST(test_HaveKeyCorrect, 102);
  RUN_TEST(test_HaveKeyIncorrect, 113);
  RUN_TEST(test_AddWithAuthUseKey, 122);
  RUN_TEST(test_EmptyKey, 131);
  RUN_TEST(test_auth_log2, 160);
  RUN_TEST(test_AddrMatch_anull, 203);
  RUN_TEST(test_AddrMatch_self4, 234);
  RUN_TEST(test_AddrMatch_self6, 245);
  RUN_TEST(test_AddrMatch_afmix, 256);
  RUN_TEST(test_AddrMatch_ipv4, 268);
  RUN_TEST(test_AddrMatch_ipv6, 298);

  return (UnityEnd());
}
