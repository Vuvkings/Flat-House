#include<iostream>
#include "Header.h";
using namespace std;

int main() {
    Man* Ivanovy{ new Man[3] };
    Ivanovy[0].init(1100, "Ivanov", "Nikolay", "Georgevich", 14, 7, 1977);
    Ivanovy[1].init(1101, "Ivanov", "Valentyna", "Ivanovna", 10, 4, 1978);
    Ivanovy[2].init(1102, "Ivanov", "Eva", "Nikolayevna", 6, 6, 2002);

    for (int i{ 0 }; i < 3; ++i) { std::cout << Ivanovy[i] << '\n'; }
    cout << '\n';

    Man* Volik{ new Man[3] };
    Volik[0].init(3230, "Volik", "Vladimir", "Petrovich", 6, 5, 1978);
    Volik[1].init(3231, "Volik", "Kateryna", "Ivanovna", 4, 4, 1980);
    Volik[2].init(3232, "Volik", "Dmitry", "Vladimirovich", 25, 6, 2016);

    Man person_1{ 5100,"Levchenko","Stepan","Vasylyevich",15,6,1981 };
    Man person_2{ 5101,"Popova","Alena","Stepanovna",1,4,1984 };

    Man person_3{ person_1 };
    Man person_4{ move(person_2) };

    cout << person_1 << '\n' << person_2 << '\n' << '\n' << person_3 << '\n' << person_4 << '\n' << '\n';

    Flat flat_1{ 1,2 };
    Flat flat_2{ 2,1 };
    Flat flat_3{ 3,2 };
    Flat flat_4{ 4,1 };
    cout << flat_1 << '\n' << flat_2 << '\n' << flat_3 << '\n' << flat_4 << "\n\n";
    for (int i{ 0 }; i < 3; ++i) { flat_1.addOccupant(move(Ivanovy[i])); }
    flat_2.addOccupant(person_1);
    flat_3.addOccupant(Man{ 1221, "Fain", "Eugene", "Yakovlevich", 21, 9, 1978 }).addOccupant(Man{ 1222, "Fain", "Marina", "Borisovnavna", 3, 2, 1981 });
    flat_4.addOccupant(move(person_4));
    Flat flat_5{ 1,3 };
    for (int i{ 0 }; i < 3; ++i) { flat_5.addOccupant(move(Volik[i])); }

    cout << flat_1 << '\n' << flat_2 << '\n' << flat_3 << '\n' << flat_4 << '\n';
    cout << '\n';
    cout << person_1 << '\n' << person_4 << '\n' << '\n';

    Home home_1;
    Home home_2{ 12,8 };
    cout << home_1 << '\n' << home_2 << '\n';

    home_1.addFlat(flat_1, 0).addFlat(flat_2, 1).addFlat(flat_3, 2).addFlat(flat_4, 3);
    cout << home_1 << '\n';
    home_1.removeFlat(2);
    home_2.addFlat(move(flat_5), 0).addFlat(move(flat_3), 2);
    cout << home_1 << '\n' << home_2 << '\n';

    delete[]Ivanovy;
    delete[]Volik;

	return 0;
}