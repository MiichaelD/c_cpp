#include <iostream> 
#include <inttypes.h> // PRIXPTR

/* 
	Memory alignment:	https://en.wikipedia.org/wiki/Data_structure_alignment
						https://www.youtube.com/watch?v=OKjOZBaKlOc

	
	Data stored in memory must be "aligned" according to the length of the data.

	Byte Data:		Can go to any address.

	Half Word Data:	Must be "halfword alligned", addresses must be even numbers (divisible by 2)
					Ending in Hex: 0, 2, 4, 6, 8, A, C, E. Binary: 0

	Word Data:		Must be "word aligned", addesses must be divisible by 4
					Ending in Hex: 0, 4, 8 or C. Binary: 00

	Doubleword Data:Must be "double word aligned", addresses must be divisible by 8
					Ending in Hex: 0 or 8. Binary: 000

	Paragraph Data:	Aligns to 16 bytes. Ending in Hex: 0. Binary: 0000

	Page Data:		Aligns to 256 bytes. Ending in Hex: 00. Binary: 0000 0000
	

	This program aligns required memory to the specified alignment size

	That is if a program needs allocations to be aligned in 16 byte shunks, the 
	total amount of memory allocated should be multiple of 16. if the requested memory
	is not multiple of 16, the requested memory will be increased to the next multiple.

	To allocate 6 bytes and aligning to 8 bytes:
	 ___ ___
   0|___|___|
	|___|___|
	|___|___|
	|___|___|
	|___|___| < other memory ends here
	|___|___| < new one should start here if not aligned, right?
	|___|___|
	|___|___|15
	 ___ ___
 >16|___|___| but aligned memory should start at 16 
	|___|___|
	|___|___|
	|___|___|
	|___|___|
	|___|___|
	|___|___|
	|___|___|31
	
*/
using namespace std;

inline size_t mem_alignment(size_t bytes) {
    const size_t x = sizeof(void *) - 1;
    size_t result = (bytes + x) & ~x;
	cout << "mem_aligning: " << std::dec << bytes << " + "<< x << " & 0x" << std::hex << ~x << ", = " << std::dec << result;

	void *mem = malloc(result);
	cout << ". Allocated in: 0x" << std::hex << (uintptr_t)mem << endl;
	free(mem);

    return result;
}

void mem_alignment1(size_t bytes, size_t alignment){
	--alignment; // 16byte alignment - 1. 
	cout << "mem_aligning: "<< std::dec << bytes << " + " << alignment << " & 0x"<< std::hex << ~alignment << " = " ;
    size_t result = (bytes + alignment) & ~alignment;
    // void *mem = malloc(bytes + alignment); // original
    void *mem = malloc(result);// why bytes+alignment when you can ask for the exact size?, am I missunserstanding this?
    cout << std::dec << result << ", Allocated in 0x" << std::hex << (uintptr_t)mem;
    void *ptr = reinterpret_cast<void*>(((uintptr_t)mem + alignment) & ~(uintptr_t)alignment);
    cout << ", Aligned @ 0x" << std::hex <<(uintptr_t)ptr << endl;
    free(mem);
}

// void mem_alignment1_original(size_t bytes, size_t alignment){
// 	--alignment; // 16byte alignment - 1. 
//     void *mem = malloc(bytes + alignment);
//     void *ptr = reinterpret_cast<void*>(((uintptr_t)mem + alignment) & ~(uintptr_t)alignment);
//     free(mem);
// }

void mem_alignment2(size_t bytes, size_t align){
	--align;
	uintptr_t mask = ~(uintptr_t)align;
    void *mem = malloc(bytes+align);
    void *ptr = (void *)(((uintptr_t)mem+align) & mask);
    printf("0x%08" PRIXPTR ", 0x%08" PRIXPTR "\n", (uintptr_t)mem, (uintptr_t)ptr);
    // printf("0x%10" PRIXPTR ", 0x%10" PRIXPTR "\n", (uintptr_t)mem, (uintptr_t)ptr);
    free(mem);
}

int main(){
	mem_alignment(6);
	mem_alignment(8);
	mem_alignment(12);
	mem_alignment(18);
	mem_alignment(1024);
	cout << endl << endl;


	mem_alignment1(1, 2);
	mem_alignment1(2, 2);
	mem_alignment1(3, 2);
	mem_alignment1(4, 2);
	cout << endl;
	mem_alignment1(8, 8);
	mem_alignment1(12, 8);
	mem_alignment1(18, 8);
	mem_alignment1(1024, 8);
	cout << endl;
	mem_alignment1(8, 16);
	mem_alignment1(12, 16);
	mem_alignment1(18, 16);
	mem_alignment1(1024, 16);
	cout << endl << endl;


	mem_alignment2(8, 16);
	mem_alignment2(12, 16);
	mem_alignment2(18, 16);
	mem_alignment2(1024, 16);
}