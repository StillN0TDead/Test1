#include<iostream>
#include"String.h"
using namespace std;

String::String() : data(nullptr), size(0) {}

String::String(const char c) : data(nullptr), size(0)
{
    setFrom(&c, 1);
}

String::String(const char* s) : data(nullptr), size(0)
{
    if (s != nullptr)
        setFrom(s, cstrLen(s));
}

String::String(const String& obj) : data(nullptr), size(0)
{
    if (obj.data != nullptr)
        setFrom(obj.data, obj.getLength());
}

String& String::operator=(const String& obj)   // needed for safe copying
{
    if (this != &obj)
    {
        if (obj.data == nullptr)
        {
            delete[] data;
            data = nullptr;
            size = 0;
        }
        else
            setFrom(obj.data, obj.getLength());
    }
    return *this;
}

String::~String()
{
    delete[] data;
}

// Reads a line from console into this object
void String::input()
{
    int cap = 16, n = 0;
    char* buf = new char[cap];
    char c;
    while (std::cin.get(c) && c != '\n')
    {
        if (c == '\r') continue;
        if (n + 1 >= cap)
        {
            char* bigger = new char[cap * 2];
            for (int i = 0; i < n; i++) bigger[i] = buf[i];
            delete[] buf;
            buf = bigger;
            cap *= 2;
        }
        buf[n++] = c;
    }
    buf[n] = '\0';
    delete[] data;
    data = buf;
    size = cap;
    shrink();
}

// Make array size equal to the string's length (+1 for '\0')
void String::shrink()
{
    if (data == nullptr) return;
    int len = getLength();
    if (size == len + 1) return;
    setFrom(data, len);
}

char& String::at(const int index)
{
    static char dummy = '\0';
    if (index < 0 || index >= getLength())
    {
        std::cout << "String::at -> index out of range\n";
        dummy = '\0';
        return dummy;
    }
    return data[index];
}

const char& String::at(const int index) const
{
    static const char dummy = '\0';
    if (index < 0 || index >= getLength())
    {
        std::cout << "String::at -> index out of range\n";
        return dummy;
    }
    return data[index];
}

bool String::isEmpty() const
{
    return data == nullptr || data[0] == '\0';
}

int String::getLength() const { return cstrLen(data); }
int String::getSize() const { return size; }

void String::display() const
{
    if (data != nullptr) std::cout << data;
}

// First occurrence of substr starting at 'start'; -1 if not found
int String::find(const String& substr, const int start) const
{
    int len = getLength(), sl = substr.getLength();
    if (start < 0 || start > len) return -1;
    for (int i = start; i + sl <= len; i++)
        if (matchesAt(i, substr)) return i;
    return -1;
}

// Insert substr at given index
void String::insert(const int index, const String& substr)
{
    int len = getLength(), sl = substr.getLength();
    if (index < 0 || index > len || sl == 0) return;
    char* nd = new char[len + sl + 1];
    int j = 0;
    for (int i = 0; i < index; i++) nd[j++] = data[i];
    for (int i = 0; i < sl; i++) nd[j++] = substr.data[i];
    for (int i = index; i < len; i++) nd[j++] = data[i];
    nd[j] = '\0';
    delete[] data;
    data = nd;
    size = len + sl + 1;
}

// Remove 'count' characters starting at index
void String::remove(const int index, const int count)
{
    int len = getLength();
    if (index < 0 || index >= len || count <= 0) return;
    int c = count;
    if (index + c > len) c = len - index;
    for (int i = index; i + c <= len; i++)   // also moves '\0'
        data[i] = data[i + c];
    shrink();
}

// Replace all occurrences of old with newSubStr; returns count
int String::replace(const String& old, const String& newSubStr)
{
    int len = getLength(), ol = old.getLength(), nl = newSubStr.getLength();
    if (ol == 0) return 0;

    int count = 0;
    int pos = find(old, 0);
    while (pos != -1)
    {
        count++;
        pos = find(old, pos + ol);
    }
    if (count == 0) return 0;

    int total = len + count * (nl - ol);
    char* nd = new char[total + 1];
    int i = 0, j = 0;
    while (i < len)
    {
        if (i + ol <= len && matchesAt(i, old))
        {
            for (int k = 0; k < nl; k++) nd[j++] = newSubStr.data[k];
            i += ol;
        }
        else
            nd[j++] = data[i++];
    }
    nd[j] = '\0';
    delete[] data;
    data = nd;
    size = total + 1;
    return count;
}

void String::trimLeft()
{
    int k = 0, len = getLength();
    while (k < len && isWhite(data[k])) k++;
    if (k > 0) remove(0, k);
}

