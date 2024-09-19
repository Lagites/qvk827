#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

/* Kauppaketjut
 *
 * Kuvaus:
 *   Ohjelma lukee tietoja kauppaketjuista syötetiedostosta, jonka rivit
 * ovat muotoa:
 * kauppaketjun_nimi;kaupan_sijainti;tuotteen_nimi;tuotteen_hinta.
 * Ohjelma tarkistaa, että tiedoston kultakin riviltä löytyy edellä
 * mainitut neljä datakenttää.
 *   Tiedostosta löytyvät tiedot kerätään sopivaan tietorakenteeseen, joka
 * koostuu STL:n säiliöistä ja tietueista. Tämän jälkeen käyttäjä voi
 * tehdä hakuja tietorakenteeseen käyttämällä komentoja chains, stores,
 * selection, cheapest ja products. Komennoilla on eri määrä parametreja,
 * ja ohjelma tarkistaa, että käyttäjä antoi oikean määrän parametreja
 * ja että parametrit (kauppaketjun nimi, kaupan sijainti,  tuotteen nimi)
 * löytyvät tietorakenteesta.
 *
 * Ohjelman toiminnan voi lopettaa komennolla quit.
 *
 * Ohjelman kirjoittaja
 * Nimi: Jukka Välimäki
 * Opiskelijanumero: 153036662
 * Käyttäjätunnus: qvk827
 * E-Mail: jukka.valimaki@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta (jos sellaisia on):
 * Ohjelma käyttää std-kirjaston map-rakenteita tietojen säilytykseen ja hakemiseen.
 * Map järjestää tietueet iteroidessa automaattisesti aakkosjärjestykseen ja tekee hakemisesta helpompaa
 * Chains-sisältää avainparin kauppaketjun nimi ja arvona map-rakenteen kaupoista.
 * Kauppojen ei tarvitsisi olla struct-rakenteessa, koska ne sisältävät vain map-tietueen tuotteista,
 * mutta on nätimpi näin.
 *
 * */

using namespace std;

const char SEPARATOR = ';';
const string OUT_OF_STOCK = "out-of-stock";

//product_name on mukana structissa erityisvaatimusten johdosta, mutta sama tieto on map-rakenteen
//avaimena niin ohjelmassa sitä käytetään ainoastaan tietojen tulostusfunkioissa.
struct Product {
    string product_name;
    double price;
};

struct Shop{
    map<string, Product> products;
};

/**
 * Pilkkoo annetun rivin listaksi erotinmerkillä
 *
 * @param line Käsiteltävä tekstirivi
 * @param separator Erotinmerkki
 * @return Lista erotelluista merkkijonoista
 */
std::vector< std::string > split(std::string& line, char separator)
{
    std::vector< std::string > result = { };
    std::string::size_type index = 0;
    std::string::size_type prevPos = 0;
    while(true){
        index  = line.find(separator,index);
        if(index != std::string::npos){
            std::string subStr = line.substr(prevPos,index - prevPos);
            //std::cout << "index: " << index << " subStr " << subStr << " Size:" << subStr.size() <<  std::endl;
            if(subStr.size() > 0 )
                result.push_back(subStr);
        }
        else{
            std::string subStr = line.substr(prevPos,line.size() - prevPos);
            if(subStr.size() > 0 )
                result.push_back(subStr);
            break;
        }
        index++;
        prevPos = index;
    }
    line.find(separator);
    return result;
}

/**
 * Käsittelee annetun rivin ja lisää tiedot map-tietueeseen.
 *
 * @param chains Tietue, johon arvot tallennetaan
 * @param line Käsiteltävä tekstirivi
 * @return onnistuiko rivin käsittely
 */
