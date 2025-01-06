#include <iostream>
#include "Statistic.cpp"
using namespace std;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL);
typedef long long ll;
typedef long double ld;

int main(){
    fastio;
    DataAnalysis* analysis_chromecast = new DataAnalysis("Chromecast.csv");
    analysis_chromecast->Compute();
    analysis_chromecast->print_DataAnalysis_file();
    analysis_chromecast->print_DataAnalysis_file_for_Graphics();
    delete analysis_chromecast;

    DataAnalysis* analysis_smart_tv = new DataAnalysis("Smart-tv.csv");
    analysis_smart_tv->Compute();
    analysis_smart_tv->print_DataAnalysis_file();
    analysis_smart_tv->print_DataAnalysis_file_for_Graphics();
    delete analysis_smart_tv;
    return 0;
}