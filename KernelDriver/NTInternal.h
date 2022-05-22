#pragma once
#include <ntifs.h>

typedef struct _CM_CALLBACK_BLOCK {
    LIST_ENTRY CallbackListEntry;
    LIST_ENTRY PreCallListHead;
    PVOID Unknown1;
    PEX_CALLBACK_FUNCTION Function;
    UNICODE_STRING Altitude;
    LIST_ENTRY ObjectContextListHead;
}CM_CALLBACK_BLOCK, * PCM_CALLBACK_BLOCK;