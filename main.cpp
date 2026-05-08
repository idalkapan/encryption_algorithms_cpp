# sifreleme
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

// Fonksiyon prototipleri
string caesarSifrele(const string& metin, int kaydirma);
string caesarCoz(const string& metin, int kaydirma);
string lineerSifrele(const string& metin, int a, int b);
string lineerCoz(const string& metin, int a, int b);
string rsaSifrele(const string& metin, int anahtar);
string rsaCoz(const string& metin, int anahtar);
string transpozisyonSifrele(const string& metin);
string transpozisyonCoz(const string& metin);

// Fonksiyon tanımları

string caesarSifrele(const string& metin, int kaydirma) {
    string sifreliMetin = "";
    for (char c : metin) {
        if (isalpha(c)) {
            char kaydirilmisKarakter = (c - 'a' + kaydirma) % 26 + 'a';
            sifreliMetin += kaydirilmisKarakter;
        } else {
            sifreliMetin += c;
        }
    }
    return sifreliMetin;
}

string caesarCoz(const string& metin, int kaydirma) {
    string cozulmusMetin = "";
    for (char c : metin) {
        if (isalpha(c)) {
            char kaydirilmamisKarakter = (c - 'a' - kaydirma + 26) % 26 + 'a';
            cozulmusMetin += kaydirilmamisKarakter;
        } else {
            cozulmusMetin += c;
        }
    }
    return cozulmusMetin;
}

string lineerSifrele(const string& metin, int a, int b) {
    string sifreliMetin = "";
    for (char karakter : metin) {
        int sifreliKarakter = (a * (int)karakter) + b;
        sifreliMetin += to_string(sifreliKarakter) + " ";
    }
    return sifreliMetin;
}

string lineerCoz(const string& sifreliMetin, int a, int b) {
    string orjinalMetin = "";
    istringstream iss(sifreliMetin);
    string sifreliDeger;
    try {
        while (iss >> sifreliDeger) {
            int sifreliKarakter = stoi(sifreliDeger);
            int orjinalKarakter = (sifreliKarakter - b) / a;
            orjinalMetin += (char)orjinalKarakter;
        }
    } catch (const std::out_of_range& e) {
        cout << "Hata: Tamsayı sınırları dışında bir değer var. Deşifreleme başarısız." << endl;
        return "";
    } catch (const std::invalid_argument& e) {
        cout << "Hata: Geçersiz bir giriş var. Deşifreleme başarısız." << endl;
        return "";
    }
    return orjinalMetin;
}

string rsaSifrele(const string& metin, int anahtar) {
    string sifreliMetin = metin;
    for (char& c : sifreliMetin) {
        c += anahtar;
    }
    return sifreliMetin;
}

string rsaCoz(const string& sifreliMetin, int anahtar) {
    string orjinalMetin = sifreliMetin;
    for (char& c : orjinalMetin) {
        c -= anahtar;
    }
    return orjinalMetin;
}

string transpozisyonSifrele(const string& metin) {
    float sutun = 5.0;
    int satirSayisi = ceil(metin.length() / sutun);
    vector<vector<char> > sifrelenmis(satirSayisi, vector<char>(sutun));
    int index = 0;
    for (int col = 0; col < sutun; col++) {
        for (int row = 0; row < satirSayisi; row++) {
            if (index < metin.length()) {
                sifrelenmis[row][col] = metin[index];
                index++;
            } else {
                sifrelenmis[row][col] = ' ';
            }
        }
    }
    string sifreliMetin;
    for (int row = 0; row < satirSayisi; row++) {
        for (int col = 0; col < sutun; col++) {
            sifreliMetin += sifrelenmis[row][col];
        }
    }
    return sifreliMetin;
}

string transpozisyonCoz(const string& sifreliMetin) {
    float sutun = 5.0;
    int satirSayisi = sifreliMetin.length() / sutun;
    vector<vector<char> > cozulmus(satirSayisi, vector<char>(sutun));
    int index = 0;
    for (int row = 0; row < satirSayisi; row++) {
        for (int col = 0; col < sutun; col++) {
            cozulmus[row][col] = sifreliMetin[index];
            index++;
        }
    }
    string duzMetin;
    for (int col = 0; col < sutun; col++) {
        for (int row = 0; row < satirSayisi; row++) {
            duzMetin += cozulmus[row][col];
        }
    }
    return duzMetin;
}

int main() {
    int secenek;
    cout << "1. Caesar Şifreleme/Çözme" << endl;
    cout << "2. Lineer Şifreleme/Çözme" << endl;
    cout << "3. RSA Şifreleme/Çözme" << endl;
    cout << "4. Transpozisyon Şifreleme/Çözme" << endl;
    cout << "Secenek seciniz: ";
    cin >> secenek;

    switch (secenek) {
        case 1: {
            int kaydirma;
            string metin;
            cout << "Metni giriniz: ";
            cin >> metin;
            cout << "Kaydirma miktarini giriniz: ";
            cin >> kaydirma;
            cout << "Sifreli Metin: " << caesarSifrele(metin, kaydirma) << endl;
            cout << "Cozulmus Metin: " << caesarCoz(caesarSifrele(metin, kaydirma), kaydirma) << endl;
            break;
        }
        case 2: {
            int a, b;
            string metin;
            cout << "Metni giriniz: ";
            cin >> metin;
            cout << "a degerini giriniz: ";
            cin >> a;
            cout << "b degerini giriniz: ";
            cin >> b;
            cout << "Sifreli Metin: " << lineerSifrele(metin, a, b) << endl;
            cout << "Cozulmus Metin: " << lineerCoz(lineerSifrele(metin, a, b), a, b) << endl;
            break;
        }
        case 3: {
            int anahtar;
            string metin;
            cout << "Metni giriniz: ";
            cin >> metin;
            cout << "Anahtar degerini giriniz: ";
            cin >> anahtar;
            cout << "Sifreli Metin: " << rsaSifrele(metin, anahtar) << endl;
            cout << "Cozulmus Metin: " << rsaCoz(rsaSifrele(metin, anahtar), anahtar) << endl;
            break;
        }
        case 4: {
            string metin;
            cout << "Metni giriniz: ";
            cin >> metin;
            cout << "Sifreli Metin: " << transpozisyonSifrele(metin) << endl;
            cout << "Cozulmus Metin: " << transpozisyonCoz(transpozisyonSifrele(metin)) << endl;
            break;
        }
        default:
            cout << "Gecersiz secenek!" << endl;
    }

    return 0;
}
