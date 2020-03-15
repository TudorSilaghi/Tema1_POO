#include <iostream>
#include <stdarg.h>
#include <cstdarg>

using namespace std;

class vector
{
private:
    int n;
    double *v;
    double nr_dat;

public:
    vector(double nr_dat = 0, int n = 1)                /// constructor initializare
    {
        this->n = n;
        this->v = new double[n];      ///aloc dinamic
        for (int i = 0; i < n; ++i)
            v[i] = nr_dat;
    }

    vector (vector &);                                  /// constructor copiere

    void citire(istream &in);
    void afisare(ostream &out);

    friend istream& operator>>(istream &in, vector& data);
    friend ostream& operator<<(ostream &out, vector& data);
    vector& operator=(vector& data);

    void reactualizare (double, int);

    friend vector& operator+(vector& data1, vector& data2);
    friend vector& operator-(vector& data1, vector& data2);
    friend vector& operator+=(vector& data1, vector& data2);
    friend vector& operator-=(vector& data1, vector& data2);
    friend int operator==(vector& data1, vector& data2);
    friend int operator!=(vector& data1, vector& data2);

    friend int length(vector& data);

    friend vector& suma_vectorilor(int nr_vectori, vector& data1, ...);
    friend vector& maximul_vectorilor(int nr_vectori, vector& data1, ...);
};

vector::vector(vector &data)
{
    this->n = data.n;
    this->v = data.v;
}

void vector::citire(istream &in)
{
    cout << "Cititi numarul de componente: ";
    in >> this->n;
    cout << "Cititi numarul dat: ";
    in >> this->nr_dat;

    reactualizare(nr_dat, n);
}

istream& operator>>(istream& in, vector& v)
{
    v.citire(in);
    return in;
}

void vector::afisare(ostream &out)
{
    for (int i = 0; i < n; ++i)
    {
        out << v[i] << " ";
    }
    out << "\n";
}

ostream& operator<<(ostream& out, vector& data)
{
    data.afisare(out);
    return out;
}

vector& vector::operator=(vector& data)
{
    n = data.n;
    for (int i = 0; i < n; ++i)
    {
        v[i] = data.v[i];
    }
}

void vector::reactualizare(double nr_dat, int new_size)
{
    delete[] v;

    v = new double[new_size];
    n = new_size;
    for (int i = 0; i < new_size; ++i)
        v[i] = nr_dat;
}

inline vector& operator+(vector &data1, vector &data2)
{
    if (data1.n != data2.n)
    {
        cout << "Nu se pot aduna cei 2 vectori!";
        return data1;
    }

    vector *data_adunare = new vector(0, data1.n);
    data_adunare->n = data1.n;
    for (int i = 0; i < data1.n; ++i)
        data_adunare->v[i] = data1.v[i] + data2.v[i];

    return *data_adunare;
}

inline vector& operator-(vector &data1, vector &data2)
{
    if (data1.n != data2.n)
    {
        cout << "Nu se pot scadea cei 2 vectori!";
        return data1;
    }

    vector *data_scadere = new vector(0, data1.n);
    data_scadere->n = data1.n;
    for (int i = 0; i < data1.n; ++i)
        data_scadere->v[i] = data1.v[i] - data2.v[i];

    return *data_scadere;
}

vector& operator+=(vector &data1, vector &data2)
{
    if (data1.n != data2.n)
    {
        cout << "Nu se pot aduna cei 2 vectori!";
        return data1;
    }
    for (int i = 0; i < data1.n; ++i)
        data1.v[i] = data1.v[i] + data2.v[i];

    return data1;
}

vector& operator-=(vector &data1, vector &data2)
{
    if (data1.n != data2.n)
    {
        cout << "Nu se pot scadea cei 2 vectori!";
        return data1;
    }
    for (int i = 0; i < data1.n; ++i)
        data1.v[i] = data1.v[i] - data2.v[i];

    return data1;
}

int operator==(vector &data1, vector &data2)
{
    if (data1.n != data2.n)
    {
        cout << "Vectorii NU sunt egali.";
        return 0;
    }
    for (int i = 0; i < data1.n; ++i)
        if (data1.v[i] != data2.v[i])
        {
            cout << "Vectorii NU sunt egali.";
            return 0;
        }
    cout << "Vectorii sunt egali!";
    return 1;
}

int operator!=(vector &data1, vector &data2)
{
    if (data1.n != data2.n)
    {
        cout << "Vectorii NU sunt egali.";
        return 1;
    }
    for (int i = 0; i < data1.n; ++i)
        if (data1.v[i] != data2.v[i])
        {
            cout << "Vectorii NU sunt egali.";
            return 1;
        }
    cout << "Vectorii sunt egali!";
    return 0;
}

int length(vector &data)
{
    if (data.v == NULL)
        return 0;
    return data.n;
}

vector& suma_vectorilor(int nr_vectori, vector& data1, ...)
{
    va_list lista_de_vectori;
    vector *vector_suma = &data1;

    va_start(lista_de_vectori, data1);
    for (int i = 1; i < nr_vectori; ++i)
        if (data1.n != va_arg(lista_de_vectori, vector).n)
        {
            cout << "Vectorii nu au aceeasi dimensiune" << endl;
            return data1;
        }
    va_end(lista_de_vectori);

    va_start(lista_de_vectori, data1);
    for (int i = 1; i < nr_vectori; ++i)
        *vector_suma += va_arg(lista_de_vectori, vector);
    va_end(lista_de_vectori);

    return *vector_suma;
}

