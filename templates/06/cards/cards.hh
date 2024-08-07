#ifndef CARDS_HH
#define CARDS_HH

#include <iostream>
#include <memory>

// Määrittely tietorakenteelle, joka kuvaa korttipinon alkion eli yhden kortin.
// Definition of a data structure for an element of a card deck, i.e. a card.
struct Card_data
{
    int data;
    std::shared_ptr<Card_data> next;
};

class Cards
{
public:
    // Rakentaja, joka alustaa päällimmäisen alkion arvoksi nullptr.
    // A constructor that initializes the top item as nullptr.
    Cards();

    // Purkaja.
    // Destructor
    ~Cards();

    // Lisää uuden kortin annetulla id:llä pinon päällimmäiseksi.
    // Adds a new card with the given id as the topmost element.
    void add(int id);

    // Poistaa pinon päällimmäisen kortin ja palauttaa sen viiteparametrissa
    // id. Paluuarvona on false, jos ja vain jos pino oli tyhjä.
    //
    // Removes the topmost card and passes it in the reference parameter id to
    // the caller. Returns false, if and only if the data structure is empty.
    bool remove(int& id);

    // Tulostaa tietorakenteen sisällön järjestysnumeroineen
    // parametrina annettuun tietovirtaan s aloittaen ensimmäisestä alkiosta.
    //
    // Prints the content of the data structure with ordinal numbers to the
    // output stream s, given as a parameter, starting from the first element.
    void print_from_top_to_bottom(std::ostream& s);

    // Tulostaa tietorakenteen sisällön järjestysnumeroineen
    // parametrina annettuun tietovirtaan s aloittaen viimeisestä alkiosta.
    //
    // Prints the content of the data structure with ordinal numbers to the
    // output stream s, given as a parameter, starting from the last element.
    void print_from_bottom_to_top(std::ostream& s);

    // Siirtää tietorakenteen ensimmäisen alkion viimeiseksi.
    // Paluuarvona on false, jos pino oli tyhjä, muutoin true.
    //
    // Moves the first element of the data structure as the last one.
    // Returns false, if the data structure is empty, otherwise returns true.
    bool top_to_bottom();

    // Kääntää tietorakenteen sisällön päinvastaiseksi.
    // Reverses the content of the data structure as opposite.
    void reverse();

private:
    // Osoitin korttipinon päällimmäiseen korttiin (ÄLÄ MUUTA TÄTÄ NIMEÄ).
    // Pointer to the topmost card (DON'T CHANGE THE NAME OF THIS).
    std::shared_ptr<Card_data> top_;

    // Funktio, jota voit käyttää apuna metodin print_from_bottom_to_top
    // toteuttamisessa.
    //
    // Function that you can use in the implementing print_from_bottom_to_top.
    int recursive_print(std::shared_ptr<Card_data> top, std::ostream& s);
};

#endif // CARDS_HH
