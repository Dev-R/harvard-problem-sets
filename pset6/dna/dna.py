import csv
import sys
import random


def main():
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py data.csv sequence.txt")
    # Extract the STR sequence from the database header
    STR_headers = get_STR()
    # Read database into memory from file
    database = read_database()
    # Read DNA sequence data into memory from file
    dna_data = read_dna_data()
    # Analyse DNA sequence for a certain STR and  get the STR count
    STR = analyze_DNA(dna_data, STR_headers)
    # Check for the name with the higest STR match
    name = match_STR(database, STR, STR_headers)
    # Print the owner name of the DNA Sequence
    print(name)

    
# Extract the STR sequence from the database header
def get_STR():
    STR = []
    with open(sys.argv[1]) as f:
        firstline = f.readline()
        lst = firstline.rstrip("\n").split(",")
        lst.remove(lst[0])
    return lst
    
    
# Extract data from the database file and return it as a rows of dict
def read_database():
    f = open(sys.argv[1], 'r')
    data = csv.DictReader(f)
    return data
   
    
# Extract dna sequence from the database file and return it as a rows of dict
def read_dna_data():
    f = open(f"{sys.argv[2]}", "r")
    data = f.read()
    return data


# check whether a certain STR exist and return num.occurance
def analyze_DNA(DNA_sequence, STR_lst):
    dict = {}
    dict['name'] = 0
    for STR in STR_lst:
        STR_num = check_STR(STR, DNA_sequence)
        dict[STR] = STR_num
    return dict


def check_STR(STR, DNA):
    "check whether a certain STR exist and return num.occurance"
    # both STR, DNA are strings
    # substr_max = s_max , substr_min = s_min
    s_max, s_min, previous_index = len(STR), 0, 0
    current_freq = 0  # store no of consecutive occurance of STR 
    highest_freq = 0  # store highest no of consecutive occurance of STR 
    for i in range(len(DNA)):
        current_index = i
        if DNA[i:s_max + i] == STR:
            # check the distance difference between the two STR first char
            if (current_index - previous_index) == s_max:
                current_freq += 1
                if current_freq > highest_freq:
                    highest_freq = current_freq
            else:
                current_freq = 0
            previous_index = i
    # correct STR no.occurance
    if highest_freq >= 1:
        highest_freq += 1
    return highest_freq 


# Match STR to the owner in the database
def match_STR(database, STR, STR_headers):
    dict = STR
    name_match = {}
    for row in database:
        for key in row:
            if str(dict[key]) == str(row[key]):
                if row['name'] not in name_match:
                    name_match.setdefault(row['name'], []).append(key)
                else:
                    name_match[row['name']].append(key)
    return match_owner(name_match, STR_headers)


# Match STR sequence to owner
def match_owner(name_match, STR_headers):
    dict = name_match
    for key in name_match:
        if len(dict[key]) == len(STR_headers):
            return(key)
    return('No match')
    

if __name__ == "__main__":
    
    main()
    