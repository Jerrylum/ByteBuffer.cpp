#include "../UnitTest1/ByteBuffer.h"

int main() {
    ByteBuffer me = ByteBuffer::allocate(20);

    //char* backed = new char[20]();
    //ByteBuffer me = ByteBuffer::wrap(20, backed, 4, 16);

    me.position(2);
    me.put((char)1);
    me.put((char)2);
    me.put((char)3);
    me.put((char)4);
    me.position(2);
    me.compact();
    //me.put(123);
    //me.put(const_cast<char*>("hello world"), 11);

    /*std::cout << "\npos:" << me.position() << ", lim:" << me.limit() << "\n";

    me.flip();

    std::cout << "\npos:" << me.position() << ", lim:" << me.limit() << "\n";*/

    for (int i = 0; i < me.capacity(); ++i)
        std::cout << std::hex << (int)me[i] << " ";

    me.~ByteBuffer();
}
