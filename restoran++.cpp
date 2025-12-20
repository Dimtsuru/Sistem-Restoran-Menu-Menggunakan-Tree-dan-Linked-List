// Algoritma dan Struktur Data (B) - Praktikum UAP Kelompok 1 - Restoran++
// Anggota:
// 1. Ahmadtovich Hathori Astro 	245150300111016
// 2. Wiratirta Tuhu Alirkahuripan 	245150300111017
// 3. Rafael Prima Sirait 	        245150300111018
// 4. M. Musawwirul Husna	        245150300111021
// 5. Dillon Imtitsal Pratama 	    245150300111026
// 6. I Gede Tio Pradipta Jasapada	245150307111028
#include <iostream>
#include <vector>
using namespace std;

// node linked list daftar makanan
class nodeList {
public:
    int price;
    string name;
    nodeList* next;

    nodeList(int p, string n) {
        name = n;
        price = p;
        next = nullptr;
    }
};

// node tree menu
class nodeTree {
public:
    int id, jumlah;
    string namaTipeMakanan;
    nodeTree* left;
    nodeTree* right;
    nodeList* menuList;

    // parameterized constructor
    nodeTree(int _id, string nama) {
        id = _id;
        jumlah = 0;
        namaTipeMakanan = nama;
        left = nullptr;
        right = nullptr;
        menuList = nullptr;
    }
    
    // Destructor
    ~nodeTree() {
        nodeList* current = menuList;
        while (current != nullptr) {
            nodeList* temp = current->next;
            delete current;
            current = temp;
        }
        delete left;
        delete right;
    }
};

// tree untuk menyimpan menu berdasarkan kategori makanan
class treeMenu {
public:
    nodeTree* root;

    // default constructor
    treeMenu() {
        root = nullptr;
    }
    
    // menambahkan node ke tree
    void addNodeTree(int id, string name) {
        if (root == NULL)
            root = new nodeTree(id, name);
        else
            addNodeTreeBranch(root, id, name);
    }
    
    // menambahkan node ke tree jika root sudah diisi
    void addNodeTreeBranch(nodeTree *node, int id, string name) {
        if (id <= node->id) {
            if (node->left == NULL)
                node->left = new nodeTree(id, name);
            else
                addNodeTreeBranch(node->left, id, name);
        } 
        else if (id > node->id) {
            if (node->right == NULL)
                node->right = new nodeTree(id, name);
            else
                addNodeTreeBranch(node->right, id, name);
        }
    }

    // Fungsi untuk mencari node berdasarkan ID
    nodeTree* findNode(nodeTree* node, int id) {
        if (node == nullptr) return nullptr;
        if (node->id == id) return node;
        if (node->id > id) return findNode(node->left, id);
        return findNode(node->right, id);
    }

    // Menambahkan item ke menuList berdasarkan ID nodeTree
    void addMenuItem(int targetId, int price, string name) {
        nodeTree* targetNode = findNode(root, targetId);
        if (targetNode == nullptr) return;
        nodeList* newItem = new nodeList(price, name);
        if (targetNode->menuList == nullptr) {
            targetNode->menuList = newItem;
        } else {
            nodeList* temp = targetNode->menuList;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newItem;
        }
        targetNode->jumlah++;
    }

    // Menampilkan isi tree secara pre-order dan linkedlistmenu di dalamnya
    void display(nodeTree* node) {
        if (node == nullptr) return;
        if (node->menuList != NULL) {
            cout << node->namaTipeMakanan << endl;
            nodeList* temp = node->menuList;
            int i = 1;
            while (temp != nullptr) {
                cout << "   " << i << ".\tRp. " << temp->price << "\t" << temp->name << endl;
                temp = temp->next;
                i++;
            }
        }
        display(node->left);
        display(node->right);
    }
    
    // mengganti harga makanan
    void updateMenuItem(int nodeId, int itemIndex, int newPrice) {
        nodeTree* targetNode = findNode(root, nodeId);
        if (targetNode == nullptr) return;
        nodeList* temp = targetNode->menuList;
        for (int i = 1; i <= targetNode->jumlah; i++) {
            if (i == itemIndex) {
                temp->price = newPrice;
                break;
            }
            temp = temp->next;
        }
    }
    
