#config ------------------------------------------------------------------------
PROGGRAMS=	ola args argsenv somargs \
			getpid fork1 fork2 forks forks2 forksarg \
			program2 exec1 exec2 myshell \
			pipes1 pipes2 pipes3 \
			files1 files2a files2b files3 files3a \
			shm1a shm1b shm2a shm2b shm3a shm3b \
			signal1a signal1b kill pause signal3 signalfiles1 signalfiles3 signalshm1 signalshm1a \
			server1 client1 server2 client2 server3 \
			p14-1-1-pipes p14-1-1a-pipes p14-1-1a-shm p14-1-3a-shm \
			server-randomint client-randomint server-negpos client-negpos server-soma client-soma

MODULES=	sockets.o

CC=gcc
RM=rm
MSG=echo

#processes ---------------------------------------------------------------------
all: ${PROGGRAMS} ${MODULES}

ola: ola.c
	${CC} ola.c -o ola
	
args: args.c
	${CC} args.c -o args

argsenv: argsenv.c
	${CC} argsenv.c -o argsenv

somargs: somargs.c
	${CC} somargs.c -o somargs

getpid: getpid.c
	${CC} getpid.c -o getpid

fork1: fork1.c
	${CC} fork1.c -o fork1

fork2: fork2.c
	${CC} fork2.c -o fork2

forks: forks.c
	${CC} forks.c -o forks

forks1: forks1.c
	${CC} forks1.c -o forks1

forksarg: forksarg.c
	${CC} forksarg.c -o forksarg

program2: program2.c
	${CC} program2.c -o program2

exec1: exec1.c
	${CC} exec1.c -o exec1
	
exec2: exec2.c
	${CC} exec2.c -o exec2

myshell: myshell.c
	${CC} myshell.c -o myshell

#pipes -------------------------------------------------------------------------
pipes1: pipes1.c
	${CC} pipes1.c -o pipes1

pipes2: pipes2.c
	${CC} pipes2.c -o pipes2

pipes3: pipes3.c
	${CC} pipes3.c -o pipes3

#files -------------------------------------------------------------------------
files1: files1.c
	${CC} files1.c -o files1

files1a: files1a.c
	${CC} files1a.c -o files1a

files2b: files2b.c
	${CC} files2b.c -o files2b

files3: files3.c
	${CC} files3.c -o files3

files3a: files3a.c
	${CC} files3a.c -o files3a

#shared memory -----------------------------------------------------------------
shm1a: shm1a.c
	${CC} shm1a.c -o shm1a

shm1b: shm1b.c
	${CC} shm1b.c -o shm1b

shm2a: shm2a.c
	${CC} shm2a.c -o shm2a

shm2b: shm2b.c
	${CC} shm2b.c -o shm2b

shm3a: shm3a.c
	${CC} shm3a.c -o shm3a

shm3b: shm3b.c
	${CC} shm3b.c -o shm3b

#signals -----------------------------------------------------------------------
sigal1a: sigal1a.c
	${CC} sigal1a.c -o sigal1a

sigal1b: sigal1b.c
	${CC} sigal1b.c -o sigal1b

kill: kill.c
	${CC} kill.c -o kill

pause: pause.c
	${CC} pause.c -o pause

signal3: signal3.c
	${CC} signal3.c -o signal3

signalfiles1: signalfiles1.c
	${CC} signalfiles1.c -o signalfiles1

signalfiles3: signalfiles3.c
	${CC} signalfiles3.c -o signalfiles3


signalshm1: signalshm1.c
	${CC} signalshm1.c -o signalshm1

signalshm1a: signalshm1a.c
	${CC} signalshm1a.c -o signalshm1a


#sokets ------------------------------------------------------------------------
sockets.o: sockets.c sockets.h
	${CC} sockets.c -c -o sockets.o

server1: server1.c sockets.o
	${CC} server1.c sockets.o -o server1

client1: client1.c sockets.o
	${CC} client1.c sockets.o -o client1

server2: server2.c sockets.o
	${CC} server2.c sockets.o -o server2

client2: client2.c sockets.o
	${CC} client2.c sockets.o -o client2

server3: server3.c sockets.o
	${CC} server3.c sockets.o -o server3

server-randomint: server-randomint.c sockets.o
	${CC} server-randomint.c sockets.o -o server-randomint

client-randomint: client-randomint.c sockets.o
	${CC} client-randomint.c sockets.o -o client-randomint

server-negpos: server-negpos.c sockets.o
	${CC} server-negpos.c sockets.o -o server-negpos

client-negpos: client-negpos.c sockets.o
	${CC} client-negpos.c sockets.o -o client-negpos

server-soma: server-soma.c sockets.o
	${CC} server-soma.c sockets.o -o server-soma

client-soma: client-soma.c sockets.o
	${CC} client-soma.c sockets.o -o client-soma


#exercicios aula p14 -----------------------------------------------------------
p14-1-1-pipes: p14-1-1-pipes.c
	${CC} p14-1-1-pipes.c -o p14-1-1-pipes

p14-1-1a-pipes: p14-1-1a-pipes.c
	${CC} p14-1-1a-pipes.c -o p14-1-1a-pipes

p14-1-1a-shm: p14-1-1a-shm.c
	${CC} p14-1-1a-shm.c -o p14-1-1a-shm

p14-1-3a-shm: p14-1-3a-shm.c
	${CC} p14-1-3a-shm.c -o p14-1-3a-shm


#clean & rebuid ----------------------------------------------------------------
clean:
	@${MSG} removendo os programas e modulos
	@${RM} ${PROGGRAMS} ${MODULES}
	
rebluid: clean all
	@${MSG} programas refeitos