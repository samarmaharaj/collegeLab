#include <iostream>
#include <windows.h>
#include <process.h> // For _beginthread

using namespace std;

HANDLE rw_mutex;   // Controls access to shared data
CRITICAL_SECTION mutex;  // Protects reader_count
int reader_count = 0;
int shared_data = 0;

unsigned __stdcall reader(void* arg) {
    int id = *((int*)arg);
    while (true) {
        EnterCriticalSection(&mutex);
        reader_count++;
        if (reader_count == 1)
            WaitForSingleObject(rw_mutex, INFINITE); // First reader locks writers
        LeaveCriticalSection(&mutex);

        cout << "Reader " << id << " is reading: " << shared_data << endl;
        Sleep(1000); // Sleep for 1 second

        EnterCriticalSection(&mutex);
        reader_count--;
        if (reader_count == 0)
            ReleaseSemaphore(rw_mutex, 1, NULL); // Last reader unlocks writers
        LeaveCriticalSection(&mutex);
        
        Sleep(rand() % 3000 + 1000); // Sleep for 1 to 3 seconds
    }
    return 0;
}

unsigned __stdcall writer(void* arg) {
    int id = *((int*)arg);
    while (true) {
        WaitForSingleObject(rw_mutex, INFINITE);
        shared_data += 10;
        cout << "Writer " << id << " wrote: " << shared_data << endl;
        Sleep(2000); // Sleep for 2 seconds
        ReleaseSemaphore(rw_mutex, 1, NULL);

        Sleep(rand() % 5000 + 2000); // Sleep for 2 to 5 seconds
    }
    return 0;
}

int main() {
    HANDLE readers[5], writers[2];
    int ids[5] = {1, 2, 3, 4, 5};

    rw_mutex = CreateSemaphore(NULL, 1, 1, NULL);
    InitializeCriticalSection(&mutex);

    for (int i = 0; i < 5; i++)
        readers[i] = (HANDLE)_beginthreadex(NULL, 0, reader, &ids[i], 0, NULL);

    for (int i = 0; i < 2; i++)
        writers[i] = (HANDLE)_beginthreadex(NULL, 0, writer, &ids[i], 0, NULL);

    WaitForMultipleObjects(5, readers, TRUE, INFINITE);
    WaitForMultipleObjects(2, writers, TRUE, INFINITE);

    for (int i = 0; i < 5; i++)
        CloseHandle(readers[i]);
    
    for (int i = 0; i < 2; i++)
        CloseHandle(writers[i]);

    CloseHandle(rw_mutex);
    DeleteCriticalSection(&mutex);

    return 0;
}