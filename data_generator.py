import string

def generate_data():
    uppercase_letters = list(string.ascii_uppercase)
    lowercase_letters = list(string.ascii_lowercase)
    numbers = list(string.digits)
    all_chars = uppercase_letters + lowercase_letters + numbers
    with open("data.txt", "w+") as f:
        for i in range(90000000):
            f.write(random.choice(all_chars))

generate_data()