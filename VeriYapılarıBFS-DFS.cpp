//BERK AKIN 191307012
#include <iostream>
#include <locale>
using namespace std;
#define MAX 6

struct düğüm
{
    char işaret;
    bool işaretlimi;
};
struct düğüm* DüğümDizisi[MAX];
//KUYRUK YAPISI
int Kuyruk[MAX];
int Arka = -1;
int Ön = 0;
int KuyrukDüğümSayısı = 0;

//KOMŞULUK MATRİSİ
int KomşulukM[MAX][MAX];
int DüğümSayısı = 0;

//YIĞIN YAPISI
int Yığın[MAX];
int top = -1;

//KOMŞULUK MATRİSİ VE GRAF TANIMLAMA
void DüğümEkle(char işaret)
{
    struct düğüm* geçici = new düğüm();
    geçici->işaret = işaret;
    geçici->işaretlimi = false;
    DüğümDizisi[DüğümSayısı++] = geçici;
}
void KenarEkle(int baş, int son)
{
    KomşulukM[baş][son] = 1;
    KomşulukM[son][baş] = 1;
}

//DFS VE BFS DE ELEMANLARI YAZARKEN ÇAĞIRILACAK METOT
void DüğümYaz(int Yuva)
{
    cout << DüğümDizisi[Yuva]->işaret << "\t";
}

//GEZİLEN BİR DÜĞÜMÜN İŞARETLİ OLUP OLMADIĞI İÇİN KONTROL METODU
int İşaretKontrolü(int Yuva)
{
    int i;
    for (i = 0; i < DüğümSayısı; i++)
    {
        if (KomşulukM[Yuva][i] == 1 && DüğümDizisi[i]->işaretlimi == false)
            return i;
    }
    return -1;
}

//KUYRUK YAPISI İLE BFS METOTLARI
void Ekle(int data)
{
    Kuyruk[++Arka] = data;
    KuyrukDüğümSayısı++;
}
int Sil()
{
    KuyrukDüğümSayısı--;
    return Kuyruk[Ön++];
}
bool KuyrukBoşMu()
{
    return KuyrukDüğümSayısı == 0;
}
void BFS()
{
    int i;
    DüğümDizisi[0]->işaretlimi = true;
    DüğümYaz(0);
    Ekle(0);
    int q;

    while (!KuyrukBoşMu())
    {
        int geçici = Sil();

        while ((q = İşaretKontrolü(geçici)) != -1)
        {
            DüğümDizisi[q]->işaretlimi = true;
            DüğümYaz(q);
            Ekle(q);
        }
    }
    for (i = 0;i < DüğümSayısı;i++)
    {
        DüğümDizisi[i]->işaretlimi = false;
    }
}

//YIĞIN YAPISI İLE DFS METOTLARI
void Push(int Değer)
{
    Yığın[++top] = Değer;
}
int Pop()
{
    return Yığın[top--];
}
int Peek()
{
    return Yığın[top];
}
bool YığınBoşMu()
{
    return top == -1;
}
void DFS()
{
    int i;
    DüğümDizisi[0]->işaretlimi = true;
    DüğümYaz(0);
    Push(0);

    while (!YığınBoşMu())
    {
        int İşaretsiz = İşaretKontrolü(Peek());
        if (İşaretsiz == -1)
        {
            Pop();
        }
        else
        {
            DüğümDizisi[İşaretsiz]->işaretlimi = true;
            DüğümYaz(İşaretsiz);
            Push(İşaretsiz);
        }
    }
    for (i = 0;i < DüğümSayısı;i++)
    {
        DüğümDizisi[i]->işaretlimi = false;
    }
}

int main()
{
    int i, j;

    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
            KomşulukM[i][j] = 0;
    }

    DüğümEkle('A');  DüğümEkle('B');  DüğümEkle('C');
    DüğümEkle('D');  DüğümEkle('E');  DüğümEkle('F');

    KenarEkle(0, 1);KenarEkle(0, 3);KenarEkle(0, 4);KenarEkle(1, 2);
    KenarEkle(2, 4);KenarEkle(2, 5);KenarEkle(3, 4);KenarEkle(4, 5);

    cout << "BFS : " << endl; BFS();
    cout << endl;
    cout << "DFS : " << endl; DFS();
    cout << endl;

    return 41;
}