    // menghapus makanan dari menu
    void deleteMenuItem(int nodeId, int itemIndex) {
        nodeTree* targetNode = findNode(root, nodeId);
        if (targetNode == nullptr) return;
        nodeList* temp = targetNode->menuList;
        if (itemIndex == 1) {
            targetNode->menuList = temp->next;
            delete temp;
            targetNode->jumlah--;
            return;
        }
        for (int i = 2; i <= targetNode->jumlah; i++) {
            if (i == itemIndex) {
                nodeList* toDelete = temp->next;
                temp->next = toDelete->next;
                delete toDelete;
                targetNode->jumlah--;
                break;
            }
            temp = temp->next;
        }
    }
    
    // mengurutkan daftar makanan dalam 1 tipe
    nodeList* sortingDaftarMakanan(nodeList *node) {
        if (node == NULL) return node;
        nodeList* sorted = nullptr;
        while (node != NULL) {
            nodeList* current = node;
            node = node->next;
            current->next = nullptr;
            if (!sorted || current->price < sorted->price) {
                current->next = sorted;
                sorted = current;
            } else {
                nodeList* temp = sorted;
                while (temp->next && temp->next->price < current->price) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }
        }
        return sorted;
    }
    
    // Mengurutkan menu berdasarkan harga pada semua tipe
    void sortingMenu(nodeTree* node) {
        if (!node) return;
        node->menuList = sortingDaftarMakanan(node->menuList);
        sortingMenu(node->left);
        sortingMenu(node->right);
    }
    
    // Destructor
    ~treeMenu() {
        delete root;
    }
};

// class untuk memasukkan makanan ke menu
class masukinMenu {
public:
    treeMenu menu;

