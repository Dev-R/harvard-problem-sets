def main():
    name = get_name()
    print_name(name)
    
    
def get_name():
    name = input("What is your name?")
    return name
    
    
def print_name(name):
    print(f"hello,{name}")


if __name__ == "__main__":
    main()
    