void String::trimRight()
{
    int len = getLength();
    while (len > 0 && isWhite(data[len - 1])) len--;
    if (data != nullptr && len != getLength())
        setFrom(data, len);
}

void String::trim()
{
    trimLeft();
    trimRight();
}

void String::makeUpper()
{
    for (int i = 0; i < getLength(); i++)
        if (data[i] >= 'a' && data[i] <= 'z') data[i] = data[i] - 'a' + 'A';
}

void String::makeLower()
{
    for (int i = 0; i < getLength(); i++)
        if (data[i] >= 'A' && data[i] <= 'Z') data[i] = data[i] - 'A' + 'a';
}

void String::reverse()
{
    int len = getLength();
    for (int i = 0; i < len / 2; i++)
    {
        char t = data[i];
        data[i] = data[len - 1 - i];
        data[len - 1 - i] = t;
    }
}

// Change the array to newSize bytes (truncating if needed)
void String::reSize(int newSize)
{
    if (newSize <= 0)
    {
        delete[] data;
        data = nullptr;
        size = 0;
        return;
    }
    char* nd = new char[newSize];
    int len = getLength();
    int i = 0;
    for (; i < len && i < newSize - 1; i++) nd[i] = data[i];
    nd[i] = '\0';
    delete[] data;
    data = nd;
    size = newSize;
}

// Behaves like strcmp: <0, 0, >0
int String::compare(const String& s2) const
{
    const char* a = (data != nullptr) ? data : "";
    const char* b = (s2.data != nullptr) ? s2.data : "";
    int i = 0;
    while (a[i] != '\0' && a[i] == b[i]) i++;
    return (int)(unsigned char)a[i] - (int)(unsigned char)b[i];
}

// First 'count' characters as a new String
String String::left(const int count) const
{
    int len = getLength();
    int c = count;
    if (c > len) c = len;
    if (c < 0) c = 0;
    String r;
    r.setFrom(data, c);
    return r;
}

// Last 'count' characters as a new String
String String::right(const int count) const
{
    int len = getLength();
    int c = count;
    if (c > len) c = len;
    if (c < 0) c = 0;
    String r;
    r.setFrom(data + (len - c), c);
    return r;
}

long long int String::convertToInteger() const
{
    int i = 0, len = getLength();
    while (i < len && isWhite(data[i])) i++;
    bool neg = false;
    if (i < len && (data[i] == '-' || data[i] == '+'))
    {
        neg = (data[i] == '-');
        i++;
    }
    long long int v = 0;
    while (i < len && data[i] >= '0' && data[i] <= '9')
    {
        v = v * 10 + (data[i] - '0');
        i++;
    }
    return neg ? -v : v;
}

// ----- page 2 -----
float String::convertToFloat() const
{
    int i = 0, len = getLength();
    while (i < len && isWhite(data[i])) i++;
    bool neg = false;
    if (i < len && (data[i] == '-' || data[i] == '+'))
    {
        neg = (data[i] == '-');
        i++;
    }
    double v = 0;
    while (i < len && data[i] >= '0' && data[i] <= '9')
    {
        v = v * 10 + (data[i] - '0');
        i++;
    }
    if (i < len && data[i] == '.')
    {
        i++;
        double scale = 0.1;
        while (i < len && data[i] >= '0' && data[i] <= '9')
        {
            v += (data[i] - '0') * scale;
            scale /= 10;
            i++;
        }
    }
    return (float)(neg ? -v : v);
}

// Returns a new String = this + s2 (this is not changed)
String String::concatenate(const String& s2) const
{
    int l1 = getLength(), l2 = s2.getLength();
    String r;
    char* nd = new char[l1 + l2 + 1];
    for (int i = 0; i < l1; i++) nd[i] = data[i];
    for (int i = 0; i < l2; i++) nd[l1 + i] = s2.data[i];
    nd[l1 + l2] = '\0';
    r.data = nd;
    r.size = l1 + l2 + 1;
    return r;
}

// Appends s2 to this object
void String::concatEqual(const String& s2)
{
    String r = concatenate(s2);   // safe even if s2 is *this
    *this = r;
}

// Stores the number as a string
void String::setNumber(const long long int num)
{
    unsigned long long u = (num < 0) ? (0ULL - (unsigned long long)num)
        : (unsigned long long)num;
    char tmp[24];
    int n = 0;
    if (u == 0) tmp[n++] = '0';
    while (u > 0)
    {
        tmp[n++] = (char)('0' + (int)(u % 10));
        u /= 10;
    }
    if (num < 0) tmp[n++] = '-';
    char out[24];
    for (int i = 0; i < n; i++) out[i] = tmp[n - 1 - i];
    setFrom(out, n);
}