/*lint -e???? -save */
/* AUTOGENERATED FILE. DO NOT EDIT. */
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>
#include "unity.h"
#include "cmock.h"
#include "mock_nrf_802154_rsch_crit_sect.h"

typedef struct _CMOCK_nrf_802154_rsch_crit_sect_init_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  int CallOrder;

} CMOCK_nrf_802154_rsch_crit_sect_init_CALL_INSTANCE;

typedef struct _CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALL_INSTANCE
{
  UNITY_LINE_TYPE LineNumber;
  int CallOrder;
  rsch_prio_t Expected_prio;
  int IgnoreArg_prio;

} CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALL_INSTANCE;

static struct mock_nrf_802154_rsch_crit_sectInstance
{
  int nrf_802154_rsch_crit_sect_init_IgnoreBool;
  CMOCK_nrf_802154_rsch_crit_sect_init_CALLBACK nrf_802154_rsch_crit_sect_init_CallbackFunctionPointer;
  int nrf_802154_rsch_crit_sect_init_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE nrf_802154_rsch_crit_sect_init_CallInstance;
  int nrf_802154_rsch_crit_sect_prio_request_IgnoreBool;
  CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALLBACK nrf_802154_rsch_crit_sect_prio_request_CallbackFunctionPointer;
  int nrf_802154_rsch_crit_sect_prio_request_CallbackCalls;
  CMOCK_MEM_INDEX_TYPE nrf_802154_rsch_crit_sect_prio_request_CallInstance;
} Mock;

extern jmp_buf AbortFrame;
extern int GlobalExpectCount;
extern int GlobalVerifyOrder;

void mock_nrf_802154_rsch_crit_sect_Verify(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.nrf_802154_rsch_crit_sect_init_CallInstance, cmock_line, "Function 'nrf_802154_rsch_crit_sect_init' called less times than expected.");
  if (Mock.nrf_802154_rsch_crit_sect_init_CallbackFunctionPointer != NULL)
    Mock.nrf_802154_rsch_crit_sect_init_CallInstance = CMOCK_GUTS_NONE;
  UNITY_TEST_ASSERT(CMOCK_GUTS_NONE == Mock.nrf_802154_rsch_crit_sect_prio_request_CallInstance, cmock_line, "Function 'nrf_802154_rsch_crit_sect_prio_request' called less times than expected.");
  if (Mock.nrf_802154_rsch_crit_sect_prio_request_CallbackFunctionPointer != NULL)
    Mock.nrf_802154_rsch_crit_sect_prio_request_CallInstance = CMOCK_GUTS_NONE;
}

void mock_nrf_802154_rsch_crit_sect_Init(void)
{
  mock_nrf_802154_rsch_crit_sect_Destroy();
}

void mock_nrf_802154_rsch_crit_sect_Destroy(void)
{
  CMock_Guts_MemFreeAll();
  memset(&Mock, 0, sizeof(Mock));
  Mock.nrf_802154_rsch_crit_sect_init_CallbackFunctionPointer = NULL;
  Mock.nrf_802154_rsch_crit_sect_init_CallbackCalls = 0;
  Mock.nrf_802154_rsch_crit_sect_prio_request_CallbackFunctionPointer = NULL;
  Mock.nrf_802154_rsch_crit_sect_prio_request_CallbackCalls = 0;
  GlobalExpectCount = 0;
  GlobalVerifyOrder = 0;
}

void nrf_802154_rsch_crit_sect_init(void)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_nrf_802154_rsch_crit_sect_init_CALL_INSTANCE* cmock_call_instance = (CMOCK_nrf_802154_rsch_crit_sect_init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.nrf_802154_rsch_crit_sect_init_CallInstance);
  Mock.nrf_802154_rsch_crit_sect_init_CallInstance = CMock_Guts_MemNext(Mock.nrf_802154_rsch_crit_sect_init_CallInstance);
  if (Mock.nrf_802154_rsch_crit_sect_init_IgnoreBool)
  {
    return;
  }
  if (Mock.nrf_802154_rsch_crit_sect_init_CallbackFunctionPointer != NULL)
  {
    Mock.nrf_802154_rsch_crit_sect_init_CallbackFunctionPointer(Mock.nrf_802154_rsch_crit_sect_init_CallbackCalls++);
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "Function 'nrf_802154_rsch_crit_sect_init' called more times than expected.");
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, "Function 'nrf_802154_rsch_crit_sect_init' called earlier than expected.");
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, "Function 'nrf_802154_rsch_crit_sect_init' called later than expected.");
}

void nrf_802154_rsch_crit_sect_init_CMockIgnore(void)
{
  Mock.nrf_802154_rsch_crit_sect_init_IgnoreBool = (int)1;
}

void nrf_802154_rsch_crit_sect_init_CMockExpect(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_nrf_802154_rsch_crit_sect_init_CALL_INSTANCE));
  CMOCK_nrf_802154_rsch_crit_sect_init_CALL_INSTANCE* cmock_call_instance = (CMOCK_nrf_802154_rsch_crit_sect_init_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "CMock has run out of memory. Please allocate more.");
  Mock.nrf_802154_rsch_crit_sect_init_CallInstance = CMock_Guts_MemChain(Mock.nrf_802154_rsch_crit_sect_init_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
}

