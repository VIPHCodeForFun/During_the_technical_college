# General comments

Your code style is a mirror of your mind! Use comments where necessary, take
care for clean indentation. If your program does not compile then it receives
zero points.

Try to use the concepts and mechanisms we learned in the lecture when
appropriate. For instance, use javadoc comments, proper visibility for fields,
package definitions, and so on without being explicitly mentioned in the
assignments.

## Assignment A: Concurrent ring buffer queue

Implement a class `ConcurrentRingBuffer` that implements the interface
`ConcurrentFifoQueue`. The ring buffer contains a fixed size array of Object
objects. Typically, you also have a read-index that points to the array element
that is read next by `pop()` and a write-index that points to the array element
written next by `push()`. See https://en.wikipedia.org/wiki/Circular_buffer for
details on how a ring buffer works. Take care that

* you read the javadoc of the interface specification of `ConcurrentFifoQueue`
  and
* that appropriate synchronizations methods are applied, such that the ring
  buffer can be used in a concurrent use case.

Of course, you are supposed to implement a solution by yourself and not employ
an existing library class for circular buffers or synchronized buffers.

## Assignment B: Consumer and Producer

Implement a class `ConsumerProducerDemo` that is a multithreaded demonstration
of the `ConcurrentRingBuffer` with two producer threads and one consumer thread:

* The class contains a `ConcurrentRingBuffer` of capacity 6.
* A producer thread inserts every 500 ms an object, like an integer or the
  thread ID, into the ring buffer and prints a message about this on the
  console.
* A consumer thread reads every 500 ms an object from the ring buffer and
  prints a message about this on the console.

You should observe that initially the three threads concurrently `push()` and
`pop()` elements, but when the queue gets full a producer can only `push()` after
the consumer executed `pop()`.

The demo should wait for a key press, after which it clears the ring buffer,
and again both producer threads can `push()` elements concurrently until the
queue becomes full.

A sample run could look like this (the numbers in [] is the thread ID):

```console
% java ConsumerProducerDemo    |
Press any key to clear         |
[14] consumed 1                |
[12] produced 0                | -- two producers insert
[13] produced 1                |
[14] consumed 0                |
[13] produced 1                |
[12] produced 0                |
[14] consumed 0                |
[13] produced 1                |
[12] produced 0                |
[14] consumed 1                |
[13] produced 1                |
[12] produced 0                |
[14] consumed 1                |
[13] produced 1                |
[12] produced 0                |
[14] consumed 0                |
[13] produced 1                | -- queue becomes full
[14] consumed 1                |
[13] produced 1                |
[14] consumed 0                |
[12] produced 0                |
[14] consumed 1                |
[13] produced 1                |
[14] consumed 0                |
[12] produced 0                |
[14] consumed 1                |
[12] produced 0                | -- key pressed
                               |
Press any key to stop          |
[13] produced 1                |
[14] consumed 1                |
[12] produced 0                | -- again two producers can insert
[13] produced 1                |
[14] consumed 0                |
[12] produced 0                |
[13] produced 1                |
[14] consumed 1                |
[12] produced 0                |
[13] produced 1                |
[14] consumed 0                |
[12] produced 0                |
[13] produced 1                |
[14] consumed 1                |
[12] produced 0                |
[14] consumed 0                |
[13] produced 1                |
[14] consumed 1                |
[12] produced 0                |
                               |
Terminate consumer 14          |
Terminate producer 13          |
Terminate producer 12          |
Shutdown                       |
```

You have to:

* Implement a class Producer and a class Consumer that both implement the
  `Runnable` interface.
* Insert the TODOs in `ConsumerProducerDemo.java` and take care for the exception
  handling.

In case that you did/could not finish assignment A then you may use the code in
`ConcurrentRingBuffer.backup.java` instead. That file implements a solution using
the Java-API library classes.
