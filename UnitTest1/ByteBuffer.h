#pragma once

#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

#define BYTEBUFFER_H

class ByteBuffer {
private:
    int _mark = -1;
    size_t _position = 0;
    size_t _limit;
    size_t _capacity;

    char* hb;
    int offset = 0;
    bool released = true;

    ByteBuffer(int mark, int pos, int lim, int cap, char* hb, int offset);
    ByteBuffer(int cap, int lim);
    ByteBuffer(int bufsize, char* buf, int off, int len);

    int nextGetIndex();
    int nextGetIndex(int nb);
    int nextPutIndex();
    int nextPutIndex(int nb);
    int checkIndex(int i);
    int checkIndex(int i, int nb);

    int markValue();
    void discardMark();

    int ix(int i);

    static void checkBounds(int off, int len, int size);

public:
    static ByteBuffer allocate(size_t capacity);
    static ByteBuffer wrap(size_t arrsize, char* array);
    static ByteBuffer wrap(size_t arrsize, char* array, size_t offset, size_t length);

    ~ByteBuffer();
    ByteBuffer(const ByteBuffer& that);

    char* array();
    int arrayOffset();

    ByteBuffer& compact();
    size_t capacity();
    int compareTo(ByteBuffer& that);
    // this method does not actually erase the data in the buffer
    ByteBuffer& clear();
    // no duplicate();
    ByteBuffer& flip();
    bool equals(ByteBuffer& that);
    template <class T> T get();
    template <class T> T get(size_t idx);
    char get();
    char get(size_t idx);
    ByteBuffer& get(char* dst, size_t offset, size_t length);
    ByteBuffer& get(char* dst, size_t length);
    std::string getNTBS(int maxSize = 1024);
    bool hasRemaining();
    // no order()
    template <class T> ByteBuffer& put(T value);
    template <class T> ByteBuffer& put(size_t index, T value);
    ByteBuffer& put(char value);
    ByteBuffer& put(ByteBuffer& src);
    ByteBuffer& put(size_t index, char value);
    ByteBuffer& put(char* src, size_t length);
    ByteBuffer& put(char* src, size_t offset, size_t length);
    ByteBuffer& putNTBS(const char* str);
    ByteBuffer& putNTBS(std::string str);

    size_t limit();
    ByteBuffer& limit(size_t newLimit);
    ByteBuffer& mark();
    char* output();  // new, create a new char array with the bytes from position
                     // to limit - 1
    size_t position();
    ByteBuffer& position(size_t newPosition);
    size_t remaining();
    ByteBuffer& reset();
    ByteBuffer& rewind();
    // no slice()

    char& operator[](size_t idx);  // new, same as .array()[idx]
    bool operator==(const ByteBuffer& rhs);
};


template<class T>
ByteBuffer& ByteBuffer::put(T value)
{
    char* bytes = static_cast<char*>(static_cast<void*>(&value));

    return put(bytes, sizeof(T));
}

template<class T>
inline ByteBuffer& ByteBuffer::put(size_t index, T value)
{
    char* bytes = static_cast<char*>(static_cast<void*>(&value));
    size_t length = sizeof(T);

    /*for (size_t i = 0; i < sizeof(T); i++)
        put(index + i, bytes[i]);*/
    memcpy(&hb[ix(checkIndex(index))], bytes, length);
    nextPutIndex(length);

    return *this;
}

template<class T>
inline T ByteBuffer::get()
{
    size_t length = sizeof(T);

    checkIndex(position(), length);

    char* buf = new char[sizeof(T)];
    for (int i = 0; i < sizeof(T); i++)
        buf[i] = get();
    T ans;
    memcpy(&ans, buf, sizeof(T));
    delete[] buf;

    return ans;
}

template<class T>
inline T ByteBuffer::get(size_t idx)
{
    size_t length = sizeof(T);

    checkIndex(idx, length);

    char* buf = new char[sizeof(T)];
    for (int i = 0; i < sizeof(T); i++)
        buf[i] = get(idx + i);
    T ans;
    memcpy(&ans, buf, sizeof(T));
    delete[] buf;

    return ans;
}