#!/usr/bin/python3
import os, sys
os.system("sudo apt-get -y install libgtk2.0-dev build-essential g++-multilib")

os.system("wget -N -q bochs.sourceforge.net/getcurrent.html")

with open("getcurrent.html", "r") as f:
	data = f.read()

indexer = """<b>Current Release:</b><BR><a href="http://bochs.sourceforge.net/getcurrent.html
" class="sidebar"><i><u>"""

i = data.index(indexer) + len(indexer)
#Bochs X.X.X

if (data[i: i+6] == "Bochs "): 
	i += 6

	k = i
	while data[k] != "<": k+=1
	verBochs = data[i:k]
	print("Bochs Version:", verBochs)
	
else: raise Exception("Unable to determine Bochs Version.  ")


os.system("wget -N sourceforge.net/projects/bochs/files/bochs/%s/bochs-%s.tar.gz -O bochs-%s.tar.gz"%(verBochs, verBochs, verBochs))

os.system("tar -zxvf bochs-%s.tar.gz"%verBochs)


with open("build_bochs", "w") as f:
	f.write("cd bochs-%s\n"%verBochs)
	f.write(r"""./configure LDFLAGS='-pthread' --enable-smp \
		      --enable-cpu-level=6 \
		      --enable-all-optimizations \
		      --enable-x86-64 \
		      --enable-pci \
			  --enable-plugins \
		      --enable-vmx \
		      --enable-debugger \
		      --enable-disasm \
		      --enable-debugger-gui \
		      --enable-logging \
		      --enable-fpu \
		      --enable-3dnow \
		      --enable-sb16=dummy \
		      --enable-cdrom \
		      --enable-x86-debugger \
		      --enable-iodebug \
		      --disable-plugins \
		      --disable-docbook \
              #--enable-gdb-stub \
		      --with-x --with-x11""")

	f.write("\nmake\n")
	if "install" in sys.argv: f.write("sudo cp -f -v ./bochs /usr/bin/bochsdbg\n")
	else: f.write("cp -f -v ./bochs ../bochsdbg\n")
os.system("bash build_bochs")
