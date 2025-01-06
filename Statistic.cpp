#include<bits/stdc++.h>
#include <sys/resource.h>
#include <cstdlib>
using namespace std;
#define fastio ios_base::sync_with_stdio(false),cin.tie(NULL);
typedef long long ll;
typedef long double ld;


//Biblioteca

struct DataAnalysis{
    string device_type;
    int data_quant;
    int bins;
    map<ll,int> compression_id;
    string inputFile;
    vector<vector<pair<ld,int> > > hour_up,hour_down;
    vector<ld> General_Ava_Var_StaDev_up;
    vector<vector<ld> > Hour_Ava_Var_StaDev_up;
    vector<ld> General_Ava_Var_StaDev_down;
    vector<vector<ld> > Hour_Ava_Var_StaDev_down;
    vector<pair<int,ld>> max_traffic_up,max_traffic_down;

public:
    DataAnalysis(string filename) {
        hour_up.resize(24);
        hour_down.resize(24);
        General_Ava_Var_StaDev_up.resize(3);
        Hour_Ava_Var_StaDev_up.resize(24, vector<ld>(3));
        General_Ava_Var_StaDev_down.resize(3);
        Hour_Ava_Var_StaDev_down.resize(24, vector<ld>(3));
        data_quant = 0;

        inputFile = filename;
        device_type = filename;

        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Erro ao abrir o arquivo: " << filename << endl;
            exit(1);
        }

