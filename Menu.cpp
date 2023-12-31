
#include <iostream>
#include <iomanip>
#include "Menu.h"
#include "Statistics.h"
#include "Filter.h"

using namespace std;

Menu::Menu() {}

Graph *Menu::getGraph() { return graph; }
AirTable *Menu::getAirTable() { return airTable; }
CityTable *Menu::getCityTable() { return cityTable; }

/**
 * @brief Abre o menu principal.
*/
void Menu::openMenu() {
    cout << setw(25) << "Welcome!" << endl;
    initialOptions();
}

/**
 * @brief Fecha o menu.
*/
int Menu::closeMenu() {
    return 0;
}

/**
 * @brief Apresenta as opções inicais do menu.
*/
void Menu::initialOptions() {
    cout << "What do you want to do?" << endl;
    cout << "1. Statistics\n" << "2. Best flight option\n" << "3. Filter\n" << "4. Quit\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){statistics();}
    if (option == "2"){sourceLocation();}
    if (option == "3"){filter();}
    if (option == "4"){closeMenu();}
}


/**
 * @brief Apresenta as opções de estatístcas do menu.
*/
void Menu::statistics() {
    cout << "What do you want to consult?" << endl;
    cout << "1.Numbers\n" << "2.Others\n" << "3.Go back\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){statisticsNumbers();}
    if (option == "2"){statisticsOthers();}
    if (option == "3"){initialOptions();}
}

/**
 * @brief Apesenta as opções de estatísticas que retornam um número.
 * Esta função também retorna os dados pedidos.
*/
void Menu::statisticsNumbers() {
    cout << "Which number do you want to see?" << endl;
    cout << "1.Total number of airports\n" << "2.Total number of flights\n" << "3.Number of flights and airlines out of an airport\n"
            << "4.Number of flights\n" << "5.Number of countries\n" << "6.Number of destinations for an airport\n"
            << "7.Number of destinations for an airport with X stops\n" << "8.Go back\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4" || option == "5" || option == "6" || option == "7" || option == "8")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1") { Statistics::totalNumberAirports(graphAtual); askContinue(); }
    if (option == "2") { Statistics::totalNumberFlights(graphAtual); askContinue(); }
    if (option == "3") { Airport airport = askAirport(); Statistics::numFlightOutAir(graphAtual, airport); askContinue(); }
    if (option == "4") { statistics4(); }
    if (option == "5") { statistics5(); }
    if (option == "6") { Airport airport = askAirport(); string mode = askMode(); Statistics::numDestinationsAirport(graphAtual, airport, mode); askContinue(); }
    if (option == "7") { Airport airport = askAirport(); string mode = askMode(); int x = askX(); Statistics::numberReachable(graphAtual, airport, x, mode); askContinue(); }
    if (option == "8") { statistics(); }
}

/**
 * @brief Apresenta as opções relacionadas ao número de voos.
 * Esta função também retorna os dados pedidos.
*/
void Menu::statistics4() {
    cout << "Per what?" << endl;
    cout << "1.Per city\n" << "2.Per airline\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){ string city = askCity(); Statistics::flightsPerCity(graphAtual, city); askContinue();}
    if (option == "2"){ Airline airline = askAirline(); Statistics::flightsPerAirline(graphAtual, airline); askContinue();}
}

/**
 * @brief Apresenta as opções relacionadas ao número de países.
 * Esta função também retorna os dados pedidos.
*/
void Menu::statistics5() {
    cout << "1.That a given airport flies to\n" << "2.That a given city flies to\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1") { Airport airport = askAirport(); Statistics::countriesPerAirport(graphAtual, airport); askContinue(); }
    if (option == "2") { string city = askCity(); Statistics::countriesPerCity(graphAtual, city); askContinue(); }
}

/**
 * @brief Apresenta as opções de escolha de destino.
 * @return string - Retorna string com a opção escolhida.
*/
string Menu::askMode() {
    cout << "Which destinations?" << endl;
    cout << "1.Airports\n" << "2.Cities\n" << "3.Countries\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1") { return "airport"; }
    if (option == "2") { return "city"; }
    if (option == "3") { return "country"; }
    return " ";
}

