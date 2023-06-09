import tkinter as tk
from tkinter import messagebox

# Define the fruit names and prices
fruits = {
    "Apple": 10,
    "Banana": 15,
    "Orange": 12,
    "Mango": 20,
    "Pineapple": 30,
    "Grapes": 25,
    "Papaya": 18,
    "Kiwi": 22,
    "Watermelon": 35,
    "Pear": 17,
    "Lemon": 8,
    "Cherry": 28,
    "Strawberry": 30,
    "Raspberry": 32,
    "Blueberry": 27,
    "Peach": 20,
    "Apricot": 16,
    "Plum": 14,
    "Grapefruit": 18,
    "Pomegranate": 40,
}

# Initialize the cart list
cart = []


def add_to_cart():
    # Get the selected fruit and quantity
    fruit = var_fruit.get()
    quantity = var_quantity.get()

    # Add the item to the cart list
    cart.append([fruit, int(quantity)])

    # Show a confirmation message
    messagebox.showinfo("Item Added", f"{quantity} {fruit}(s) added to cart.")


def calculate_total():
    # Calculate the total price of all items in the cart
    total_price = sum([fruits[item[0]] * item[1] for item in cart])

    # Get the money input from the user
    money = input_field.get()
    messagebox.showinfo("User Input", f"You entered: {money}")

    # Check if the amount is sufficient to pay for the items in the cart
    if int(money) < total_price:
        messagebox.showerror("Error", "Insufficient amount.")
    else:
        # Calculate the change
        change = int(money) - total_price

        # Show the customer information and the total price in a message box
        name = "MOIZ"
        customer = 2
        messagebox.showinfo("Customer Information", f"Name: {name}, Customer No: {customer}")
        messagebox.showinfo("Total Price", f"The total price of all items in the cart is {total_price} dollars.\n\nAmount paid: {money} dollars\nChange: {change} dollars.")

        # Show the total amount in a Label widget
        total_label.config(text=f"Total amount: {total_price} dollars")

def delete_from_cart():
    for i in range(len(cart)):
        if cart[i][0] == var_fruit.get():
            cart[i][1] -= 1
            messagebox.showinfo("Item Removed", f"Quantity updated {cart[i][1]}")
            break

def show_cart_summary():
    # Calculate the total price of all items in the cart
    total_price = sum([fruits[item[0]] * item[1] for item in cart])

    # Generate a summary message
    summary = "Cart Summary:\n\n"
    for item in cart:
        summary += f"{item[1]} x {item[0]} = {fruits[item[0]] * item[1]} dollars\n"
    summary += f"\nTotal Price: {total_price} dollars"
    # Show the summary in a message box
    messagebox.showinfo("Cart Summary", summary)
# Create a window object
window = tk.Tk()

# Set the window title
window.title("Fruit Price Calculator")

# Set the window size
window.geometry("400x300")

# Add a label for the fruit selection
label_fruit = tk.Label(window, text="Select a fruit:")
label_fruit.pack()

# Add a dropdown menu for the fruit selection
var_fruit = tk.StringVar(window)
var_fruit.set(list(fruits.keys())[0])
menu_fruit = tk.OptionMenu(window, var_fruit, *fruits.keys())
menu_fruit.pack()

# Add a label for the quantity selection
label_quantity = tk.Label(window, text="Select a quantity:")
label_quantity.pack()

# Add a dropdown menu for the quantity selection
var_quantity = tk.StringVar(window)
var_quantity.set("1")
menu_quantity = tk.OptionMenu(window, var_quantity, "1", "2", "3", "4", "5")
menu_quantity.pack()

# Add a button to add the item to the cart
button_add = tk.Button(window, text="Add to Cart", command=add_to_cart)
button_add.pack()

# Add a button to delete the selected item from the cart
button_delete = tk.Button(text="Delete Item", command=delete_from_cart)
button_delete.pack()

# Add a label for instructions
label = tk.Label(window, text="Enter your input:")
label.pack()

# Add an Entry widget to get user input
input_field = tk.Entry(window)
input_field.pack()

# Add a button to submit user input
submit_button = tk.Button(window, text="Submit", command=calculate_total)
submit_button.pack()

# Add a Label widget to display the total amount
total_label = tk.Label(window, text="")
total_label.pack()

window.mainloop()
