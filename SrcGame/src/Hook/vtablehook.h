#ifndef VTABLEHOOK_H
#define VTABLEHOOK_H




















#include <stdint.h>

#ifdef WIN32
#include <Windows.h>
#elif __linux__
#include <unistd.h>
#include <sys/mman.h>
int vtablehook_pagesize = sysconf(_SC_PAGE_SIZE);
int vtablehook_pagemask = ~(vtablehook_pagesize-1);
#endif

int vtablehook_unprotect(void* region) {
#ifdef WIN32
        MEMORY_BASIC_INFORMATION mbi;
        VirtualQuery((LPCVOID)region, &mbi, sizeof(mbi));
        VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &mbi.Protect);
        return mbi.Protect;
#elif __linux__
        mprotect((void*) ((intptr_t)region & vtablehook_pagemask), vtablehook_pagesize, PROT_READ|PROT_WRITE|PROT_EXEC);
        return PROT_READ|PROT_EXEC;
#endif
}

void vtablehook_protect(void* region, int protection) {
#ifdef WIN32
        MEMORY_BASIC_INFORMATION mbi;
        VirtualQuery((LPCVOID)region, &mbi, sizeof(mbi));
        VirtualProtect(mbi.BaseAddress, mbi.RegionSize, protection, &mbi.Protect);
#elif __linux__
        mprotect((void*) ((intptr_t)region & vtablehook_pagemask), vtablehook_pagesize, protection);
#endif
}








void* vtablehook_hook(void* instance, void* hook, int offset) {
        intptr_t vtable = *((intptr_t*)instance);
        intptr_t entry = vtable + offset;
        intptr_t original = *((intptr_t*) entry);

        int original_protection = vtablehook_unprotect((void*)entry);
        *((intptr_t*)entry) = (intptr_t)hook;
        vtablehook_protect((void*)entry, original_protection);

        return (void*)original;
}

#endif 