/**
 * @brief Verifica se uma string pode ser convertida para inteiro.
 * @param s - string pedida.
 * @return true se a string poder ser convertida para inteiro, else false
*/
bool isInteger(const std::string& s) {
    std::istringstream iss(s);
    int num;
    iss >> num;
    return iss.eof() && !iss.fail();
}

/**
 * @brief Verifica se uma string pode ser convertida para double.
 * @param s - string pedida.
 * @return true se a string poder ser convertida para double, else false.
*/
bool isDouble(const std::string &s) {
    try {
        std::stod(s);
        return true;
    } catch (...){
        return false;
    }
}

/**
 * @brief Pergunta número máximo de paragens.
 * @return int - Retorna número máximo de paragens convertido para inteiro.
*/
int Menu::askX() {
    cout << "Number of maximum stops: ";
    string n; cin >> n;

    while (!isInteger(n)) {
        cout << "Invalid, try again. Number of maximum stops: ";
        cin >> n;
    }

    cout << " " << endl;
    return stoi(n);
}

/**
 * @brief Exibe opções de estatísticas.
 *
 * Permite aos usuários escolher entre várias operações.
 */
void Menu::statisticsOthers() {
    cout << "What do you want to see?" << endl;
    cout << "1.Flight trip(s) with the greatest number of stops\n"
         << "2.Top-k airport with the greatest number of flights (air traffic capacity)\n"
         << "3.Airports that are essential to the networks circulation capability\n"
         << "4.Go back\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){ Statistics::maxTrip(graphAtual); askContinue(); }
    if (option == "2"){ int k = askK(); Statistics::topKAirTraffic(graphAtual,k-1); askContinue(); }
    if (option == "3"){ Statistics::airport_art(graphAtual); askContinue(); }
    if (option == "4"){ statistics(); }
    cout << " " << endl;
}

/**
 * @brief Pergunta ao usuário número de airports para a pesquisa.
 *
 * @return int - Retorna o valor inteiro de airports especificado pelo usuário.
 */
int Menu::askK(){
    cout << "By what k-airport do you wish to search for?" << endl;
    cout << "Number: ";
    string option; cin >> option;

    while (!isInteger(option) || (stoi(option) <= 0)) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    return stoi(option);
}

/**
 * @brief Gerencia opções de filtros de companhias aéreas.
 *
 * Permite aos usuários ativar, desativar ou alterar filtros de companhias aéreas.
 */
void Menu::filter() {
    cout << "Filter search by airlines. ";
    if(airlineFilter) cout<<"(ON) \n"; else cout<<"(OFF) \n";
    if(airlineFilter) cout << "1.Change filter\n"; else cout << "1.Activate filter\n";
    cout << "2.Deactivate filter\n"
         << "3.Go back\n";

    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2"|| option == "3" )) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }
    cout << " " << endl;
    if (option == "1"){airlineFilter = true; activateFilter();}
    if (option == "2"){airlineFilter = false; graphAtual = graph; filter();}
    if (option == "3"){initialOptions();}
}

/**
 * @brief Ativa o filtro de companhias aéreas.
 *
 * Permite aos usuários especificar companhias aéreas para as opções serem filtradas.
 */
void Menu::activateFilter() {
    cout << "Which airlines do you wish to travel with? "<<"(ex: Ryanair,TAP Air Portugal)\n";
    cout << "Airlines: ";
    string names; getline(cin,names);
    getline(cin, names);
    istringstream iss(names);
    string airline;
    while (getline(iss, airline, ',')) {
        while (airTable->findAirlineByName(airline) == nullptr) {
            cout << "Invalid input. "<< "Airlines: ";
            getline(cin, names);
            istringstream newIss(names);
            getline(newIss, airline, ',');
        }
    }
    auto airlineCodes = Filter::airlineFilter(names, airTable);
    graphAtual = Filter::airlineFilterGraph(airlineCodes, graph, airTable);
    cout << " " << endl;
    filter();
}

/**
 * @brief Pede ao usuário para especificar o aeroporto.
 *
 * Os usuários podem pesquisar aeroportos por código ou por nome.
 * @return Airport - Retorna o aeroporto selecionado.
 */
Airport Menu::askAirport() {
    cout << "How do you wish to search for the airport?" << endl;
    cout << "1.By the airport code\n" << "2.By the airport name\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){ return askAirportCode(); }
    if (option == "2"){ return askAirportName(); }
    return Airport("DSM");
}

