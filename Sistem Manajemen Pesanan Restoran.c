//Proyek Akhir Semester
//Kelompok 16
//Efranandi Abi Rafdi		1806181975
//Stanley Darwin Chandra	1806233865
//Program Sistem Order Restoran

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <conio.h>

struct item{
	int kode;
	char nama[100];
	int harga;
	int kuantitas;
	int numCust;
	int done;
	int stock;
	struct item *next;
};

struct item *menu_start = NULL;
struct item *order_start = NULL;

int nomor_pegawai[2] = {1806181975, 1806233865};
int input_nomor_pegawai;

int mainMen_opt;
int pgwMen_opt;
int editMen_opt;
int editFood_opt;
int custMen_opt;

char item_nama_edit[100];
int  item_harga_edit;
int item_kode_edit;
int item_kuantitas_edit;
int item_done_edit;
int item_stock_edit;

char item_nama_trf[100];
int item_harga_trf;
int item_numCust_trf;
int item_kuantitas_trf;

int ganti;
int cust_count = 0;
int ordr_count = 0;
int ordering = 1;
int browsing = 1;
int sumHargaTotal=0;
int sumHarga = 0;

int i, j, k;

void mainMenu();
void pegawai();
void edit_menu();
void traverseMenu();
void insertFood(char item_nama_edit[100], int item_harga_edit, int item_kode_edit, int item_stock_edit);
void deleteFood(int item_kode_edit);
void editFood(int item_kode_search);
void customer();
void sortkecilMenu();
void sortbesarMenu();
void swap(struct item *d1, struct item *d2);
void input_pesanan();
void insertOrder(int item_kode_edit, int item_kuantitas_edit);
void traverseOrder();
void inputMainMenu();
void total_harga();
void daftarPsn();
void psnSelesai(int item_done_edit);
void login();
void totDijual();
void about();
void help();


int main(){
	mainMenu();
	return 0;
}

//Ditampilkan judul program dan main menu
void mainMenu(){
	system("cls");
	printf("%46sPROGRAM PESANAN RESTORAN\n", " ");
	printf("%52sVersi 1.1.0\n\n", " ");
	printf("%50s<< MAIN MENU >>\n\n", " ");
	printf("%47s --- MODE PROGRAM ---\n", " ");
	printf("%51s1. Pelanggan\n", " ");
	printf("%51s2. Pegawai\n", " ");
	printf("%51s3. Help\n", " ");
	printf("%51s4. About Us\n", " ");
	printf("%51s5. Exit\n", " ");
	inputMainMenu();			//Masuk ke fungsi input untuk main menu
}

void inputMainMenu(){
	printf("\n%51sPILIH MODE: ", " ");
	scanf("%d", &mainMen_opt);			//Input mode yang dipilih
	
	if(mainMen_opt == 1){
		//Ditampilkan menu pemesanan awalnya
		system("cls");
		customer();
	}else if(mainMen_opt == 2){
		//Ditampilkan menu login sebelum ke menu pegawai
		login();
	}else if(mainMen_opt == 3){
		//Ditampilkan menu help
		help();
		printf("\n\nTekan ENTER untuk lanjut");
		getch();
		mainMenu();
	}else if(mainMen_opt == 4){
		//Ditampilkan menu informasi pembuat program
		about();
		printf("\n\nTekan ENTER untuk lanjut");
		getch();
		mainMenu();
	}else if(mainMen_opt == 5){
		exit(0);
	}else{
		//Pesan error input yang diberikan salah
		printf("\n%48sERROR: INVALID INPUT\n\n", " ");
		printf("Tekan ENTER untuk lanjut");
		getch()	;
		mainMenu();
	}
}

