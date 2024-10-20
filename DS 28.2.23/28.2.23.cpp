#include <stdio.h>
#include <string.h>

struct dob{
	int tgl, bln, thn;
	
};

struct orang{
	
	char nama [20];
	char alamat [20];
};

struct mahasiswa{
	char NIM[12];
	float nilai;
	struct orang ORG;
	struct dob birth;
	
	
};

int main(){
	struct mahasiswa MHS;
	strcpy(MHS.NIM, "251000000000");
	strcpy(MHS.ORG.nama, "Glorp");
	MHS.birth.tgl = 12;
	MHS.birth.bln = 01;
	MHS.birth.thn = 98;
	
	printf("Nama: %s\n", MHS.ORG.nama);
	printf("NIM: %s\n",MHS.NIM);
	printf("Date Of Birth: %d/%d/%d\n",MHS.birth.tgl,MHS.birth.bln,MHS.birth.thn);
	
	
	 return 0;
}
