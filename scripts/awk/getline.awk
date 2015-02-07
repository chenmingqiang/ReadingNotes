BEGIN {
    "date" | getline
    close("date")
    print $0
}
