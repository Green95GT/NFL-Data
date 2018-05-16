def nfl_wins(team):
    count = 0
    for row in nfl:
        if row[2] == team:
            count = count + 1
    return count

import csv

def main():
    f = open("nfl.csv", 'r')
    nfl = list(csv.reader(f))

    cowboys_wins = nfl_wins("Dallas Cowboys")
    falcons_wins = nfl_wins("Atlanta Falcons")

if __name__ == '__main__':
    main()
