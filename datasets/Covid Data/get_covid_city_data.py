import pandas as pd
from tqdm import tqdm 
import os 

def write_city_data(cityname):
    df = pd.read_excel('https://www.arcgis.com/sharing/rest/content/items/b5e7488e117749c19881cce45db13f7e/data',sheet_name = 'Veckodata Kommun_stadsdel')
    df['KnNamn'] = df['KnNamn'].str.replace('å','a').replace('ä','a').replace('ö','o').replace('Ä','A').replace('Å','A').replace('Ö','O')
    df = df.drop(columns=['Stadsdel','KnKod','Stadsdel','Kommun_stadsdel','tot_antal_fall_per10000inv','antal_fall_per10000_inv','tot_antal_fall'])
    df = df.loc[df['KnNamn'] == cityname]
    df.drop(columns = ['KnNamn'])
    df.to_csv('Covid_{}.csv'.format(cityname),index=False)

#filenames = os.listdir()
#citynames = [f[:-4].split('_')[-1] for f in filenames if f.endswith('.csv')]
citynames = ['Falun', 'Umea', 'Lulea', 'Falsterbo', 'Lund', 'Boras', 'Visby', 'Karlstad', 'Soderarm']
#print(citynames)
for cityname in tqdm(citynames):
    write_city_data(cityname)
print('Done')
input()