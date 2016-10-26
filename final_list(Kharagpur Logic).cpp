#include <bits/stdc++.h>
using namespace std ;
const int MAXN = 3001 ; // Max entries in the table
const int MAX_COLLEGES = 500 ; // variable says it all
typedef pair<int,pair<string,string> > node ;
bool taken[MAX_COLLEGES] ;
int ranks[MAXN] ;
string names[MAXN] , college[MAXN];
map<string,int> map_college_to_index ; // map every college to a unique index
set<node > remaining_teams ,remaining_teams2; // stores teams not yet selected
vector<node > final_list ; // final ranklist

/* Converts number to a string */
/* Because to_string does not work in MinGW */
string to_string(int num)
{
    string res = "" ;
    while(num > 0) {
        char digit = '0' + (num % 10) ;
        res += digit ;
        num /= 10 ;
    }
    reverse(res.begin() , res.end()) ;
    return res ;
}
/* Boring stuff */
string pad_zeros(int RANK)
{
    string res = to_string(RANK) ;
    int len = res.size() ;
    if(len == 1) {
        return "00"+res ;
    }
    else if(len == 2) {
        return "0" + res ;
    }
    return res ;
}
int main()
{
    freopen("data_amrita.in" , "r" , stdin) ;
    freopen("amrita_list.out" , "w" , stdout) ;
    int total_teams ;
    cin >> total_teams ;
    for(int i = 1 ; i <= total_teams ; ++i) {
        cin >> ranks[i] ;
        string temp ;
        getline(cin,temp);
        getline(cin,names[i]) ;
        getline(cin,college[i]) ;
    }
    int index = 1 ;
    for(int i = 1 ; i <= total_teams ; ++i) {
        if(map_college_to_index.find(college[i]) == map_college_to_index.end()) {
            map_college_to_index[college[i]] = index++ ;
        }
        remaining_teams.insert({ranks[i],{names[i],college[i]}}) ;
    }
    remaining_teams2 = remaining_teams ;
    for(;;)
    {
        if(remaining_teams.empty())
            break ;
        // find current top teams of all colleges
        for(int i = 1 ; i <= index ; ++i) {
            taken[i] = false ;
        }
        for(auto &entry : remaining_teams) {
            if(taken[map_college_to_index[entry.second.second]]) {
                continue ;
            }
            taken[map_college_to_index[entry.second.second]] = true ;
            final_list.push_back(entry) ;
            remaining_teams2.erase(remaining_teams2.find(entry)) ;
        }
        remaining_teams = remaining_teams2 ;
    }
    int final_rank = 1 ;
    cout << setw(5) << "RANK" << setw(10) << "TEAM" << setw(20) << "COLLEGE\n";
    for(auto &entry : final_list) {
        string temp = pad_zeros(final_rank++) ;
        cout << temp << "\t\t" << entry.second.first << "\t\t" << entry.second.second << '\n' ;
    }
    return 0 ;
}
