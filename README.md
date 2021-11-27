# A Knockoff  Version of ByteBuffer.java

The title is actually quite accurate, ngl.



## How to use

Copy files `ByteBuffer.h` and `ByteBuffer.cpp` in the `UnitTest1` folder.



## Examples

### Put & Get

```cpp
ByteBuffer b = ByteBuffer::allocate(20);

b.put(1234);
b.put((short)5678);
b.put(true);

b.flip().remaining(); // 4 + 2 + 1 = 7

int num1 = b.get<int>(); // 1234
short num2 = b.get<short>(); // 5678
bool bool1 = b.get<bool>(); // true
```



### Bulk Put & Bulk Get

```cpp
ByteBuffer b = ByteBuffer::allocate(20);

char buf[10] = { 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a };
b.put(&buf[0], 3, 6); // write: 0x34 to 0x39

b.flip();

char* dst = new char[5]();
b.get(dst, 2, 3); // finally: 0x00 0x00 0x34 0x35 0x36
delete[] dst;
```



### Array backing

```cpp
char* arr = new char[20]();
ByteBuffer b = ByteBuffer::wrap(20, arr);

arr[0] = true; // boolean is 1 byte size
b.put(1, (short)5678); // short is 2 bytes size

b.rewind();

b.get<bool>(); // true
b.get<short>(); // 5678
```



Learn what is ByteBuffer: [Java NIO Buffer Tutorial - HowToDoInJava](https://howtodoinjava.com/java/nio/java-nio-2-0-working-with-buffers/) (English ver.), [Java NIO — Buffer 的基本觀念與使用方式. 前言 | by Carl | Medium](https://medium.com/@clu1022/java-nio-buffer-c98b52fd93ca) (Chinese ver.).

Learn how ByteBuffer works: [JDK Source Code: ByteBuffer Test Case](http://hg.openjdk.java.net/jdk7/jdk7/jdk/file/9b8c96f96a0f/test/java/nio/Buffer/), [ByteBuffer Java Doc](https://docs.oracle.com/javase/7/docs/api/java/nio/ByteBuffer.html), [ByteBuffer.java Source Code on GitHub](https://github.com/himnay/java7-sourcecode/blob/master/java/nio/ByteBuffer.java).




## Things we don't have:

- `allocateDirect` and `isDirect` : we are already using cpp
- `duplicate`, `slice` and `asCharBuffer` : we might encounter pointer issues
- `asReadOnlyBuffer` and `isReadOnly` : they are unnecessary
- `order` (ah, maybe I will implement it later)



## New features:

### Deep Clone

```cpp
ByteBuffer b = ByteBuffer::allocate(20);
b.put(1234);

ByteBuffer c = b; // deep clone
c.put(5678);

b.position() != c.position(); // true
```



### Array Output

```cpp
ByteBuffer b = ByteBuffer::allocate(20);
b.put(1234);
b.put('e');

char* dst = b.flip().output();
int length = b.remaining(); // 5 bytes

dst[4] == 'e'; // true
    
delete[] dst;
```



### Subscript Operator

```cpp
ByteBuffer b = ByteBuffer::allocate(20);
b.put('e');
b[0] == 'e'; // true

b[1] = 'f';
b.get() == 'f'; // true
```



### String I/O

Also read: [Null-terminated byte strings - cppreference.com](https://en.cppreference.com/w/c/string/byte)

```cpp
std::string earth = "earth";

ByteBuffer b = ByteBuffer::allocate(20);
b.putNTBS("hello ");
b.putNTBS(earth);

b.array(); // 68 65 6c 6c 6f 20 00 65 61 72 74 68 00 XX XX XX XX XX XX XX

b.flip();
b.getNTBS(); // "hello "
b.getNTBS(); // "earth"
```