    masukinMenu() {
        // Bangun struktur tree
        menu.addNodeTree(4, "Menu");
        
        menu.addNodeTree(2, "Minuman");
        menu.addNodeTree(6, "Makanan");
        
        menu.addNodeTree(1, "Hot Drink");
        menu.addNodeTree(3, "Cold Drink");
        
        menu.addNodeTree(5, "Main Dish");
        menu.addNodeTree(8, "Snack");
        
        menu.addNodeTree(7, "Dessert");
        menu.addNodeTree(9, "Appetizer");
        
        // Tambahkan item ke kategori Appetizer
        menu.addMenuItem(9, 25000, "Bruschetta");
        menu.addMenuItem(9, 20000, "Garlic Bread");
        menu.addMenuItem(9, 22000, "Spring Roll");
        menu.addMenuItem(9, 23000, "French Fries");
        menu.addMenuItem(9, 30000, "Chicken Wings");
        menu.addMenuItem(9, 28000, "Mozzarella Sticks");
        menu.addMenuItem(9, 24000, "Onion Rings");
        menu.addMenuItem(9, 27000, "Stuffed Mushrooms");
        menu.addMenuItem(9, 26000, "Mini Quiche");
        menu.addMenuItem(9, 25000, "Soup Of The Day");
        menu.addMenuItem(9, 15000, "Fried Tofu");
        menu.addMenuItem(9, 29000, "Chicken Satay");
        menu.addMenuItem(9, 32000, "Beef Nachos");
        menu.addMenuItem(9, 21000, "Salad Roll");
        menu.addMenuItem(9, 20000, "Edamame");
        menu.addMenuItem(9, 27000, "Mini Sandwich");
        menu.addMenuItem(9, 29000, "Cheesy Potato Skins");
        menu.addMenuItem(9, 31000, "Dimsum Basket");
        menu.addMenuItem(9, 22000, "Tahu Walik");
        menu.addMenuItem(9, 20000, "Perkedel Kentang");
        
        // Tambahkan item ke kategori Dessert
        menu.addMenuItem(7, 35000, "Chocolate Lava Cake");
        menu.addMenuItem(7, 38000, "Cheesecake");
        menu.addMenuItem(7, 25000, "Fruit Salad");
        menu.addMenuItem(7, 23000, "Pudding Cokelat");
        menu.addMenuItem(7, 40000, "Tiramisu");
        menu.addMenuItem(7, 32000, "Banana Split");
        menu.addMenuItem(7, 30000, "Ice Cream Sundae");
        menu.addMenuItem(7, 27000, "Pisang Keju");
        menu.addMenuItem(7, 35000, "Brownies Ice Cream");
        menu.addMenuItem(7, 39000, "Creme Brulee");
        menu.addMenuItem(7, 34000, "Waffle Ice Cream");
        menu.addMenuItem(7, 15000, "Klepon");
        menu.addMenuItem(7, 18000, "Serabi Solo");
        menu.addMenuItem(7, 26000, "Pudding Mangga");
        menu.addMenuItem(7, 22000, "Donat Mini");
        menu.addMenuItem(7, 20000, "Es Doger");
        menu.addMenuItem(7, 25000, "Martabak Manis Mini");
        menu.addMenuItem(7, 28000, "Roti Bakar Cokelat Keju");
        menu.addMenuItem(7, 36000, "Strawberry Parfait");
        menu.addMenuItem(7, 37000, "Pannacotta");
        
        // Tambahkan item ke kategori Main Dish
        menu.addMenuItem(5, 25000, "Ayam Bakar Madu");
        menu.addMenuItem(5, 20000, "Nasi Goreng Kampung");
        menu.addMenuItem(5, 22000, "Sate Ayam Bumbu Kacang");
        menu.addMenuItem(5, 45000, "Iga Bakar Sambal Ijo");
        menu.addMenuItem(5, 27000, "Mie Goreng Seafood");
        menu.addMenuItem(5, 50000, "Sop Buntut Spesial");
        menu.addMenuItem(5, 23000, "Nasi Ayam Geprek Keju");
        menu.addMenuItem(5, 28000, "Dori Sambal Matah");
        menu.addMenuItem(5, 35000, "Rendang Daging Sapi");
        menu.addMenuItem(5, 30000, "Cumi Saus Padang");
        menu.addMenuItem(5, 26000, "Ayam Woku Belanga");
        menu.addMenuItem(5, 34000, "Bebek Goreng Kremes");
        menu.addMenuItem(5, 38000, "Tongseng Kambing");
        menu.addMenuItem(5, 32000, "Udang Bakar Madu");
        menu.addMenuItem(5, 21000, "Nasi Liwet Solo");
        menu.addMenuItem(5, 24000, "Capcay Kuah Oriental");
        menu.addMenuItem(5, 27000, "Ayam Rica-Rica Manado");
        menu.addMenuItem(5, 40000, "Gurame Asam Manis");
        menu.addMenuItem(5, 29000, "Sapo Tahu Seafood");
        menu.addMenuItem(5, 15000, "Tumis Kangkung Terasi");
        menu.addMenuItem(5, 13000, "Soto Krispi");
        
        // Tambahkan item ke kategori Cold
        menu.addMenuItem(3, 5000, "Es Teh Manis");
        menu.addMenuItem(3, 6000, "Es Jeruk");
        menu.addMenuItem(3, 15000, "Jus Alpukat");
        menu.addMenuItem(3, 12000, "Jus Mangga");
        menu.addMenuItem(3, 7000, "Lemon Tea");
        menu.addMenuItem(3, 4000, "Air Mineral");
        menu.addMenuItem(3, 12000, "Soda Gembira");
        menu.addMenuItem(3, 15000, "Thai Tea");
        menu.addMenuItem(3, 16000, "Green Tea Latte");
        menu.addMenuItem(3, 17000, "Matcha Latte");
        menu.addMenuItem(3, 14000, "Milkshake Cokelat");
        menu.addMenuItem(3, 14000, "Milkshake Stroberi");
        menu.addMenuItem(3, 10000, "Es Kelapa Muda");
        menu.addMenuItem(3, 16000, "Taro Latte");
        menu.addMenuItem(3, 25000, "Screwdriver");
        
        // Tambahkan item ke kategori Hot
        menu.addMenuItem(1, 8000, "Kopi Hitam");
        menu.addMenuItem(1, 10000, "Kopi Susu");
        menu.addMenuItem(1, 18000, "Cappuccino");
        menu.addMenuItem(1, 10000, "Teh Tarik");
        menu.addMenuItem(1, 8000, "Wedang Jahe");
        menu.addMenuItem(1, 9000, "Bandrek");
        menu.addMenuItem(1, 18000, "Hot Chocolate");
        menu.addMenuItem(1, 25000, "Pumpkin Spice Latte");
        menu.addMenuItem(1, 22000, "Herbal Latte");
        menu.addMenuItem(1, 20000, "Susu Kurma");
    }

