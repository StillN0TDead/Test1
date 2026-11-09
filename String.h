#ifndef STRING_H
#define STRING_H
class String
{
    char* data;
    int size;

    // ---------- private helpers ----------
    static int cstrLen(const char* s)
    {
        int n = 0;
        if (s != nullptr)
            while (s[n] != '\0') n++;
        return n;
    }

    static bool isWhite(char c)
    {
        return c == ' ' || c == '\t' || c == '\n' || c == '\r';
    }

    // Replace contents with exactly 'len' characters copied from s
    void setFrom(const char* s, int len)
    {
        char* nd = new char[len + 1];
        for (int i = 0; i < len; i++) nd[i] = s[i];
        nd[len] = '\0';
        delete[] data;
        data = nd;
        size = len + 1;
    }

    bool matchesAt(int pos, const String& sub) const
    {
        int sl = sub.getLength();
        for (int k = 0; k < sl; k++)
            if (data[pos + k] != sub.data[k]) return false;
        return true;
    }

public:
    String();

    String(const char c);
    String(const char* s);

    String(const String& obj);

    String& operator=(const String& obj);

    ~String();

    void input();
    void shrink();
    char& at(const int index);
    const char& at(const int index) const;
    bool isEmpty() const;
    int getLength() const;
    int getSize() const;
    void display() const;
    int find(const String& substr, const int start = 0) const;
    void insert(const int index, const String& substr);
    void remove(const int index, const int count = 1);
    int replace(const String& old, const String& newSubStr);
    void trimLeft();
    void trimRight();
    void trim();
    void makeUpper();
    void makeLower();
    void reverse();
    void reSize(int newSize);
    int compare(const String& s2) const;
    String left(const int count) const;
    String right(const int count) const;
    long long int convertToInteger() const;
    float convertToFloat() const;
    String concatenate(const String& s2) const;
    void concatEqual(const String& s2);
    void setNumber(const long long int num);
};



#endif