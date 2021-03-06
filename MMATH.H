/*******************************************************************
������⥪� �������⭮� ��䬥⨪� MMATH v. 1.12 (12 ������ 1996 �.)
(�) �� "���" (�. ���쪮�)
  ���� MMATH.H
*************************************************************************/

#ifndef __MMATH_H32VC
#define __MMATH_H32VC
#include "mdef.h"

#define m_len(X) ((int)X[0])
        // ����� X � ������

#define m_ifzero(X) ((X)[0]==1 && (X)[1] == 0)
        // X==0 ?

#define m_odd(X) ((X)[1] % 2 == 1)
        // X - ���⭮� ?
#define m_msb(X) (X[(int)X[0]])
        // �����頥� ���訩 ���� �᫠ X

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------*/
// ��䬥��᪨� ����樨
void m_add ( M_LONG x, M_LONG y, M_LONG z );
// z := x + y

int m_cmp ( M_LONG x, M_LONG y );
// �����頥� -1, �᫨ X < Y
// �����頥� 0, �᫨  X ==Y
// �����頥� 1, �᫨  X > Y

void m_div ( M_LONG x, M_LONG y, M_LONG z, M_LONG m );
// ������� x �� y
// z - ��⭮�
// m - ���⮪

void m_div1 ( M_LONG x, DIGIT y, M_LONG z, DIGIT *m );
// ������� x �� y, �᫨ ����� y = 1
// z - ��⭮�
// m - ���⮪

void m_egcd ( M_LONG x, M_LONG y, M_LONG gcd, M_LONG a );
// gcd:= ��� ( x, y )
// �᫨ gcd == 1, � a:=(1/x) mod y

int m_inv ( M_LONG x, M_LONG m, M_LONG y );
// y := x^-1 ( mod m )
// (���᫥��� ���⭮�� ������� � ����)
// �����頥��� ���祭��:
//      0 - �᫨ ����� ������� �������
//    1 - �᫨ �� �������

DIGIT m_inv1 ( DIGIT x );
// ���᫥��� x^-1 ( mod 2^32 )

void m_mul ( M_LONG x, M_LONG y, M_LONG z );
// z := x * y
// !!! &z != &x, &z != &y  ( �.�. z �� ����� ࠧ������� ��
//              ������ ����� � x ��� y )

#define m_mulmod(x,y,m,z) \
        { \
        DIGIT tmpVarm1[M_MAXSIZE*2+2]; \
        M_LONG tmpVarm2; \
        m_mul ( x, y, tmpVarm1 ); \
        m_div ( tmpVarm1, m, tmpVarm2, z ); }
// z := x * y % m

#define m_sqrmod(x,m,z) \
        { \
        DIGIT tmpVarm1[M_MAXSIZE*2+2]; \
        M_LONG tmpVarm2; \
        m_sqr ( x, tmpVarm1 ); \
        m_div ( tmpVarm1, m, tmpVarm2, z ); }
// z := x * x % m

#define m_mod(x,y,m) \
        { \
        M_LONG tmpVarm2; \
        m_div ( x,y,tmpVarm2,m); }
// m := x % y

void m_blockpowmod (M_LONG x, M_LONG y,
                        M_LONG m,
                        M_LONG z           );

void m_blockmontpowmod (M_LONG x, M_LONG y,
                        M_LONG m,
                        M_LONG z           );
// ���������� � �⥯��� ����� ��⮤�� �� ���⣮���

void m_blockmontpowmod2 (M_LONG x, M_LONG y,
                       M_LONG a, M_LONG b,
                       M_LONG m,
                       M_LONG z           );

void m_sqr ( M_LONG x, M_LONG y );
// y = x^2
// !!! &x != &y

void m_sub ( M_LONG x, M_LONG y, M_LONG z );
// z := x - y

void m_copy ( M_LONG y, M_LONG x );
// y := x

/*---------------------------------------------------------------*/
 void m_error ( int code );

int m_bitcount ( M_LONG x );
// �����頥� ���� ����� x � ����

int m_firstbit ( M_LONG x );
// �����頥� ����� ���襣� ��� � ���襬 ����� x

int m_getbit ( M_LONG x, int k );
// �����頥� k-� ��� �᫠ x

void m_setbit ( M_LONG x, int k );
// ��⠭�������� k-� ��� �᫠ x � 1

void m_shl ( M_LONG x, char nbits );
// x <<= nbits(nbits<32)

void m_shr ( M_LONG x, char nbits );
// x >>= nbits(nbits<32)

void m_normalize ( M_LONG x );
// �������� �㫥�, ����� � ��砫� x

void m_rand ( M_LONG x, int len );
// �������� ��砩��� �᫮ ������ len

void m_zero ( M_LONG x, int len );
// ��⠭�������� ����� x � len � �������� ��� ��ﬨ

char* m2str ( char* s, M_LONG x );
// �८�ࠧ������ �᫠ � ��ப� ( �� �᭮����� 16 )

void str2m ( M_LONG x, char* s );
// �८�ࠧ������ ��ப� ( �� �᭮����� 16 ) � �᫮

#ifdef __cplusplus
}
#endif

#endif

