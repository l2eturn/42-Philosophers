#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// โครงสร้างที่จะเก็บข้อมูลสำหรับแต่ละ thread
typedef struct {
    int id;
    char* message;
} ThreadData;

// ฟังก์ชันที่จะรันใน thread
void* printMessage(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    printf("Thread ID: %d, Message: %s\n", data->id, data->message);
    return NULL;
}

int main() {
    pthread_t thread1, thread2;
    ThreadData data1 = {1, "Hello from 1"};
    ThreadData data2 = {2, "Hello from 2"};

    // สร้าง thread พร้อมส่งข้อมูล
    if(pthread_create(&thread1, NULL, printMessage, (void*)&data1)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }
    if(pthread_create(&thread2, NULL, printMessage, (void*)&data2)) {
        fprintf(stderr, "Error creating thread\n");
        return 1;
    }

    // รอให้ thread ทำงานเสร็จ
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
