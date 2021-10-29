# MNXB01-PROJECT
The project of the course MNXB01

///////////////////////////////////////////////////////

I highly suggest if anyone is still struggling for Root,
the following commands to load Root on Aurora may help

module load GCC/5.4.0-2.26

module load OpenMPI/1.10.3

module load ROOT/6.10.02-Python-2.7.12

and then if you 

root  or  root -l 

under the directory with rootlogon.C ( on github it is with the MY absolute path of include/, you should change it to you OWN path),
then all will run automatically, no need for Makefile anymore.

/////////////////////////////////////////////////////////


Use the makefile to compile the project.
Run the command "module load GCCcore/8.3.0" if you're compiling on aurora.
The standard compiler is too old.

The project will not compile on windows, only on aurora.
To compile on windows remove $(ROOT_LIB) in the makefile.

https://www.overleaf.com/4442485513qrkytxnthsqr
the link for an online latex editor to the project report