void customer(){
	//Cek apakah daftar menu kosong
	if(menu_start == NULL){
		printf("%47s--- DAFTAR MENU KOSONG ---\n", " ");
		printf("\nTekan ENTER untuk lanjut");
		getch();
		mainMenu();
	}
	//Ditampilkan daftar menu
	traverseMenu();
	
	browsing = 1;
	//Looping untuk input di menu pelanggan
	while(browsing == 1){
		printf("\n\n%44s --- PENGATURAN DAFTAR MENU ---\n\n", " ");
		printf("%48s1. Urutkan dari termurah\n", " ");
		printf("%48s2. Urutkan dari termahal\n", " ");
		printf("%48s3. Input pesanan\n", " ");
		printf("%48s4. BACK\n", " ");
		printf("\n%51sMASUKAN PILIHAN: ", " ");
		scanf("%d", &custMen_opt);
		
		if(custMen_opt == 1){
			system("cls");
			sortkecilMenu();			//Daftar menu diurutkan dari harga terendah
			traverseMenu();
		}else if(custMen_opt == 2){
			system("cls");
			sortbesarMenu();			//Daftar menu diurutkan dari harga tertinggi
			traverseMenu();
		}else if(custMen_opt == 3){
			cust_count++;	
			printf("\n%51s- PELANGGAN %d -\n", " ", cust_count);
			printf("\n%25sMasukan nomor makanan yang ingin dipesan sesuai pada daftar menu\n", " ");
			ordering = 1;			//Set kondisi ke memesan
			input_pesanan();		//Menu input pesanan
			sumHargaTotal+=sumHarga;
		}else if(custMen_opt == 4){
			mainMenu();
			cust_count--;
		}
	}
}

//sort linkedlist menu dari harga terkecil
void sortkecilMenu(){
	struct item *ptr;
	struct item temp;
	struct item *lptr = NULL;
	do {
		ganti = 0;
		ptr = menu_start;
		while(ptr->next != lptr){					//Mengakses linked list
			if(ptr->harga > ptr->next->harga){		//Jika harganya lebih besar ditukar
				swap(ptr, ptr->next);
				ganti = 1;
			}
			ptr = ptr->next;
		}
		lptr = ptr;
	}
	while(ganti == 1);
}

//sort linkedlist menu dari harga terbesar
void sortbesarMenu(){
	struct item *ptr;
	struct item temp;
	struct item *lptr = NULL;
	do {
		ganti = 0;
		ptr = menu_start;
		while(ptr->next != lptr){					//Mengakses linked list
			if(ptr->harga < ptr->next->harga){		//Jika harganya lebih besar ditukar
				swap(ptr, ptr->next);
				ganti = 1;
			}
			ptr = ptr->next;
		}
		lptr = ptr;
	}
	while(ganti == 1);
}

//Fungsi menukar isi linked list
void swap(struct item *d1, struct item *d2){
	struct item temp = *d1;
	d1->kode = d2->kode;
	strcpy(d1->nama, d2->nama);
	d1->harga = d2->harga;
	d1->stock = d2->stock;
	d2->kode = temp.kode;
	strcpy(d2->nama, temp.nama);
	d2->harga =  temp.harga;
	d2->stock = temp.stock;
	
}

void input_pesanan(){
	//looping input pesanan selagi user ingin tambah
	printf("%44sInput -1 untuk selesai memesan\n", " ");
	while(ordering == 1){
		printf("\n%52sPESANAN: ", " ");		//Input kode makanan
		scanf("%d", &item_kode_edit);
		if(item_kode_edit == -1){
			traverseOrder();
			total_harga();
			ordering = 0;
			continue;
		}
		printf("%52sKUANTITAS: ", " ");		//Input kuantitas makanan
		scanf("%d", &item_kuantitas_edit);
		if(item_kuantitas_edit == -1){
			traverseOrder();
			total_harga();
			ordering = 0;
			continue;
		}
		
		insertOrder(item_kode_edit, item_kuantitas_edit);		//Dimasukan ke linked list pesanan
		
		printf("\n%49s--- DAFTAR PESANAN ---\n\n", " ");
		printf("%32s|%10sNama Makanan%10s| Kuantitas | Harga @item |\n", " ", " ", " ");
		printf("%32s------------------------------------------------------------", " ");
		traverseOrder();			//Display daftar pesanan
		total_harga();
		
		printf("\n\n%46sTAMBAH PESANAN? (1. YA / 0. TIDAK) ", " ");
		printf("\n%46sINPUT: ", " ");
		scanf("%d", &ordering);		//Opsi tambah pesanan
	}
	sumHargaTotal+=sumHarga;
	mainMenu();
}

