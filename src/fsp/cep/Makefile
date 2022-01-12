#config ------------------------------------------------------------------------
PROGGRAMS=	ola args argsenv somargs \
			getpid fork1 fork2 forks \
			program2 exec1 exec2 myshell \
			pipes1 pipes2 pipes3 \
			files1 files2a files2b files3 files3a \
			shm1a shm1b shm2a shm2b \
			signal1a signal1b kill pause signal3 signalshm1
CC=gcc
RM=rm
MSG=echo

#processes ---------------------------------------------------------------------
all: ${PROGGRAMS}

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

files2a: files2a.c
	${CC} files2a.c -o files2a

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

signalshm1: signalshm1.c
	${CC} signalshm1.c -o signalshm1

#clean & rebuid ----------------------------------------------------------------
clean:
	@${MSG} removendo os programas
	@${RM} ${PROGGRAMS}
	
rebluid: clean all
	@${MSG} programas refeitos