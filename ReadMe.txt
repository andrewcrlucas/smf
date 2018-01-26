
Thread0 is a periodic thread using osDelay()

Thread1 and Thread2 simulate a producer / consumer relationship using two
  semaphores

Thread3 and Threaad4 simulate the protection of a resource using a mutex when
  more than one thread wants to use it

Thread5, Thread6 and Thread7 simulate a thread that needs two other threads to
  complete an operation before progressings.  The communication mechanism used
  is via EventFlags.

  