    // Tampilkan isi menu
    void displaying() {
        cout << "====================MENU====================\n";
        menu.display(menu.root);
    }
};

// node queue untuk antrian pesanan
struct Pesanan {
    vector<string> daftarPesanan;
    vector<int> harga;
    Pesanan *next;
    
    // Destructor
    ~Pesanan() {
        next = nullptr;
    }
};

// queue antrian pesanan
class QueuePesanan {
public:
    Pesanan* front;
    Pesanan* back;
    int jumlah;

    // default constructor
    QueuePesanan() {
        front = nullptr;
        back = nullptr;
        jumlah = 0;
    }

    // menambahkan pesanan ke antrian
    void enqueue(Pesanan* p) {
        if (back == nullptr) {
            front = back = p;
        } else {
            back->next = p;
            back = p;
        }
        back->next = nullptr;
        jumlah++;
    }

    // mengeluarkan pesanan dari antrian
    Pesanan* dequeue() {
        if (front == nullptr) return nullptr;
        Pesanan* temp = front;
        front = front->next;
        if (front == nullptr) back = nullptr;
        jumlah--;
        return temp;
    }
    
    // memeriksa apakah antrian kosong
    bool empty() {
        if (front == nullptr) return true;
        return false;
    }
    
    // Destructor
    ~QueuePesanan() {
        while (!empty()) {
            Pesanan* temp = dequeue();
            delete temp;
        }
    }
};

