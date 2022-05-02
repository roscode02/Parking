#include<iostream>
#include<vector>
#include<map>
using namespace std;
class parking
{
    
    
    public:
    int total_spots;
    vector<int> spots;
    vector<int> allocated;
    map<int , int> vehicleHour;
    map<int , int> allocatedSpace;
    
    parking()
    {
        total_spots = 0;
    }
    parking(int n)
    {
        total_spots = n;
        spots = vector<int>(n);
        allocated = vector<int>(n);
    }
    pair<bool , int> checkiffull(string s)
    {
        int SpaceNeeded = ReturnSize(s);
        int allocationNumber = -1;
        for(int i= 0; i < allocated.size() ; i++)
        {
            bool SpaceFound =true;
            if(allocated[i] == 0)
            {
                for(int j = i+1 ; j < i + 1 +  SpaceNeeded  ; j++)
                {
                    if(j == allocated.size())
                    {
                        if(s == "bike")
                        {
                            SpaceFound = true;
                        }
                        else
                        {
                            SpaceFound = false;
                        }
                        break;
                    }
                    if(allocated[i+j] != 0)
                    {
                        SpaceFound = false;
                    }
                }
                if(SpaceFound)
                {
                    allocationNumber = i;
                    break;
                }
            }
        }
        if(allocationNumber >= 0)
        {
            return make_pair(true , allocationNumber);
        }
        else
        {
            return make_pair(false , allocationNumber);
        }

    }
    int ReturnSize(string type);
    void assignarea(string type)
    {
        pair<bool , int> find = checkiffull(type);
        if(find.first == false)
        {
            cout<<"\n Sorry space cant be allocated \n ";
        }
        else
        {
            cout<<"\n Park at parking spot :- "<<find.second;
            int id , hr;
            cout<<"\n Enter vehicle id :- ";
            cin>>id;
            cout<<"\n Enter hour :- ";
            cin>> hr;
            vehicleHour[id] = hr;
            int SpaceNeeded = ReturnSize(type);
            for(int i = find.second ; i < find.second + SpaceNeeded ; i++)
            {
                allocated[i] = 1;
            }
            cout<<"\n Current parking space looks like :- ";
            for(auto x: allocated)
            {
                cout<<x;
            }
            cout<<endl;
            allocatedSpace[id] = find.second;
        }
    }
};
int parking::ReturnSize(string type)
{
    if(type == "Car" or type == "car")
    {
        return 2;
    }
    else if( type == "Bus" or type == "bus")
    {
        return 4;
    }
    else if( type == "Bike" or type == "bike")
    {
        return 1;
    }
    else
    {
        cout<<"\n Enter valid vehicle type";
    }
}
class checkout : public parking{
    int cost;
    int ExitTime;
    public:
    checkout()
    {
        cost = 0;
    }
    checkout(int n)
    {
        total_spots = n;
        spots = vector<int>(n);
        allocated = vector<int>(n);
    }
    void checkOut(string type , int uid)
    {
        int outHr , Charge;
        cout<<"\n Enter check out time :- ";
        cin>>outHr;
        if(vehicleHour.find(uid) != vehicleHour.end())
        {
            int hr = vehicleHour[uid];
            Charge = findCharge(type , hr);
            int spaceAllocated = allocatedSpace[uid];
            int Space = ReturnSize(type);
            cout<<"\n Total cost will be "<<findCharge(type , outHr - hr)<<"\n";
            for(int i= spaceAllocated ; i < spaceAllocated + Space ; i++)
            {
                allocated[i] = 0;
            }
            cout<<"\n Current parking space looks like :- ";
            for(auto x: allocated)
            {
                cout<<x;
            }
            cout<<endl;
        }
        else
        {
            cout<<"\n Enter valid car number \n";
        }
    }
    int findCharge(string s , int id);
};
int checkout :: findCharge(string s , int Hr)
{
    if(s == "Car" or s == "car")
    {
        return 56*Hr;
    }
    else if( s == "Bus" or s == "bus")
    {
        return 100*Hr;
    }
    else if( s == "Bike" or s == "bike")
    {
        return 34*Hr;
    }
    else
    {
        cout<<"\n Enter valid vehicle type \n";
    }
}
int main()
{
    int spots;
    cout<<"\n Enter the total spots for parking :- ";
    cin>>spots;
    checkout c(spots);
    int entermore = true;
    cout<<"\n Only bike , car , bus can be parked \n bike will take 1 space \n car will take 2 space \n Bus will take 4 space";
    cout<<"\n When asked for type enter bike , car , bus \n\n" ;
    while(entermore)
    {
        int select=0;
        string type;
        int uid=0;
        cout<<"\n Available options to search \n";
        cout<<"\n 1.) to park the vehicle \n";
        cout<<"\n 2.) to remove the vehicle \n";
        cout<<"\n 3.) exit";
        cout<<endl;
        cout<<"\n Choose among the options :- ";
        cin>>select;
        switch (select)
        {
        case 1:
            cout<<"\n Enter type of vehicle :- ";
            cin>>type;
            c.assignarea(type);
            break;
        case 2:
            cout<<"\n Enter type of vehicle :- ";
            cin>>type;
            cout<<"\n Enter id of vehicle :- ";
            cin>>uid;
            c.checkOut(type , uid);
            break;
        case 3:
            exit(0);
            break;    
        default:
            break;
        }

    }
    return 0;
}