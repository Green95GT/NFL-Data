import csv

def main():
    f = open("nfl.csv", "r")
    nfl = list(csv.reader(f))
    patriots_wins = 0

    # Loop through the list of rows, each time "New England Patriots" is found
    # in the third column (index value of 2), increase `patriots_wins` by 1
    for row in nfl:
        if row[2] == "New England Patriots":
            patriots_wins += 1

if __name__ == '__main__':
    main()            
