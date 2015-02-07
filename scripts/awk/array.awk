BEGIN {
    item[101]="HD Camcorder";
    item[102]="Refrigerator";
    item[103]="MP3 Player";
    item[104]="Tennis Racket";
    item[105]="Laser Printer";
    item[1001]="Tennis Ball";
    item[55]="Laptop";
    item["na"]="Not Available";
    print item["101"];
    print item[102];
    print item["103"];
    print item[104];
    print item["105"];
    print item[1001];
    print item[55];
    print item["na"];
    print item["nonexist"]
}