bool readRowData(map<string,map<string,Shop>>& chains, string line)
{
    vector<string> lines = split(line, SEPARATOR);
    //Jos rivi ei sisällä oikeaa määrää kenttiä, palautetaan virhe
    if(lines.size() != 4){
        return false;
    }

    string chain = lines.at(0);
    string shop = lines.at(1);
    string product = lines.at(2);
    string price = lines.at(3);    

    //Jos jokin arvo on tyhjä, palautetaan virhe
    if(chain.length() == 0 || shop.length() == 0 || product.length() == 0 || price.length() == 0){
        return false;
    }

    double priceNum;
    if (price.compare(OUT_OF_STOCK) == 0){
        priceNum = __DBL_MAX__;
    }
    else{
        priceNum = stod(price);
    }

    //Etsitään löytyykö kauppaketjua jo tietueesta. Jos löytyy, etsitään kauppa, muuten lisätään uusi kauppaketju, kauppa ja tuote
    map<string,map<string,Shop>>::iterator chainIter = chains.find(chain);
    if(chainIter  != chains.end()){
        //Etsitään löytyykö kauppaa jo tietueesta. Jos löytyy, etsitään tuote, muuten lisätään uusi kauppa ja tuote
        map<string,Shop>::iterator shopIter = chainIter ->second.find(shop);
        if(shopIter != chainIter->second.end()){
            //Etsitään löytyykö tuotetta jo tietueesta. Jos löytyy, päivitetään hinta, muuten lisätään uusi tuote
            map<string,Product>::iterator productIter = shopIter->second.products.find(product);
            if(productIter != shopIter->second.products.end()){
                productIter->second.price = priceNum;
            }
            else{
                shopIter->second.products.insert({product, Product{product,priceNum}});
            }
        }
        else{
            Shop newShop = {};
            newShop.products.insert({product, Product{product,priceNum}});
            chainIter->second.insert({shop, newShop});
        }
    }
    else{
        Shop newShop = {};
        newShop.products.insert({product, Product{product,priceNum}});
        pair <string,map<string,Shop>> newChain = {};
        newChain.first = chain;
        newChain.second.insert({shop, newShop});
        chains.insert(newChain);
    }

    return true;
}

/**
 * Palauttaa hinnan kahden desimaalin tarkkuudella tai 'out of stock' jos hinta on doublen maksimiarvo
 *
 * @param price hinta numerona
 * @return hinta stringinä
 */
string getprice(double price)
{
    string priceStr;
    if(price == __DBL_MAX__){
        priceStr = "out of stock";
    }
    else{
        stringstream ss;
        ss << fixed << setprecision(2) << price;
        priceStr = ss.str();
    }
    return priceStr;
}

/**
 * Tulostaa näytölle tunnetut kauppaketjut
 *
 * @param chains Tietue, josta kauppaketjut luetaan
 */
void printChains(map<string,map<string,Shop>> chains)
{
    map<string,map<string,Shop>>::iterator iter = chains.begin();
    while(iter  != chains.end()){
        cout << iter->first << endl;
        iter++;
    }
}

/**
 * Tulostaa näytölle kauppaketjun kaupat
 *
 * @param chains Tietue, josta kauppaketjut luetaan
 * @param chain Haluttu kauppaketju
 */
void printStores(map<string,map<string,Shop>> chains, string chain)
{
    map<string,map<string,Shop>>::iterator chainIter = chains.find(chain);
    if(chainIter != chains.end()){
        map<string,Shop>::iterator shopIter = chainIter->second.begin();
        while(shopIter  != chainIter->second.end()){
            cout << shopIter->first << endl;
            shopIter++;
        }
    }
    else{
        cout << "Error: unknown chain name" << endl;
    }
}

/**
 * Tulostaa näytölle kauppaketjun kaupat
 *
 * @param chains Tietue, josta kauppaketjut luetaan
 * @param chain Kauppaketju, josta kauppa etsitään
 * @param shop Kauppa, jonka valikoima tulostetaan
 */
void printSelection(map<string,map<string,Shop>> chains, string chain, string shop)
{
    map<string,map<string,Shop>>::iterator chainIter = chains.find(chain);
    if(chainIter != chains.end()){
        map<string,Shop>::iterator shopIter = chainIter->second.find(shop);
        if(shopIter  != chainIter->second.end()){
            map<string,Product>::iterator productIter = shopIter->second.products.begin();
            while(productIter != shopIter->second.products.end()){
                cout << productIter->second.product_name << " "  << getprice(productIter->second.price) << endl;
                productIter++;
            }
        }
        else{
            cout << "Error: unknown store" << endl;
        }
    }
    else{
        cout << "Error: unknown chain name" << endl;
    }
}

/**
 * Tulostaa näytölle tuotteen halvimman hinnan ja kaupan mistä se löytyy.
 * Tulostaa viestin jos tuote on tuntematon tai loppu
 *
 * @param chains Tietue, josta kauppaketjut luetaan
 * @param product Tuote, jota etsitään
 */
