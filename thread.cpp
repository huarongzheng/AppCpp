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
#endif


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
