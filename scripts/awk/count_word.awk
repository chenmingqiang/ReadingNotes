#!/usr/bin/awk -f

BEGIN { 
    total = 0; 
    FS=" ";
}
{
    total += NF;
    print "line", FNR, " : ",NF, "words"
}
END {
    print "total : ", total
}
    

