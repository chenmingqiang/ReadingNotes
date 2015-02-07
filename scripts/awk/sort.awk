BEGIN {
    item["apple"] = 5
    item["orange"] = 3
    item["banana"] = 8
    item["grape"] = 10

    for (x in item) {
        print "the price of", x, "is", item[x]
    }

    asort(item);

    for (x in item) {
        print "the price of", x, "is", item[x]
    }
}
