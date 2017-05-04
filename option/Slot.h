#pragma once

typedef int Key;
typedef char * Value;

typedef struct _slot
{
	Key key;
	Value val;
} CSlot;