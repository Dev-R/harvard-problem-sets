from cs50 import get_int
from cs50 import get_string
'''
Height: 4
   #  #
  ##  ##
 ###  ###
####  ####
1-prompt the user with get_int for the half-pyramid’s height, a positive integer between 1 and 8
'''


def main():
    # get height
    height = get_input()
    # building block vertically
    for height_y in range(1, height + 1):
        # add space
        for space in range(height - height_y):
            add_space()
        # building block horizintally
        for width_x in range(1, (height_y * 2) + 1):
            add_blocks(width_x, height_y)
        add_new_line()
        
        
def get_input():
    # verify input is >! and input < 8
    while True:
        height = get_height()
        if not(height < 1 or height > 8):
            break
    return height


def get_height():
    return get_int("Height:")


def add_space():
    print(" ", end="")
    
    
def add_blocks(width, height):
    print("#",  end='')
    if(width == height):
        print("  ", end='')
        
        
def add_new_line():
    print("")
    
    
if __name__ == "__main__":
    main()
