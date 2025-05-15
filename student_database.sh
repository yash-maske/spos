#!/bin/bash

DB="student_db.txt"

create_database() {
    if [ -f "$DB" ]; then
        echo "Database already exists."
    else
        touch "$DB"
        echo "Database created successfully."
    fi
}

view_database() {
    if [ -s "$DB" ]; then
        echo "RollNo | Name | Marks"
        echo "----------------------"
        cat "$DB"
    else
        echo "Database is empty or doesn't exist."
    fi
}

insert_record() {
    read -p "Enter Roll Number: " roll
    grep -q "^$roll|" "$DB" && echo "Record already exists." && return
    read -p "Enter Name: " name
    read -p "Enter Marks: " marks
    echo "$roll|$name|$marks" >> "$DB"
    echo "Record inserted."
}

delete_record() {
    read -p "Enter Roll Number to delete: " roll
    grep -q "^$roll|" "$DB" || { echo "Record not found."; return; }
    grep -v "^$roll|" "$DB" > temp && mv temp "$DB"
    echo "Record deleted."
}

modify_record() {
    read -p "Enter Roll Number to modify: " roll
    grep -q "^$roll|" "$DB" || { echo "Record not found."; return; }
    read -p "Enter New Name: " name
    read -p "Enter New Marks: " marks
    grep -v "^$roll|" "$DB" > temp
    echo "$roll|$name|$marks" >> temp
    mv temp "$DB"
    echo "Record modified."
}

student_result() {
    read -p "Enter Roll Number: " roll
    grep "^$roll|" "$DB" || echo "Record not found."
}

while true; do
    echo ""
    echo "Student Database Menu:"
    echo "a) Create database"
    echo "b) View database"
    echo "c) Insert a record"
    echo "d) Delete a record"
    echo "e) Modify a record"
    echo "f) Result of a particular student"
    echo "g) Exit"
    read -p "Enter your choice: " choice

    case $choice in
        a|A) create_database ;;
        b|B) view_database ;;
        c|C) insert_record ;;
        d|D) delete_record ;;
        e|E) modify_record ;;
        f|F) student_result ;;
        g|G) echo "Exiting..."; break ;;
        *) echo "Invalid choice. Please try again." ;;
    esac
done
