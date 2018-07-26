#if 0
// example for thread::operator=
#include <iostream>       // std::cout
#include <thread>         // std::thread, std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

void pause_thread(int n)
{
  std::this_thread::sleep_for (std::chrono::seconds(n));
  std::cout << "pause of " << n << " seconds ended\n";
}

int main()
{
  std::thread threads[5];                         // default-constructed threads

  std::cout << std::thread::hardware_concurrency() << " hw concurrency\n" ;
  std::cout << "Spawning 5 threads...\n";
  for (int i=0; i<5; ++i)
    threads[i] = std::thread(pause_thread,i+1);   // move-assign threads

  std::cout << "Done spawning threads. Now waiting for them to join:\n";
  for (int i=0; i<5; ++i)
    threads[i].join();

  std::cout << "All threads joined!\n";

  return 0;
}


// timed_mutex::try_lock_for example
#include <iostream>       // std::cout
#include <chrono>         // std::chrono::milliseconds
#include <thread>         // std::thread
#include <mutex>          // std::timed_mutex

std::timed_mutex mtx;

void fireworks (int i) {
  // waiting to get a lock: each thread prints "-" every 200ms:
  while (!mtx.try_lock_for(std::chrono::milliseconds(200))) {
    std::cout  << i;
  }
  // got a lock! - wait for 1s, then this thread prints "*"
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::cout<< i << "*\n" ;
  mtx.unlock();
}

int main ()
{
  std::thread threads[10];
  // spawn 10 threads:
  for (int i=0; i<10; ++i)
    threads[i] = std::thread(fireworks, i);

  for (auto& th : threads) th.join();

  return 0;
}

#include <memory>
#include <iostream>

using namespace std;

int main()
{
    struct Son
    {
        int age;
    };
    struct Father
    {
        Son son;
    };

    shared_ptr<Father> father = make_shared<Father>();
    shared_ptr<Son> sona(father, &father->son);

    cout << father.use_count()  << endl;
    cout << sona.use_count()    << endl;
    father.reset();
    cout << father.use_count()  << endl;
    cout << sona.use_count()    << endl;
    sona.reset();
    cout << father.use_count()  << endl;
    cout << sona.use_count()    << endl;
}


#include <sys/mman.h>  
#include <sys/types.h>  
#include <sys/stat.h>  
#include <fcntl.h>  
#include <unistd.h>  
#include <stdio.h>  

int main(int argc, char** argv)  
{  
    int fd,i;  
    int pagesize,offset;  
    char *p_map;  
    struct stat sb;  

    /* ??page size */
    pagesize = sysconf(_SC_PAGESIZE);
    printf("pagesize is %d\n",pagesize);

    /* ???? */
    fd = open(argv[1], O_RDWR, 00777);
    fstat(fd, &sb);
    printf("file size is %zd\n", (size_t)sb.st_size);

    offset = 0;
    p_map = (char *)mmap(NULL, pagesize * 2, PROT_READ|PROT_WRITE,
            MAP_SHARED, fd, offset);
    close(fd);

    printf("char %c\n", p_map[sb.st_size+20]);
    p_map[sb.st_size+1000] = '8';  /* ?????? */
    p_map[pagesize] = '9';    /* ????? */
    printf("string %s\n", p_map);

    munmap(p_map, pagesize * 2);

    return 0;
}  
#endif


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<vector>
#include<array>
#include<iostream>
#include<time.h>
#include<algorithm>

using namespace std;

typedef void (*FP)(int);

struct SumClass
{
    inline void operator()(int t)
    {
        static long long sum = 0;
        sum += t;
    }
};

inline void sumUp(int t)
{
    static long long sum = 0;
    sum += t;
}

int main()
{
    int i;
    float f = -1.0;
    i = *(int *)&f;
    printf("val of i=%x\n", i);



#if 0
    vector<int> ary(10,2);
    //int ary[10];
    for (int i=0; i<20; ++i) {
        ary[i]=0;
    }



    const int SIZE_VECTOR = 10000000;
    vector<int> vInt;
    for (int i = 0; i < SIZE_VECTOR; ++i)
    {
        vInt.push_back(i);
    }
    auto sumObj = SumClass();

    long beginTime = clock();
    for (int i = 0; i < 100; ++i)
    {
        for_each(vInt.begin(), vInt.end(), sumUp);
        //for_each(vInt.begin(), vInt.end(), sumObj);
        //for_each(vInt.begin(), vInt.end(), [](int t){
        //    static long long sum = 0;
        //    sum += t;
        //});
    }
    long endTime = clock();
    cout<<"beginTime:"<<beginTime<<"  endTime:"<<endTime<<"  endTime-beginTime:"<<double(endTime-beginTime)/CLOCKS_PER_SEC<<endl;


    int fd;
    char c[3];
    char s[] = "I am child process\n";
    vector<int> bias_shape(false, 18);
    printf("%d\n", bias_shape[0]);

    fd = open("data.txt",O_RDWR,0);

    pid_t mypid = fork();
    if (mypid == 0)
    {
        fd = 1;//stdout  
        printf("%d\n", (unsigned int)(sizeof(s)));
        write(fd,s,sizeof(s));
        sleep(3);
        exit(0);
    }
    else
    {
        wait(NULL);
        read(fd,c,2);
        c[2]='\0';
        printf("c = %s\n",c);
        exit(0);
    }
    const char *s1  = "hellohwc";
    char s2[] = "hellohwc";
    char s3[100];
    char *s4=(char*)malloc(100);
    void *s5=(void*)malloc(100);
    cout << sizeof(s1) << endl; 
    cout << sizeof(s2) << endl;
    cout << sizeof(s3) << endl;
    cout << sizeof(s4) << endl;
    cout << sizeof(s5) << endl;
    cout << sizeof(char) << endl;
#endif
}
