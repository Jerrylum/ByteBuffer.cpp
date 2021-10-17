#include "CppUnitTest.h"
#include "ByteBuffer.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace std;

//#define SPEEDTEST

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        static long ic(int i) {
            int j = i % 54;
            return j + 'a' + ((j > 26) ? 128 : 0);
        }

#ifdef SPEEDTEST
        static void ck(ByteBuffer& b, bool cond) { }

        static void ck(ByteBuffer& b, size_t got, size_t expected) { }

        static void ck(ByteBuffer& b, long got, long expected) { }

        static void ck(ByteBuffer& b, float got, float expected) { }

        static void ck(ByteBuffer& b, double got, double expected) { }
#else
        static void ck(ByteBuffer& b, bool cond) {
            Assert::IsTrue(cond, L"Condition failed");
        }

        static void ck(ByteBuffer& b, size_t got, size_t expected) {
            Assert::AreEqual(expected, got);
        }

        static void ck(ByteBuffer& b, long got, long expected) {
            Assert::AreEqual(expected, got);
        }

        static void ck(ByteBuffer& b, float got, float expected) {
            Assert::AreEqual(expected, got);
        }

        static void ck(ByteBuffer& b, double got, double expected) {
            Assert::AreEqual(expected, got);
        }
#endif // SPEEDTEST


        static void relGet(ByteBuffer& b) {
            int n = b.capacity();
            for (int i = 0; i < n; i++)
                ck(b, (long)b.get(), (long)((char)ic(i)));
            b.rewind();
        }

        static void relGet(ByteBuffer& b, int start) {
            int n = b.remaining();
            for (int i = start; i < n; i++)
                ck(b, (long)b.get(), (long)((char)ic(i)));
            b.rewind();
        }

        static void absGet(ByteBuffer& b) {
            int n = b.capacity();
            for (int i = 0; i < n; i++)
                ck(b, (long)b.get(), (long)((char)ic(i)));
            b.rewind();
        }

        static void bulkGet(ByteBuffer& b) {
            int n = b.capacity();
            char* a = new char[n + 7]();
            b.get(a, 7, n);
            for (int i = 0; i < n; i++)
                ck(b, (long)a[i + 7], (long)((char)ic(i)));
            delete[] a;
        }

        static void relPut(ByteBuffer& b) {
            int n = b.capacity();
            b.clear();
            for (int i = 0; i < n; i++)
                b.put((char)ic(i));
            b.flip();
        }

        static void absPut(ByteBuffer& b) {
            int n = b.capacity();
            b.clear();
            for (int i = 0; i < n; i++)
                b.put(i, (char)ic(i));
            b.limit(n);
            b.position(0);
        }

        static void bulkPutArray(ByteBuffer& b) {
            int n = b.capacity();
            b.clear();
            char* a = new char[n + 7]();
            for (int i = 0; i < n; i++)
                a[i + 7] = (char)ic(i);
            b.put(a, 7, n);
            b.flip();
            delete[] a;
        }

        static void bulkPutBuffer(ByteBuffer& b) {
            int n = b.capacity();
            b.clear();
            ByteBuffer c = ByteBuffer::allocate(n + 7);
            c.position(7);
            for (int i = 0; i < n; i++)
                c.put((char)ic(i));
            c.flip();
            c.position(7);
            b.put(c);
            b.flip();
        }

        static void testHet(int level, ByteBuffer& b) {

            int p = b.position();
            b.limit(b.capacity());
            //show(level, b);
            std::cout << ("    put:");

            b.put((char)1);
            b.put(std::numeric_limits<char>::max());
            std::cout << (" char");

            b.put((short)1);
            b.put(std::numeric_limits<short>::max());
            std::cout << (" short");

            b.put(1);
            b.put(std::numeric_limits<int>::max());
            std::cout << (" int");

            b.put((long)1);
            b.put(std::numeric_limits<long>::max());
            std::cout << (" long");

            b.put((float)1);
            b.put(std::numeric_limits<float>::min());
            b.put(std::numeric_limits<float>::max());
            std::cout << (" float");

            b.put((double)1);
            b.put(std::numeric_limits<double>::min());
            b.put(std::numeric_limits<double>::max());
            std::cout << (" double");

            std::cout << "\n";
            b.limit(b.position());
            b.position(p);
            // show(level, b);
            std::cout << ("    get:");

            ck(b, (long)b.get<char>(), 1);
            ck(b, (long)b.get<char>(), std::numeric_limits<char>::max());
            std::cout << (" char");

            ck(b, (long)b.get<short>(), 1);
            ck(b, (long)b.get<short>(), std::numeric_limits<short>::max());
            std::cout << (" short");

            ck(b, (long)b.get<int>(), (long)1);
            ck(b, (long)b.get<int>(), (long)std::numeric_limits<int>::max());
            std::cout << (" int");

            ck(b, b.get<long>(), 1);
            ck(b, b.get<long>(), std::numeric_limits<long>::max());
            std::cout << (" long");

            ck(b, b.get<float>(), 1);
            ck(b, b.get<float>(), std::numeric_limits<float>::min());
            ck(b, b.get<float>(), std::numeric_limits<float>::max());
            std::cout << (" float");

            ck(b, b.get<double>(), 1);
            ck(b, b.get<double>(), std::numeric_limits<double>::min());
            ck(b, b.get<double>(), std::numeric_limits<double>::max());
            std::cout << (" double");

            std::cout << "\n";

        }

        static void testHetAbs(int level, ByteBuffer& b) {

            b.limit(b.capacity());
            //show(level, b);
            std::cout << ("    put:");

            b.put(10, (char)1);
            b.put(20, std::numeric_limits<char>::max());
            std::cout << (" char");

            b.put(30, (short)1);
            b.put(40, std::numeric_limits<short>::max());
            std::cout << (" short");

            b.put(50, 1);
            b.put(60, std::numeric_limits<int>::max());
            std::cout << (" int");

            b.put(70, (long)1);
            b.put(80, std::numeric_limits<long>::max());
            std::cout << (" long");

            b.put(90, (float)1);
            b.put(100, std::numeric_limits<float>::min());
            b.put(110, std::numeric_limits<float>::max());
            std::cout << (" float");

            b.put(120, (double)1);
            b.put(130, std::numeric_limits<double>::min());
            b.put(140, std::numeric_limits<double>::max());
            std::cout << (" double");

            std::cout << "\n";
            b.limit(148);

            // show(level, b);
            std::cout << ("    get:");

            ck(b, (long)b.get<char>(10), 1);
            ck(b, (long)b.get<char>(20), std::numeric_limits<char>::max());
            std::cout << (" char");

            ck(b, (long)b.get<short>(30), 1);
            ck(b, (long)b.get<short>(40), std::numeric_limits<short>::max());
            std::cout << (" short");

            ck(b, (long)b.get<int>(50), (long)1);
            ck(b, (long)b.get<int>(60), (long)std::numeric_limits<int>::max());
            std::cout << (" int");

            ck(b, b.get<long>(70), 1);
            ck(b, b.get<long>(80), std::numeric_limits<long>::max());
            std::cout << (" long");

            ck(b, b.get<float>(90), 1);
            ck(b, b.get<float>(100), std::numeric_limits<float>::min());
            ck(b, b.get<float>(110), std::numeric_limits<float>::max());
            std::cout << (" float");

            ck(b, b.get<double>(120), 1);
            ck(b, b.get<double>(130), std::numeric_limits<double>::min());
            ck(b, b.get<double>(140), std::numeric_limits<double>::max());
            std::cout << (" double");

            std::cout << "\n";

        }

        static void test(int level, ByteBuffer& b) {
            //show(level, b);

            relPut(b);
            relGet(b);
            absGet(b);
            bulkGet(b);

            absPut(b);
            relGet(b);
            absGet(b);
            bulkGet(b);

            bulkPutArray(b);
            relGet(b);

            bulkPutBuffer(b);
            relGet(b);

            // Compact

            relPut(b);
            b.position(13);
            b.compact();
            b.flip();
            relGet(b, 13);

            // Exceptions

            relPut(b);
            b.limit(b.capacity() / 2);
            b.position(b.limit());


            Assert::ExpectException<std::out_of_range>([&]() {
                b.get<short>();
                });

            Assert::ExpectException<std::overflow_error>([&]() {
                b.put((char)42);
                });

            // The index must be non-negative and lesss than the buffer's limit.
            Assert::ExpectException<std::out_of_range>([&]() {
                b.get<short>(b.limit());
                });
            Assert::ExpectException<std::out_of_range>([&]() {
                b.get<short>(-1);
                });

            Assert::ExpectException<std::out_of_range>([&]() {
                b.put(b.limit(), (char)42);
                });

            Assert::ExpectException<std::invalid_argument>([&]() {
                b.position(0);
                b.mark();
                b.compact();
                b.reset();
                });


            // Values

            b.clear();
            b.put((char)0);
            b.put((char)-1);
            b.put((char)1);
            b.put(255);
            b.put(0);



            b.flip();
            Assert::AreEqual(b.get(), (char)0);
            Assert::AreEqual(b.get(), (char)-1);
            Assert::AreEqual(b.get(), (char)1);
            Assert::AreEqual(b.get(), (char)255);
            Assert::AreEqual(b.get(), (char)0);

            // Comparison
            b.rewind();
            ByteBuffer b2 = ByteBuffer::allocate(b.capacity());
            b2.put(b);
            b2.flip();
            b.position(2);
            b2.position(2);
            if (!b.equals(b2)) {
                for (int i = 2; i < b.limit(); i++) {
                    char x = b.get(i);
                    char y = b2.get(i);
                    if (x != y)
                        std::cout << "[" << i << "] " << x << " != " << y << "\n";
                }
                Assert::Fail(L"Identical buffers not equal");
            }
            if (b.compareTo(b2) != 0)
                Assert::Fail(L"Comparison to identical buffer != 0");

            b.limit(b.limit() + 1);
            b.position(b.limit() - 1);
            b.put((char)99);
            b.rewind();
            b2.rewind();
            if (b.equals(b2))
                Assert::Fail(L"Non-identical buffers equal");
            if (b.compareTo(b2) <= 0)
                Assert::Fail(L"Comparison to shorter buffer <= 0");
            b.limit(b.limit() - 1);

            b.put(2, (char)42);
            if (b.equals(b2))
                Assert::Fail(L"Non-identical buffers equal");
            if (b.compareTo(b2) <= 0)
                Assert::Fail(L"Comparison to lesser buffer <= 0");

            // Check equals and compareTo with interesting values
            char VALUES[5] = { std::numeric_limits<char>::min(), (char)-1, (char)0, (char)1, std::numeric_limits<char>::max() };

            for (char x : VALUES)
            {
                char* xa = new char[1]();
                xa[0] = x;
                ByteBuffer xb = ByteBuffer::wrap(1, xa);
                if (xb.compareTo(xb) != 0)
                {
                    Assert::Fail(L"compareTo not reflexive");
                }
                if (!xb.equals(xb))
                {
                    Assert::Fail(L"equals not reflexive");
                }
                for (char y : VALUES)
                {
                    char* ya = new char[1]();
                    ya[0] = y;
                    ByteBuffer yb = ByteBuffer::wrap(1, ya);
                    if (xb.compareTo(yb) != -yb.compareTo(xb))
                    {
                        Assert::Fail(L"compareTo not anti-symmetric");
                    }
                    if ((xb.compareTo(yb) == 0) != xb.equals(yb))
                    {
                        Assert::Fail(L"compareTo inconsistent with equals");
                    }
                    if (xb.compareTo(yb) != (x - y))
                    {
                        Assert::Fail(L"Incorrect results for ByteBuffer.compareTo");
                    }
                    if (xb.equals(yb) != ((x == y) || ((x != x) && (y != y)))) {
                        Assert::Fail(L"Incorrect results for ByteBuffer.equals");
                    }
                    delete[] ya;
                }
                delete[] xa;
            }

            // Heterogeneous accessors

            //b.order(ByteOrder.BIG_ENDIAN);
            for (int i = 0; i <= 9; i++) {
                b.position(i);
                testHet(level + 1, b);
            }
            //b.order(ByteOrder.LITTLE_ENDIAN);
            b.position(3);
            testHet(level + 1, b);

            testHetAbs(level + 1, b);
        }

        TEST_METHOD(testViaAllocate)
        {
            test(0, ByteBuffer::allocate(7 * 1024));
        }

        TEST_METHOD(testViaWrap)
        {
            char* buf = new char[7 * 1024]();
            test(0, ByteBuffer::wrap(7 * 1024, buf, 0, 7 * 1024));
            delete[] buf;
        }

        TEST_METHOD(testArray)
        {
            char* ba = new char[1024]();

            int offset = 47;
            int length = 900;
            ByteBuffer b = ByteBuffer::wrap(1024, ba, offset, length);
            //show(0, b);
            ck(b, b.capacity(), 1024);
            ck(b, b.position(), offset);
            ck(b, b.limit(), offset + length);

            // The offset must be non-negative and no larger than <array.length>.
            Assert::ExpectException<std::invalid_argument>([=]() { ByteBuffer::wrap(1024, ba, -1, 1024); });

            Assert::ExpectException<std::invalid_argument>([=]() { ByteBuffer::wrap(1024, ba, 1024 + 1, 1024); });

            Assert::ExpectException<std::invalid_argument>([=]() { ByteBuffer::wrap(1024, ba, 0, -1); });

            Assert::ExpectException<std::invalid_argument>([=]() { ByteBuffer::wrap(1024, ba, 0, 1024 + 1); });

            Assert::ExpectException<std::invalid_argument>([=]() { ByteBuffer::wrap(1024, nullptr, 0, 5); });

            Assert::ExpectException<std::invalid_argument>([=]() { ByteBuffer::wrap(1024, (char*)nullptr); });
        }

        TEST_METHOD(testCustom)
        {
            ByteBuffer b = ByteBuffer::allocate(7 * 1024);
            relPut(b);

            ByteBuffer c = b;

            Assert::IsTrue(b == c);
            Assert::IsTrue(b.equals(c));
            Assert::AreEqual(b.position(), c.position());
            Assert::AreEqual(b.limit(), c.limit());
            Assert::AreEqual(b.capacity(), c.capacity());
            Assert::AreEqual(b.arrayOffset(), c.arrayOffset());
            Assert::AreEqual(b.hasRemaining(), c.hasRemaining());

            relGet(c);

            Assert::AreEqual(c[0], c.array()[0]);
            c[0] = 3;
            Assert::AreEqual(c[0], c.array()[0]);
            Assert::AreNotEqual(c[0], b.array()[0]);
            Assert::AreNotEqual(c[0], b[0]);

            ByteBuffer d = ByteBuffer::wrap(b.capacity(), b.position(0).output());
            Assert::IsTrue(b == d);
            delete[] d.array();

            std::string earth = "earth";

            b.clear();
            b.putNTBS("hello ").putNTBS(earth);
            b.rewind();

            Assert::AreEqual(std::string("hello "), b.getNTBS());
            Assert::AreEqual(earth, b.getNTBS());
        }
    };
}
