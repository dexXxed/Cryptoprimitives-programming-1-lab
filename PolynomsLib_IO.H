#ifndef POLYNOMS_IO_PROCEDURES
#define POLYNOMS_IO_PROCEDURES
// ����� �������� � ��������� ����
void print_pol(M_LONG f);

/* ����� �������� � ��������� ����
	(�� ������� �������� � �������) */
void print_vect(M_LONG f);


// ����� �������� � ��������� ���� � ��������� ���� 
// ���� f_out ������ ������� (� ������ ������)
void fprint_pol(FILE *f_out,M_LONG f);

#endif