        string line;
        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);
            string device_id_str, date_hour, bytes_up_str, bytes_down_str;
            getline(ss, device_id_str, ',');
            getline(ss, date_hour, ',');
            getline(ss, bytes_up_str, ',');
            getline(ss, bytes_down_str, ',');

            ll device_id = stoll(device_id_str);
            ld bytes_up = stold(bytes_up_str);
            ld bytes_down = stold(bytes_down_str);
            int hour = stoi(date_hour.substr(11, 2));

            if (hour < 0 || hour >= 24) {
                cerr << "Erro: hora fora do intervalo [0, 23]" << hour << endl;
                exit(1);
            }

            data_quant++;
            if (compression_id.find(device_id) == compression_id.end()) {
                compression_id[device_id] = compression_id.size() + 1;
            }

            if (bytes_up > 0) {
                bytes_up = log10(bytes_up);
            }
            if (bytes_down > 0) {
                bytes_down = log10(bytes_down);
            }

            hour_up[hour].emplace_back(bytes_up, compression_id[device_id]);
            hour_down[hour].emplace_back(bytes_down, compression_id[device_id]);
        }

        bins = 1 + log2(data_quant);
    }

    void Avareage(vector<vector<pair<ld,int> > > &data,vector<vector<ld> > &hour_data, vector<ld>&general_data){
        ld sum_t = 0,sum_n = 0;
        for(int i = 0; i < data.size(); i++){
            ld sum_i = 0;
            for(int j = 0; j < data[i].size(); j++){
                sum_i += data[i][j].first;
            }
            if(data[i].size() == 0) hour_data[i][0] = 0;
            else hour_data[i][0] = ld(sum_i/data[i].size());
            sum_t += sum_i; sum_n += data[i].size();
        }
        general_data[0] = ld(sum_t/sum_n);
}


    void Variance(vector<vector<pair<ld,int> > > &data, vector<vector<ld> > &hour_data, vector<ld>&general_data){
        ld sum_t = 0,sum_n = 0;;
        for(int i = 0; i < data.size(); i++){
            ld sum_i = 0;
            for(int j = 0; j < data[i].size(); j++){
                sum_i += ((data[i][j].first - hour_data[i][0]) * (data[i][j].first - hour_data[i][0]));
            }
            if(data[i].size() == 0) hour_data[i][1] = 0;
            else hour_data[i][1] = ld(sum_i/data[i].size());
            sum_t += sum_i; sum_n += data[i].size();
        }
        general_data[1] = ld(sum_t/sum_n);
    }


    void Standard_Deviation(vector<vector<ld> > &hour_data,vector<ld> &general_data){
        for(int i = 0; i < hour_data.size(); i++){
            hour_data[i][2] = sqrt(hour_data[i][1]);
        }
        general_data[2] = sqrt(general_data[1]);
    }


    void max_traffic(vector<vector<ld> > &data, vector<pair<int,ld>> &max_traffic_td){
        ld max_data_1 = 0, max_data_2 = 0;
        int max_data_time_1;
        int max_data_time_2;
        for(int i = 0; i < data.size(); i++){
            if(max_data_1 < data[i][0]){
                max_data_2 = max_data_1;
                max_data_time_2 = max_data_time_1;
                max_data_1 = data[i][0];
                max_data_time_1 = i;
            }
            else{
                if(max_data_2 < data[i][0]){
                    max_data_2 = data[i][0];
                    max_data_time_2 = i;
                }
            }
            
        }
        max_traffic_td.push_back(make_pair(max_data_time_1,max_data_1));
        max_traffic_td.push_back(make_pair(max_data_time_2,max_data_2));
    }

    void Compute() {
        Avareage(hour_up, Hour_Ava_Var_StaDev_up, General_Ava_Var_StaDev_up);
        Avareage(hour_down, Hour_Ava_Var_StaDev_down, General_Ava_Var_StaDev_down);

        Variance(hour_up, Hour_Ava_Var_StaDev_up, General_Ava_Var_StaDev_up);
        Variance(hour_down, Hour_Ava_Var_StaDev_down, General_Ava_Var_StaDev_down);

        Standard_Deviation(Hour_Ava_Var_StaDev_up, General_Ava_Var_StaDev_up);
        Standard_Deviation(Hour_Ava_Var_StaDev_down, General_Ava_Var_StaDev_down);

        max_traffic(Hour_Ava_Var_StaDev_up, max_traffic_up);
        max_traffic(Hour_Ava_Var_StaDev_down, max_traffic_down);
    }

    void print_DataAnalysis_file_for_Graphics() {
        string outputFileName = "DataAnalysis_Graphics_" + inputFile;
        ofstream file(outputFileName);

        file << device_type << '\n';

        file << data_quant  << '\n';

        file << bins << '\n';
        //Hour upload
        for(int i = 0; i < hour_up.size();i++){
            for(auto val : hour_up[i]){
                file << val.first << " ";
            }
            file << '\n';
        }
        //Hour download
        for(int i = 0; i < hour_down.size();i++){
            for(auto val : hour_down[i]){
                file << val.first << " ";
            }
            file << '\n';
        }

        //Estatistic_hour upload
        for(int i = 0; i < Hour_Ava_Var_StaDev_up.size(); i++){
            file << Hour_Ava_Var_StaDev_up[i][0] << " " << Hour_Ava_Var_StaDev_up[i][1] << " " << Hour_Ava_Var_StaDev_up[i][2] << '\n';
        }

        //Estatistic_hour download
        for(int i = 0; i < Hour_Ava_Var_StaDev_down.size(); i++){
            file << Hour_Ava_Var_StaDev_down[i][0] << " " << Hour_Ava_Var_StaDev_down[i][1] << " " << Hour_Ava_Var_StaDev_down[i][2] << '\n';
        }

        //Max traffic
        for(auto i: max_traffic_up){
            file << i.first << " " << i.second << '\n'; 
        }
        file << 1 + log2(2) << '\n';

        for(auto i: max_traffic_down){
            file << i.first << " " << i.second << '\n'; 
        }
        file << 1 + log2(2);
    }

    void print_DataAnalysis_file() {
        string outputFileName = "DataAnalysis_" + inputFile;
        ofstream file(outputFileName);

        file << "Estatísticas Gerais:" << device_type <<  '\n';
        file << "Bytes upload" << '\n';
        file << "Média:" << General_Ava_Var_StaDev_up[0]<< '\n';
        file << "Variância:"<< General_Ava_Var_StaDev_up[1]<< '\n';
        file << "Desvio Padrão:"<< General_Ava_Var_StaDev_up[2]<< '\n';

        file << "Bytes Download" << '\n';
        file << "Média:" << General_Ava_Var_StaDev_down[0]<< '\n';
        file << "Variância:"<< General_Ava_Var_StaDev_down[1]<< '\n';
        file << "Desvio Padrão:"<< General_Ava_Var_StaDev_down[2]<< '\n';
    }
};


