import matplotlib.pyplot as plt
import seaborn as sns
import numpy as np

def histogram(data,b,type,device):
    plt.hist(data, bins=b, edgecolor='black', color='skyblue')
    plt.title('Histograma no(a) ' + device + ' - Estatísticas gerais')
    plt.xlabel('Intervalos - ' + type)
    plt.ylabel('Quantidade')
    plt.show()

def Box_plot_General(data1,type1,data2,type2,data3,type3,data4,type4):
    data = [data1, data2, data3,data4]

    plt.figure(figsize=(8, 6))
    sns.boxplot(data=data)

    plt.title("Box Plots - Estatística gerais")
    plt.xticks([0, 1, 2, 3], [type1, type2, type3,type4])

    plt.show()

def Empirical_Distribution_Function(data,type,device):
    data = np.sort(data)

    edf = np.arange(1, len(data) + 1) / len(data)

    plt.figure(figsize=(8, 6))
    plt.step(data, edf, where='post', label="Função Empírica de Distribuição")
    plt.xlabel("Valor")
    plt.ylabel("EDF")
    plt.title("Função Empírica de Distribuição de " + type + " no(a) " + device + ' - Estatística gerais')
    plt.grid(True)
    plt.legend()
    plt.show()

def Box_plot_Hour(matriz,type,device):
    plt.figure(figsize=(8, 6))
    sns.boxplot(data=matriz)
    plt.title("Box Plots de " + type + " no(a) " + device + ' - Estatística por horário')
    plt.xticks([0, 1, 2, 3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23], ['00h','01h', '02h', '03h', '04h', '05h', '06h', '07h', '08h', '09h', '10h', '11h', '12h', '13h', '14h', '15h', '16h', '17h', '18h', '19h', '20h', '21h', '22h', '23h' ])
    plt.show()

def Graphic_Est(matriz,type,device):
    matriz = np.array(matriz)

    avareage = matriz[:, 0]
    variance = matriz[:, 1]
    sta_dev = matriz[:, 2]

    plt.figure(figsize=(10, 6))
    plt.plot(range(24), avareage, label='Média', marker='o')
    plt.plot(range(24), variance, label='Variância', marker='x')
    plt.plot(range(24), sta_dev, label='Desvio Padrão', marker='s')
    plt.title('Média, Variância e Desvio Padrão de ' + type + ' no(a) ' + device + ' - Estatística por horário')
    plt.xlabel('Hora')
    plt.ylabel('Valor')
    plt.legend()
    plt.grid(True)
    plt.show()

arq_1 = "DataAnalysis_Graphics_Smart-tv.csv"
arq_2 = "DataAnalysis_Graphics_Chromecast.csv"
up_list_1 = []
down_list_1 = []
up_list_2 = []
down_list_2 = []

hour_up_list_1 = []
hour_down_list_1 = []
hour_up_list_2 = []
hour_down_list_2 = []

hour_est_up_1 = []
hour_est_down_1 = []
hour_est_up_2 = []
hour_est_down_2 = []

max_traffic_dataup_1 = []
max_traffic_dataup_2 = []
max_traffic_datadown_1 = []
max_traffic_datadown_2 = []
max_traffic_down_1 = []
max_traffic_down_2 = []
max_traffic_up_1 = []
max_traffic_up_2 = []

with open(arq_1, 'r') as file:
    device_type_1 = (file.readline().strip())
    data_quant_1 = int(file.readline().strip())
    bins_arq_1 = int(file.readline().strip())

    for i in range(24):
        up_list = list(map(float, file.readline().split()))
        up_list_1 += up_list
        hour_up_list_1.append(up_list[:])  

    for i in range(24):
        down_list = list(map(float, file.readline().split()))
        down_list_1 += down_list
        hour_down_list_1.append(down_list[:]) 

    for i in range(24):
        hour_list = list(map(float, file.readline().split()))
        hour_est_up_1.append(hour_list[:])  

    for i in range(24):
        hour_list = list(map(float, file.readline().split()))
        hour_est_down_1.append(hour_list[:]) 

    max_traffic_up_1.append(list(map(float, file.readline().split())))
    max_traffic_up_1.append(list(map(float, file.readline().split())))
    max_traffic_bin_1 = int(file.readline().strip())

    max_traffic_dataup_1.append(max_traffic_up_1[0][1])
    max_traffic_dataup_1.append(max_traffic_up_1[1][1])

    max_traffic_down_1.append(list(map(float, file.readline().split())))
    max_traffic_down_1.append(list(map(float, file.readline().split())))
    max_traffic_bin_1 = int(file.readline().strip())

    max_traffic_datadown_1.append(max_traffic_down_1[0][1])
    max_traffic_datadown_1.append(max_traffic_down_1[1][1])



