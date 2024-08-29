#include <stdio.h>
#include <Windows.h>

#define DESIRED_ADDRESS (PVOID)0x00'00'00'20'00'00'00'00

int main()
{
	SetConsoleTitleW(L"FixedCodeApplication");

	printf("ProcessId: %d, Pointer: %p, Size: %d\n",
		GetCurrentProcessId(),
		DESIRED_ADDRESS,
		sizeof(DWORD));

	PDWORD pValue = (PDWORD)VirtualAlloc(
		DESIRED_ADDRESS,
		sizeof(DWORD),
		MEM_COMMIT | MEM_RESERVE,
		PAGE_READWRITE);
	if (pValue == NULL) {
		printf("ERROR, can't allocated desired address %p\n", DESIRED_ADDRESS);
		exit(1);
	}
	*pValue = 515;

	while (TRUE) {
		printf("[%p]: *pValue: %d\n", pValue, *pValue);
		//Sleep(1000);
		getchar();
		(*pValue)--;
	}

	/*
	DWORD value = 616;
	while (TRUE) {
		printf("[%p]: value: %d\n", &value, value);
		getchar();
		value--;
	}
	*/

	/*
	PDWORD pValue = (PDWORD)malloc(sizeof(DWORD));
	*pValue = 717;

	while (TRUE) {
		printf("[%p]: *pValue: %d\n", pValue, *pValue);
		getchar();
		(*pValue)--;
	}
	*/

	return EXIT_SUCCESS;
}