void printCheapest(map<string,map<string,Shop>> chains, string product)
{
    double price = __DBL_MAX__;
    bool productFound = false;
    set<string> shops = {};
    map<string,map<string,Shop>>::iterator chainIter = chains.begin();
    while(chainIter  != chains.end()){
        map<string,Shop>::iterator shopIter = chainIter->second.begin();
        while(shopIter  != chainIter->second.end()){
            map<string,Product>::iterator productIter = shopIter->second.products.find(product);
            if(productIter != shopIter->second.products.end()){
                if(!productFound)
                    productFound = true;
                if(productIter->second.price == __DBL_MAX__)
                    break;
                if(productIter->second.price == price)
                    shops.insert(chainIter->first + " " + shopIter->first);
                else if(productIter->second.price < price){
                    price = productIter->second.price;
                    shops.clear();
                    shops.insert(chainIter->first + " " + shopIter->first);
                }
            }
            shopIter++;
        }
        chainIter++;
    }
    if(!productFound)
        cout << "The product is not part of product selection" << endl;
    else if(productFound && shops.size() == 0)
        cout << "The product is temporarily out of stock everywhere" << endl;
    else{
        cout << getprice(price) << " euros" << endl;
        for(string shop : shops){
           cout << shop << endl;
        }
    }
}

/**
 * Tulostaa näytölle kaikki listatut tuotteet joka kaupasta.
 *
 * @param chains Tietue, josta kauppaketjut luetaan
 */
void printProducts(map<string,map<string,Shop>> chains)
{
    set<string> products = {};
    map<string,map<string,Shop>>::iterator chainIter = chains.begin();
    while(chainIter  != chains.end()){
        map<string,Shop>::iterator shopIter = chainIter->second.begin();
        while(shopIter  != chainIter->second.end()){
            map<string,Product>::iterator productIter = shopIter->second.products.begin();
            while(productIter != shopIter->second.products.end()){
                if(products.find(productIter->first) == products.end())
                    products.insert(productIter->second.product_name);
                productIter++;
            }
            shopIter++;
        }
        chainIter++;
    }

    for(string product : products){
       cout << product << endl;
    }
}

int main()
{
    string inputFile;
    cout << "Input file: ";
    getline(std::cin, inputFile);

    ifstream reader(inputFile);
    if(!reader){
        cout << "Error: the input file cannot be opened" << endl;
        return EXIT_FAILURE;
    }

    string line;
    map<string,map<string,Shop>> chains= {};

    while(getline(reader,line)){
        if(!readRowData(chains,line)){
            cout << "Error: the input file has an erroneous line" << endl;
            return EXIT_FAILURE;
        }
    }
    reader.close();

    while(true){
        cout << "> ";
        string command;
        getline(std::cin, command);

        vector<string> lines = split(command, ' ');
        if(lines.size() == 0)
            continue;

        if(lines.at(0).compare("quit") == 0){
            break;
        }

        else if(lines.at(0).compare("chains") == 0){
            if(lines.size() != 1){
                cout << "Error: error in command " << lines.at(0) << endl;
                continue;
            }
            printChains(chains);
        }
        else if(lines.at(0).compare("stores") == 0){
            if(lines.size() != 2){
                cout << "Error: error in command " << lines.at(0) << endl;
                continue;
            }
            printStores(chains,lines.at(1));
        }
        else if(lines.at(0).compare("selection") == 0){
            if(lines.size() != 3){
                cout << "Error: error in command " << lines.at(0) << endl;
                continue;
            }
            printSelection(chains,lines.at(1),lines.at(2));
        }
        else if(lines.at(0).compare("cheapest") == 0){
            if(lines.size() != 2){
                cout << "Error: error in command " << lines.at(0) << endl;
                continue;
            }
            printCheapest(chains,lines.at(1));
        }
        else if(lines.at(0).compare("products") == 0){
            if(lines.size() != 1){
                cout << "Error: error in command " << lines.at(0) << endl;
                continue;
            }
            printProducts(chains);
        }
        else{
            cout << "Error: unknown command: " << command << endl;
        }
    }


    return EXIT_SUCCESS;
}
