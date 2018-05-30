#ifndef __StrUtil_h__
#define __StrUtil_h__

#include <vector>
#include <string>
#include <deque>

using namespace std;

class StrUtil
{
  public:
    static string trim(const string &str);
    static string trim_crlf(const string &str);
    static string trim_blanks(const string &str);
    static string trim_undesirable(const string &s, const string &undesirable);

  public:
    static int string2int(const string &str);
    static string int2string(int i);
    static long string2long(const string &str);
    static string long2string(long i);

    static float string2float(const string &str);
    static string float2string(float f, int r = 2); // �Ҽ��� ���ڸ����� ǥ��

  public:
    static int findIgnoreCase(const string &str, const string &x);
    static bool equalsIgnoreCase(const string &str1, const string &str2);

  public:
    static string toupper(const string &str);
    static string tolower(const string &str);

  public:
    static void split(const string &str, vector<string> &tokens,
                      const string &delim = " ", int num = 0);

    static vector<string> split(const string &str,
                                const string &delim, int num = 0);

    static void split_deque(const string &str, deque<string> &tokens,
                      const string &delim = " ", int num = 0);

    static deque<string> split_deque(const string &str,
                                const string &delim, int num = 0);

  public:
    // str�ӿ� �ִ� ��� x�� y�� ��ü�ϱ�
    static string replace(const string &str, const string &x, const string &y);

    // str�ӿ� �ִ� ù��° x�� y�� ��ü�ϱ�
    static string replaceFirst(const string &str, const string &x, const string &y);

  public:
    static string join(const string &glue, vector<string> &tokens);
    static string join_deque(const string &glue, deque<string> &tokens);

  public:
    static bool endsWith(const string &str, const string &x); 
    static bool endsWithIgnoreCase(const string &str, const string &x); 

    static bool beginsWith(const string &str, const string &x); 
    static bool beginsWithIgnoreCase(const string &str, const string &x); 

    static bool startsWith(const string &str, const string &x);
    static bool startsWithIgnoreCase(const string &str, const string &x); 

//
// public:
//   static bool equalsIgnoreCase(const string &s1, const string &s2);
//

  public:
    // 2003/08/27 "*, ?" ������ MS-DOS ���� ��Ī Wildcard ��Ī �Լ�
    static bool simpleMatch(const string &string, const string &pattern);

  public:
    // --------------------------------------------------------------------
    // 2004/05/04 strstr()�� �����ѵ�, ��ҹ��ڸ� �������� �ʴ� �Լ��� �ʿ���.
    //            strstrIgnoreCase()
    // --------------------------------------------------------------------
    static
     char *strstrIgnoreCase(const char *str, int m, const char *pattern, int n);
    static
     char *strstrIgnoreCase(const char *str, const char *pattern);

  public:
    // 2004-05-19
    // �� ��Ʈ���� ���Ͽ�, �տ��� ��ġ�ϴ� �ִ� ������ prefix �Ǵ�
    //                       �ڿ��� ��ġ�ϴ� �ִ� ������ postfix ���ϱ�
    static string equalPrefix(const string &s1, const string &s2);
    static string equalPostfix(const string &s1, const string &s2);

  public:
    // non-printable character�� ���� ���ڷ� �ٲٴ� �ڵ�
    static string ca2sp(const string &str);
};

#endif // __StrUtil_h__