with open(arq_2, 'r') as file:
    device_type_2 = (file.readline().strip())
    data_quant_2 = int(file.readline().strip())
    bins_arq_2 = int(file.readline().strip())


    for i in range(24):
        up_list = list(map(float, file.readline().split()))
        up_list_2 += up_list
        hour_up_list_2.append(up_list[:])  

    for i in range(24):
        down_list = list(map(float, file.readline().split()))
        down_list_2 += down_list
        hour_down_list_2.append(down_list[:])  

    for i in range(24):
        hour_list = list(map(float, file.readline().split()))
        hour_est_up_2.append(hour_list[:]) 

    for i in range(24):
        hour_list = list(map(float, file.readline().split()))
        hour_est_down_2.append(hour_list[:])

    max_traffic_up_2.append(list(map(float, file.readline().split())))
    max_traffic_up_2.append(list(map(float, file.readline().split())))
    max_traffic_bin_2 = int(file.readline().strip())

    max_traffic_dataup_2.append(max_traffic_up_2[0][1])
    max_traffic_dataup_2.append(max_traffic_up_2[1][1])

    max_traffic_down_2.append(list(map(float, file.readline().split())))
    max_traffic_down_2.append(list(map(float, file.readline().split())))
    max_traffic_bin_2 = int(file.readline().strip())

    max_traffic_datadown_2.append(max_traffic_down_2[0][1])
    max_traffic_datadown_2.append(max_traffic_down_2[1][1])

#General Statistics
histogram(up_list_1,bins_arq_1,'Bytes Up',device_type_1[:len(device_type_1)-4])
histogram(down_list_1,bins_arq_1,'Bytes down',device_type_1[:len(device_type_1)-4])

histogram(up_list_2,bins_arq_2,'Bytes Up',device_type_2[:len(device_type_2)-4])
histogram(down_list_2,bins_arq_2,'Bytes down',device_type_2[:len(device_type_2)-4])

Empirical_Distribution_Function(up_list_1, 'Upload',device_type_1[:len(device_type_1)-4] )
Empirical_Distribution_Function(down_list_1, 'Download',device_type_1[:len(device_type_1)-4])

Empirical_Distribution_Function(up_list_2, 'Upload',device_type_2[:len(device_type_2)-4])
Empirical_Distribution_Function(down_list_2, 'Download',device_type_2[:len(device_type_2)-4])

Box_plot_General(up_list_1, device_type_1[:len(device_type_1)-4]+'-UP', up_list_2, device_type_2[:len(device_type_2)-4]+'-UP', down_list_1, device_type_1[:len(device_type_1)-4]+'-down', down_list_2, device_type_2[:len(device_type_2)-4]+'-down')

#Hour Statistics
Box_plot_Hour(hour_up_list_1,'Upload',device_type_1[:len(device_type_1)-4])
Box_plot_Hour(hour_down_list_1, 'Download',device_type_1[:len(device_type_1)-4])
Box_plot_Hour(hour_up_list_2,'Upload',device_type_2[:len(device_type_2)-4])
Box_plot_Hour(hour_down_list_2,'Download',device_type_2[:len(device_type_2)-4])

Graphic_Est(hour_est_up_1,'Upload',device_type_1[:len(device_type_1)-4] )
Graphic_Est(hour_est_down_1, 'Download',device_type_1[:len(device_type_1)-4])
Graphic_Est(hour_est_up_2, 'Upload',device_type_2[:len(device_type_2)-4])
Graphic_Est(hour_est_down_2, 'Download',device_type_2[:len(device_type_2)-4])

#Max traffic
histogram(max_traffic_dataup_1,max_traffic_bin_1,'Bytes Up',device_type_1[:len(device_type_1)-4])
histogram(max_traffic_datadown_1,max_traffic_bin_1,'Bytes Down',device_type_1[:len(device_type_1)-4])
histogram(max_traffic_dataup_2,max_traffic_bin_2,'Bytes Up',device_type_2[:len(device_type_2)-4])
histogram(max_traffic_datadown_2,max_traffic_bin_2,'Bytes Down',device_type_2[:len(device_type_2)-4])