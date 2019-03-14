// Luntraru Chris Grupa 135
// Compiler: MinGW64, standard c++17
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::shared_ptr;
using std::make_shared;
using std::for_each;
using std::istream;
using std::ostream;

class Application;
class Company;

enum Service {
    COST_CONTROL,
    DES_DRIVER,
    RENTAL,
    LEASING,
    COUNT
};

// reprezinta o comanda
class Trip {
    friend istream &operator >>(istream &is, Trip &t) {
       t.clear();

       int servCnt = 0;
       is >> servCnt;
       is >> t.mStart >> t.mEnd >> t.mCost >> t.mCompanyCode >> t.mInternational;
       for (int i = 0; i < servCnt; ++i) {
           int s;
           is >> s;
           switch (s) {
               case 0:
                   t.mEmployedServices.emplace_back(Service::COST_CONTROL);
                   break;
               case 1:
                   t.mEmployedServices.emplace_back(Service::DES_DRIVER);
                   break;
               case 2:
                   t.mEmployedServices.emplace_back(Service::RENTAL);
                   break;
               case 3:
                   t.mEmployedServices.emplace_back(Service::LEASING);
                   break;
               default:
                   throw std::runtime_error("BAD SERVICE CODE");
           }
       }

       return is;
    }

    friend ostream &operator <<(ostream &os, const Trip &t) {
        os << "Start: " << t.mStart << '\n';
        os << "End: " << t.mEnd << '\n';
        os << "Cost: " << t.mCost << '\n';
        os << "Company Code: " << t.mCompanyCode << '\n';
        os << "Is International: " << std::boolalpha << t.mInternational << '\n';

        for_each(t.mEmployedServices.begin(), t.mEmployedServices.end(), [&os](const Service &s) {
            switch (s) {
                case Service::COST_CONTROL:
                    os << "Cost control\n";
                    break;
                case Service::DES_DRIVER:
                    os << "Designated driver\n";
                    break;
                case Service::RENTAL:
                    os << "Rental\n";
                    break;
                case Service::LEASING:
                    os << "Leasing\n";
                    break;
                default:
                    throw std::runtime_error("BAD SERVICE CODE");
            }
        });

        return os;
    }

    string mStart;
    string mEnd;
    int mCost;
    int mCompanyCode;
    bool mInternational;
    vector<Service> mEmployedServices;

    void clear() {
        mStart = "";
        mEnd = "";
        mCost = -1;
        mCompanyCode = -1;
        mEmployedServices.clear();
    }

public:
    Trip() {
        mStart = "";
        mEnd = "";
        mCost = -1;
        mCompanyCode = -1;
        mInternational = false;
    }

    Trip(string start, string end, int cost, int compCode, bool international, vector<Service> serv) {
        mStart = start;
        mEnd = end;
        mCost = cost;
        mCompanyCode = compCode;
        mInternational = international;
        mEmployedServices = serv;
    }

    vector <Service> getServ() const {
        return mEmployedServices;
    }

    int getCost() const {
        return mCost;
    }

    int getCompCode() const {
        return mCompanyCode;
    }

    bool isInternational() const {
        return mInternational;
    }
};

// Transport de persoane
class Company {
protected:
    string mName;
    int mProfit;
    int mCompCode;
    int mPriceperKM;
public:
    Company(string name, int code, int price) {
        mName = name;
        mCompCode = code;
        mPriceperKM = price;
    }

    string getName() {
        return mName;
    }

    int getCode() {
        return mCompCode;
    }

    int getProfit() const {
        return mProfit;
    }

    int getDist(string st, string ed) const {
        return rand() % 100;
    }

    virtual void addTrip() = 0;

    virtual int getCost(string st, string ed, int flat) {
        return getDist(st, ed) * mPriceperKM + flat;
    };
};

// Cost control + desig driver
class C1Comp: public Company {
    int mDDFlat;
public:

