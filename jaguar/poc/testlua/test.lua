function a()
    print "1\n"
    ret = my_function("\ntexto desde lua")
    n = "2"
    print("\n3:", ret)
    ret2 = my_function(n);
    print("\n4:", ret2)
end

a();