/**
 * @brief Pede ao usuário o código de um aeroporto.
 *
 * @return Airport - Retorna o aeroporto correspondente ao código.
 */
Airport Menu::askAirportCode() {
    cout << "Airport code: ";
    string code; cin >> code;

    auto itCode = graphAtual->findVertexCode(code);
    while (itCode == nullptr) {
        cout << "Invalid, try again. Airport code: ";
        cin >> code;
        itCode = graphAtual->findVertexCode(code);
    }
    cout << " " << endl;
    return itCode->getAirport();
}

/**
 * @brief Pede ao usuário o nome de um aeroporto.
 *
 * @return Airport - Retorna o aeroporto correspondente ao nome.
 */
Airport Menu::askAirportName() {
    bool first = true;
    string name; getline(cin, name);

    auto itName = graphAtual->findVertexName(name);
    while (itName == nullptr) {
        if (first) { cout << "Airport name: "; first = false; }
        else cout << "Invalid, try again. Airport name:  ";
        getline(cin, name);
        itName = graphAtual->findVertexName(name);
    }
    cout << " " << endl;
    return itName->getAirport();
}

/**
 * @brief Pergunta ao usuário para especificar uma airline.
 *
 * Os usuários podem pesquisar companhias aéreas por código ou por nome.
 * @return Airline - Retorna airline selecionada.
 */
Airline Menu::askAirline() {
    cout << "How do you wish to search for the airline?" << endl;
    cout << "1.By the airline code\n" << "2.By the airline name\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "1"){ return askAirlineCode(); }
    if (option == "2"){ return askAirlineName(); }
    return Airline();
}

/**
 * @brief Pergunta ao usuário pelo código de uma airline.
 *
 * @return Airline - Retorna airline correspondente ao código.
 */
Airline Menu::askAirlineCode() {
    cout << "Airline code: ";
    string code; cin >> code;

    auto itCode = airTable->findAirline(code);
    while (itCode == nullptr) {
        cout << "Invalid, try again. Airline code: ";
        cin >> code;
        itCode = airTable->findAirline(code);
    }
    cout << " " << endl;
    return *itCode;
}

/**
 * @brief Pergunta ao usuário pelo nome de uma airline.
 *
 * @return Airline - Retorna airline correspondente ao nome.
 */
Airline Menu::askAirlineName() {
    bool first = true;
    string name; getline(cin, name);

    auto itName = airTable->findAirlineByName(name);
    while (itName == nullptr) {
        if (first) { cout << "Airline name: "; first = false; }
        else cout << "Invalid, try again. Airline name:  ";
        getline(cin, name);
        itName = airTable->findAirlineByName(name);
    }
    cout << " " << endl;
    return *itName;
}

/**
 * @brief Pergunta ao usuário por um nome de cidade.
 *
 * @return string - Retorna o nome da cidade especificado pelo usuário.
 */
string Menu::askCity() {
    bool first = true;
    string city; getline(cin, city);

    bool itCity = cityTable->find(city);
    while (!itCity) {
        if (first) { cout << "City: "; first = false; }
        else cout << "Invalid, try again. City: ";
        getline(cin, city);
        itCity = cityTable->find(city);
    }

    cout << " " << endl;
    return city;
}

/**
 * @brief Gerencia o local de origem para uma viagem.
 *
 * Permite aos usuários especificar a origem da viagem.
 */
