BEGIN {
    SUBSEP="#"
    item[1,1]=10;
    item[1,2]=20;
    item[2,1]=30;
    item[2,2]=40;
    for (x in item) {
        print "item index", x, "=", item[x];
    }
}