//Fungsi insert pesanan ke linked list
void insertOrder(int item_kode_edit, int item_kuantitas_edit){
	struct item *currentMen;
	struct item *currentOrdr;
	struct item *link = (struct item*)malloc(sizeof(struct item));
	
	//Jika menu kosong
	if(menu_start == NULL){
		printf("%47s--- DAFTAR MENU KOSONG ---\n", " ");
		return;
	}
	
	currentMen = menu_start;			//Mulai dari linked list menu awal
	while(currentMen->kode != item_kode_edit){
		if(currentMen->next == NULL){
			printf("\n%48sERROR: INVALID INPUT\n\n", " ");		//Makanan tidak ditemukan
			input_pesanan();
		}else{
			currentMen = currentMen->next;
		}
	}
	//Posisi linked list ditemukan
	
	if(item_kuantitas_edit > currentMen->stock){
		printf("\n%44sERROR: MELAMPAUI STOCK YANG TERSEDIA\n", " ");
		input_pesanan();
	}
	
	//Mengisi struct baru
	link->numCust = cust_count;
	strcpy(link->nama, currentMen->nama);
	link->harga = currentMen->harga;
	link->kuantitas = item_kuantitas_edit;
	link->done = 0;
	currentMen->stock -= item_kuantitas_edit;
	
	if(order_start == NULL){
		order_start = link;
		order_start->next = NULL;
		return;
	}
	
	currentOrdr = order_start;
	while(currentOrdr->next != NULL){
		currentOrdr = currentOrdr->next;
	}
	//Ke posisi akhir
	
	//Menghubungkan ke linked list
	currentOrdr->next = link;		
	link->next = NULL;
}

void traverseOrder(){
	struct item *current;
	current = order_start;
	
	//Ke posisi pesanan setiap pelanggan
	while(current->numCust != cust_count){
		current = current->next;
	}
	
	//Pesanan kosong
	if(current == NULL){
		printf("%46s--- DAFTAR PESANAN KOSONG ---", " ");
		return;
	}
	
	//Display list pesanan
	while(current != NULL){
		printf("\n%32s|%2s%-30s|%4s%-4d%3s|%2sRp%-6d%3s|", " ", " ", current->nama, " ", current->kuantitas, " ", " ", current->harga, " ");
		current = current->next;
	}
}

