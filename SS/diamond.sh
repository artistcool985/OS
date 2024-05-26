#!/bin/bash
read -p "Enter the number of rows for the diamond pattern: " n

for ((i=1; i<=n; i++)); do
    for ((j=i; j<n; j++)); do
        echo -n " "
    done
    for ((k=1; k<=(2*i-1); k++)); do
        echo -n "*"
    done
    echo
done

for ((i=n-1; i>=1; i--)); do
    for ((j=n; j>i; j--)); do
        echo -n " "
    done
    for ((k=1; k<=(2*i-1); k++)); do
        echo -n "*"
    done
    echo
done