int main() {
    masukinMenu daftar;
    QueuePesanan antrian;
    Pesanan* pesananSekarang = new Pesanan;
    string password = "SotoKrispi";
    int a;
    
    cout << "Selamat datang di Restoran++ :)\n";
    do {
        cout << "====================Pilihan====================\n";
        cout << "1. Tampilkan Menu\n2. Tambahkan Pesanan\n3. Selesaikan Pesanan\n4. Tampilkan Semua Pesanan (banyak antrian: " << antrian.jumlah << ")\n5. Ubah Harga Makanan(admin)\n6. Hapus Makanan(admin)\n7. Tambah Makanan(admin)\n8. Urutkan Berdasarkan Harga\n9. Keluar\nMasukkan Pilihan: ";
        cin >> a;
        switch (a) {
            case 1: // Tampilkan Menu
                daftar.displaying();
                break;
            case 2: { // Tambahkan Pesanan
                int x, y, z;
                do {
                    cout << "1. Makanan\n2. Minuman\n3. Selesai\nMasukkan Pilihan: ";
                    cin >> x;
                    if (x == 1) {
                        cout << "1. Appetizer\n2. Main Dish\n3. Dessert\nMasukkan Pilihan: ";
                        cin >> y;
                        // menyesuaikan input dengan id tipe yang benar
                        if (y == 1) y = 9; 
                        else if (y == 2) y = 5;
                        else if (y == 3) y = 7;
                        else {
                            cout << "Kategori makanan tidak ditemukan\n";
                            continue;
                        }
                    } else if (x == 2) {
                        cout << "1. Hot\n2. Cold\nMasukkan Pilihan: ";
                        cin >> y;
                        // menyesuaikan input dengan id tipe yang benar
                        if (y == 2) y = 3;
                        else if (y != 1) {
                            cout << "Kategori makanan tidak ditemukan\n";
                            continue;
                        }
                    } else {
                        antrian.enqueue(pesananSekarang);
                        pesananSekarang = new Pesanan;
                        cout << "Pesanan ditambahkan ke antrian\n";
                        break;
                    }
                    cout << "Masukkan angka makanan: ";
                    cin >> z;
                    nodeTree* temp = daftar.menu.findNode(daftar.menu.root, y);
                    nodeList* m = temp->menuList;
                    for (int i = 1; i <= temp->jumlah; i++) {
                        if (i == z) {
                            pesananSekarang->daftarPesanan.push_back(m->name);
                            pesananSekarang->harga.push_back(m->price);
                            break;
                        }
                        m = m->next;
                    }
                } while (x != 3);
                break;
            }
            case 3: { // Selesaikan Pesanan
                if (!antrian.empty()) {
                    Pesanan* p = antrian.dequeue();
                    cout << "Pesanan selesai:\n";
                    int total = 0;
                    for (int i = 0; i < p->daftarPesanan.size(); i++) {
                        cout << " - " << p->daftarPesanan[i] << " Rp. " << p->harga[i] << endl;
                        total += p->harga[i];
                    }
                    cout << " total: Rp. " << total << endl;
                    delete p;
                } else {
                    cout << "Antrian kosong\n";
                }
                break;
            }
            case 4: { // Tampilkan Semua Pesanan
                if (!antrian.empty()) {
                    Pesanan* p = antrian.front;
                    for (int j = 0; j < antrian.jumlah; j++) {
                        cout << "Pesanan ke-" << j+1 << endl;
                        for (int i = 0; i < p->daftarPesanan.size(); i++) {
                            cout << "  - " << p->daftarPesanan[i] << " Rp. " << p->harga[i] << endl;
                        }
                        p = p->next;
                    }
                } else {
                    cout << "Antrian kosong\n";
                }
                break;
            }
            case 5: { // Ubah Harga Makanan
                cout << "Masukkan password: ";
                string password = "SotoKrispi";
                string pass; cin >> pass;
                if (password != pass) {
                    cout << "Password salah!!!\n";
                    break;
                }
                cout << "Masukkan id tipe [1)hot 3)cold 5)main dish 7)Dessert 9)Appetizer]: ";
                int y; cin >> y;
                cout << "Masukkan angka makanan: ";
                int z; cin >> z;
                cout << "Masukkan harga baru (contoh: Rp.50.000 => 50000): ";
                int x; cin >> x;
                daftar.menu.updateMenuItem(y, z, x);
                break;
            }
            case 6: { // Hapus Makanan
                cout << "Masukkan password: ";
                string pass; cin >> pass;
                if (password != pass) {
                    cout << "Password salah!!!\n";
                    break;
                }
                cout << "Masukkan id tipe [1)hot 3)cold 5)main dish 7)Dessert 9)Appetizer]: ";
                int y; cin >> y;
                cout << "Masukkan angka makanan: ";
                int z; cin >> z;
                daftar.menu.deleteMenuItem(y, z);
                break;
            }
            case 7: { // Tambah Makanan
                cout << "Masukkan password: ";
                string pass; cin >> pass;
                if (password != pass) {
                    cout << "Password salah!!!\n";
                    break;
                }
                cout << "Masukkan id tipe [1)hot 3)cold 5)main dish 7)Dessert 9)Appetizer]: ";
                int y; cin >> y;
                cin.ignore();
                cout << "Masukkan nama makanan: ";
                string z; 
                getline(cin, z);
                cout << "Masukkan harga makanan (contoh: Rp.50.000 => 50000): ";
                int x; cin >> x;
                daftar.menu.addMenuItem(y, x, z);
                break;
            }
            case 8: { // Urutkan Berdasarkan Harga
                daftar.menu.sortingMenu(daftar.menu.root);
                cout << "Menu berhasil diurutkan\n";
                break;
            }
            case 9: // Keluar
                cout << "Terima Kasih :)\n";
                break;
            default:
                cout << "Pilihan tidak ada dalam menu !!!\n";
                break;
        }
        cout << endl;
    } while (a != 9);

    return 0;
}
