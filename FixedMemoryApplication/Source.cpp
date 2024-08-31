#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <iomanip>

#define DESIRED_ADDRESS (PVOID)0x00'00'00'20'00'00'00'00

template <typename T>
void PerformOutput(T value)
{
	T* pValue = (T*)VirtualAlloc(
		DESIRED_ADDRESS,
		sizeof(T),
		MEM_COMMIT | MEM_RESERVE,
		PAGE_READWRITE);
	if (pValue == NULL) {
		throw std::runtime_error("Can't allocated desired address");
	}
	*pValue = value;

	while (TRUE) {
		std::cout << "[0x" << std::hex << pValue << "]: " << std::fixed << std::setprecision(2)
			<< *pValue << std::endl;
		std::cin.get();
		(*pValue)--;
	}
}

int main(int argc, CHAR* argv[])
{
	try {
		if (argc < 2) {
			throw std::runtime_error("Required command-line arguments are not specified");
		}

		SetConsoleTitleW(L"FixedMemoryApplication");

		printf("ProcessId Pointer, Size\n");
		printf("%d 0x%p %d\n",
			GetCurrentProcessId(),
			DESIRED_ADDRESS,
			sizeof(DWORD));
		puts("");

		if (strcmp(argv[1], "int32") == 0) {
			PerformOutput<INT32>(515);
		}
		else if (strcmp(argv[1], "int64") == 0) {
			PerformOutput<INT64>(616);
		}
		else if (strcmp(argv[1], "float") == 0) {
			PerformOutput<FLOAT>(3.66);
		}
		else if (strcmp(argv[1], "double") == 0) {
			PerformOutput<DOUBLE>(4.76);
		}
		else {
			throw std::runtime_error("Specified type is invalid");
		}
	}
	catch (std::exception& ex) {
		std::cout << ex.what() << std::endl;
	}

	return EXIT_SUCCESS;
}