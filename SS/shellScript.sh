#!/bin/bash

name=$1
cake=0
coffee=0
iceCream=0
choice=0
price=( [pcake]=3 [pcoffee]=3 [piceCream]=3 )
echo "Welcome to the shop $name"
echo "We have a total of ${#price[@]} items"
echo "Price of cake: ${price[pcake]} Price of coffee: ${price[pcoffee]} Price of ice cream: ${price[piceCream]}"

calculateTotalAmount() {
    echo "You have bought $cake cakes, $coffee coffees, and $iceCream ice creams on $(date)"
    totalAmount=$((cake*price[pcake] + coffee*price[pcoffee] + iceCream*price[piceCream]))
    echo "Total amount to be paid: $totalAmount"
}

while [ $choice -ne 4 ]; do
    echo "Enter choice: 1. Buy cake 2. Buy Coffee 3. Buy Ice Cream 4. Exit"
    read choice
    case $choice in
        1)
            echo "How many cakes do you want to buy?"
            read tcakes
            cake=$((cake+tcakes))
            ;;
        2)
            echo "How many coffees do you want to buy?"
            read tcoffee
            coffee=$((coffee+tcoffee))
            ;;
        3) 
            echo "How many ice creams do you want to buy?"
            read ticeCream
            iceCream=$((iceCream+ticeCream))
            ;;
        4) 
            echo "Thank you for shopping with us, $name"
            calculateTotalAmount
            break
            ;;
        *)
            echo "Please try a valid choice"
            ;;
    esac    
done