void Menu::sourceLocation() {
    cout << "How do you want to specify your source location?" << endl;
    cout << "1.Airport code\n" << "2.Airport name\n" << "3.City\n" << "4.Geographical coordinates\n" << "5.Go back\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4" || option == "5")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }
    cout << " " << endl;
    vector<Airport> airportsSource;
    if (option == "1"){
        airportsSource.push_back(askAirportCode());
        cout << " " << endl;
        destinationLocation(airportsSource);
    }
    if (option == "2"){
        airportsSource.push_back(askAirportName());
        cout << " " << endl;
        destinationLocation(airportsSource);
    }
    if (option == "3"){
        airportsSource = Filter::AirportsCity(graphAtual, askCity());
        cout << " " << endl;
        destinationLocation(airportsSource);
    }
    if (option == "4"){
        cout << "Latitude: ";
        string latitude; cin >> latitude;

        while (!isDouble(latitude) || (stod(latitude) <= 0)) {
            cout << "Invalid input. Latitude: ";
            cin >> latitude;
        }

        cout << " " << endl;
        double lat = stod(latitude);

        cout << "Longitude: ";
        string longitude; cin >> longitude;

        while (!isDouble(longitude) || (stod(longitude) <= 0)) {
            cout << "Invalid input. Longitude: ";
            cin >> longitude;
        }

        cout << " " << endl;
        double lon = stod(longitude);

        airportsSource = Filter::geographicalLocation(graphAtual, lat, lon);

        cout << "Closest Airport:"<<endl;
        for (auto air: airportsSource)
            cout<<air.getCode()<<endl;

        cout << " " << endl;
        destinationLocation(airportsSource);
    }
    if (option == "5") {initialOptions();}

}

/**
 * @brief Gerencia o local de destino para uma viagem.
 *
 * Permite aos usuários especificar o destino de sua jornada.
 * @param airportsSource - vetor de aeroportos de origem.
 */
void Menu::destinationLocation(vector<Airport> airportsSource) {
    cout << "How do you want to specify your destination location?" << endl;
    cout << "1.Airport code\n" << "2.Airport name\n" << "3.City\n" << "4.Geographical coordinates\n" << "5.Go back\n";
    cout << "Option: ";
    string option; cin >> option;

    while (!(option == "1" || option == "2" || option == "3" || option == "4" || option == "5")) {
        cout << "Invalid input. Option: ";
        cin >> option;
    }
    cout << " " << endl;
    vector<Airport> airportsDest;
    if (option == "1"){
        airportsDest.push_back(askAirportCode());
    }
    if (option == "2"){
        airportsDest.push_back(askAirportName());
    }
    if (option == "3"){
        airportsDest = Filter::AirportsCity(graphAtual, askCity());
    }
    if (option == "4"){
        cout << "Latitude: ";
        string latitude; cin >> latitude;

        while (!isDouble(latitude) || (stod(latitude) <= 0)) {
            cout << "Invalid input. Latitude: ";
            cin >> latitude;
        }

        cout << " " << endl;
        double lat = stod(latitude);

        cout << "Longitude: ";
        string longitude; cin >> longitude;

        while (!isDouble(longitude) || (stod(longitude) <= 0)) {
            cout << "Invalid input. Longitude: ";
            cin >> longitude;
        }

        cout << " " << endl;
        double lon = stod(longitude);

        airportsDest = Filter::geographicalLocation(graphAtual, lat, lon);

        cout << "Closest Airports:"<<endl;
        for (auto air: airportsDest){
            cout<<air.getCode()<<endl;
        }
    }
    if (option == "5") { sourceLocation(); }
    cout << " " << endl;

    if (option != "5" && Filter::bestOptionNoFilters(graphAtual, airportsSource, airportsDest)) {
        cout << " " << endl;
        cout << "Do you want to filter your options by minimum number of different airlines?" << endl;
        cout << "Yes\n" << "No\n";
        cout << "Answer: ";
        string op;
        cin >> op;

        while (!(op == "Yes" || op == "No" || op == "yes" || op == "no")) {
            cout << "Invalid input. Answer: ";
            cin >> op;
        }

        cout << " " << endl;
        if (op == "Yes" || op == "yes")
            Filter::minAirlines(graphAtual, airportsSource, airportsDest);
    }
    askContinue();
}

/**
 * @brief Pergunta ao usuário se ele deseja continuar.
 *
 * Oferece uma opção para os usuários continuarem ou saírem do programa.
 */
void Menu::askContinue() {
    cout << " " << endl;
    cout << "---------------------------------\n";
    cout << "Do you want to do something else?\n";
    cout << "Yes\n" << "No\n" ;
    cout << "Answer: ";
    string option; cin >> option;

    while (!(option == "Yes" || option == "No" || option == "yes" || option == "no")) {
        cout << "Invalid input. Answer: ";
        cin >> option;
    }

    cout << " " << endl;
    if (option == "Yes" || option == "yes") { initialOptions(); }
    if (option == "No" || option == "no") { closeMenu(); }
}