void total_harga(){
	struct item *current;
	current = order_start;
	
	//Ke posisi setiap pelanggan
	while(current->numCust != cust_count){
		current = current->next;
	}
	
	//Pesanan kosong
	if(current == NULL){
		printf("%46s--- DAFTAR PESANAN KOSONG ---", " ");
		return;
	}
	
	//Penjumlahan harga
	sumHarga = 0;
	while(current != NULL){
		sumHarga += (current->harga)*(current->kuantitas);
		current = current->next;
	}
	
	printf("\n%32s------------------------------------------------------------\n", " ");
	printf("%32s|%29sTOTAL HARGA: Rp%-12d  |", " ", " ", sumHarga);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------
//Fungsi login sehingga hanya pegawai yang bisa akses
void login(){
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("%51s<< LOGIN >>\n", " ");
	printf("%35sMasukan Nomor Pegawai: ", " ");
	scanf("%d", &input_nomor_pegawai);
	for(i = 0; i < 2; i++){				//Komparasi kesamaan data dengan input nomor pegawai
		if(input_nomor_pegawai == nomor_pegawai[i]){
			system("cls");
			pegawai();				//Input ditemukan di dalam data
		}
	}
	if(i==2){							//Jika 3 kali salah, kembali ke main menu
			printf("\n%50sAKSES DITOLAK\n", " ");
			printf("\nTekan ENTER untuk lanjut");
			getch();
			mainMenu();
	}
}

//Fungsi display pesanan setiap pelanggan
void daftarPsn(){
	struct item *current;
	current = order_start;
	
	if(current == NULL){
		printf("%46s--- DAFTAR PESANAN KOSONG ---", " ");
		return;
	}
	
	printf("%51s<< DAFTAR PESANAN >>\n\n", " ");
	printf("%32s|%10sNama Makanan%10s| Kuantitas | No Pelanggan |\n", " ", " ", " ");
	printf("%32s-------------------------------------------------------------", " ");
	
	while(current != NULL){
		if(current->done == 0){
			printf("\n%32s|%2s%-30s|%4s%-4d%3s|%4s%-4d%6s|", " ", " ", current->nama, " ", current->kuantitas, " ", " ", current->numCust, " ");
			current = current->next;
		}else if(current->done == 1){
			current = current->next;
		}
	}
}

void psnSelesai(int item_done_edit){
	struct item *current;
	current = order_start;
	
	if(current == NULL){
		printf("\n%46s--- DAFTAR PESANAN KOSONG ---", " ");
	}
	
	//Searching ke data yang ingin ditandai
	while(current != NULL){
		if(current->numCust == item_done_edit){
			current->done = 1;			//Menandai pesanan selesai
			current = current->next;
		}else{
			current = current->next;
		}
	}
}

//Fungsi menu pegawai
void pegawai(){
	printf("%50s<< MENU PEGAWAI>>\n\n", " ");
	printf("%47s --- FITUR PROGRAM ---\n", " ");
	printf("%46s1. Daftar Pesanan Pelanggan\n", " ");
	printf("%46s2. Pengaturan Menu Makanan\n", " ");
	printf("%46s3. Tandai Pesanan Selesai\n", " ");
	printf("%46s4. Total Pendapatan\n", " ");
	printf("%46s5. BACK\n", " ");
	printf("\n%51sPILIH FITUR: ", " ");
	scanf("%d", &pgwMen_opt);
	
	if(pgwMen_opt == 1){
		system("cls");
		daftarPsn();
		printf("\n\nTekan ENTER untuk lanjut");
		getch();
		system("cls");
		pegawai();
	}else if(pgwMen_opt == 2){
		system("cls");
		edit_menu();
		printf("\n\nTekan ENTER untuk lanjut");
		getch();
		system("cls");
		pegawai();
	}else if(pgwMen_opt == 3){
		printf("\n\t\t\t\t\tPesanan pelanggan berapa: ");
		scanf("%d", &item_done_edit);
		psnSelesai(item_done_edit);
		printf("\n\nTekan ENTER untuk lanjut");
		getch();
		system("cls");
		pegawai();
	}else if(pgwMen_opt == 4){
		printf("\n\t\t\t\t\t\tTOTAL PENDAPATAN: Rp%-20d\n", sumHargaTotal);
		printf("\n\nTekan ENTER untuk lanjut");
		getch();
		system("cls");
		pegawai();
	}else if(pgwMen_opt == 5){
		system("cls");
		mainMenu();
	}else{
		printf("\n%48sERROR: INVALID INPUT\n\n", " ");				//Jika salah memasukan input
		printf("\nTekan ENTER untuk lanjut");
		getch();
		system("cls");
		pegawai();
	}
}

//Fungsi edit makanan
void edit_menu(){
	printf("%45s<< PENGATURAN MENU MAKANAN >>\n\n", " ");
	printf("%49s1. Add makanan\n", " ");
	printf("%49s2. Delete makanan\n", " ");
	printf("%49s3. Edit makanan\n", " ");
	printf("%49s4. BACK\n", " ");
	printf("\n%51sMASUKAN PILIHAN: ", " ");
	scanf("%d", &editMen_opt);
	
	if(editMen_opt == 1){
		printf("\n%49s --- ADD MAKANAN ---\n\n", " ");
		printf("%35sMasukkan nama makanan:  ", " ");
		scanf(" %[^\n]", &item_nama_edit);
		printf("%35sMasukkan harga makanan: ", " ");
		scanf("%d", &item_harga_edit);
		printf("%35sMasukkan kode makanan:  ", " ");
		scanf("%d", &item_kode_edit);
		printf("%35sMasukkan stock makanan: ", " ");
		scanf("%d", &item_stock_edit);
		insertFood(item_nama_edit, item_harga_edit, item_kode_edit, item_stock_edit);		//Memasukan makanan ke linked list menu makanan
		printf("\n");
		traverseMenu();
	}else if(editMen_opt == 2){
		printf("\n%47s --- DELETE MAKANAN ---\n\n", " ");
		printf("%34sKode makanan yang ingin dihapus: ", " ");
		scanf("%d", &item_kode_edit);
		deleteFood(item_kode_edit);			//Menghapus makanan dari linked list menu manakan
		printf("\n");
		traverseMenu();
	}else if(editMen_opt == 3){
		printf("\n%48s --- EDIT MAKANAN ---\n\n", " ");
		printf("%34sKode makanan yang ingin diedit: ", " ");
		scanf("%d", &item_kode_edit);
		editFood(item_kode_edit);			//Mengedit makanan dari linked list menu makanan
		printf("\n");
		traverseMenu();
	}else if(editMen_opt == 4){
		system("cls");
		pegawai();			//Kembali ke menu pegawai
	}else{
		printf("\n%48sERROR: INVALID INPUT\n\n", " ");				//Jika salah memasukan input
		printf("\nTekan ENTER untuk lanjut");
		getch();
		system("cls");
		edit_menu();
	}
}

void traverseMenu(){
	struct item *current;
	current = menu_start;
	
	//Menu kosong
	if(current == NULL){
		printf("%46s--- DAFTAR MENU KOSONG ---", " ");
		return;
	}
	//Display menu makanan
	printf("%49s--- DAFTAR MENU ---\n\n", " ");
	printf("%26s| Kode |%10sNama Makanan%10s|%4sHarga%4s| Stock |\n", " ", " ", " ", " ", " ");
	printf("%26s---------------------------------------------------------------", " ");
	while(current != NULL){
		printf("\n%26s| %-4d |%2s%-30s|%2sRp%-6d%3s| %-5d |", " ", current->kode, " ", current->nama, " ", current->harga, " ", current->stock);
		current = current->next;
	}
}

//Fungsi add makanan ke menu makanan
void insertFood(char item_nama_edit[100], int item_harga_edit, int item_kode_edit, int item_stock_edit){
	struct item *current;
	struct item *link = (struct item*)malloc(sizeof(struct item));
	
	//Membuat isi struct makanan baru
	link->kode = item_kode_edit;
	strcpy(link->nama, item_nama_edit);
	link->harga = item_harga_edit;
	link->stock = item_stock_edit;
	
	//Jika menu kosong di-add ke awal
	if(menu_start == NULL){
		menu_start = link;
		menu_start->next = NULL;
		return;
	}
	
	//Cek apakah kode sudah digunakan
	current = menu_start;
	if(current->next == NULL){
		if(item_kode_edit == current->kode){
			printf("\n%48sERROR: KODE SUDAH DIGUNAKAN\n\n", " ");
			return;
		}
	}
	while(current->next != NULL){
		if(item_kode_edit == current->kode){
			printf("\n%48sERROR: KODE SUDAH DIGUNAKAN\n\n", " ");
			return;
		}
		current = current->next;
	}
	
	//Menghubungkan struct baru ke linked list
	current->next = link;
	link->next = NULL;
}

//Fungsi menghapus makanan dari menu
void deleteFood(int item_kode_edit){
	struct item *current = menu_start;
	struct item *previous = NULL;
	
	//Jika menu kosong akan kembali ke menu pegawai
	if(menu_start == NULL){
		return;
	}
	
	//Mencari makanan dengan kode yang diberikan
	while(current->kode != item_kode_edit){
		if(current->next == NULL){
			printf("\n%48sERROR: MAKANAN TIDAK DITEMUKAN\n\n", " ");
			return;
		}else{
			previous = current;
			current = current->next;
		}
	}
	
	//Jika hanya ada satu makanan akan menjadi kosong
	if(current == menu_start){
		menu_start = menu_start->next;
	}else{
		previous->next = current->next;		//makanan dikeluarkan dari list
	}
	free(current);
}

void editFood(int item_kode_search){
	struct item *current;
	struct item *temp;
	
	//Daftar menu kosong
	if(menu_start == NULL){
		printf("\n%49s--- DAFTAR MENU KOSONG ---", " ");
		return;
	}
	
	//Mencari makanan dengan kode yang diinput
	current = menu_start;
	while(current->kode != item_kode_edit){
		if(current->next == NULL){
			printf("\n%48sERROR: MAKANAN TIDAK DITEMUKAN\n\n", " ");
			return;
		}else{
			current = current->next;
		}
	}
	//Makanan ditemukan
	
	//Display informasi makanan untuk konfirmasi
	printf("\n%48sNama makanan: %s\n", " ", current->nama);
	printf("%48sHarga:        %d\n", " ", current->harga);
	printf("%48sStock:        %d\n", " ", current->stock);
	
	printf("\n%51s --- OPTION ---\n\n", " ");
	printf("%49s1. Edit nama\n", " ");
	printf("%49s2. Edit harga\n", " ");
	printf("%49s3. Edit stock\n", " ");
	printf("%49s4. BACK\n", " ");
	printf("\n%51sMASUKAN PILIHAN: ", " ");
	scanf("%d", &editFood_opt);
	
	//Looping jika input salah
	while(editFood_opt < 1 || editFood_opt > 4){
		printf("\n%48sERROR: INVALID INPUT\n\n", " ");	
		printf("\n%51sMASUKAN PILIHAN: ", " ");
		scanf("%d", &editFood_opt);
	}
	
	if(editFood_opt == 1){			//Mengganti nama makanan
		strcpy(temp->nama, current->nama);
		
		printf("%42sGanti dengan nama: ", " ");
		scanf(" %[^\n]", &item_nama_edit);
		
		strcpy(current->nama, item_nama_edit);
		printf("\n%35s%s berhasil diganti dengan %s\n", " ", temp->nama, current->nama);
	}else if(editFood_opt == 2){			//Mengganti harga makanan
		temp->harga = current->harga;
		
		printf("%42sGanti dengan harga: ", " ");
		scanf("%d", &item_harga_edit);
		
		current->harga = item_harga_edit;
		printf("\n%35s Harga Rp%d berhasil diganti dengan Rp%d\n", " ", temp->harga, current->harga);
	}else if(editFood_opt == 3){
		temp->stock = current->stock;
		
		printf("%42sGanti dengan stock sebanyak: ", " ");
		scanf("%d", &item_stock_edit);
		
		current->stock = item_stock_edit;
		printf("\n%35sStock %d berhasil diganti dengan %d\n", " ", temp->stock, current->stock);
	}else if(editFood_opt == 4){		//Kembali ke menu pegawai
		system("cls");
		edit_menu();
	}
}


//Fungsi informasi pembuat program
void about(){
	printf("-----------------------------------------------------------------------------------------------------------------------\n");
	printf("%50s<< ABOUT US >>\n\n", " ");
	printf("%45s--- Kelompok 16 Lombok ---\n", " ");
	printf("%40sEfranandi Abi Rafdi\t(1806181975)\n%40sStanley Darwin Chandra\t(1806233865)\n", " ", " ");
}

//Fungsi help
void help(){
	printf("\n%52s<< HELP >>\n\n", " ");
	printf("%8s1. Jika ada error dengan INVALID INPUT, maka artinya anda salah input pilihan.\n", " ");
	printf("%8s2. Jika pada sisi pegawai belum input daftar pesanan, maka bagian pelanggan muncul daftar menu kosong.\n", " ");
	printf("%8s3. Untuk bagian pegawai akses menggunakan NPM.\n", " ");
	printf("%8s4. Jika pada sisi pegawai telah tandai semua pesanan selesai, maka muncul daftar pesanan menu kosong.\n", " ");
	printf("%8s5. Jika pegawai menggunakan kode makanan yang sama, maka akan muncul error.\n", " ");
	printf("%8s6. Jika muncul error makanan tidak ditemukan artinya tidak ada makanan dengan kode tersebut.\n", " ");
}