void nrf_802154_rsch_crit_sect_init_StubWithCallback(CMOCK_nrf_802154_rsch_crit_sect_init_CALLBACK Callback)
{
  Mock.nrf_802154_rsch_crit_sect_init_CallbackFunctionPointer = Callback;
}

void nrf_802154_rsch_crit_sect_prio_request(rsch_prio_t prio)
{
  UNITY_LINE_TYPE cmock_line = TEST_LINE_NUM;
  CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALL_INSTANCE* cmock_call_instance = (CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALL_INSTANCE*)CMock_Guts_GetAddressFor(Mock.nrf_802154_rsch_crit_sect_prio_request_CallInstance);
  Mock.nrf_802154_rsch_crit_sect_prio_request_CallInstance = CMock_Guts_MemNext(Mock.nrf_802154_rsch_crit_sect_prio_request_CallInstance);
  if (Mock.nrf_802154_rsch_crit_sect_prio_request_IgnoreBool)
  {
    return;
  }
  if (Mock.nrf_802154_rsch_crit_sect_prio_request_CallbackFunctionPointer != NULL)
  {
    Mock.nrf_802154_rsch_crit_sect_prio_request_CallbackFunctionPointer(prio, Mock.nrf_802154_rsch_crit_sect_prio_request_CallbackCalls++);
    return;
  }
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "Function 'nrf_802154_rsch_crit_sect_prio_request' called more times than expected.");
  cmock_line = cmock_call_instance->LineNumber;
  if (cmock_call_instance->CallOrder > ++GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, "Function 'nrf_802154_rsch_crit_sect_prio_request' called earlier than expected.");
  if (cmock_call_instance->CallOrder < GlobalVerifyOrder)
    UNITY_TEST_FAIL(cmock_line, "Function 'nrf_802154_rsch_crit_sect_prio_request' called later than expected.");
  if (!cmock_call_instance->IgnoreArg_prio)
  {
    UNITY_TEST_ASSERT_EQUAL_MEMORY((void*)(&cmock_call_instance->Expected_prio), (void*)(&prio), sizeof(rsch_prio_t), cmock_line, "Function 'nrf_802154_rsch_crit_sect_prio_request' called with unexpected value for argument 'prio'.");
  }
}

void CMockExpectParameters_nrf_802154_rsch_crit_sect_prio_request(CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALL_INSTANCE* cmock_call_instance, rsch_prio_t prio)
{
  memcpy(&cmock_call_instance->Expected_prio, &prio, sizeof(rsch_prio_t));
  cmock_call_instance->IgnoreArg_prio = 0;
}

void nrf_802154_rsch_crit_sect_prio_request_CMockIgnore(void)
{
  Mock.nrf_802154_rsch_crit_sect_prio_request_IgnoreBool = (int)1;
}

void nrf_802154_rsch_crit_sect_prio_request_CMockExpect(UNITY_LINE_TYPE cmock_line, rsch_prio_t prio)
{
  CMOCK_MEM_INDEX_TYPE cmock_guts_index = CMock_Guts_MemNew(sizeof(CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALL_INSTANCE));
  CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALL_INSTANCE* cmock_call_instance = (CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALL_INSTANCE*)CMock_Guts_GetAddressFor(cmock_guts_index);
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "CMock has run out of memory. Please allocate more.");
  Mock.nrf_802154_rsch_crit_sect_prio_request_CallInstance = CMock_Guts_MemChain(Mock.nrf_802154_rsch_crit_sect_prio_request_CallInstance, cmock_guts_index);
  cmock_call_instance->LineNumber = cmock_line;
  cmock_call_instance->CallOrder = ++GlobalExpectCount;
  CMockExpectParameters_nrf_802154_rsch_crit_sect_prio_request(cmock_call_instance, prio);
}

void nrf_802154_rsch_crit_sect_prio_request_StubWithCallback(CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALLBACK Callback)
{
  Mock.nrf_802154_rsch_crit_sect_prio_request_CallbackFunctionPointer = Callback;
}

void nrf_802154_rsch_crit_sect_prio_request_CMockIgnoreArg_prio(UNITY_LINE_TYPE cmock_line)
{
  CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALL_INSTANCE* cmock_call_instance = cmock_call_instance = (CMOCK_nrf_802154_rsch_crit_sect_prio_request_CALL_INSTANCE*)CMock_Guts_GetAddressFor(CMock_Guts_MemEndOfChain(Mock.nrf_802154_rsch_crit_sect_prio_request_CallInstance));
  UNITY_TEST_ASSERT_NOT_NULL(cmock_call_instance, cmock_line, "prio IgnoreArg called before Expect on 'nrf_802154_rsch_crit_sect_prio_request'.");
  cmock_call_instance->IgnoreArg_prio = 1;
}

/* lint -restore */
