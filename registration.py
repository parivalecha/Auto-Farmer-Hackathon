def display_welcome_message():
    print("Welcome to the Auto Farmer App! Say bye bye to backbend with Auto Farmer, your farming friend")
    print("-------------------------------")

def create_account():
    print("\nLet's create your account.")
    name = input("Enter your name: ")
    email = input("Enter your email address: ")
    password = input("Choose a password: ")
    print("\nAccount created successfully!")
    print("You have registered with us.")

def main():
    display_welcome_message()
    create_account()

if __name__ == "__main__":
    main()