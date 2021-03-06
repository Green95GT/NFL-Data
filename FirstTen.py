class Dataset:
    def __init__(self, data):
        self.header = data[0]
        self.data = data[1:]
    
    def __str__(self):
        data_string = self.data[:10]
        return str(data_string)
    
    def column(self, label):
        if label not in self.header:
            return None
        
        index = 0
        for idx, element in enumerate(self.header):
            if label == element:
                index = idx
        
        column = []
        for row in self.data:
            column.append(row[index])
        return column
    
    def count_unique(self, label):
        unique_results = set(self.column(label))
        count = len(unique_results)
        return count

import csv    
    
def main():
    f = open("nfl.csv", 'r')
    csvreader = csv.reader(f)
    nfl_data = list(csvreader)    

    nfl_dataset = Dataset(nfl_data)
    print(nfl_dataset)

if __name__ == '__main__':
    main()
