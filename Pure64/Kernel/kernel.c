#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <idtLoader.h>
#include <stdint.h>
#include <speaker.h>
#include <time.h>
#include <SysCallDispatcher.h>
#include <interrupts.h>
#include <keyboard.h>
#include <time.h>


extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

static const uint64_t PageSize = 0x1000;

//Points to Userland's main function
static void * const sampleCodeModuleAddress = (void*)0x400000;
static void * const sampleDataModuleAddress = (void*)0x500000;

typedef int (*EntryPoint)();


void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * initializeKernelBinary()
{
	char buffer[10];

	print("[x64BareBones]");
	newLine();

	print("CPU Vendor:");
	print(cpuVendor(buffer));
	newLine();

	print("[Loading modules]");
	newLine();
	void * moduleAddresses[] = {
		sampleCodeModuleAddress,
		sampleDataModuleAddress
	};

	loadModules(&endOfKernelBinary, moduleAddresses);
	print("[Done]");
	newLine();
	newLine();

	print("[Initializing kernels binary]");
	newLine();

	clearBSS(&bss, &endOfKernel - &bss);

	print("  text: 0x");
	printHex((uint64_t)&text);
	newLine();
	print("  rodata: 0x");
	printHex((uint64_t)&rodata);
	newLine();
	print("  data: 0x");
	printHex((uint64_t)&data);
	newLine();
	print("  bss: 0x");
	printHex((uint64_t)&bss);

	newLine();
	print("[Done]");
	newLine();
	newLine();
	return getStackBase();
}

int main()
{
	//Guardo las posiciones del main de Userland tal que
	extern uint64_t * RestoreIP;
	RestoreIP = sampleCodeModuleAddress;
	extern void * RestoreSP;
	RestoreSP = (void*)(_getRSP() - 2*8);
	clearScreen();
	load_idt();
	((EntryPoint)sampleCodeModuleAddress)();
	while(1);
	return 0;
}
	/*

	newLine();

	//Syscall 1
	for (int x = 300; x < 300+350; x++)
		for (int y = 500; y < 500+100; y++)
		{
			SysCallDispatcher(1, x, y, GREEN_COLOR);
		}

	//Syscall 2
	int current_time[3];
	SysCallDispatcher(2, (uint64_t)current_time, (uint64_t)current_time+4, (uint64_t)current_time+8);
	printDec(current_time[0]);
	print(":");
	printDec(current_time[1]);
	print(":");
	printDec(current_time[2]);
	newLine();

	//Syscall 3
	char string[500];
	print("Tiene 3 segundos para escribir algo:");
	timer_wait(3);
	SysCallDispatcher(3, 0, (uint64_t)string, 0);
	printFormat(string, YELLOW_COLOR, BLACK_COLOR);

	//Syscall 4
	SysCallDispatcher(4, 2, 0, 0);
	SysCallDispatcher(4, 1, (uint64_t)"ERROR GRAVE!", 5);
	SysCallDispatcher(4, 0, (uint64_t)" Mentira! Era una prueba", 50);

	//Syscall 5
	SysCallDispatcher(5, 0, 0, 0);

	//Syscall 6
	SysCallDispatcher(6, 300, 500, 0);
	printFormat("Edite el cursor y ahora estoy por aqui!", BLACK_COLOR, GREEN_COLOR);
	newLine();
	print("Resultado de ejecutar el main de Userland:    ");
	printHex(((EntryPoint)sampleCodeModuleAddress)());

	//Syscall 8
	SysCallDispatcher(8, 0, (uint64_t)"ERROR GRAVE!", 15);
	SysCallDispatcher(8, 5, (uint64_t)"14:38:15", 15);
	while(1);
	return 0;
}*/