vector& maximul_vectorilor(int nr_vectori, vector& data1, ...)
{
    va_list lista_de_vectori;
    vector *vector_maxim = &data1;

    va_start(lista_de_vectori, data1);
    for (int i = 1; i < nr_vectori; ++i)
        if (data1.n != va_arg(lista_de_vectori, vector).n)
        {
            cout << "Vectorii NU au aceeasi dimensiune!" << endl;
            return data1;
        }
    va_end(lista_de_vectori);

    va_start(lista_de_vectori, data1);
    for (int i = 1; i < nr_vectori; ++i)
    {
        vector_maxim->nr_dat = max(vector_maxim->nr_dat, va_arg(lista_de_vectori, vector).nr_dat);
        (*vector_maxim).reactualizare(vector_maxim->nr_dat, vector_maxim->n);
    }
    va_end(lista_de_vectori);

    return *vector_maxim;
}

void menu_output()
{
    cout << " Silaghi Tudor-Adrian - 211 - Tema 14 - Clasa 'vector': \n";
    cout << "\n\t MENIU:";
    cout << "\n===========================================\n\n";

    cout << "1. Suma a 2 vectori" << endl;
    cout << "2. Diferenta a 2 vectori" << endl;
    cout << "3. Verifica daca 2 vectori sunt egali" << endl;
    cout << "4. Aduna un vector la un altul" << endl;
    cout << "5. Scade un vector dintr-altul" << endl;
    cout << "6. Afisaza lungimea unui vector" << endl;
    cout << "7. Afisaza suma mai multor vectori" << endl;
    cout << "8. Afisaza maximul mai multor vectori" << endl;
    cout << "9. Reactualizeaza vectorul" << endl;
    cout << "0. Iesire." << endl;
}

void menu()
{
    int option;                 /* optiunea aleasa din meniu */
    option = 0;

    do
    {
        menu_output();

        cout << "\nIntroduceti numarul actiunii: ";
        cin >> option;

        if (option == 1)
        {
            vector data1, data2;
            cout << "Primul vector este: \n";
            cin >> data1;
            cout << "Al doilea vector este: \n";
            cin >> data2;
            cout << "\nSuma vectorilor este: " << data1 + data2;
        }

        if (option == 2)
        {
            vector data1, data2;
            cout << "Primul vector este: \n";
            cin >> data1;
            cout << "Al doilea vector este: \n";
            cin >> data2;
            cout << "\nDiferenta vectorilor este: " << data1 - data2;
        }

        if (option == 3)
        {
            vector data1, data2;
            cout << "Primul vector este: \n";
            cin >> data1;
            cout << "Al doilea vector este: \n";
            cin >> data2;

            if(data1 == data2)
                cout << "Cei 2 vectori sunt egali!" << endl;
            else cout << "Cei 2 vectori NU sunt egali!" << endl;
        }

        if (option == 4)
        {
            vector data1, data2;
            cout << "\nPrimul vector este: \n";
            cin >> data1;
            cout << "\nAl doilea vector este: \n";
            cin >> data2;

            cout << "\nPrimul vector a devenit: ";
            data1 += data2;
            cout << data1 << endl;
        }

        if (option == 5)
        {
            vector data1, data2;
            cout << "\nPrimul vector este: \n";
            cin >> data1;
            cout << "\nAl doilea vector este: \n";
            cin >> data2;

            cout << "\nPrimul vector a devenit: ";
            data1 -= data2;
            cout << data1 << endl;
        }

        if (option == 6)
        {
            vector data;
            cout << "\nScrie vectorul: \n";
            cin >> data;
            cout << "Lungimea vectorului este: " << length(data) << endl;
        }

        if (option == 7)
        {
            int nr, i;
            cout << "\nNumarul de vectori: ";
            cin >> nr;
            vector data[i], vector_suma;
            cout << "\nPrimul vector este: \n";
            cin >> data[0];
            for (i = 1; i < nr; ++i)
            {
                cout << "Al " << i+1 << "-lea vector este: \n";
                cin >> data[i];
            }
            vector_suma = data[0];
            for (i = 1; i < nr; ++i)
                vector_suma = suma_vectorilor(2, vector_suma, data[i]);

            cout << "\nSuma vectorilor este: " << vector_suma << endl;
        }

        if (option == 8)
        {
            int nr, i;
            cout << "\nNumarul de vectori: ";
            cin >> nr;
            vector data[nr], vector_maxim;
            cin >> data[0];
            cout << "\nPrimul vector este: \n";
            cout << data[0];

            for (i = 1; i < nr; ++i)
            {
                cin >> data[i];
                cout << "Al " << i+1 << "-lea vector este: \n";
                cout << data[i];
            }
            vector_maxim = data[0];
            for (i = 1; i < nr; ++i)
                vector_maxim = maximul_vectorilor(2, vector_maxim, data[i]);

            cout <<"\nMaximul veectorilor dati este: " << vector_maxim << endl;
        }

        if (option == 9)
        {
            vector data;
            cin >> data;
            cout << "Vectorul initial este: ";
            cout << data;

            int nr_componente;
            double nr_dat;

            cout << "Schimba numarul de componente: ";
            cin >> nr_componente;
            cout << "Actualizarea vectorului cu numarul: ";
            cin >> nr_dat;

            data.reactualizare(nr_dat, nr_componente);

            cout << "\nVectorul reactualizat este: " << data << endl;
        }

        if (option == 0)
        {
            cout << "\nEXIT!\n";
        }
        if (option < 0 || option > 9)
        {
            cout << "\nSelectie invalida\n";
        }
        cout << "\n";
        system("pause"); ///Pauza - Press any key to continue...
        system("cls");   ///Sterge continutul curent al consolei
    }
    while(option!=0);
}

int main()
{
    menu();

    return 0;
}

