import numpy as np
import os


os.system("make clean")
headers = [f for f in os.listdir("include/") if os.path.isfile(os.path.join("include/", f))]
sources = [f for f in os.listdir("src/") if os.path.isfile(os.path.join("src/", f))]
prog = [f for f in os.listdir("prog/") if os.path.isfile(os.path.join("prog/", f))]

lines_headers = 0
lines_sources = 0
lines_prog = 0
listClasses = np.array([],dtype="string");
print "\nHeaders: \n"
for h in headers:
    if (h.find('~') == -1 and h.find("swo") == -1 and h.find("swp") == -1):
        f = open("include/"+h, "r")
        i = 0
        for line in f:
            i += 1
            tmp = np.array(line.split(), dtype='string')
            a, = np.where(tmp == "class")
            if (len(a) > 0 and len(tmp) > a[0]+1):
                b, = np.where(listClasses == tmp[a[0]+1])
                if (len(b) == 0):
                    listClasses = np.hstack((listClasses, tmp[a[0]+1]))
        f.close()
        lines_headers += i
        print h,":",i,"lines."

print "\nSub total headers:",lines_headers,"lines.\n\n\nSources:\n"
for s in sources:
    if (s.find('~') == -1 and s.find("swo") == -1 and s.find("swp") == -1):
        f = open("src/"+s, "r")
        i = 0
        for line in f:
            i += 1
        f.close()
        lines_sources += i
        print s,":",i,"lines."
    
print "\nSub total sources:",lines_sources,"lines.\n\n\nProgs:\n"
for p in prog:
    if (p.find('~') == -1 and p.find("swo") == -1 and p.find("swp") == -1):
        f = open("prog/"+p, "r")
        i = 0
        for line in f:
            i += 1
        f.close()
        lines_prog += i
        print p,":",i,"lines."
    
print "\nSub total progs",lines_prog,"lines."
print "\nTotal: -",lines_headers+lines_sources+lines_prog,"lines."
print "\n       -",len(listClasses),"classes."
