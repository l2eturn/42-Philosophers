#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0; // ตัวแปรร่วมที่ทุก thread สามารถเข้าถึงได้
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; // Mutex

// ฟังก์ชันที่จะรันใน thread
void* incrementCounter(void* arg) {
    // ใช้ mutex ในการ lock การเข้าถึงตัวแปรร่วม
    pthread_mutex_lock(&lock);
    counter += 1; // เพิ่มค่า counter
    printf("Counter value: %d\n", counter);
    pthread_mutex_unlock(&lock); // ปลดล็อค mutex

    return NULL;
}

int main() {
    pthread_t threads[5];

    // สร้างหลาย ๆ thread
    for(int i = 0; i < 5; i++) {
        if(pthread_create(&threads[i], NULL, incrementCounter, NULL)) {
            fprintf(stderr, "Error creating thread\n");
            return 1;	
        }
    }

    // รอให้ทุก ๆ thread ทำงานเสร็จ
    for(int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&lock); // ทำลาย mutex เมื่อใช้งานเสร็จแล้ว

    return 0;
}