    C1Comp(int DDFlat, string name, int code, int price) : Company(name, code, price) {
        mDDFlat = DDFlat;
    }

    int getCost(string st, string ed, bool isDD) {
        if (isDD) {
            return Company::getCost(st, ed, mDDFlat);
        } else {
            return Company::getCost(st, ed, 0);
        }
    }
};

// Rental + Op leasing
class C2Comp: public Company {

public:
    C2Comp(int rentalCost, string name, int code, int price) : Company(name, code, price) {

    }

    void rentalRequest() {

    }
};

// Marfa de volum mic + cost control
class C3Comp: public Company {
public:
    C3Comp(string name, int code, int price) : Company(name, code, price) {

    }
};

//Multinationala: marfa + DD + cost control + limuzina
class C4Comp: public Company {
public:
    C4Comp(string name, int code, int price) : Company(name, code, price) {

    }
};

// Limuzina etc
class C5Comp: public Company {
public:
    C5Comp(string name, int code, int price) : Company(name, code, price) {

    }
};


// singleton (aplicatia e considerata functionalitatea centralizata,
// nu ce are efectiv cineva in mana)
class Application {
    static shared_ptr<Application> ptr;

    vector<Trip> mTrips;
    vector<shared_ptr<Company>> mCompanies;

    Application() = default;

public:

    void printTripsByCompany() {
        sort(mTrips.begin(), mTrips.end(), [](const Trip &t1, const Trip &t2) {
            return t1.getCompCode() < t1.getCompCode();
        });

        for_each(mTrips.begin(), mTrips.end(), [](Trip &t) {
            cout << t << '\n';
        });

        cout << "_____________________________________________________\n";
    }

    void printCompaniesByDecreasingProfit() {
        sort(mCompanies.begin(), mCompanies.end(), [](const shared_ptr<Company> &t1, const shared_ptr<Company> &t2) {
            return t1->getProfit() > t2->getProfit();
        });

        for_each(mCompanies.begin(), mCompanies.end(), [](shared_ptr<Company> &t) {
            cout << t << '\n';
        });

        cout << "_____________________________________________________\n";
    }

    void printUsesOfService() {
        vector<int>count(Service::COUNT + 1, 0);
        for_each(mTrips.begin(), mTrips.end(), [&count](const Trip &t) {
            vector <Service> servOf = t.getServ();
            for_each(servOf.begin(), servOf.end(), [&count](const Service &s) {
                ++count[s];
            });
        });

        cout << "Uses of Cost Control: " << count[Service::COST_CONTROL] << '\n';
        cout << "Uses of Designated Driver: " << count[Service::DES_DRIVER] << '\n';
        cout << "Uses of Rental: " << count[Service::RENTAL] << '\n';
        cout << "Uses of Leasing: " << count[Service::LEASING] << '\n';
        cout << "_____________________________________________________\n";
    }
    ~Application() {
        mTrips.clear();
    }

    static shared_ptr<Application> getInstance() {
        if (ptr == nullptr) {
            ptr = make_shared<Application>(Application());
        }

        return ptr;
    }

    void addTrip(const Trip &trip) {
        mTrips.push_back(trip);
    }

    void requestCar(const Company &comp, string st, string ed, bool international, vector<Service> serv) {

    }
};

shared_ptr<Application>Application::ptr = nullptr;


int main() {
    shared_ptr<Application> app = Application::getInstance();
    int tripNr = 0;
    cin >> tripNr;
    // read trip as servicecnt, start, end, cost, company code, {services}
    for (int i = 0; i < tripNr; ++i) {
        Trip t;
        cin >> t;
        app->addTrip(t);
    }

    app->printTripsByCompany();
    app->printCompaniesByDecreasingProfit();
    app->printUsesOfService();


    return 0;
}
//Exemplu:
//2
//1 as fsa 231 4334 0 2
//2 sss ddd 22 531 0 0 1
